#include "micro.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, char *argv[]){

    long ciclos_max = CICLOS_MAX;
    uint16_t halt;
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
            printf("entro bien\n");
            halt = strtol(argv[i+1], &halt_aux, 16);
            printf("leyo %04x\n", halt);
            if(halt_aux){
                micro_destruir(micro);
                return 1;
            }
        }
        else if(!strcmp(argv[i], "-ciclos")){
            printf("entro bien\n");
            ciclos_max = atoi(argv[i + 1]);
            printf("leyo %ld\n", ciclos_max); //Usar strtol en vez de atoi.
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
    printf("esta ejecutando\n");
    while (get_ciclos(micro) < ciclos_max && get_pc(micro) != halt){ // pc o puede ser inst->codigo?

        ejecutar_instruccion(micro);
    }
    printf("salio!\n");
    micro_destruir(micro);

	return 0;
}
