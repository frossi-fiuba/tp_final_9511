#include "operaciones.h"
#include "micro.h"
#include "status.h"

#include <stdint.h>

static void DE (mos6502_t *p_mos, uint8_t *registro);
static void LD (mos6502_t *p_mos, instruccion_t *p_inst, uint8_t *registro);
static void CP (mos6502_t *p_mos, instruccion_t *p_inst, uint8_t registro);
static void INC_all (mos6502_t *p_mos, uint8_t * registro);
static void TRANSFER(mos6502_t *p_mos, uint8_t from, uint8_t *to);

void ADC(mos6502_t *p_mos, instruccion_t *p_inst){

	uint16_t res = p_mos->a + *(p_inst->m) + get_status(&(p_mos->status), CARRY);

 	set_overflow(&(p_mos->status), *(p_inst->m), p_mos->a, res);
 	set_carry(&(p_mos->status), res);
    set_negative(&(p_mos->status), res);
    set_zero(&(p_mos->status), res);

	p_mos->a = res;
}

void AND(mos6502_t *p_mos, instruccion_t *p_inst){

	(p_mos->a) &=  *(p_inst->m);

	set_zero(&(p_mos->status), p_mos->a);
	set_negative(&(p_mos->status), p_mos->a);

}

void ASL(mos6502_t *p_mos, instruccion_t *p_inst){

	set_status (&(p_mos->status), CARRY, MASK_MSB & *(p_inst->m));

	(*(p_inst->m)) <<= 1; 
	
	set_zero (&(p_mos->status), *(p_inst->m));
	set_negative(&(p_mos -> status), *(p_inst->m));
}

void BCC(mos6502_t *p_mos, instruccion_t *p_inst){

	if (!get_status(&(p_mos->status), CARRY))
		p_mos->pc += (int8_t) (*(p_inst->m));
}

void BCS(mos6502_t *p_mos, instruccion_t *p_inst){

	if (get_status(&(p_mos->status), CARRY))
		p_mos->pc += (int8_t) (*(p_inst->m));
}


void BEQ(mos6502_t *p_mos, instruccion_t *p_inst){

	if (get_status(&(p_mos->status), ZERO))
		p_mos->pc += (int8_t) (*(p_inst->m));
}

void BIT(mos6502_t *p_mos, instruccion_t *p_inst){

	set_zero(&(p_mos->status), p_mos->a & *(p_inst->m));
	set_status(&(p_mos->status), OVERFLOW, OVERFLOW & *(p_inst->m));
	set_status(&(p_mos->status), NEGATIVE, NEGATIVE & *(p_inst->m));
}

void BMI(mos6502_t *p_mos, instruccion_t *p_inst){

	if (get_status(&(p_mos->status), NEGATIVE))
		p_mos->pc += (int8_t) (*(p_inst->m));
}

void BNE(mos6502_t *p_mos, instruccion_t *p_inst){

	if (!get_status(&(p_mos->status), ZERO))
		p_mos->pc += (int8_t) (*(p_inst->m));
}

void BPL(mos6502_t *p_mos, instruccion_t *p_inst){

	if (!get_status(&(p_mos->status), NEGATIVE))
		p_mos->pc += (int8_t) (*(p_inst->m));
}

void BRK(mos6502_t *p_mos, instruccion_t *p_inst){

	uint16_t aux = p_mos->pc + 1;
	p_mos->mem[PAGE_1|p_mos->sp] = (aux & 0xFF00) >> 8;
	p_mos->sp--;
	p_mos->mem[PAGE_1|p_mos->sp] = aux & 0x00FF;
	p_mos->sp--;
	p_mos->mem[PAGE_1|p_mos->sp] = p_mos->status | 0x30; // 0x30 setea los bits 4 y 5.
	p_mos->sp--;
	p_mos->pc = (p_mos->mem[0xFFFF] << 8) | p_mos->mem[0xFFFE];
	set_status(&(p_mos->status), INTERRUPT_DISABLE, 1);	
}

void BVC(mos6502_t *p_mos, instruccion_t *p_inst){

	if (!get_status(&(p_mos->status), OVERFLOW))
		p_mos->pc += (int8_t) (*(p_inst->m));
}

void BVS(mos6502_t *p_mos, instruccion_t *p_inst){

	if (get_status(&(p_mos->status), OVERFLOW))
		p_mos->pc += (int8_t) (*(p_inst->m));
}

void CLC(mos6502_t *p_mos, instruccion_t *p_inst){

	set_status(&(p_mos->status), CARRY, 0);
}

void CLD(mos6502_t *p_mos, instruccion_t *p_inst){

	set_status(&(p_mos->status), DECIMAL, 0);
}

void CLI(mos6502_t *p_mos, instruccion_t *p_inst){

	set_status(&(p_mos->status), INTERRUPT_DISABLE, 0);
}

void CLV(mos6502_t *p_mos, instruccion_t *p_inst){

	set_status(&(p_mos->status), OVERFLOW, 0);
}

void CP(mos6502_t *p_mos, instruccion_t *p_inst, uint8_t registro){

	set_status(&(p_mos->status), CARRY, registro >= *(p_inst->m));
	set_status(&(p_mos->status), ZERO, *(p_inst->m) == registro);
	set_status(&(p_mos->status), NEGATIVE, *(p_inst->m) > registro);
}

void CMP(mos6502_t *p_mos, instruccion_t *p_inst){

	CP(p_mos, p_inst, p_mos->a);
}

void CPX(mos6502_t *p_mos, instruccion_t *p_inst){

	CP(p_mos, p_inst, p_mos->x);
}

void CPY(mos6502_t *p_mos, instruccion_t *p_inst){

	CP(p_mos, p_inst, p_mos->y);
}

void DE(mos6502_t *p_mos, uint8_t *registro){

	(*registro)--;
	
	set_zero (&(p_mos->status), *registro);
	set_negative (&(p_mos->status), *registro);
}

void DEC(mos6502_t *p_mos, instruccion_t *p_inst){

	DE(p_mos, p_inst->m);
}

void DEX(mos6502_t *p_mos, instruccion_t *p_inst){

	DE(p_mos, &(p_mos->x));
}

void DEY(mos6502_t *p_mos, instruccion_t *p_inst){

	DE(p_mos, &(p_mos->y));
}

void EOR(mos6502_t *p_mos, instruccion_t *p_inst){

	p_mos->a ^= * (p_inst->m);

	set_zero(&(p_mos->status), p_mos->a);
	set_negative(&(p_mos->status), p_mos->a);
}

void INC_all(mos6502_t *p_mos, uint8_t * registro){

	(*registro)++;

	set_zero(&(p_mos->status), *registro);
	set_negative(&(p_mos->status), *registro);
}

void INC(mos6502_t *p_mos, instruccion_t *p_inst){

	INC_all(p_mos, p_inst->m);
}

void INX(mos6502_t *p_mos, instruccion_t *p_inst){

	INC_all(p_mos, &(p_mos->x));
}

void INY(mos6502_t *p_mos, instruccion_t *p_inst){

	INC_all(p_mos, &(p_mos->y));
}

void JMP(mos6502_t *p_mos, instruccion_t *p_inst){

	p_mos->pc = p_inst->direccion;
}

void JSR(mos6502_t *p_mos, instruccion_t *p_inst){

	p_mos->mem[PAGE_1|p_mos->sp] = (p_mos->pc - 1) >> 8;
	p_mos->sp--;
	p_mos->mem[PAGE_1|p_mos->sp] = p_mos->pc - 1;
	p_mos->sp--;
	p_mos->pc = p_inst->direccion;
}

void LD(mos6502_t *p_mos, instruccion_t *p_inst, uint8_t *registro){

	*registro = *(p_inst->m);

	set_zero(&(p_mos->status), *registro);
	set_negative(&(p_mos->status), *registro);
}

void LDA(mos6502_t *p_mos, instruccion_t *p_inst){

	LD(p_mos, p_inst,&(p_mos->a));
}


void LDX(mos6502_t *p_mos, instruccion_t *p_inst){

	LD(p_mos, p_inst,&(p_mos->x));
}


void LDY(mos6502_t *p_mos, instruccion_t *p_inst){

	LD(p_mos, p_inst,&(p_mos->y));
}

void LSR(mos6502_t *p_mos, instruccion_t *p_inst){

	set_status(&(p_mos->status), CARRY, *(p_inst->m) & MASK_LSB);
	*(p_inst->m) >>= 1;

	set_zero (&(p_mos->status), *(p_inst->m));
	set_negative (&(p_mos->status), *(p_inst->m));
}

void NOP(mos6502_t *p_mos, instruccion_t *p_inst){ 
}

void ORA(mos6502_t *p_mos, instruccion_t *p_inst){

	p_mos->a |= *(p_inst->m);

	set_zero (&(p_mos->status), p_mos->a);
	set_negative (&(p_mos->status), p_mos->a);
}

void PHA(mos6502_t *p_mos, instruccion_t *p_inst){
	
	p_mos->mem[PAGE_1 | p_mos->sp--] = p_mos->a;
}

void PHP(mos6502_t *p_mos, instruccion_t *p_inst){
	
	p_mos->mem[PAGE_1 | p_mos->sp--] = p_mos->status | 0x30; // &0x30 setea los bits 4 y 5.

}

void PLA(mos6502_t *p_mos, instruccion_t *p_inst){

	p_mos->sp++;
	p_mos->a = p_mos->mem[PAGE_1 | p_mos->sp];

	set_zero (&(p_mos->status), p_mos->a);
	set_negative (&(p_mos->status), p_mos->a);
}

void PLP(mos6502_t *p_mos, instruccion_t *p_inst){
	
	p_mos->sp++;
	p_mos->status = (p_mos->mem[PAGE_1 | p_mos->sp] & 0xCF); // &0xCF ignora el estado de los bits 4 y 5. 
}

void ROL(mos6502_t *p_mos, instruccion_t *p_inst){

	rotate_left(&(p_mos->status), p_inst->m);

	set_zero (&(p_mos->status), *(p_inst->m));
	set_negative (&(p_mos->status), *(p_inst->m));
}

void ROR(mos6502_t *p_mos, instruccion_t *p_inst){

	rotate_right(&(p_mos->status),p_inst->m);

	set_zero (&(p_mos->status), *(p_inst->m));
	set_negative (&(p_mos->status), *(p_inst->m));
}

void RTI(mos6502_t *p_mos, instruccion_t *p_inst){

	PLP(p_mos, p_inst);

	p_mos->sp++;
	uint8_t primer_byte  = (p_mos->mem)[PAGE_1 | p_mos->sp++]; 
	
	p_mos->pc = (((p_mos->mem)[PAGE_1 | p_mos->sp] << 8) | primer_byte);
	
}

void RTS(mos6502_t *p_mos, instruccion_t *p_inst){

	p_mos->sp++;
	uint8_t primer_byte  = (p_mos->mem)[PAGE_1 | p_mos->sp++]; 
	
	p_mos->pc = (((p_mos->mem)[PAGE_1 | p_mos->sp] << 8) | primer_byte) + 1;
}

void SBC(mos6502_t *p_mos, instruccion_t *p_inst){

	uint16_t aux = *(p_inst->m) + !get_status(&(p_mos->status), CARRY);
	uint16_t res = p_mos->a - aux;
	uint8_t aux_V1 = 0;
	uint8_t aux_V2 = 0;

	set_overflow(&aux_V1, *(p_inst->m), get_status(&(p_mos->status), CARRY), aux);
	set_overflow(&aux_V2, p_mos->a, ~aux, res);
	set_status(&(p_mos->status), OVERFLOW, aux_V1 ^ aux_V2);
	set_carry(&(p_mos->status), ~res);
    set_negative(&(p_mos->status), res);
    set_zero(&(p_mos->status), res);
	
	p_mos->a = res;
}

void SEC(mos6502_t *p_mos, instruccion_t *p_inst){ 

	set_status (&(p_mos->status), CARRY, 1);
}

void SED(mos6502_t *p_mos, instruccion_t *p_inst){

	set_status (&(p_mos->status), DECIMAL, 1);
}

void SEI(mos6502_t *p_mos, instruccion_t *p_inst){

	set_status (&(p_mos->status), INTERRUPT_DISABLE, 1);
}

void STA(mos6502_t *p_mos, instruccion_t *p_inst){

	*(p_inst->m) = p_mos->a;
}

void STX(mos6502_t *p_mos, instruccion_t *p_inst){

	*(p_inst->m) = p_mos->x;
}

void STY(mos6502_t *p_mos, instruccion_t *p_inst){

	*(p_inst->m) = p_mos->y;
}

void TRANSFER(mos6502_t *p_mos, uint8_t from, uint8_t *to){

	*to = from;

	set_zero (&(p_mos->status), *to);
	set_negative (&(p_mos->status), *to);
}

void TAX(mos6502_t *p_mos, instruccion_t *p_inst){

	TRANSFER(p_mos, p_mos->a, &(p_mos->x));
}

void TAY(mos6502_t *p_mos, instruccion_t *p_inst){

	TRANSFER(p_mos, p_mos->a, &(p_mos->y));
}

void TSX(mos6502_t *p_mos, instruccion_t *p_inst){
	
	TRANSFER(p_mos, p_mos->sp, &(p_mos->x));
}

void TXA(mos6502_t *p_mos, instruccion_t *p_inst){

	TRANSFER(p_mos, p_mos->x, &(p_mos->a));
}

void TXS(mos6502_t *p_mos, instruccion_t *p_inst){

	p_mos->sp = p_mos->x;
}

void TYA(mos6502_t *p_mos, instruccion_t *p_inst){

	TRANSFER(p_mos, p_mos->y, &(p_mos->a));
}
