#include "status.h"

#include <stdbool.h>
#include <stdint.h>

bool get_status (uint8_t *reg, flag_t flag){

	return (*reg & flag);
}

void set_status (uint8_t *reg, flag_t flag, bool status){

	if (status)
		*reg |= flag;
	
	else 
		*reg &= ~flag;
}
				
void set_zero (uint8_t *reg, uint8_t res){

    set_status (reg, ZERO, !res);

}

void set_negative (uint8_t *reg, uint8_t res){
	
	set_status (reg, NEGATIVE, res & MASK_MSB);

}

void set_carry (uint8_t *reg, uint16_t res){
	
    set_status (reg, CARRY, res & MASK_CARRY);
}

void set_overflow (uint8_t *reg, uint8_t a, uint8_t b, uint8_t res){

	set_status (reg, OVERFLOW, ( ((a & MASK_MSB) == (b & MASK_MSB)) && ((res & MASK_MSB) != (a & MASK_MSB))));
}

void rotate_left (uint8_t *reg, uint8_t *x){


    bool x_msb = (*x & MASK_MSB);

    *x <<= 1;

    if (get_status(reg, CARRY))
        *x |= MASK_LSB;  

    set_status (reg, CARRY, x_msb);
}

void rotate_right (uint8_t *reg, uint8_t *x){

    uint8_t x_lsb = (*x & MASK_LSB);

    *x >>= 1;

    if (get_status(reg, CARRY))
        *x |= MASK_MSB;

    set_status (reg, CARRY, x_lsb);
}
