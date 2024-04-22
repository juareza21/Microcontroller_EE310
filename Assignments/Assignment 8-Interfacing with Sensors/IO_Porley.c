/* -------------------------
 *  Title: Interfacing with Sensors
 * -------------------------
 * Purpose:
 * This program takes the inputs from two touch-less switches as a code and acts
 * differently depending on if the code is correct. If the code is correct to
 * that of the SECRET_CODE, then the connected motor will be turned on. If the
 * code is not correct then a buzzer will play instead. the code also contains
 * an emergency switch which is enabled as an interrupt that buzzes the buzzer
 * to a specific melody to signify it has been enabled.
 * Dependencies: IOHeader.h, IO_innit.h, IOfunctions.h
 * Compiler: MPLAB X IDE v6.20: XC8 (v2.46)
 * Author: Alex Juarez
 * Outputs: PORTD PORTB1, PORTB4, PORTB5, PORTB7, PORTC2
 * Inputs: PORTB2, PORTB3, PORTB6, PORTC3
 * Versions:
 *  V1.0: 04/19/2024 - First working version
 */

#include "IOHeader.h"
#include "IO_innit.h"
#include "IOfunctions.h"
#include <xc.h>

#define _XTAL_FREQ 4000000
#define FCY     _XTAL_FREQ/4

void initialize(void);
void check(void);

void main(void) {
    initialize();
    
    check();
    return;
}
