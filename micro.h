#ifndef MICRO_H
#define MICRO_H

#include <stdint.h>
#include <stdbool.h>

struct mos6502;
typedef struct mos6502 mos6502_t;
/*
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
};*/


mos6502_t * micro_crear();
void micro_destruir(mos6502_t *);
bool cargar_rom(mos6502_t *,char *);


void ejecutar_instruccion(mos6502_t * p_mos);
// assert Testea todos los registros del microprocesador contra los valores provistos
void assert_microprocesador(const char *test, mos6502_t *m, uint16_t pc, uint8_t a, uint8_t x, uint8_t y, uint8_t status, uint8_t ciclos_micro);
void resetear_microprocesador(mos6502_t *m, uint8_t *mem, uint16_t pc);
#endif
