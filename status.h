#ifndef STATUS_H
#define STATUS_H

#include <stdbool.h>
#include <stdint.h>

#define MASK_MSB 0x80
#define MASK_LSB 0x01
#define MASK_CARRY 0x100

typedef enum {NEGATIVE = 0x80, OVERFLOW = 0x40, BREAK = 0x10, DECIMAL = 0x08, INTERRUPT_DISABLE = 0x04, ZERO = 0x02, CARRY = 0x01} flag_t;

/* Dado un puntero al registro de status reg y un 
flag devuelve true si dicho flag está activado o 
false si no.*/
bool get_status(uint8_t *reg, flag_t flag);

/* Dado un puntero al registro de status reg, un flag 
y un valor de status almacena ese status en el registro. */
void set_status(uint8_t *reg, flag_t flag, bool status);

/* Dado un puntero al registro de status reg y el resultado 
de una operación, setea el status Zero de acuerdo a dicho resultado. */
void set_zero(uint8_t *reg, uint8_t res);

/* Dado un puntero al registro de status reg y el resultado 
de una operación, setea el status Negative de acuerdo a dicho resultado. */
void set_negative(uint8_t *reg, uint8_t res);

/* Dado un puntero al registro de status reg y el resultado 
de una adición de dos unsigned de 8 bits, setea el status Carry de 
acuerdo a dicho resultado. */
void set_carry(uint8_t *reg, uint16_t res);

/* Dado un puntero al registro de status reg, los operandos a y b que 
participaron de la operación y el resultado de la misma res, 
setea el status Overflow de acuerdo a dicho resultado. */
void set_overflow(uint8_t *reg, uint8_t a, uint8_t b, uint8_t res);

/* Recibe un puntero al registro de status reg y un puntero a una variable x 
y realiza una rotación a izquierda de x. El bit que entra en la posición 0 
de x debe ser el Carry de reg mientras que el bit que se cae de la posición 7 
de x debe quedar como nuevo Carry de reg.*/
void rotate_left(uint8_t *reg, uint8_t *x);

/* Recibe un puntero al registro de status reg y un puntero a una variable x 
y realiza una rotación a derecha de x. El bit que entra en la posición 7 de x 
debe ser el Carry de reg mientras que el bit que se cae de la posición 0 de x 
debe quedar como nuevo Carry de reg. */
void rotate_right(uint8_t *reg, uint8_t *x);


#endif
