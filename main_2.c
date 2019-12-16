#include "micro.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define CICLOS_MAX 83007452

int main(int argc, char *argv[]){

    long ciclos_max = CICLOS_MAX;
    uint8_t halt;
    char * halt_aux;

    if(argc > 8) 
      return 1; //Chequear que la condición esté bien.
    
    if(argc % 2)
        return 1;

    mos6502_t * micro = micro_crear(); // aca va puntero y crear micro

    if(!micro) 
        return 1;
    
    for(size_t i = 2; i < argc; i += 2){
        if(!strcmp(argv[i], "-log")){
            if(!setear_log(micro ,argv[i+1])){
                micro_destruir(micro);
                return 1;
            }
        }
       else if(!strcmp(argv[i], "-halt")){
            halt = strtol(argv[i+1], &halt_aux, 16); 
            if(halt_aux)
                return 1;
        }
        else if(!strcmp(argv[i], "-ciclos")){
            ciclos_max = atoi(argv[i + 1]); //Usar strtol en vez de atoi.
        }

        else{
            micro_destruir(micro);
            return 1;
        }
    }


    if(!cargar_rom(micro, argv[1])){ 
        micro_destruir(micro);
        return 1;
    }
    
    while (get_ciclos(micro) < ciclos_max || get_pc(micro) != halt){ // pc o puede ser inst->codigo?

        ejecutar_instruccion(micro);
    }

    micro_destruir(micro);

	return 0;
}
