#ifndef OPERACIONES_H
#define OPERACIONES_H

#include "micro.h"

#define PAGE_1 0x0100

typedef void(*f_operaciones_t)(mos6502_t *, instruccion_t *);

void ADC (mos6502_t *, instruccion_t *);
void AND (mos6502_t *, instruccion_t *);
void ASL (mos6502_t *, instruccion_t *);
void BCC (mos6502_t *, instruccion_t *);
void BCS (mos6502_t *, instruccion_t *);
void BEQ (mos6502_t *, instruccion_t *);
void BIT (mos6502_t *, instruccion_t *);
void BMI (mos6502_t *, instruccion_t *);
void BNE (mos6502_t *, instruccion_t *);
void BPL (mos6502_t *, instruccion_t *);
void BRK (mos6502_t *, instruccion_t *);
void BVC (mos6502_t *, instruccion_t *);
void BVS (mos6502_t *, instruccion_t *);
void CLC (mos6502_t *, instruccion_t *);
void CLD (mos6502_t *, instruccion_t *);
void CLI (mos6502_t *, instruccion_t *);
void CLV (mos6502_t *, instruccion_t *);
void CMP (mos6502_t *, instruccion_t *);
void CPX (mos6502_t *, instruccion_t *);
void CPY (mos6502_t *, instruccion_t *);
void DEC (mos6502_t *, instruccion_t *);
void DEX (mos6502_t *, instruccion_t *);
void DEY (mos6502_t *, instruccion_t *);
void EOR (mos6502_t *, instruccion_t *);
void INC (mos6502_t *, instruccion_t *);
void INX (mos6502_t *, instruccion_t *);
void INY (mos6502_t *, instruccion_t *);
void JMP (mos6502_t *, instruccion_t *);
void JSR (mos6502_t *, instruccion_t *);
void LDA (mos6502_t *, instruccion_t *);
void LDX (mos6502_t *, instruccion_t *);
void LDY (mos6502_t *, instruccion_t *);
void LSR (mos6502_t *, instruccion_t *);
void NOP (mos6502_t *, instruccion_t *);
void ORA (mos6502_t *, instruccion_t *);
void PHA (mos6502_t *, instruccion_t *);
void PHP (mos6502_t *, instruccion_t *);
void PLA (mos6502_t *, instruccion_t *);
void PLP (mos6502_t *, instruccion_t *);
void ROL (mos6502_t *, instruccion_t *);
void ROR (mos6502_t *, instruccion_t *);
void RTI (mos6502_t *, instruccion_t *);
void RTS (mos6502_t *, instruccion_t *);
void SBC (mos6502_t *, instruccion_t *);
void SEC (mos6502_t *, instruccion_t *);
void SED (mos6502_t *, instruccion_t *);
void SEI (mos6502_t *, instruccion_t *);
void STA (mos6502_t *, instruccion_t *);
void STX (mos6502_t *, instruccion_t *);
void STY (mos6502_t *, instruccion_t *);
void TAX (mos6502_t *, instruccion_t *);
void TAY (mos6502_t *, instruccion_t *);
void TSX (mos6502_t *, instruccion_t *);
void TXA (mos6502_t *, instruccion_t *);
void TXS (mos6502_t *, instruccion_t *);
void TYA (mos6502_t *, instruccion_t *);

#endif
