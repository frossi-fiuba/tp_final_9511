#ifndef DIRECCIONAMIENTO_H
#define DIRECCIONAMIENTO_H

#include "micro.h"

typedef void(*f_direccionamiento_t)(mos6502_t *, instruccion_t *);

// No indexados, no en memoria
void implicito (mos6502_t *p_mos, instruccion_t *p_inst);
void acumulador (mos6502_t *p_mos, instruccion_t *p_inst);
void inmediata (mos6502_t *p_mos, instruccion_t *p_inst);
// No indexados, en memoria
void relativa (mos6502_t *p_mos, instruccion_t *p_inst);
void absoluta (mos6502_t *p_mos, instruccion_t *p_inst);
void pagina_cero (mos6502_t *p_mos, instruccion_t *p_inst);
void indirecta (mos6502_t *p_mos, instruccion_t *p_inst);
// Indexados
void absoluta_x (mos6502_t *p_mos, instruccion_t *p_inst);
void absoluta_y (mos6502_t *p_mos, instruccion_t *p_inst);
void pagina_cero_x (mos6502_t *p_mos, instruccion_t *p_inst);
void pagina_cero_y (mos6502_t *p_mos, instruccion_t *p_inst);
void index_indirecta_x (mos6502_t *p_mos, instruccion_t *p_inst);
void indirecta_index_y (mos6502_t *p_mos, instruccion_t *p_inst);

#endif
