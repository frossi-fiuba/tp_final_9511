#include "micro.h"
#include "diccionario.h"
#include "direccionamiento.h"
#include "operaciones.h"

#include <stdint.h>
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>

// Ejecuta una instrucción del microprocesador
void ejecutar_instruccion(mos6502_t * p_mos){

	uint8_t opcode = (p_mos->mem)[p_mos->pc]; 

	(p_mos->pc)++; 

	instruccion_t instruccion;

	(instruccion.codigo) = opcode;

	(instruccion.ciclos) = diccionario[opcode].ciclos;
	
	f_direccionamiento_t direccionamiento = diccionario[opcode].dir; 

	direccionamiento(p_mos, &instruccion); // esta setea el operando para dsp poder acceder desde operacion al operando que corresponda

	f_operaciones_t operacion = diccionario[opcode].op;

	operacion (p_mos, &instruccion);

	(p_mos->ciclos) += (instruccion.ciclos);
}


// Testea todos los registros del microprocesador contra los valores provistos
void assert_microprocesador(const char *test, mos6502_t *m, uint16_t pc, uint8_t a, uint8_t x, uint8_t y, uint8_t status, uint8_t ciclos_micro) {
    fprintf(stderr, "%s... ", test);

    assert(m->pc == pc);
    assert(m->a == a);
    assert(m->x == x);
    assert(m->y == y);
    assert(m->status == status);
    assert(m->ciclos == ciclos_micro);

    fprintf(stderr, "OK\n");
}

// Inicializa los registros del microprocesador
void resetear_microprocesador(mos6502_t *m, uint8_t *mem, uint16_t pc) {
    m->a = m->x = m->y = 0;
    m->status = 0x00;

    m->mem = mem;
    m->pc = pc;

    m->ciclos = 0;
}