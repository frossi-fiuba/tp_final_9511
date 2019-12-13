#include "micro.h"
#include <stdio.h>
#include <string.h>
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

    instruccion_t *inst; // puntero a la estructura de instruccion (actual)

    char *log;  // locacion absoluta del archivo log donde grabar

    long ciclos;        // Cantidad de ciclos totales de ejecución.
};

int main(int argc, char *argv[]){

    long ciclos_max = 83007452;
    uint8_t halt;
    char * halt_aux;

    if(argc > 6) 
      return 1; //Chequear que la condición esté bien.
    
    if(!(argc % 2))
        return 1;

    mos6502_t * micro = micro_crear(); // aca va puntero y crear micro
    
    if(!micro) 
        return 1;

    for(size_t i = 2; i < argc; i += 2){
        if(!strcmp(argv[i], "-ciclos")){
            ciclos_max = atoi(argv[i + 1]); //Usar strtol en vez de atoi.
            break;
        }
    }

    for(size_t i = 2; i < argc; i += 2){
        if(!strcmp(argv[i], "-log")){
            strcpy(micro->log, argv[i + 1]); // verif?
            break;
        }
    }

    for(size_t i = 2; i < argc; i += 2){
        if(!strcmp(argv[i], "-halt")){
            halt = strtol(argv[i+1], &halt_aux, 16); 
            if(halt_aux)
                return 1;

            break;
        }
    }

    if(!cargar_rom(micro, argv[2])) 
        return 1;

    uint8_t primer_byte  = (micro->mem)[0xFFFC];  //primer byte
    uint8_t segundo_byte = (micro->mem)[0xFFFD];  //segundo byte

    micro->pc = ((segundo_byte << 8) | primer_byte);

    while (micro->ciclos < ciclos_max || micro->pc == halt){ // pc o puede ser inst->codigo?
        ejecutar_instruccion(micro);
    }

    micro_destruir(micro);

	return 0;
}
