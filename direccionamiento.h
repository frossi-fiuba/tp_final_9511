#ifndef DIRECCIONAMIENTO_H
#define DIRECCIONAMIENTO_H

#include "micro.h"


typedef void(*f_direccionamiento_t)(mos6502_t *, instruccion_t *);

void implicito (mos6502_t * p_mos, instruccion_t * p_inst);
void acumulador (mos6502_t * p_mos, instruccion_t * p_inst);
void inmediata (mos6502_t * p_mos, instruccion_t * p_inst);
void absoluta (mos6502_t * p_mos, instruccion_t * p_inst);


#endif