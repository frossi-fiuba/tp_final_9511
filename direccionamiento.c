#include "micro.h"
#include "direccionamiento.h"

#include <stdint.h>

void implicito (mos6502_t * p_mos, instruccion_t * p_inst){
}

void acumulador (mos6502_t * p_mos, instruccion_t * p_inst){

	(p_inst->m) = &(p_mos->a);

}
void inmediata (mos6502_t * p_mos, instruccion_t * p_inst){

	(p_inst->m) = &((p_mos->mem)[p_mos->pc]);

	(p_mos -> pc) += 1;
}
void absoluta (mos6502_t * p_mos, instruccion_t * p_inst){

	
	//(p_inst->direccion) = el numero contenido por la direccion de memoria expicitada en los 2 bytes siguientes a la instruccion
	uint8_t primer_byte  = (p_mos->mem)[(p_mos-> pc)];  //primer bytee
	uint8_t segundo_byte = (p_mos->mem)[(p_mos->pc) + 1]; //segundo bytee

	uint16_t redir = (segundo_byte << 8) | primer_byte;


	(p_inst->direccion) = redir;
	(p_inst->m) = &((p_mos->mem)[redir]);
	
	(p_mos -> pc) += 2;
}


