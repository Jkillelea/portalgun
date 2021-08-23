#include <avr/sfr_defs.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdint.h>

#include "main.h"
#include "registers.h"
#include "display_segments.h"

// Digit cycling variable, telling the interrupts which digit to render
volatile int digit = 0;

/* SPI interrupt
 * =============
 * Shift in a new number to render
 */
ISR(SPI_STC_vect)
{
    g_DisplayNumber = (g_DisplayNumber << 8) | SPDR;
}

/* Timer 1 overflow 
 * ================
 * Unused
 */
ISR(TIMER1_OVF_vect)
{
}

/* Timer 1 compare match
 * =====================
 * This function updtes the rendered number
 * on the screen by setting selecting a digit
 * and updating the segments to light up from
 * the table accordingly
 */
ISR(TIMER1_COMPA_vect)
{
    digit = (digit + 1) % DISPLAY_SIZE;
    selectDigit(digit);
    GpioD->port.byte = g_DisplayRenderBuffer[digit];
}

