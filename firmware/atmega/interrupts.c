#include <avr/sfr_defs.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdint.h>

#include "main.h"
#include "registers.h"
#include "display_segments.h"

volatile int digit  = 0;

// SPI interrupt
ISR(SPI_STC_vect)
{
    g_DisplayNumber = (g_DisplayNumber << 8) | SPDR;
}

// Timer 1 overflow
ISR(TIMER1_OVF_vect)
{
}

// Timer 1 compare match
ISR(TIMER1_COMPA_vect)
{
    // render a nybble
    GpioD->port.byte = num2segments((g_DisplayNumber >> 4*digit) & 0x0F);
    selectDigit(digit);
    digit = (digit + 1) % 4;
}

