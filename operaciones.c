#include "operaciones.h"
#include "micro.h"
#include "status.h"

#include <stdint.h>


static void DE (mos6502_t *p_mos, instruccion_t *p_inst, uint8_t * registro);
static void LD (mos6502_t * p_mos, instruccion_t * p_inst, uint8_t * registro);

void ADC(mos6502_t * p_mos, instruccion_t * p_inst){

	uint16_t aux = 0;

	aux = (p_mos->a) + ( ( (p_mos->status) & CARRY) + * (p_inst->m) ) ;

	set_carry (&(p_mos->status), aux);
	set_zero (&(p_mos->status), aux);
	set_negative (&(p_mos->status), aux);

	(p_mos->a) = aux;
}

void AND (mos6502_t * p_mos, instruccion_t * p_inst){

	
	(p_mos->a) &=  * (p_inst->m);

	set_zero (&(p_mos->status), p_mos->a);
	set_negative (&(p_mos->status), p_mos->a);

}

void ASL(mos6502_t * p_mos, instruccion_t * p_inst){

	
	set_status (&(p_mos -> status), CARRY, MASK_MSB & *(p_inst->m));

	(* (p_inst->m)) <<= 1; 
	
	set_zero (&(p_mos -> status), * (p_inst->m));
	set_negative (&(p_mos -> status), * (p_inst->m));
}

void CLC(mos6502_t * p_mos, instruccion_t * p_inst){

	set_status(&(p_mos -> status), CARRY, 0);
}

void CMP(mos6502_t * p_mos, instruccion_t * p_inst){

	set_status(&(p_mos->status), CARRY, *(p_inst->m) <= p_mos->a);
	set_status(&(p_mos->status), ZERO, *(p_inst->m) == p_mos->a);
	set_status(&(p_mos->status), NEGATIVE, *(p_inst->m) > p_mos->a);
}

void DE (mos6502_t *p_mos, instruccion_t *p_inst, uint8_t * registro){

	*registro -= 1;
	
	set_zero (&(p_mos->status), *registro);
	set_negative (&(p_mos->status), *registro);
}

void DEC (mos6502_t *p_mos, instruccion_t *p_inst){
	DE (p_mos, p_inst, p_inst->m);
}

void DEX (mos6502_t *p_mos, instruccion_t *p_inst){
	DE (p_mos, p_inst, &(p_mos->x));
}

void DEY (mos6502_t *p_mos, instruccion_t *p_inst){
	DE (p_mos, p_inst, &(p_mos->y));
}

void EOR (mos6502_t * p_mos, instruccion_t * p_inst){

	p_mos->a ^= * (p_inst->m);

	set_zero (&(p_mos->status), p_mos->a);
	set_negative (&(p_mos->status), p_mos->a);
}

void JMP (mos6502_t * p_mos, instruccion_t * p_inst){
	(p_mos->pc) = p_inst->direccion;
}


void LD (mos6502_t * p_mos, instruccion_t * p_inst, uint8_t * registro){

	*registro = *(p_inst->m);

	set_zero (&(p_mos->status), *registro);
	set_negative (&(p_mos->status), *registro);
}

void LDA (mos6502_t * p_mos, instruccion_t * p_inst){
	LD (p_mos, p_inst, &(p_mos->a));
}


void LDX (mos6502_t * p_mos, instruccion_t * p_inst){
	LD (p_mos, p_inst, &(p_mos->x));
}


void LDY (mos6502_t * p_mos, instruccion_t * p_inst){
	LD (p_mos, p_inst, &(p_mos->y));
}

void NOP (mos6502_t * p_mos, instruccion_t * p_inst){ 
}

void SEC (mos6502_t * p_mos, instruccion_t * p_inst){ 
	set_status (&(p_mos->status), CARRY, 1);
}

void STA(mos6502_t * p_mos, instruccion_t * p_inst){
	*(p_inst->m) = p_mos->a;
}

void STX(mos6502_t * p_mos, instruccion_t * p_inst){
	*(p_inst->m) = p_mos->x;
}

void STY(mos6502_t * p_mos, instruccion_t * p_inst){
	*(p_inst->m) = p_mos->y;
}
