#ifndef DICCIONARIO_H
#define DICCIONARIO_H

#include "micro.h"
#include "direccionamiento.h"
#include "operaciones.h"

typedef struct {
	
	f_operaciones_t op;
	f_direccionamiento_t dir;
	short ciclos;
	
} diccionario_t;

// El siguiente diccionario contiene en la coordenada "OPCODE" un puntero a la funcion correspondiente,
// contiene el direccionamiento correspondiente y la cantidad de ciclos que involucra la instruccion.

diccionario_t diccionario[256];

#endif
