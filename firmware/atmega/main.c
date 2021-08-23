#include <avr/boot.h>
#include <avr/builtins.h>
#include <avr/interrupt.h>
#include <avr/io.h>
#include <avr/sfr_defs.h>
#include <avr/pgmspace.h>
#include <stdint.h>
#include <math.h>

#include "main.h"
#include "display_segments.h"
#include "registers.h"

/* Number to render to display. Accessed in ISRs */
volatile uint16_t g_DisplayNumber = 0;
volatile uint8_t  g_DisplayRenderBuffer[DISPLAY_SIZE] = {0};

enum ClockSelectBits
{
    CS_TimerOff          = 0,
    CS_Prescaler1        = _BV(CS10),
    CS_Prescaler8        = _BV(CS11),
    CS_Prescaler64       = _BV(CS11) | _BV(CS10),
    CS_Prescaler256      = _BV(CS12),
    CS_Prescaler1024     = _BV(CS12) | _BV(CS10),
    CS_ClockT1PinRising  = _BV(CS12) | _BV(CS11),
    CS_ClockT1PinFalling = _BV(CS12) | _BV(CS11) | _BV(CS10),
};

// Configure Timer 1 for a count up to clear timer compare match
void configure_timer1(uint8_t prescalerBits, uint16_t top) {
    // Configure Timer 1
    // COM1A1 COM1A0 COM1B1 COM1B0 WGM11 WGM10
    TCCR1A = 0;
    // ICNC1 ICES1 WGM13 WGM12 CS12 CS11 CS10
    TCCR1B  = 0;
    // FOC1B FOC1A
    TCCR1C = 0;
    // ICIE1 OCIE1B OCIE1A TOIE1
    TIMSK1  = 0;

    TCCR1B |= prescalerBits;

    // Clear timer on compare match with OCR1A
    if (top)
    {
        OCR1A = top;
    }
    else
    {
        OCR1A = 0xFFFF;
    }

    TCCR1B |= _BV(WGM12);  // CTC mode
    TIMSK1 |= _BV(OCIE1A); // compare-match-clear interrupt
}

void spi_slave_init(void)
{
    // These three pins are configured automatically
    // SS   = PB2
    GpioB->ddr.b2 = DDR_IN;
    // MOSI = PB3
    GpioB->ddr.b3 = DDR_IN;
    // SCK  = PB5
    GpioB->ddr.b5 = DDR_IN;
    // This pin must be configured manually
    // MISO = PB4
    GpioB->ddr.b4  = DDR_OUT;
    GpioB->port.b4 = GPIO_HIGH;

    SpiCtrl->spe  = 1; // Enable peripheral
    SpiCtrl->spie = 1; // Interrupt enable, not firing on SS low?
}

uint8_t spi_slave_transcieve(uint8_t data)
{
    // Load data into shift register
    SpiData = data;
    // wait for transmission complete
    // while((SPSR & (1 << SPIF)));
    while (SpiStatus->spif);
    // return rx data
    return SpiData;
}

void selectDigit(int d)
{
    GpioC->port.b0 = 0;
    GpioC->port.b1 = 0;
    GpioB->port.b0 = 0;
    GpioB->port.b1 = 0;

    switch (d) {
        case 0:
            GpioC->port.b0 = 1;
            break;
        case 1:
            GpioC->port.b1 = 1;
            break;
        case 2:
            GpioB->port.b0 = 1;
            break;
        case 3:
            GpioB->port.b1 = 1;
            break;
        default:
            /* Nothing */
            break;
    }

    return;
}

/* Digits between 0 and F are precalculated and in a lookup table */
uint8_t num2segments(unsigned num)
{
    if (num <= 0x0F)
        return SEGMENT_LUT[num];
    return SEG_G;
}

/* Each digit uses 4 bits */
void renderNumberToBuffer(uint16_t num)
{
    g_DisplayRenderBuffer[0] = num2segments((num >>  0) & 0x0F);
    g_DisplayRenderBuffer[1] = num2segments((num >>  4) & 0x0F);
    g_DisplayRenderBuffer[2] = num2segments((num >>  8) & 0x0F);
    g_DisplayRenderBuffer[3] = num2segments((num >> 12) & 0x0F);
}

int main(void)
{
    // Setup Code
    cli(); // no interrupts

    // Display pin directions
    // GpioD->ddr.byte = 0xFF;   // Segments on port D, all output

    GpioD->ddr.b0 = DDR_OUT; // Digit selectors
    GpioD->ddr.b1 = DDR_OUT; // Digit selectors
    GpioD->ddr.b2 = DDR_OUT; // Digit selectors
    GpioD->ddr.b3 = DDR_OUT; // Digit selectors
    GpioD->ddr.b4 = DDR_OUT; // Digit selectors
    GpioD->ddr.b5 = DDR_OUT; // Digit selectors
    GpioD->ddr.b6 = DDR_OUT; // Digit selectors
    GpioD->ddr.b7 = DDR_OUT; // Digit selectors

    GpioB->ddr.b0 = DDR_OUT; // Digit selectors
    GpioB->ddr.b1 = DDR_OUT;
    GpioC->ddr.b0 = DDR_OUT;
    GpioC->ddr.b1 = DDR_OUT;

    spi_slave_init();

    /*
     * F_CLK = 16 MHz Prescaler = 8, Top Counter = 0x0FFF gives about a 4kHz timer.
     * Each segment is rendered every 4th interrupt, giving about a 1kHz refresh rate
     */
    configure_timer1(CS_Prescaler8, 0x0FFF);

    GpioD->port.byte = 0; // All segments off
    selectDigit(-1);      // All digits off
    // End Setup Code

    // enable interrupts, disable for debugging
    sei();

    g_DisplayNumber = 0xC137;
    renderNumberToBuffer(g_DisplayNumber);
    // __builtin_avr_delay_cycles(3*F_CPU);

    while (1)
    {
        // g_DisplayNumber++;
        renderNumberToBuffer(g_DisplayNumber);
        __builtin_avr_delay_cycles(F_CPU / 16); // roughly 16 counts per second
    }

    return 0; // should never reach the end
}
