#ifdef __cplusplus
extern "C" {
#endif

#include "avr/boot.h"
#include "avr/builtins.h"
#include "avr/interrupt.h"
#include "avr/io.h"
#include "avr/sfr_defs.h"
#include "avr/pgmspace.h"
#include <stdint.h>
#include <math.h>

#include "registers.h"

#ifdef __cplusplus
}
#endif

#define SPI_DDR  DDRB
#define SPI_PORT PORTB
#define SPI_SS   _BV(PB2)
#define SPI_MOSI _BV(PB3)
#define SPI_MISO _BV(PB4)
#define SPI_SCK  _BV(PB5)

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

    // Clear timer on compare match with OCR1A or go all the way to 0xFFFF
    if (top)
    {
        OCR1A   = top;
        TCCR1B |= _BV(WGM12);  // CTC mode
        TIMSK1 |= _BV(OCIE1A); // compare-match-clear interrupt
    }
    else
    {
        TIMSK1 |= _BV(TOIE1); // overflow interrupt
    }
}

void spi_slave_init(void)
{
    // SS   = PB2
    // MOSI = PB3
    // MISO = PB4
    // SCK  = PB5
    GpioB->ddr.b4  = 1;
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


int main(void)
{
    cli(); // no interrupts

    // Fuses set to prescaler = 1 (8ish MHz)
    // needs to happen in assembly, have to set prescaler within 4 cycles of setting CLKPCE
    // CLKPR = _BV(CLKPCE); // clk prescaler change enable
    // CLKPR = _BV(CLKPS3); // clk prescaler, divide by 256

    // DDRD |= _BV(DD0) | _BV(DD1) | _BV(DD2) | _BV(DD3); // output
    GpioC->ddr.byte = 0xFF; // all output
    GpioD->ddr.byte = 0xFF; // all output

    spi_slave_init();
    configure_timer1(CS_Prescaler1, 0x0FFF);

    GpioD->port.byte = 0;
    GpioC->port.byte = 0xFF;

    sei(); // enable interrupts

    while (1)
    {
        __builtin_avr_delay_cycles(10);
    }

    return 0; // should never reach the end
}
