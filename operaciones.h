#ifndef OPERACIONES_H
#define OPERACIONES_H

#include "micro.h"

typedef void(*f_operaciones_t)(mos6502_t *, instruccion_t *);

void ADC(mos6502_t * p_mos, instruccion_t * p_inst);
void AND (mos6502_t * p_mos, instruccion_t * p_inst);
void ASL(mos6502_t * p_mos, instruccion_t * p_inst);
void CLC(mos6502_t * p_mos, instruccion_t * p_inst);
void CMP(mos6502_t * p_mos, instruccion_t * p_inst);
void DEC (mos6502_t *p_mos, instruccion_t *p_inst);
void DEX (mos6502_t *p_mos, instruccion_t *p_inst);
void DEY (mos6502_t *p_mos, instruccion_t *p_inst);
void EOR (mos6502_t * p_mos, instruccion_t * p_inst);
void JMP (mos6502_t * p_mos, instruccion_t * p_inst);
void LDA (mos6502_t * p_mos, instruccion_t * p_inst);
void LDX (mos6502_t * p_mos, instruccion_t * p_inst);
void LDY (mos6502_t * p_mos, instruccion_t * p_inst);
void NOP (mos6502_t * p_mos, instruccion_t * p_inst);
void SEC (mos6502_t * p_mos, instruccion_t * p_inst);
void STA(mos6502_t * p_mos, instruccion_t * p_inst);
void STX(mos6502_t * p_mos, instruccion_t * p_inst);
void STY(mos6502_t * p_mos, instruccion_t * p_inst);

#endif
