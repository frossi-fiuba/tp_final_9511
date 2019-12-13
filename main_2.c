#include "micro.h"
#include <assert.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, char *argv[]){

    long ciclos_max = 83007452;

    if(argc > 6) return 1; //Chequear que la condición esté bien.
    
    mos6502_t * micro = micro_crear(); // aca va puntero y crear micro
    if(!micro) return 1;

    for(size_t i = 0; i < argc; i++){
        if(!strcmp(argv[i], "-ciclos")){
            ciclos_max = atoi(argv[i + 1]); //Usar strtol en vez de atoi.
            break;
        }
    }

    if(!cargar_rom(micro, argv[2])) return 1;
    ejecutar_instruccion(micro);

    micro_destruir(micro);

	return 0;
}