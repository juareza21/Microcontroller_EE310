/* 
 * File:   IO_innit.h
 * Author: alexjuarezaragon
 *
 * Created on April 16, 2024, 5:10 PM
 */

#include <xc.h>

void initialize(void){
    PORTD = 0; ANSELD = 0; LATD = 0; TRISD = 0b00000000;
    PORTB = 0; ANSELB = 0; LATB = 0; TRISB = 0b01001101;
    PORTC = 0; ANSELC = 0; LATC = 0; TRISC = 0b00001000;
    //PORTB bit 0 is the interrupt
    //PORTB bit 1 is the output for the 1st Photo-resistor circuit
    //PORTB bit 2 is the input of the 1st Photo-resistor circuit
    //PORTB bit 3 is the output for the 2nd Photo-resistor circuit
    //PORTB bit 4 is the input of the 2nd Photo-resistor circuit
    //PORTB bit 5 is the DIG_OUT for the relay 
    //PORTB bit 6 is not used
    //PORTB bit 7 is the SYS_LED
    
    //Enable interrupt priority bit in INTCON0 register
    INTCON0bits.IPEN = 1;
    
    //Enables high priority interrupts
    INTCON0bits.GIEH = 1;
    
    //Enables low priority interrupts
    INTCON0bits.GIEL = 1;
    
    //INterrupt on rising edge  of INT0 pin
    INTCON0bits.INT0EDG = 0;
    
    //Sets the interrupt high priority (IP) for INT0 - INT0IP
    IPR1bits.INT0IP = 1;
    
    //Enable the interrupt (IE) for INT0
    PIE1bits.INT0IE = 1;
    
    //Clears interrupt flag for INT0
    PIR1bits.INT0IF = 1;
    
    IVTBASEU = 0x00;
    IVTBASEH = 0x40;
    IVTBASEL = 0x08;
    
    return;
}
