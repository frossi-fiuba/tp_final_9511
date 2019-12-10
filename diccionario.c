#include "diccionario.h"
#include "direccionamiento.h"
#include "operaciones.h"


diccionario_t diccionario [256] = {

	[0x69] = {ADC, inmediata, 2},

	[0x6D] = {ADC, absoluta, 4},

	[0x29] = {AND, inmediata, 2},

	[0x2D] = {AND, absoluta, 4},

	[0x0A] = {ASL, acumulador, 2},

	[0x0E] = {ASL, absoluta, 6},

	[0x18] = {CLC, implicito, 2},

	[0xC9] = {CMP, inmediata, 2},

	[0xCD] = {CMP, absoluta, 4},

	[0xCE] = {DEC, absoluta, 6},

	[0xCA] = {DEX, implicito, 2},

	[0x88] = {DEY, implicito, 2},

	[0x49] = {EOR, inmediata, 2},

	[0x4D] = {EOR, absoluta, 4},

	[0x4C] = {JMP, absoluta, 3},

	[0xA9] = {LDA, inmediata, 2},

	[0xAD] = {LDA, absoluta, 4},

	[0xA2] = {LDX, inmediata, 2},

	[0xAE] = {LDX, absoluta, 4},

	[0xA0] = {LDY, inmediata, 2},

	[0xAC] = {LDY, absoluta, 4},

	[0xEA] = {NOP, implicito, 2},

	[0x38] = {SEC, implicito, 2},

	[0x8D] = {STA, absoluta, 4},

	[0x8E] = {STX, absoluta, 4},

	[0x8C] = {STY, absoluta, 4}
};

