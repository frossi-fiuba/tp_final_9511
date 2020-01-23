#include "micro.h"
#include "direccionamiento.h"

#include <stdint.h>
#include <stdio.h>

static void absoluta_all (mos6502_t *p_mos, instruccion_t *p_inst, uint8_t add);
static void pagina_cero_all (mos6502_t *p_mos, instruccion_t *p_inst, uint8_t add);

void implicito (mos6502_t *p_mos, instruccion_t *p_inst){

	p_inst->m = NULL;
}

void acumulador (mos6502_t *p_mos, instruccion_t *p_inst){

	p_inst->m = &(p_mos->a);

}

void inmediata (mos6502_t *p_mos, instruccion_t *p_inst){
	
	p_inst->m = &((p_mos->mem)[(p_mos->pc++)]);
}

void absoluta (mos6502_t * p_mos, instruccion_t *p_inst){
	absoluta_all(p_mos, p_inst, 0);
}

void relativa (mos6502_t *p_mos, instruccion_t *p_inst){

	p_inst->m = &((p_mos->mem)[p_mos->pc++]);
}

void pagina_cero (mos6502_t *p_mos, instruccion_t *p_inst){
	pagina_cero_all(p_mos, p_inst, 0);
}

void indirecta (mos6502_t *p_mos, instruccion_t *p_inst){

	uint8_t primer_byte  = (p_mos->mem)[p_mos->pc++]; 
	uint16_t redir = ((p_mos->mem)[p_mos->pc++] << 8) | primer_byte; 

	p_inst->direccion = (((p_mos->mem)[redir + 1]) << 8) | (p_mos->mem)[redir];
	p_inst->m = &(p_mos->mem[p_inst->direccion]);
}

void absoluta_x (mos6502_t *p_mos, instruccion_t *p_inst){

	absoluta_all (p_mos, p_inst, p_mos->x);
}

void absoluta_y (mos6502_t *p_mos, instruccion_t *p_inst){

	absoluta_all(p_mos, p_inst, p_mos->y); 
}

void pagina_cero_x (mos6502_t *p_mos, instruccion_t *p_inst){

	pagina_cero_all(p_mos, p_inst, p_mos->x);
}

void pagina_cero_y (mos6502_t *p_mos, instruccion_t *p_inst){

	pagina_cero_all(p_mos, p_inst, p_mos->y);
}

void index_indirecta_x (mos6502_t *p_mos, instruccion_t *p_inst){

	uint8_t redir = (p_mos->mem[p_mos->pc++] + p_mos->x);
	
	p_inst->direccion = p_mos->mem[redir] | (p_mos->mem[redir + 1] << 8);
	p_inst->m = &(p_mos->mem[p_inst->direccion]);
}

void indirecta_index_y (mos6502_t *p_mos, instruccion_t *p_inst){

	uint8_t redir = p_mos->mem[p_mos->pc++];

	p_inst->direccion = (p_mos->mem[redir] | (p_mos->mem[redir + 1] << 8)) + p_mos->y;
	p_inst->m = &(p_mos->mem[p_inst->direccion]);

}


void absoluta_all (mos6502_t *p_mos, instruccion_t *p_inst, uint8_t add){

	uint8_t primer_byte  = (p_mos->mem)[p_mos->pc++]; 
	
	p_inst->direccion = (((p_mos->mem)[p_mos->pc++] << 8) | primer_byte) + add;
	p_inst->m = &((p_mos->mem)[p_inst->direccion]);
}

void pagina_cero_all (mos6502_t *p_mos, instruccion_t *p_inst, uint8_t add){
	
	uint8_t aux = p_mos->mem[p_mos->pc++] + add;

	p_inst->direccion =  0x00FF & aux; 	
	p_inst->m = &(p_mos->mem[p_inst->direccion]);
}




