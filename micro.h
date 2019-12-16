#ifndef MICRO_H
#define MICRO_H

#include <stdint.h>
#include <stdbool.h>
#define CICLOS_MAX 83007452
#define HALT_MAX 0x336d

struct mos6502;
typedef struct mos6502 mos6502_t;

/* Crea una nueva estructura del tipo mos6502_t.
 * Post: Devuelve un mos6502 con el log seteado por default en "log_d".*/
mos6502_t * micro_crear();

/* Elimina una estructura del tipo mos6502_t pasada por parámetro.
 * Pre: La estructura pasada por parámetro debe estar creada.*/
void micro_destruir(mos6502_t *);

/* Carga en la memoria del mos6502_t lo leído del archivo pasado como parámetro.
 * Pre: La estructura pasada por parámetro debe estar creada y el archivo debe existir.
 * Post: Devuelve false si no pudo realizar la operación y true si fue exitosa. */
bool cargar_rom(mos6502_t *, char *);

/* Carga en el log del mos6502_t los valores del mismo.
 * Pre: La estructura pasada por parámetro debe estar creada y el log debe existir.
 * Post: Devuelve false si no pudo realizar la operación y true si fue exitosa. */
bool addto_log (mos6502_t *, char *);

/* Crea un log para la estructura 6502_t utilizando el nombre del archivo pasado por parámetro.
 * Pre: La estructura pasada por parámetro debe estar creada.
 * Post: Devuelve false si no pudo realizar la operación y true si fue exitosa. */
bool setear_log (mos6502_t *, char *);

/* Devuelve la cantidad de ciclos del mos6502_t.
 * Pre: La estructura pasada por parámetro debe estar creada.*/
long get_ciclos(mos6502_t*);

/* Devuelve el pc del mos6502_t.
 * Pre: La estructura pasada por parámetro debe estar creada.*/
uint16_t get_pc(mos6502_t*);

/* Ejecuta una instrucción del microprocesador
 * Pre: La estructura pasada por parámetro debe estar creada, deben estar cargados su log y su memoria.*/
void ejecutar_instruccion(mos6502_t * p_mos);

/* Resetea el microprocesador.
 * Pre: La estructura pasada por parámetro debe estar creada, deben estar cargados su log y su memoria.
 * Post: Los registros, los ciclos y el status valen 0 mientras que la memoria y el pc se setean a los valores pasados 
 * por parámetro.*/
void resetear_microprocesador(mos6502_t *m, uint8_t *mem, uint16_t pc);
#endif
