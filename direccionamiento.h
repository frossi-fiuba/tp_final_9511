#ifndef DIRECCIONAMIENTO_H
#define DIRECCIONAMIENTO_H

#include "micro.h"

typedef void(*f_direccionamiento_t)(mos6502_t *);

// no indexados, no en memoria
void implicito (mos6502_t *p_mos);
void acumulador (mos6502_t *p_mos);
void inmediata (mos6502_t *p_mos);
// no indexados, en memoria
void relativa (mos6502_t *p_mos);
void absoluta (mos6502_t *p_mos);
void pagina_cero (mos6502_t *p_mos);
void indirecta (mos6502_t *p_mos);
// indexadas
void absoluta_x (mos6502_t *p_mos);
void absoluta_y (mos6502_t *p_mos);
void pagina_cero_x (mos6502_t *p_mos);
void pagina_cero_y (mos6502_t *p_mos);
void index_indirecta_x (mos6502_t *p_mos);
void indirecta_index_y (mos6502_t *p_mos);

#endif
