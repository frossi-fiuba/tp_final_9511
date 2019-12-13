#ifndef MICRO_H
#define MICRO_H

#include <stdint.h>
#include <stdbool.h>

struct mos6502;
typedef struct mos6502 mos6502_t;

mos6502_t * micro_crear();
void micro_destruir(mos6502_t *);
bool cargar_rom(mos6502_t *, char *);
bool addto_log (mos6502_t *, char *);
bool setear_log (mos6502_t *, char *);
long get_ciclos(mos6502_t*);
uint16_t get_pc(mos6502_t*);
void ejecutar_instruccion(mos6502_t * p_mos);
void assert_microprocesador(const char *test, mos6502_t *m, uint16_t pc, uint8_t a, uint8_t x, uint8_t y, uint8_t status, uint8_t ciclos_micro);
void resetear_microprocesador(mos6502_t *m, uint8_t *mem, uint16_t pc);
#endif
