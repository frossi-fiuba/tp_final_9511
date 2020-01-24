#ifndef MICRO_H
#define MICRO_H

#include <stdint.h>
#include <stdbool.h>
#define CICLOS_MAX 83400598
#define HALT_MAX 0x336d

typedef struct {
    uint8_t codigo;     // Opcode.
    short ciclos;       // Cantidad de ciclos de la instrucción.
    uint8_t *m;         // Puntero al operando (registro o memoria).
    uint16_t direccion; // Dirección del operando (si corresponde).
} instruccion_t;

typedef struct mos6502 {
    uint8_t a, x, y;    // Registros A, X e Y.
    uint16_t pc;        // Program counter.
    uint8_t status;     // Registro de status.
    uint8_t sp;         // Stack pointer.
    uint8_t *mem;       // Memoria.

    long ciclos;        // Cantidad de ciclos totales de ejecución.
} mos6502_t;


/* Crea el microprocesador.
 * Post: Devuelve un mos6502 con el log seteado por default en "log_d".*/
mos6502_t * micro_crear();

/* Elimina el microprocesador.
 * Pre: La estructura pasada por parámetro debe estar creada.*/
void micro_destruir(mos6502_t *);

/* Carga en la memoria del micro la ROM pasada por parámetro.
 * Pre: El micro pasado por parámetro debe estar creado y el archivo debe existir.
 * Post: Devuelve "false" si no pudo realizar la operación y true si fue exitosa. */
bool cargar_rom(mos6502_t *, char *);

/* Carga en el arhivo de log una linea correspondiente al estado actual del micro.
 * Pre: El micro pasado por parámetroy el log deben existir.
 * Post: Devuelve false si no pudo realizar la operación y true si fue exitosa. */
bool addto_log (mos6502_t *, char *);

/* Devuelve la cantidad de ciclos del procesador hasta el momento.
 * Pre: El micro pasado por parámetro debe estar creado.*/
long get_ciclos(mos6502_t*);

/* Devuelve el estado actual de progam counter.
 * Pre: El micro pasado por parámetro debe estar creado.*/
uint16_t get_pc(mos6502_t*);

/* Ejecuta una instrucción del microprocesador
 * Pre: El micro pasado por parámetro debe estar creado, deben estar cargados su log y su memoria.*/
void ejecutar_instruccion(mos6502_t *p_mos, char *log_file);

/* Resetea el microprocesador.
 * Pre: El micro pasado por parámetro debe estar creado, deben estar cargados su log y su memoria.
 * Post: Los registros, los ciclos y el status valen 0 mientras que la memoria y el pc se setean a los valores pasados 
 * por parámetro.*/
void resetear_microprocesador(mos6502_t *m, uint8_t *mem, uint16_t pc);
#endif
