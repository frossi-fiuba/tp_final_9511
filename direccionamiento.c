#include "micro.h"
#include "direccionamiento.h"

#include <stdint.h>
#include <stdio.h>

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

static void absoluta_all (mos6502_t *p_mos, uint8_t add);
static void pagina_cero_all (mos6502_t *p_mos, uint8_t add);

void implicito (mos6502_t * p_mos){

	p_mos->inst->m = NULL;
}

void acumulador (mos6502_t * p_mos){

	(p_mos->inst->m) = &(p_mos->a);

}

void inmediata (mos6502_t * p_mos){
	
	(p_mos->inst->m) = &((p_mos->mem)[p_mos->pc++]);
}

void absoluta (mos6502_t * p_mos){
	absoluta_all(p_mos, 0);
}

void relativa (mos6502_t *p_mos){

	(p_mos->inst->m) = &((p_mos->mem)[p_mos->pc++]);
}

void pagina_cero (mos6502_t *p_mos){
	pagina_cero_all(p_mos, 0);
}

void indirecta (mos6502_t *p_mos){

	uint8_t primer_byte  = (p_mos->mem)[p_mos->pc];  //primer byte de la direccion a buscar el dato
	p_mos->pc++;
	uint16_t redir = ((p_mos->mem)[p_mos->pc] << 8) | primer_byte; // se obtuvo el valor de la direccion de memoria en la cual se contiene los valores a donde saltar.
	p_mos->pc++;
	p_mos->inst->direccion = (((p_mos->mem)[redir + 1]) << 8) | (p_mos->mem)[redir];
	p_mos->inst->m = &(p_mos->mem[p_mos->inst->direccion]);
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

	uint16_t redir = (p_mos->mem[p_mos->pc] + p_mos->x);// & 0x011;
	p_mos->pc++;
	p_mos->inst->direccion = p_mos->mem[redir] | (p_mos->mem[redir + 1] << 8);
	p_mos->inst->m = &(p_mos->mem[p_mos->inst->direccion]);
	/*
	uint16_t redir = 0;
	uint8_t aux =(p_mos->mem)[(p_mos->pc++)] + p_mos->x;
	redir |= aux; //0x0000 | 0xAA = 0x00AA quizas simplemente igualarlo funcione

	uint8_t primer_byte_aux = (p_mos->mem)[(redir)]; // primer byte
	uint8_t segundo_byte_aux = (p_mos->mem)[(p_mos->pc) + 1]; //se gundo byte

	uint16_t redir_aux = (segundo_byte_aux << 8) | primer_byte_aux;

	(p_mos->inst->m) = &((p_mos->mem)[redir_aux]); */
}

void indirecta_index_y (mos6502_t *p_mos){

	uint16_t redir = (p_mos->mem[p_mos->pc] + p_mos->y) & 0x011;
	p_mos->pc++;
	p_mos->inst->direccion = (p_mos->mem[redir] | (p_mos->mem[redir + 1] << 8));
	p_mos->inst->m = &(p_mos->mem[p_mos->inst->direccion]);
	/*
	uint8_t aux = (p_mos->mem)[p_mos->pc];

	uint8_t primer_byte = (p_mos->mem)[(aux)]; // primer byte
	uint8_t segundo_byte = (p_mos->mem)[(aux) + 1]; //segundo byte

	uint16_t redir = ((segundo_byte << 8) | primer_byte) + p_mos->y;

	p_mos->inst->m = &((p_mos->mem)[redir]);

	p_mos-> pc++; */

}


void absoluta_all (mos6502_t *p_mos, uint8_t add){
	//(p_mos->inst->direccion) = el numero contenido por la direccion de memoria expicitada en los 2 bytes siguientes a la instruccion
	
	uint8_t primer_byte  = (p_mos->mem)[p_mos->pc]; 
	p_mos->pc++;
	(p_mos->inst->direccion) = (((p_mos->mem)[p_mos->pc++] << 8) | primer_byte) + add;
	(p_mos->inst->m) = &((p_mos->mem)[p_mos->inst->direccion]);
	
	//(p_mos -> pc) += 2;
}

void pagina_cero_all (mos6502_t *p_mos, uint8_t add){
	
	p_mos->inst->direccion = 0x00FF & (p_mos->mem[p_mos->pc] + add); // p_mos->inst->direccion = (p_mos->mem[p_mos->pc++] & add);
	p_mos->pc++;
	p_mos->inst->m = &(p_mos->mem[p_mos->inst->direccion]);
	/*
	p_mos->inst->direccion = 0 | (p_mos->mem[p_mos->pc++] + add); // p_mos->inst->direccion = (p_mos->mem[p_mos->pc++] & add);
	p_mos->inst->m = &(p_mos->mem[p_mos->inst->direccion]);
	/ *
	uint16_t redir = 0;
	uint8_t aux =(p_mos->mem)[(p_mos->pc)] + add; 
	redir |= aux; //0x0000 | 0xAA = 0x00AA quizas simplemente igualarlo funcione

	(p_mos->inst->direccion) = redir; // al final esta no creo ver DEC y CMP
	(p_mos->inst->m) = &((p_mos->mem)[redir]); // cual de las dos? 

	p_mos-> pc++; */
}




