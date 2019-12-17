#include "micro.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, char *argv[]){

    long ciclos_max = CICLOS_MAX;
    uint16_t halt = HALT_MAX;
    char **aux = NULL;

    if(argc > 8) 
      return 1; 
    
    if(argc % 2)
        return 1;

    mos6502_t * micro = micro_crear(); 

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
            halt = strtol(argv[i+1], aux, 16);
            printf("leyo %04x\n", halt);
            if(aux && **aux != '\n'){
                micro_destruir(micro);
                return 1;
            }
        }
        else if(!strcmp(argv[i], "-ciclos")){
            printf("entro bien\n");
            ciclos_max = strtol(argv[i + 1], aux, 10);
            if(aux && **aux != '\n'){
                micro_destruir(micro);
                return 1;
            }
            ciclos_max = atoi(argv[i + 1]);
            printf("leyo %ld\n", ciclos_max); 
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
    size_t i = 1;
    while (get_ciclos(micro) <= ciclos_max && get_pc(micro) != halt){ 
        printf("%zu\n",i);
        i++;
        ejecutar_instruccion(micro);
    }
    printf("salio!\n");
    printf("ciclos: %ld\n", get_ciclos(micro));
    micro_destruir(micro);

	return 0;
}
