#include "micro.h"
#include "direccionamiento.h"
#include "status.h"

#include <stdint.h>

typedef struct {
    uint8_t codigo;     // Opcode.
    short ciclos;       // Cantidad de ciclos de la instrucción.
    uint8_t *m;         // Puntero al operando (registro o memoria).
    uint16_t direccion; // Dirección del operando (si corresponde).
} instruccion_t;

struct mos6502 {
    uint8_t a, x, y;    // Registros A, X e Y.
    uint16_t pc;        // Program counter.
    uint8_t status;     // Registro de status.
    uint8_t sp;         // Stack pointer.
    uint8_t *mem;       // Memoria.

    instruccion_t * inst; // puntero a la estructura de instruccion (actual)

    long ciclos;        // Cantidad de ciclos totales de ejecución.
};

void absoluta_all (mos6502_t *p_mos, uint8_t add){
	//(p_mos->inst->direccion) = el numero contenido por la direccion de memoria expicitada en los 2 bytes siguientes a la instruccion
	uint8_t primer_byte  = (p_mos->mem)[(p_mos->pc)];  //primer byte
	uint8_t segundo_byte = (p_mos->mem)[(p_mos->pc) + 1]; //segundo byte

	uint16_t redir = ((segundo_byte << 8) | primer_byte) + add; // que pasa si hay carry? deberia hacer en 32 bits y check?

	(p_mos->inst->direccion) = redir;
	(p_mos->inst->m) = &((p_mos->mem)[redir]);
	
	(p_mos -> pc) += 2;
}

void pagina_cero_all (mos6502_t *p_mos, uint8_t add){

	uint16_t redir = 0;
	uint8_t aux =(p_mos->mem)[(p_mos->pc)] + add;
	redir |= aux; //0x0000 | 0xAA = 0x00AA quizas simplemente igualarlo funcione

	(p_mos->inst->direccion) = redir; // al final esta no creo ver DEC y CMP
	(p_mos->inst->m) = &((p_mos->mem)[redir]); // cual de las dos? 

	(p_mos-> pc) += 1;
}

void implicito (mos6502_t * p_mos){
}

void acumulador (mos6502_t * p_mos){

	(p_mos->inst->m) = &(p_mos->a);

}
void inmediata (mos6502_t * p_mos){

	(p_mos->inst->m) = &((p_mos->mem)[p_mos->pc]);

	(p_mos -> pc) += 1;
}
void absoluta (mos6502_t * p_mos){
	absoluta_all(p_mos, 0);
}

void relativa (mos6502_t *p_mos){

	(p_mos->inst->m) = &((p_mos->mem)[p_mos->pc]); 
	if(!get_status(p_mos->inst->m, NEGATIVE)){
		(p_mos -> pc) += *(p_mos->inst->m);
	}
	else{
		uint8_t *op = p_mos->inst->m; 
		set_status(op, NEGATIVE, false);
		(p_mos -> pc) -= *op; 
	}
}

void pagina_cero (mos6502_t *p_mos){
	pagina_cero_all(p_mos, 0);
}

void indirecta (mos6502_t *p_mos){

	uint8_t primer_byte  = (p_mos->mem)[(p_mos->pc)];  //primer byte de la direecion a buscar el dato
	uint8_t segundo_byte = (p_mos->mem)[(p_mos->pc) + 1]; //segundo byte de la direccion a buscar el dato

	uint16_t redir = (segundo_byte << 8) | primer_byte; // se obtuvo el valor de la direccion de memoria en la cual se contiene los valores a donde saltar.

	uint8_t primer_byte_aux = (p_mos->mem)[(redir)]; // primer byte
	uint8_t segundo_byte_aux = (p_mos->mem)[(p_mos->pc) + 1]; //segundo byte

	uint16_t redir_aux = (segundo_byte_aux << 8) | primer_byte_aux; // este valor es el valor al cual el JMP va

	(p_mos->inst->direccion) = redir_aux;
	
	(p_mos -> pc) += 2;
}

void absoluta_x (mos6502_t *p_mos){
	absoluta_all (p_mos, p_mos->x);
}

void absoluta_y (mos6502_t *p_mos){
	absoluta_all(p_mos, p_mos->y); 
}

void pagina_cero_x (mos6502_t *p_mos){
	pagina_cero_all(p_mos, p_mos->x);
}

void pagina_cero_y (mos6502_t *p_mos){
	pagina_cero_all(p_mos, p_mos->y);
}

void index_indirecta_x (mos6502_t *p_mos){

	uint16_t redir = 0;
	uint8_t aux =(p_mos->mem)[(p_mos->pc)] + p_mos->x;
	redir |= aux; //0x0000 | 0xAA = 0x00AA quizas simplemente igualarlo funcione

	uint8_t primer_byte_aux = (p_mos->mem)[(redir)]; // primer byte
	uint8_t segundo_byte_aux = (p_mos->mem)[(p_mos->pc) + 1]; //se gundo byte

	uint16_t redir_aux = (segundo_byte_aux << 8) | primer_byte_aux;

	(p_mos->inst->m) = &((p_mos->mem)[redir_aux]); 

	(p_mos-> pc) += 1;

}

void indirecta_index_y (mos6502_t *p_mos){

	uint8_t aux = (p_mos->mem)[p_mos->pc];

	uint8_t primer_byte = (p_mos->mem)[(aux)]; // primer byte
	uint8_t segundo_byte = (p_mos->mem)[(aux) + 1]; //segundo byte

	uint16_t redir = ((segundo_byte << 8) | primer_byte) + p_mos->y;

	p_mos->inst->m = &((p_mos->mem)[redir]);

	(p_mos-> pc) += 1;

}


