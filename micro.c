#include "micro.h"
#include "diccionario.h"
#include "direccionamiento.h"
#include "operaciones.h"

#include <stdint.h>
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

mos6502_t *micro_crear(){

    mos6502_t *micro = calloc(1, sizeof(mos6502_t));

    if(!micro)
        return NULL;

    return micro;
}

void micro_destruir(mos6502_t *micro){

    free (micro->mem);
    micro->mem = NULL;
    free (micro);
}

bool cargar_rom(mos6502_t *p_mos, char *nombre_archivo){

    FILE *f = fopen(nombre_archivo, "rb");
    
    if (!f)
        return false;

    p_mos->mem = malloc(65536 * sizeof(uint8_t));
    size_t n = fread(p_mos->mem, sizeof(uint8_t), 65536, f); // kibibytes
    
    if (n != 65536){
        fclose(f);
        return false;
    }
 
    fclose(f); 

    p_mos->pc = (((p_mos->mem)[0xFFFD] << 8) | (p_mos->mem)[0xFFFC]);
    p_mos->sp = 0xFF;
   
    return true;
}

long get_ciclos(mos6502_t *p_mos){
    return p_mos->ciclos;
}

uint16_t get_pc(mos6502_t *p_mos){
    return p_mos->pc;
}

void ejecutar_instruccion(mos6502_t *p_mos, char *log_file){

    uint8_t opcode = (p_mos->mem)[p_mos->pc]; 

    addto_log(p_mos, log_file);

    p_mos->pc++;

    instruccion_t instruccion;

    (instruccion.codigo) = opcode;

    (instruccion.ciclos) = diccionario[opcode].ciclos;
    
    f_direccionamiento_t direccionamiento = diccionario[opcode].dir; 

    direccionamiento(p_mos, &instruccion); 

    f_operaciones_t operacion = diccionario[opcode].op;

    operacion (p_mos, &instruccion);

    (p_mos->ciclos) += (instruccion.ciclos);

}

bool addto_log (mos6502_t * p_mos, char * nombre_archivo){

    FILE * f = fopen(nombre_archivo, "a");
    if (!f)
        return false;

    fprintf(f,"%04x %02x %02x %02x %02x %02x\n", p_mos->pc, p_mos->a, p_mos->x, p_mos->y, p_mos->status, p_mos->sp); 
    //fprintf(stdout,"%04x %02x %02x %02x %02x %02x\n", p_mos->pc, p_mos->a, p_mos->x, p_mos->y, p_mos->status, p_mos->sp); 
    // ^^^^ comentado para pruebas ^^^^
    fclose(f);

    return true;
    
}

void destruir_log (char * nombre_archivo){
    free (nombre_archivo);
}

void resetear_microprocesador(mos6502_t *m, uint8_t *mem, uint16_t pc) {
   
    m->a = m->x = m->y = 0;
    m->status = 0x00;

    m->mem = mem;
    m->pc = pc;

    m->ciclos = 0;
}
