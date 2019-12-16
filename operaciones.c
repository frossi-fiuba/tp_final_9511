#include "operaciones.h"
#include "micro.h"
#include "status.h"

#include <stdint.h>


typedef struct {
    uint8_t codigo;     // Opcode.
    short ciclos;       // Cantidad de ciclos de la instrucción.
    uint8_t *m;         // Puntero al operando (registro o memoria).
    uint16_t direccion; // Dirección del operando (si corresponde).
} instruccion_t;

struct mos6502 {
    uint8_t a, x, y;    // Registros A, X e Y.
    uint16_t pc;        // Program counter.
    uint8_t status;     // Registro de status.
    uint8_t sp;         // Stack pointer.
    uint8_t *mem;       // Memoria.

    instruccion_t * inst; // puntero a la estructura de instruccion (actual)

    char *log;  // locacion absoluta del archivo log donde grabar
    long ciclos;        // Cantidad de ciclos totales de ejecución.
};

static void DE (mos6502_t *p_mos, uint8_t *registro);
static void LD (mos6502_t *p_mos, uint8_t *registro);
static void CP (mos6502_t *p_mos, uint8_t registro);
static void INC_all (mos6502_t * p_mos, uint8_t * registro);
static void TRANSFER(mos6502_t *p_mos, uint8_t from, uint8_t *to);

void ADC(mos6502_t *p_mos){
	
	uint16_t aux = p_mos->a + *(p_mos->inst->m) + get_status(&(p_mos->status), CARRY);


    set_carry(&(p_mos->status), aux);
    set_negative(&(p_mos->status), aux);
    set_zero(&(p_mos->status), aux);
	set_overflow(&(p_mos->status), *(p_mos->inst->m), p_mos->a, aux);
	p_mos->a = aux;


	/*
	uint16_t aux = *(p_mos->inst->m) + get_status(&(p_mos->status), CARRY);
	uint16_t res = p_mos->a + aux;

    set_carry(&(p_mos->status), res);
    set_negative(&(p_mos->status), res);
    set_zero(&(p_mos->status), res);
	set_overflow(&(p_mos->status), *(p_mos->inst->m), get_status(&(p_mos->status), CARRY), aux);
	if(!get_status(&(p_mos->status),OVERFLOW)){
		set_overflow(&(p_mos->status), p_mos->a, aux, res);
	}
	p_mos->a = res;
	*/

	/*
	uint16_t aux = (p_mos->a)  + get_status(&(p_mos->status),CARRY);
	set_overflow(&(p_mos->status), (p_mos->a), get_status((&p_mos->status),CARRY), aux);
	uint16_t aux2 = aux + *(p_mos->inst->m);
	set_overflow(&(p_mos->status), aux, *(p_mos->inst->m), aux2); 

	p_mos->a = aux2;

	set_carry (&(p_mos->status), p_mos->a);
	set_zero (&(p_mos->status), p_mos->a);
	set_negative (&(p_mos->status), p_mos->a); */
}

void AND(mos6502_t *p_mos){

	(p_mos->a) &=  *(p_mos->inst->m);

	set_zero(&(p_mos->status), p_mos->a);
	set_negative(&(p_mos->status), p_mos->a);

}

void ASL(mos6502_t *p_mos){

	set_status (&(p_mos->status), CARRY, MASK_MSB & *(p_mos->inst->m));

	(*(p_mos->inst->m)) <<= 1; 
	
	set_zero (&(p_mos->status), *(p_mos->inst->m));
	set_negative(&(p_mos -> status), *(p_mos->inst->m));
}

void BCC(mos6502_t *p_mos){

	if (!get_status(&(p_mos->status), CARRY))
		p_mos->pc += (int8_t) (*(p_mos->inst->m));
}

void BCS(mos6502_t *p_mos){

	if (get_status(&(p_mos->status), CARRY))
		p_mos->pc += (int8_t) (*(p_mos->inst->m));
}


void BEQ(mos6502_t *p_mos){

	if (get_status(&(p_mos->status), ZERO))
		p_mos->pc += (int8_t) (*(p_mos->inst->m));
}

void BIT(mos6502_t *p_mos){

	set_zero(&(p_mos->status), p_mos->a & *(p_mos->inst->m));
	set_status(&(p_mos->status), OVERFLOW, OVERFLOW & *(p_mos->inst->m));
	set_status(&(p_mos->status), NEGATIVE, NEGATIVE & *(p_mos->inst->m));
}

void BMI(mos6502_t *p_mos){

	if (get_status(&(p_mos->status), NEGATIVE))
		p_mos->pc += (int8_t) (*(p_mos->inst->m));
}

void BNE(mos6502_t *p_mos){

	if (!get_status(&(p_mos->status), ZERO))
		p_mos->pc += (int8_t) (*(p_mos->inst->m));
}

void BPL(mos6502_t *p_mos){

	if (!get_status(&(p_mos->status), NEGATIVE))
		p_mos->pc += (int8_t) (*(p_mos->inst->m));
}

void BRK(mos6502_t *p_mos){

	uint16_t aux = p_mos->pc + 1;
	p_mos->mem[0x100|p_mos->sp] = (aux & 0xFF00) >> 8;
	p_mos->sp--;
	p_mos->mem[0x100|p_mos->sp] = aux & 0x00FF;
	p_mos->sp--;
	p_mos->mem[0x100|p_mos->sp] = p_mos->status | (1<<4) | (1<<5);
	p_mos->sp--;
	p_mos->pc = (p_mos->mem[0xFFFF] << 8) | p_mos->mem[0xFFFE];
	set_status(&(p_mos->status), INTERRUPT_DISABLE, 1);
	/*
	p_mos->mem[0x100|p_mos->sp] = p_mos->pc >> 8;
	p_mos->sp--;
	p_mos->mem[0x100|p_mos->sp] = p_mos->pc;
	p_mos->sp--;
	p_mos->mem[0x100|p_mos->sp] = p_mos->status | (1<<4) | (1<<5);
	p_mos->sp--;
	p_mos->pc = (p_mos->mem[0xFFFF] << 8) | p_mos->mem[0xFFFE];
	set_status(&(p_mos->status), INTERRUPT_DISABLE, 1);

	/ *
	uint8_t pc_lsbyte = (p_mos->pc + 1) & 0x00FF;
	uint8_t pc_msbyte = (p_mos->pc + 1) & 0xFF00;

	p_mos->mem[0x0100|p_mos->sp--] = pc_msbyte;
	p_mos->mem[0x0100|p_mos->sp--] = pc_lsbyte; // cargue el pc

	uint8_t aux_status = p_mos->status | (1<<4) | (1<<5); // quizas setear el status asi antes?
	p_mos->mem[0x0100|p_mos->sp--] = aux_status; // aca decrementado directo.

	set_status(&(p_mos->status), INTERRUPT_DISABLE, 1);
	
	uint8_t primer_byte  = (p_mos->mem)[0xFFFE];  //primer byte
	uint8_t segundo_byte = (p_mos->mem)[0xFFFF];  //segundo byte

	p_mos->pc = ((segundo_byte << 8) | primer_byte); //  esot no se... quizas no es a 0xFFF es un puntero a funcion

	set_status(&(p_mos->status), BREAK, 1); // seteo break sigue haciendo falta? */
	
}

void BVC(mos6502_t *p_mos){

	if (!get_status(&(p_mos->status), OVERFLOW))
		p_mos->pc += (int8_t) (*(p_mos->inst->m));
}

void BVS(mos6502_t *p_mos){

	if (get_status(&(p_mos->status), OVERFLOW))
		p_mos->pc += (int8_t) (*(p_mos->inst->m));
}

void CLC(mos6502_t *p_mos){

	set_status(&(p_mos->status), CARRY, 0);
}

void CLD(mos6502_t *p_mos){

	set_status(&(p_mos->status), DECIMAL, 0);
}

void CLI(mos6502_t *p_mos){

	set_status(&(p_mos->status), INTERRUPT_DISABLE, 0);
}

void CLV(mos6502_t *p_mos){

	set_status(&(p_mos->status), OVERFLOW, 0);
}

void CP(mos6502_t *p_mos, uint8_t registro){

	set_status(&(p_mos->status), CARRY, registro >= *(p_mos->inst->m));
	set_status(&(p_mos->status), ZERO, *(p_mos->inst->m) == registro);
	set_status(&(p_mos->status), NEGATIVE, *(p_mos->inst->m) > registro);
}

void CMP(mos6502_t *p_mos){

	CP(p_mos, p_mos->a);
}

void CPX(mos6502_t *p_mos){

	CP(p_mos, p_mos->x);
}

void CPY(mos6502_t *p_mos){

	CP(p_mos, p_mos->y);
}

void DE(mos6502_t *p_mos, uint8_t *registro){

	(*registro)--;
	
	set_zero (&(p_mos->status), *registro);
	set_negative (&(p_mos->status), *registro);
}

void DEC(mos6502_t *p_mos){

	DE(p_mos, p_mos->inst->m);
}

void DEX(mos6502_t *p_mos){

	DE(p_mos, &(p_mos->x));
}

void DEY(mos6502_t *p_mos){

	DE(p_mos, &(p_mos->y));
}

void EOR(mos6502_t *p_mos){

	p_mos->a ^= * (p_mos->inst->m);

	set_zero(&(p_mos->status), p_mos->a);
	set_negative(&(p_mos->status), p_mos->a);
}

void INC_all(mos6502_t * p_mos,uint8_t * registro){

	(*registro)++;

	set_zero(&(p_mos->status), *registro);
	set_negative(&(p_mos->status), *registro);
}

void INC(mos6502_t *p_mos){

	INC_all(p_mos, p_mos->inst->m);
}

void INX(mos6502_t *p_mos){

	INC_all(p_mos, &(p_mos->x));
}

void INY(mos6502_t *p_mos){

	INC_all(p_mos, &(p_mos->y));
}

void JMP(mos6502_t *p_mos){

	p_mos->pc = p_mos->inst->direccion;
}

void JSR(mos6502_t *p_mos){

	p_mos->mem[0x0100|p_mos->sp] = (p_mos->pc - 1) >> 8;
	p_mos->sp--;
	p_mos->mem[0x0100|p_mos->sp] = p_mos->pc -1;
	p_mos->sp--;
	p_mos->pc = p_mos->inst->direccion;
	/*
	uint8_t pc_lsbyte = (p_mos->pc - 1) & 0x00FF;
	uint8_t pc_msbyte = (p_mos->pc - 1) & 0xFF00;

	p_mos->mem[0x0100|p_mos->sp--] = pc_msbyte;
	p_mos->mem[0x0100|p_mos->sp--] = pc_lsbyte;

	p_mos->pc = *(p_mos->inst->m);*/
}

void LD(mos6502_t *p_mos, uint8_t *registro){

	*registro = *(p_mos->inst->m);

	set_zero(&(p_mos->status), *registro);
	set_negative(&(p_mos->status), *registro);
}

void LDA(mos6502_t *p_mos){

	LD(p_mos, &(p_mos->a));
}


void LDX(mos6502_t *p_mos){

	LD(p_mos, &(p_mos->x));
}


void LDY(mos6502_t *p_mos){

	LD(p_mos, &(p_mos->y));
}

void LSR(mos6502_t *p_mos){

	set_status(&(p_mos->status), CARRY, *(p_mos->inst->m) & MASK_LSB);
	*(p_mos->inst->m) >>= 1;

	//set_carry (&(p_mos->status), *(p_mos->inst->m));
	set_zero (&(p_mos->status), *(p_mos->inst->m));
	set_negative (&(p_mos->status), *(p_mos->inst->m));
}

void NOP(mos6502_t *p_mos){ 
}

void ORA(mos6502_t *p_mos){

	p_mos->a |= *(p_mos->inst->m);

	set_zero (&(p_mos->status), p_mos->a);
	set_negative (&(p_mos->status), p_mos->a);
}

void PHA(mos6502_t *p_mos){
	
	p_mos->mem[0x0100 | p_mos->sp] = p_mos->a;
	p_mos->sp--;
}

void PHP(mos6502_t *p_mos){
	
	p_mos->mem[0x0100 | p_mos->sp] = p_mos->status | (1<<4) | (1<<5);
	p_mos->sp--;

}

void PLA(mos6502_t *p_mos){

	p_mos->sp++;
	p_mos->a = p_mos->mem[0x0100 | p_mos->sp];

	set_zero (&(p_mos->status), p_mos->a);
	set_negative (&(p_mos->status), p_mos->a);
}

void PLP(mos6502_t *p_mos){
	
	p_mos->sp++;
	p_mos->status = (p_mos->mem[0x0100 | p_mos->sp] & 0xCF);// | (p_mos->status & 0x30); // tmb puede ser con los flags & BREAK & reservado
	//p_mos->status = (p_mos->mem[0x0100 | p_mos->sp]) | (p_mos->status & 0x30); // tmb puede ser con los flags & BREAK & reservado
}

void ROL(mos6502_t *p_mos){

	rotate_left(&(p_mos->status), p_mos->inst->m);

	set_zero (&(p_mos->status), *(p_mos->inst->m));
	set_negative (&(p_mos->status), *(p_mos->inst->m));
	//set_carry (&(p_mos->status), *(p_mos->inst->m));
}

void ROR(mos6502_t *p_mos){

	rotate_right(&(p_mos->status),p_mos->inst->m);

	set_zero (&(p_mos->status), *(p_mos->inst->m));
	set_negative (&(p_mos->status), *(p_mos->inst->m));
	//set_carry (&(p_mos->status), *(p_mos->inst->m));
}

void RTI(mos6502_t *p_mos){

	PLP(p_mos);

	p_mos->sp++;
	uint8_t primer_byte  = (p_mos->mem)[0x0100 | p_mos->sp]; //primer byte
	p_mos->sp++;  
	uint8_t segundo_byte = (p_mos->mem)[0x0100 | p_mos->sp];  //segundo byte

	p_mos->pc = ((segundo_byte << 8) | primer_byte);
	
}

void RTS(mos6502_t *p_mos){

	p_mos->sp++;
	uint8_t primer_byte  = (p_mos->mem)[0x0100 | p_mos->sp];  //primer byte
	p_mos->sp++;
	uint8_t segundo_byte = (p_mos->mem)[0x0100 | p_mos->sp];  //segundo byte
	
	p_mos->pc = ((segundo_byte << 8) | primer_byte) + 1;
}

void SBC(mos6502_t *p_mos){

	/*uint16_t aux = p_mos->a - *(p_mos->inst->m);
	set_overflow(&(p_mos->status), p_mos->a, *(p_mos->inst->m), aux);
	uint16_t aux2 = aux - (!get_status((&p_mos->status),CARRY));
	set_overflow(&(p_mos->status), aux, -(!get_status((&p_mos->status),CARRY)), aux);
	set_carry (&(p_mos->status), ~p_mos->a);*/

	/*uint16_t aux = *(p_mos->inst->m) + (!get_status((&p_mos->status),CARRY));
	uint16_t res = p_mos->a - aux;
	set_overflow(&(p_mos->status), p_mos->a, -aux, res);
	set_carry (&(p_mos->status), res);*/
	
	uint16_t aux = *(p_mos->inst->m) + !get_status(&(p_mos->status), CARRY);
	uint16_t res = p_mos->a - aux;

    set_carry(&(p_mos->status), ~res);
    set_negative(&(p_mos->status), res);
    set_zero(&(p_mos->status), res);
	set_overflow(&(p_mos->status), *(p_mos->inst->m), get_status(&(p_mos->status), CARRY), aux);
	if(!get_status(&(p_mos->status),OVERFLOW)){
		set_overflow(&(p_mos->status), p_mos->a, ~aux, res);
	}
	p_mos->a = (uint8_t)res;

	/*
	uint16_t aux = (p_mos->a)  - (!get_status((&p_mos->status),CARRY));
	set_overflow(&(p_mos->status), (p_mos->a), -(!get_status((&p_mos->status),CARRY)), aux);
	uint16_t aux2 = aux - *(p_mos->inst->m);
	set_overflow(&(p_mos->status), aux, -*(p_mos->inst->m), aux2); 

	set_carry (&(p_mos->status), ~aux2);

	p_mos->a = aux2;

	set_zero (&(p_mos->status), p_mos->a);
	set_negative (&(p_mos->status), p_mos->a); */
	
}

void SEC(mos6502_t *p_mos){ 

	set_status (&(p_mos->status), CARRY, 1);
}

void SED(mos6502_t *p_mos){

	set_status (&(p_mos->status), DECIMAL, 1);
}

void SEI(mos6502_t *p_mos){

	set_status (&(p_mos->status), INTERRUPT_DISABLE, 1);
}

void STA(mos6502_t *p_mos){

	*(p_mos->inst->m) = p_mos->a;
}

void STX(mos6502_t *p_mos){

	*(p_mos->inst->m) = p_mos->x;
}

void STY(mos6502_t *p_mos){

	*(p_mos->inst->m) = p_mos->y;
}

void TRANSFER(mos6502_t *p_mos, uint8_t from, uint8_t *to){

	*to = from;

	set_zero (&(p_mos->status), *to);
	set_negative (&(p_mos->status), *to);
}

void TAX(mos6502_t *p_mos){

	TRANSFER(p_mos, p_mos->a, &(p_mos->x));
}

void TAY(mos6502_t *p_mos){

	TRANSFER(p_mos, p_mos->a, &(p_mos->y));
}

void TSX(mos6502_t *p_mos){
	
	TRANSFER(p_mos, p_mos->sp, &(p_mos->x));
}

void TXA(mos6502_t *p_mos){

	TRANSFER(p_mos, p_mos->x, &(p_mos->a));
}

void TXS(mos6502_t *p_mos){

	p_mos->sp = p_mos->x;
}

void TYA(mos6502_t *p_mos){

	TRANSFER(p_mos, p_mos->y, &(p_mos->a));
}
