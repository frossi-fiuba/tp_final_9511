#include "micro.h"
#include "diccionario_2.h"
#include "direccionamiento.h"
#include "operaciones.h"

#include <stdint.h>
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

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

    instruccion_t *inst; // puntero a la estructura de instruccion (actual)

    char *log;  // locacion absoluta del archivo log donde grabar

    long ciclos;        // Cantidad de ciclos totales de ejecución.
};


mos6502_t *micro_crear(){
    mos6502_t *micro = calloc(1, sizeof(mos6502_t));

    if(!micro)
        return NULL;

    setear_log(micro ,"log_d");

    return micro;
}


void micro_destruir(mos6502_t * micro){
    free (micro->mem);
    micro->mem = NULL;
    free(micro->inst);
    micro->inst = NULL;
    free (micro->log);
    micro->log = NULL;
    free (micro);
}

bool cargar_rom(mos6502_t *p_mos, char *nombre_archivo){

    FILE *f = fopen(nombre_archivo,"rb");
    
    if (!f)
        return false;

    p_mos->mem = malloc(65536*sizeof(uint8_t));
    size_t n = fread(p_mos->mem, sizeof(uint8_t), 65536,f); // kibibytes
    
    if (n != 65536){
        fclose(f);
        return false;
    }
 
    // code
    fclose(f); 

    uint8_t primer_byte  = (p_mos->mem)[0xFFFC];  //primer byte
    uint8_t segundo_byte = (p_mos->mem)[0xFFFD];  //segundo byte

    p_mos->pc = ((segundo_byte << 8) | primer_byte);

    return true;
}

long get_ciclos(mos6502_t *p_mos){
    return p_mos->ciclos;
}

uint16_t get_pc(mos6502_t *p_mos){
    return p_mos->pc;
}


// Ejecuta una instrucción del microprocesador
void ejecutar_instruccion(mos6502_t * p_mos){

    uint8_t opcode = (p_mos->mem)[p_mos->pc]; 

    addto_log(p_mos, p_mos->log);

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

bool addto_log (mos6502_t * p_mos, char * nombre_archivo){

    FILE * f = fopen(nombre_archivo, "a");
    if (!f)
        return false;
    fprintf(f,"%04x %02x %02x %02x %02x %02x\n", p_mos->pc, p_mos->a, p_mos->x, p_mos->y, p_mos->status, p_mos->sp);

    fclose(f);
    return true;

}

bool setear_log (mos6502_t * p_mos, char * nombre_archivo){
    p_mos->log = malloc(strlen(nombre_archivo) + 1);
    
    if(!p_mos->log)
        return false; 
    
    strcpy(p_mos->log, nombre_archivo); 

    return true;
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
