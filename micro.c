#include "micro.h"
#include "diccionario.h"
#include "direccionamiento.h"
#include "operaciones.h"

#include <stdint.h>
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>

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

    long ciclos;        // Cantidad de ciclos totales de ejecución.
};


mos6502_t *micro_crear(){
    mos6502_t *micro = malloc(sizeof(mos6502_t));

    if(!micro)
        return NULL;

    return micro;
}


void micro_destruir(mos6502_t * icro){
    free(micro->inst);
    free (micro);
}

bool cargar_rom(mos6502_t *p_mos, char *nombre_archivo){

    FILE *f = fopen(p_mos->mem,"rb");

    if (!f)
        return false;
         // wtf son ROM pero si no M=Y no funca... lo deberia cargar ahi?
    // code
    fclose(f); 
}



// Ejecuta una instrucción del microprocesador
void ejecutar_instruccion(mos6502_t * p_mos){

	uint8_t opcode = (p_mos->mem)[p_mos->pc]; 

	(p_mos->pc)++; 

	instruccion_t instruccion;

	(instruccion.codigo) = opcode;

	(instruccion.ciclos) = diccionario[opcode].ciclos;

    p_mos->inst = &instruccion;
	
	f_direccionamiento_t direccionamiento = diccionario[opcode].dir; 

	direccionamiento(p_mos); // esta setea el operando para dsp poder acceder desde operacion al operando que corresponda

	f_operaciones_t operacion = diccionario[opcode].op;

	operacion (p_mos);

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

