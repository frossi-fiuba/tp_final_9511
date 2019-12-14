#include "diccionario_2.h"
#include "direccionamiento.h"
#include "operaciones.h"

diccionario_t diccionario [256] = {

	[0x69] = {ADC, inmediata, 2},

	[0x65] = {ADC, pagina_cero, 3},

	[0x75] = {ADC, pagina_cero_x, 4},

	[0x6D] = {ADC, absoluta, 4},

	[0x7D] = {ADC, absoluta_x, 4},

	[0x79] = {ADC, absoluta_y, 4},

	[0x61] = {ADC, index_indirecta_x, 6},

	[0x71] = {ADC, indirecta_index_y, 5},	

	[0x29] = {AND, inmediata, 2},

	[0x25] = {AND, pagina_cero, 3},	

	[0x35] = {AND, pagina_cero_x, 4},	

	[0x2D] = {AND, absoluta, 4},

	[0x3D] = {AND, absoluta_x, 4},

	[0x39] = {AND, absoluta_y, 4},

	[0x21] = {AND, index_indirecta_x, 6},

	[0x31] = {AND, indirecta_index_y, 5},

	[0x0A] = {ASL, acumulador, 2},

	[0x06] = {ASL, pagina_cero, 5},

	[0x16] = {ASL, pagina_cero_x, 6},

	[0x0E] = {ASL, absoluta, 6},

	[0x1E] = {ASL, absoluta_x, 7},	

	[0x90] = {BCC, relativa, 2},

	[0xB0] = {BCS, relativa, 2},

	[0xF0] = {BEQ, relativa, 2},

	[0x24] = {BIT, pagina_cero, 3},

	[0x2C] = {BIT, absoluta, 4},

	[0x30] = {BMI, relativa, 2},

	[0xD0] = {BNE, relativa, 2},

	[0x10] = {BPL, relativa, 2},

	[0x00] = {BRK, implicito, 7},

	[0x50] = {BVC, relativa, 2},

	[0x70] = {BVS, relativa, 2},

	[0x18] = {CLC, implicito, 2},

	[0xD8] = {CLD, implicito, 2},

	[0x58] = {CLI, implicito, 2},

	[0xB8] = {CLV, implicito, 2},

	[0xC9] = {CMP, inmediata, 2},

	[0xC5] = {CMP, pagina_cero, 3},

	[0xD5] = {CMP, pagina_cero_x, 4},

	[0xCD] = {CMP, absoluta, 4},

	[0xDD] = {CMP, absoluta_x, 4},

	[0xD9] = {CMP, absoluta_y, 4},

	[0xC1] = {CMP, index_indirecta_x, 6},

	[0xD1] = {CMP, indirecta_index_y, 5},

	[0xE0] = {CPX, inmediata, 2},

	[0xE4] = {CPX, pagina_cero, 3},

	[0xEC] = {CPX, absoluta, 4},

	[0xC0] = {CPY, inmediata, 2},

	[0xC4] = {CPY, pagina_cero, 3},

	[0xCC] = {CPY, absoluta, 4},

	[0xC6] = {DEC, pagina_cero, 5},

	[0xD6] = {DEC, pagina_cero_x, 6},

	[0xCE] = {DEC, absoluta, 6},

	[0xDE] = {DEC, absoluta_x, 7},

	[0xCA] = {DEX, implicito, 2},

	[0x88] = {DEY, implicito, 2},

	[0x49] = {EOR, inmediata, 2},

	[0x45] = {EOR, pagina_cero, 3},

	[0x55] = {EOR, pagina_cero_x, 4},

	[0x4D] = {EOR, absoluta, 4},

	[0x5D] = {EOR, absoluta_x, 4},

	[0x59] = {EOR, absoluta_y, 4},

	[0x41] = {EOR, index_indirecta_x, 6},

	[0x51] = {EOR, indirecta_index_y, 5},

	[0xE6] = {INC, pagina_cero, 5},

	[0xF6] = {INC, pagina_cero_x, 6},

	[0xEE] = {INC, absoluta, 6},

	[0xFE] = {INC, absoluta_x, 7},

	[0xE8] = {INX, implicito, 2},

	[0xC8] = {INY, implicito, 2},

	[0x4C] = {JMP, absoluta, 3},

	[0x6C] = {JMP, indirecta, 5},

	[0x20] = {JSR, absoluta, 7},

	[0xA9] = {LDA, inmediata, 2},

	[0xA5] = {LDA, pagina_cero, 3},

	[0xB5] = {LDA, pagina_cero_x, 4},

	[0xAD] = {LDA, absoluta, 4},

	[0xBD] = {LDA, absoluta_x, 4},

	[0xB9] = {LDA, absoluta_y, 4},

	[0xA1] = {LDA, index_indirecta_x, 6},

	[0xB1] = {LDA, indirecta_index_y, 5},

	[0xA2] = {LDX, inmediata, 2},

	[0xA6] = {LDX, pagina_cero, 3},

	[0xB6] = {LDX, pagina_cero_y, 4},

	[0xAE] = {LDX, absoluta, 4},

	[0xBE] = {LDX, absoluta_y, 4},

	[0xA0] = {LDY, inmediata, 2},

	[0xA4] = {LDY, pagina_cero, 3},

	[0xB4] = {LDY, pagina_cero_y, 4},

	[0xAC] = {LDY, absoluta, 4},

	[0xBC] = {LDY, absoluta_y, 4},

	[0x4A] = {LSR, acumulador, 2},

	[0x46] = {LSR, pagina_cero, 5},

	[0x56] = {LSR, pagina_cero_x, 6},

	[0x4E] = {LSR, absoluta, 6},

	[0x5E] = {LSR, absoluta_x, 7},

	[0xEA] = {NOP, implicito, 2},

	[0x09] = {ORA, inmediata, 2},

	[0x05] = {ORA, pagina_cero, 3},

	[0x15] = {ORA, pagina_cero_x, 4},

	[0x0D] = {ORA, absoluta, 4},

	[0x1D] = {ORA, absoluta_x, 4},

	[0x19] = {ORA, absoluta_y, 4},

	[0x01] = {ORA, index_indirecta_x, 6},

	[0x11] = {ORA, indirecta_index_y, 5},

	[0x48] = {PHA, implicito, 3},

	[0x08] = {PHP, implicito, 3},

	[0x68] = {PLA, implicito, 4},

	[0x28] = {PLP, implicito, 4},

	[0x2A] = {ROL, acumulador, 2},

	[0x26] = {ROL, pagina_cero, 3},

	[0x36] = {ROL, pagina_cero_x, 4},

	[0x2E] = {ROL, absoluta, 4},

	[0x3E] = {ROL, absoluta_x, 4},

	[0x6A] = {ROR, acumulador, 2},

	[0x66] = {ROR, pagina_cero, 3},

	[0x76] = {ROR, pagina_cero_x, 4},

	[0x6E] = {ROR, absoluta, 4},

	[0x7E] = {ROR, absoluta_x, 4},

	[0x40] = {RTI, implicito, 6},

	[0x60] = {RTS, implicito, 6},

	[0xE9] = {SBC, inmediata, 2},

	[0xE5] = {SBC, pagina_cero, 3},

	[0xF5] = {SBC, pagina_cero_x, 4},

	[0xED] = {SBC, absoluta, 4},

	[0xFD] = {SBC, absoluta_x, 4},

	[0xF9] = {SBC, absoluta_y, 4},

	[0xE1] = {SBC, index_indirecta_x, 6},

	[0xF1] = {SBC, indirecta_index_y, 5},

	[0x38] = {SEC, implicito, 2},

	[0xF8] = {SED, implicito, 2},

	[0x78] = {SEI, implicito, 2},

	[0x85] = {STA, pagina_cero, 3},

	[0x95] = {STA, pagina_cero_x, 4},

	[0x8D] = {STA, absoluta, 4},

	[0x9D] = {STA, absoluta_x, 5},

	[0x99] = {STA, absoluta_y, 5},

	[0x81] = {STA, index_indirecta_x, 6},

	[0x91] = {STA, indirecta_index_y, 6}, 

	[0x86] = {STX, pagina_cero, 3},

	[0x96] = {STX, pagina_cero_y, 4},

	[0x8E] = {STX, absoluta, 4},

	[0x84] = {STY, pagina_cero, 3},

	[0x94] = {STY, pagina_cero_y, 4}, 

	[0x8C] = {STY, absoluta, 4},

	[0xAA] = {TAX, implicito, 2},

	[0xA8] = {TAY, implicito, 2},

	[0xBA] = {TSX, implicito, 2},

	[0x8A] = {TXA, implicito, 2},

	[0x9A] = {TXS, implicito, 2},

	[0x98] = {TYA, implicito, 2},
};


