/*
******************************************
Project:              
Board Revision: 1.0             
Application Version: 1.0          
Date:                 
Author:               
******************************************

Description:


LICENCE:


*/

// Includes
#include "main.h"


// Defines

// Function prototypes

// Global variables

// Interrupts
ISR(PORTA_INT0_vect) {
    // Reset interrupt flag
    PORTA.INTFLAGS = 0;
}
// Main loop
int main(void) {

    // External crystal clock
    OSC.XOSCCTRL = OSC_FRQRANGE_12TO16_gc | OSC_XOSCSEL_XTAL_16KCLK_gc;
    OSC.CTRL |= 0b00001000;
    while (!(OSC.STATUS & OSC_XOSCRDY_bm));
    _PROTECTED_WRITE(CLK.CTRL, CLK_SCLKSEL_XOSC_gc);
    OSC.CTRL &= ~OSC_RC2MEN_bm;

    // Power-down sleep mode
    SLEEP.CTRL = (SLEEP_SMODE_PDOWN_gc) | (SLEEP_SEN_bm);
   
    unsigned int a = 0;
    PORTD.DIR = 0xFF;
    PORTD.OUT = 0x00;

    PMIC.CTRL |= 0b00000111;
    PORTA.DIR = 0x00;
    PORTA.INTCTRL = 0b00000011;
    PORTA.INT0MASK = 0b00000100;
    PORTA.PIN2CTRL |= (PORT_OPC_PULLUP_gc) | (PORT_ISC_FALLING_gc);

    // Enable interrupts
    sei();

    while(1) {
        PORTD.OUT = 0x00;
        _delay_ms(500);
        PORTD.OUT = 0xFF;
        a++;
        __asm__ __volatile__ ( "sleep" "\n\t" :: );
    }

    return 0;
}

// Functions
