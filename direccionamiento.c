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
    char *log;  // locacion absoluta del archivo log donde grabar

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
	
	(p_mos->inst->m) = &((p_mos->mem)[(p_mos->pc++)]);
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

	uint8_t primer_byte  = (p_mos->mem)[p_mos->pc++]; 
	uint16_t redir = ((p_mos->mem)[p_mos->pc++] << 8) | primer_byte; 

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

	uint8_t redir = (p_mos->mem[p_mos->pc++] + p_mos->x);
	
	p_mos->inst->direccion = p_mos->mem[redir] | (p_mos->mem[redir + 1] << 8);
	p_mos->inst->m = &(p_mos->mem[p_mos->inst->direccion]);
}

void indirecta_index_y (mos6502_t *p_mos){

	uint8_t redir = p_mos->mem[p_mos->pc++];

	p_mos->inst->direccion = (p_mos->mem[redir] | (p_mos->mem[redir + 1] << 8)) + p_mos->y;
	p_mos->inst->m = &(p_mos->mem[p_mos->inst->direccion]);

}


void absoluta_all (mos6502_t *p_mos, uint8_t add){

	uint8_t primer_byte  = (p_mos->mem)[p_mos->pc++]; 
	
	(p_mos->inst->direccion) = (((p_mos->mem)[p_mos->pc++] << 8) | primer_byte) + add;
	(p_mos->inst->m) = &((p_mos->mem)[p_mos->inst->direccion]);
}

void pagina_cero_all (mos6502_t *p_mos, uint8_t add){
	
	uint8_t aux = p_mos->mem[p_mos->pc++] + add;

	p_mos->inst->direccion =  0x00FF & aux; 	
	p_mos->inst->m = &(p_mos->mem[p_mos->inst->direccion]);
}




