#include <avr/sfr_defs.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdint.h>

#include "main.h"
#include "registers.h"
#include "display_segments.h"

extern int number;
volatile int digit  = 0;

// SPI interrupt
ISR(SPI_STC_vect)
{
    number = SPDR;
}

// Timer 1 overflow
ISR(TIMER1_OVF_vect)
{
}

// Timer 1 compare match
ISR(TIMER1_COMPA_vect)
{
    GpioD->port.byte = num2segments((number >> 4*digit) & 0x0F); // render a nybble
    selectDigit(digit);
    digit = (digit + 1) % 4;
}

