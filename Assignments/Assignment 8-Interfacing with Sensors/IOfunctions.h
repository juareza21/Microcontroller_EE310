/* 
 * File:   INTERRUPT_initialize.h
 * Author: alexjuarezaragon
 *
 * Created on April 19, 2024, 8:07 PM
 */

#include <xc.h>
#include <stdio.h>
#include <stdlib.h>

#define _XTAL_FREQ 4000000
#define FCY     _XTAL_FREQ/4

const char seg_code[] __at(0x100) = {0x3f, 0x06, 0x5B, 0x4F};
int SECRET_CODE = 0x23;
int INPUT = 0;
int count;
int Submit = 0;
int digit1 = 0;
int digit2 = 0;

//The interrupt
void __interrupt(irq(IRQ_INT0), base(0x4008)) INT0_ISR(void)
{
    if(PIR1 == 1){
        PIR1 = 1;
        // Makes the buzzer beep 5 times to indicate that the emergency switch has been enabled.
        for (int i = 0; i < 5; i++){
            PORTDbits.RD7 = 1;
            __delay_ms(200);
            PORTDbits.RD7 = 0;
            __delay_ms(500);
        }
        
    }
    PIR1 = 0;
}
void check(void){
    
    PORTBbits.RB7 = 1;      // Turn on SYS_LED
    PORTBbits.RB5 = 0;      // Sets relay properly
    
    // the main while loop for the program to check the input for PR1 and PR2
    while(1){
        
        // Checks for PR1 circuit input
        if (Submit == 0)
        {

            PORTBbits.RB1 = 1;                  // Turns on input for PR1
            if(PORTBbits.RB2 == 1){
                PORTD = seg_code[count];
                count++;
                __delay_ms(1000);
            }
            if(count == 4)
                count = 0;
        }
        
        
        
        // Checks if the submit switch has been pressed
        PORTCbits.RC2 = 1;
        if (PORTCbits.RC3 == 1){
            Submit++;
            if(Submit == 1){
                digit1 = count - 1;
                __delay_ms(800);
                count = 0;
                PORTD = 0;
            }
            if (Submit == 2)
                digit2 = count - 1;
            __delay_ms(2000);
        }
        PORTCbits.RC2 = 0;
        
        
        // Checks for PR2 circuit input
        if(Submit == 1)
        {
            
            PORTBbits.RB1 = 0;                  // Turn off input for PR1
            PORTBbits.RB4 = 1;                  // Turn on input for PR2
            
            // Checks if the PR2 is set
            if (PORTBbits.RB3 == 1){
                PORTD = seg_code[count];
                count++;
                __delay_ms(1000);
            }
            // Checks for overflow and resets to 0
            if (count == 4)
                count = 0;
        }
            
            // Checks if the input is equal to the Secret Code
            
            // If the input is the same then the motor will be turned on. Then
            // reset the values back to zero to restart.
        if (Submit == 2){
            
            PORTBbits.RB4 = 0;                  // Turn off input for PR2
            INPUT = (digit2*16) | (digit1);
            
            if (SECRET_CODE == INPUT){
                PORTBbits.RB5 = 1;
                __delay_ms(1200);
                PORTBbits.RB5 = 0;
                PORTD = 0;
                count = 0;
                Submit = 0;
            }
            
            // If the input is not the same then the buzzer will beep instead.
            // Then reset the values back to zero to restart.
            else{
                PORTDbits.RD7 = 1;
                __delay_ms(2000);
                PORTDbits.RD7 = 0;
                PORTD = 0;
                count = 0;
                Submit = 0;
            }
        }
            
    }
}
