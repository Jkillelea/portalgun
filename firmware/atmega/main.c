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

#define SPI_DDR  DDRB
#define SPI_PORT PORTB
#define SPI_SS   _BV(PB2)
#define SPI_MOSI _BV(PB3)
#define SPI_MISO _BV(PB4)
#define SPI_SCK  _BV(PB5)

/* Number to render to display. Accessed in ISRs */
volatile uint16_t g_DisplayNumber = 0;

enum ClockSelectBits
{
    CS_TimerOff           =  0,
    CS_Prescaler1         =  _BV(CS10),
    CS_Prescaler8         =  _BV(CS11),
    CS_Prescaler64        =  _BV(CS11) | _BV(CS10),
    CS_Prescaler256       =  _BV(CS12),
    CS_Prescaler1024      =  _BV(CS12) | _BV(CS10),
    CS_ClockT1PinRising   =  _BV(CS12) | _BV(CS11),
    CS_ClockT1PinFalling  =  _BV(CS12) | _BV(CS11) | _BV(CS10),
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
    // SS   = PB2
    // MOSI = PB3
    // MISO = PB4
    // SCK  = PB5
    GpioB->ddr.b4  = GPIO_OUT;
    GpioB->port.b4 = 1;

    SpiCtrl->spe  = 1;
    SpiCtrl->spie = 1; // interrupt enable, not firing on SS low?
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

void selectDigit(int digit)
{
    GpioC->port.b0 = 0;
    GpioC->port.b1 = 0;
    GpioB->port.b0 = 0;
    GpioB->port.b1 = 0;

    switch (digit) {
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
    }

    return;
}

uint8_t segmentLUT[] = {
            SEG_A | SEG_B | SEG_C | SEG_D | SEG_E | SEG_F,         // 0x00
            SEG_B | SEG_C,                                         // 0x01
            SEG_A | SEG_B | SEG_G | SEG_E | SEG_D,                 // 0x02
            SEG_A | SEG_B | SEG_G | SEG_C | SEG_D,                 // 0x03
            SEG_F | SEG_B | SEG_G | SEG_C,                         // 0x04
            SEG_A | SEG_F | SEG_G | SEG_C | SEG_D,                 // 0x05
            SEG_A | SEG_F | SEG_E | SEG_D | SEG_C | SEG_G,         // 0x06
            SEG_A | SEG_B | SEG_C,                                 // 0x07
            SEG_A | SEG_B | SEG_C | SEG_D | SEG_E | SEG_F | SEG_G, // 0x08
            SEG_A | SEG_B | SEG_C | SEG_G | SEG_F,                 // 0x09
            SEG_A | SEG_B | SEG_C | SEG_G | SEG_E | SEG_F,         // 0x0A
            SEG_F | SEG_G | SEG_E | SEG_D | SEG_C,                 // 0x0B
            SEG_A | SEG_F | SEG_E | SEG_D,                         // 0x0C
            SEG_B | SEG_C | SEG_G | SEG_D | SEG_E,                 // 0x0D
            SEG_A | SEG_F | SEG_E | SEG_G | SEG_D,                 // 0x0E
            SEG_A | SEG_F | SEG_E | SEG_G                          // 0x0F
};

uint8_t num2segments(unsigned num)
{
    if (num <= 0x0F)
        return segmentLUT[num];
    return SEG_G;
}


int main(void)
{
    cli(); // no interrupts

    // Display pin directions
    GpioD->ddr.byte = 0xFF;     // Segments on port D, all output
    GpioB->ddr.b0   = GPIO_OUT; // Digit selectors
    GpioB->ddr.b1   = GPIO_OUT;
    GpioC->ddr.b0   = GPIO_OUT;
    GpioC->ddr.b1   = GPIO_OUT;

    // spi_slave_init();
    configure_timer1(CS_Prescaler1, 0x0FFF);

    GpioD->port.byte = 0; // All segments off
    selectDigit(-1);      // All digits off

    // Disable for debugging
    sei(); // enable interrupts, disable for debugging

    while (1)
    {
        // GpioD->port.byte = b++;
        // __builtin_avr_delay_cycles(2000000/2);
        // GpioD->port.byte = 0;
        // __builtin_avr_delay_cycles(2000000/2);
        g_DisplayNumber++;
        __builtin_avr_delay_cycles(10000000);
    }

    return 0; // should never reach the end
}
