#ifndef OPERACIONES_H
#define OPERACIONES_H

#include "micro.h"

typedef void(*f_operaciones_t)(mos6502_t *);

void ADC (mos6502_t *p_mos);
void AND (mos6502_t *p_mos);
void ASL (mos6502_t *p_mos);
void BCC (mos6502_t *p_mos);
void BCS (mos6502_t *p_mos);
void BEQ (mos6502_t *p_mos);
void BIT (mos6502_t *p_mos);
void BMI (mos6502_t *p_mos);
void BNE (mos6502_t *p_mos);
void BPL (mos6502_t *p_mos);
void BRK (mos6502_t *p_mos);
void BVC (mos6502_t *p_mos);
void BVS (mos6502_t *p_mos);
void CLC (mos6502_t *p_mos);
void CLD (mos6502_t *p_mos);
void CLI (mos6502_t *p_mos);
void CLV (mos6502_t *p_mos);
void CMP (mos6502_t *p_mos);
void CPX (mos6502_t *p_mos);
void CPY (mos6502_t *p_mos);
void DEC (mos6502_t *p_mos);
void DEX (mos6502_t *p_mos);
void DEY (mos6502_t *p_mos);
void EOR (mos6502_t *p_mos);
void INC (mos6502_t *p_mos);
void INX (mos6502_t *p_mos);
void INY (mos6502_t *p_mos);
void JMP (mos6502_t *p_mos);
void JSR (mos6502_t *p_mos);
void LDA (mos6502_t *p_mos);
void LDX (mos6502_t *p_mos);
void LDY (mos6502_t *p_mos);
void LSR (mos6502_t *p_mos);
void NOP (mos6502_t *p_mos);
void ORA (mos6502_t *p_mos);
void PHA (mos6502_t *p_mos);
void PHP (mos6502_t *p_mos);
void PLA (mos6502_t *p_mos);
void PLP (mos6502_t *p_mos);
void ROL (mos6502_t *p_mos);
void ROR (mos6502_t *p_mos);
void RTI (mos6502_t *p_mos);
void RTS (mos6502_t *p_mos);
void SBC (mos6502_t *p_mos);
void SEC (mos6502_t *p_mos);
void SED (mos6502_t *p_mos);
void SEI (mos6502_t *p_mos);
void STA (mos6502_t *p_mos);
void STX (mos6502_t *p_mos);
void STY (mos6502_t *p_mos);
void TAX (mos6502_t *p_mos);
void TAY (mos6502_t *p_mos);
void TSX (mos6502_t *p_mos);
void TXA (mos6502_t *p_mos);
void TXS (mos6502_t *p_mos);
void TYA (mos6502_t *p_mos);

#endif
