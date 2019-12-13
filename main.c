#include "micro.h"
#include <assert.h>
#include <stdio.h>
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

int main () {

    uint8_t mem[] = {
        [0x0000] = 0xEA,
        [0x0100] = 0x38, 0x18,
        [0x0200] = 0xA9, 0x01, 0xA9, 0x00, 0xA9, 0x80,
        [0x0300] = 0x69, 0x01, 0x69, 0xFE, 0x69, 0x01, 0x69, 0x01,
        [0x0400] = 0x49, 0xF0, 0x49, 0xF0,
        [0x0500] = 0xA2, 0xDE, 0xA0, 0x4D,
        [0x0600] = 0xA2, 0x01, 0xCA, 0xCA, 0x88,
        [0x0700] = 0xA9, 0xF0, 0x29, 0xAF, 0x29, 0x5F,
        [0x0800] = 0xA9, 0x0F, 0xC9, 0x0F, 0xC9, 0x01, 0xC9, 0x10,
        [0x0900] = 0xA9, 0xC0, 0x0A, 0x0A, 0x0A,
        [0x0A00] = 0x4C, 0xAD, 0xDE,
        [0x0B00] = 0xCE, 0x06, 0x0B, 0xCE, 0x06, 0x0B, 0x01,
        [0x0C00] = 0xAD, 0x09, 0x0C, 0xAE, 0x09, 0x0C, 0xAC, 0x09, 0x0C, 0xEA,
        [0x0D00] = 0xA9, 0xAA, 0xA2, 0xBB, 0xA0, 0xCC, 0x8D, 0x0F, 0x0D, 0x8E, 0x0F, 0x0D, 0x8C, 0x0F, 0x0D, 0x00,
        [0x0E00] = 0x6D, 0x0C, 0x0E, 0x0E, 0x0C, 0x0E, 0x2D, 0x0C, 0x0E, 0x4D, 0x0C, 0x0E, 0x0F,
        [0x0F00] = 0xA9, 0x10, 0xCD, 0x05, 0x0F, 0x0F,
    };

    mos6502_t * micro = micro_crear();

    if (!micro)
        return 1;
	
    // NOP:
    resetear_microprocesador(micro, mem, 0x0000);
    ejecutar_instruccion(micro);
    assert_microprocesador("NOP", micro, 0x0001, 0, 0, 0, 0x00, 2);

    // CLC, SEC:
    resetear_microprocesador(micro, mem, 0x0100);
    ejecutar_instruccion(micro);
    assert_microprocesador("SEC", micro, 0x0101, 0, 0, 0, 0x01, 2);
    ejecutar_instruccion(micro);
    assert_microprocesador("CLC", micro, 0x0102, 0, 0, 0, 0x00, 4);

    // LDA inmediato:
    resetear_microprocesador(micro, mem, 0x0200);
    ejecutar_instruccion(micro);
    assert_microprocesador("LDA 1", micro, 0x0202, 0x01, 0, 0, 0x00, 2);
    ejecutar_instruccion(micro);
    assert_microprocesador("LDA 2", micro, 0x0204, 0x00, 0, 0, 0x02, 4);
    ejecutar_instruccion(micro);
    assert_microprocesador("LDA 3", micro, 0x0206, 0x80, 0, 0, 0x80, 6);

    // ADC inmediato:
    resetear_microprocesador(micro, mem, 0x0300);
    ejecutar_instruccion(micro);
    assert_microprocesador("ADC 1", micro, 0x0302, 0x01, 0, 0, 0x00, 2);
    ejecutar_instruccion(micro);
    assert_microprocesador("ADC 2", micro, 0x0304, 0xFF, 0, 0, 0x80, 4);
    ejecutar_instruccion(micro);
    assert_microprocesador("ADC 3", micro, 0x0306, 0x00, 0, 0, 0x03, 6);
    ejecutar_instruccion(micro);
    assert_microprocesador("ADC 4", micro, 0x0308, 0x02, 0, 0, 0x00, 8);

    // EOR inmediato:
    resetear_microprocesador(micro, mem, 0x0400);
    ejecutar_instruccion(micro);
    assert_microprocesador("EOR 1", micro, 0x0402, 0xF0, 0, 0, 0x80, 2);
    ejecutar_instruccion(micro);
    assert_microprocesador("EOR 2", micro, 0x0404, 0x00, 0, 0, 0x02, 4);


    // LDX, LDY inmediatos:
    // Se asume que LDA, LDX y LDY se programaron con un cuerpo común, los
    // flags y se testearon en LDA.
    resetear_microprocesador(micro, mem, 0x0500);
    ejecutar_instruccion(micro);
    assert_microprocesador("LDX", micro, 0x0502, 0, 0xDE, 0, 0x80, 2);
    ejecutar_instruccion(micro);
    assert_microprocesador("LDY", micro, 0x0504, 0, 0xDE, 0x4D, 0x00, 4);

    // DEX, DEY:
    // Se asume LDX
    resetear_microprocesador(micro, mem, 0x0600);
    ejecutar_instruccion(micro);
    ejecutar_instruccion(micro);
    assert_microprocesador("DEX 1", micro, 0x0603, 0, 0x00, 0, 0x02, 4);
    ejecutar_instruccion(micro);
    assert_microprocesador("DEX 2", micro, 0x0604, 0, 0xFF, 0, 0x80, 6);
    ejecutar_instruccion(micro);
    assert_microprocesador("DEY", micro, 0x0605, 0, 0xFF, 0xFF, 0x80, 8);

    // A partir de acá los tests exigen LDA

    // AND inmediato:
    resetear_microprocesador(micro, mem, 0x0700);
    ejecutar_instruccion(micro);
    ejecutar_instruccion(micro);
    assert_microprocesador("AND 1", micro, 0x0704, 0xA0, 0, 0, 0x80, 4);
    ejecutar_instruccion(micro);
    assert_microprocesador("AND 2", micro, 0x0706, 0x00, 0, 0, 0x02, 6);

    // CMP inmediato:
    resetear_microprocesador(micro, mem, 0x0800);
    ejecutar_instruccion(micro);
    ejecutar_instruccion(micro);
    assert_microprocesador("CMP 1", micro, 0x0804, 0x0F, 0, 0, 0x03, 4);// era 0x03 el ante ulitmo PARA MI ES 2 15-15
    ejecutar_instruccion(micro);
    assert_microprocesador("CMP 2", micro, 0x0806, 0x0F, 0, 0, 0x01, 6);
    ejecutar_instruccion(micro);
    assert_microprocesador("CMP 3", micro, 0x0808, 0x0F, 0, 0, 0x80, 8);

    // ASL acumulador:
    resetear_microprocesador(micro, mem, 0x0900);
    ejecutar_instruccion(micro);
    ejecutar_instruccion(micro);
    assert_microprocesador("ASL 1", micro, 0x0903, 0x80, 0, 0, 0x81, 4);
    ejecutar_instruccion(micro);
    assert_microprocesador("ASL 2", micro, 0x0904, 0x00, 0, 0, 0x03, 6);
    ejecutar_instruccion(micro);
    assert_microprocesador("ASL 3", micro, 0x0905, 0x00, 0, 0, 0x02, 8);

    // JMP:
    resetear_microprocesador(micro, mem, 0x0A00);
    ejecutar_instruccion(micro);
    assert_microprocesador("JMP", micro, 0xDEAD, 0, 0, 0, 0, 3);

    // A partir de acá, salvo STA, STX y STY, todas las operaciones ya fueron
    // probadas con otros direccionamientos. Se asume que los flags ya fueron
    // testeados y que las operaciones andan.

    // DEC absoluto:
    resetear_microprocesador(micro, mem, 0x0B00);
    ejecutar_instruccion(micro);
    assert_microprocesador("DEC 1", micro, 0x0B03, 0, 0, 0, 0x02, 6);
    assert(mem[0x0B06] == 0x00);
    ejecutar_instruccion(micro);
    assert_microprocesador("DEC 2", micro, 0x0B06, 0, 0, 0, 0x80, 12);
    assert(mem[0x0B06] == 0xFF);

    // LDA, LDX, LDY absolutos:
    resetear_microprocesador(micro, mem, 0x0C00);
    ejecutar_instruccion(micro);
    assert_microprocesador("LDA", micro, 0x0C03, 0xEA, 0, 0, 0x80, 4);
    ejecutar_instruccion(micro);
    assert_microprocesador("LDX", micro, 0x0C06, 0xEA, 0xEA, 0, 0x80, 8);
    ejecutar_instruccion(micro);
    assert_microprocesador("LDY", micro, 0x0C09, 0xEA, 0xEA, 0xEA, 0x80, 12);

    // STA, STX, STY:
    // Se asumen LDA, LDX, LDY inmediatos.
    resetear_microprocesador(micro, mem, 0x0D00);
    ejecutar_instruccion(micro);
    ejecutar_instruccion(micro);
    ejecutar_instruccion(micro);
    ejecutar_instruccion(micro);
    assert_microprocesador("STA", micro, 0x0D09, 0xAA, 0xBB, 0xCC, 0x80, 10);
    assert(mem[0x0D0F] == 0xAA);
    ejecutar_instruccion(micro);
    assert_microprocesador("STX", micro, 0x0D0C, 0xAA, 0xBB, 0xCC, 0x80, 14);
    assert(mem[0x0D0F] == 0xBB);
    ejecutar_instruccion(micro);
    assert_microprocesador("STY", micro, 0x0D0F, 0xAA, 0xBB, 0xCC, 0x80, 18);
    assert(mem[0x0D0F] == 0xCC);

    // ADC, AND, ASL, EOR absolutos:
    resetear_microprocesador(micro, mem, 0x0E00);
    ejecutar_instruccion(micro);
    assert_microprocesador("ADC", micro, 0x0E03, 0x0F, 0, 0, 0x00, 4);
    ejecutar_instruccion(micro);
    assert_microprocesador("ASL", micro, 0x0E06, 0x0F, 0, 0, 0x00, 10);
    assert(mem[0x0E0C] == 0x1E);
    ejecutar_instruccion(micro);
    assert_microprocesador("AND", micro, 0x0E09, 0x0E, 0, 0, 0x00, 14);
    ejecutar_instruccion(micro);
    assert_microprocesador("EOR", micro, 0x0E0C, 0x10, 0, 0, 0x00, 18);

    // CMP absoluto:
    // Se asume LDA inmediato.
    resetear_microprocesador(micro, mem, 0x0F00);
    ejecutar_instruccion(micro);
    ejecutar_instruccion(micro);
    assert_microprocesador("CMP", micro, 0x0F05, 0x10, 0, 0, 0x01, 6);


	return 0;
}
