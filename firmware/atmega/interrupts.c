#include <avr/sfr_defs.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdint.h>
#include "registers.h"

volatile int digit;

// SPI interrupt
ISR(SPI_STC_vect)
{
    digit = SPDR;
}

// Timer 1 overflow
ISR(TIMER1_OVF_vect) {
}

// segment to pinout translation
#define SEG_A  (1 << 1)
#define SEG_B  (1 << 0)
#define SEG_C  (1 << 4)
#define SEG_D  (1 << 6)
#define SEG_E  (1 << 7)
#define SEG_F  (1 << 2)
#define SEG_G  (1 << 3)
#define SEG_DP (1 << 5)

uint8_t num2segments(uint8_t num)
{
    switch (num) {
        case 0:
            return SEG_A | SEG_B | SEG_C | SEG_D | SEG_E | SEG_F;
        case 1:
            return SEG_B | SEG_C;
        case 2:
            return SEG_A | SEG_B | SEG_G | SEG_E | SEG_D;
        case 3:
            return SEG_A | SEG_B | SEG_G | SEG_C | SEG_D;
        case 4:
            return SEG_F | SEG_B | SEG_G | SEG_C;
        case 5:
            return SEG_A | SEG_F | SEG_G | SEG_C | SEG_D;
        case 6:
            return SEG_A | SEG_F | SEG_E | SEG_D | SEG_C | SEG_G;
        case 7:
            return SEG_A | SEG_B | SEG_C;
        case 8:
            return SEG_A | SEG_B | SEG_C | SEG_D | SEG_E | SEG_F | SEG_G;
        case 9:
            return SEG_A | SEG_B | SEG_C | SEG_G | SEG_F;
        case 0xA:
            return SEG_A | SEG_B | SEG_C | SEG_G | SEG_E | SEG_F;
        case 0xb:
            return SEG_F | SEG_G | SEG_E | SEG_D | SEG_C;
        case 0xC:
            return SEG_A | SEG_F | SEG_E | SEG_D;
        case 0xd:
            return SEG_B | SEG_C | SEG_G | SEG_D | SEG_E;
        case 0xE:
            return SEG_A | SEG_F | SEG_E | SEG_G | SEG_D;
        case 0xF:
            return SEG_A | SEG_F | SEG_E | SEG_G;
        default:
            return SEG_G;
            break;
    }
}

// Timer 1 compare match
ISR(TIMER1_COMPA_vect) {
    if (GpioC->pin.b0)
    {
        GpioD->port.byte = num2segments(digit % 0x10);
        GpioC->port.b1 = 1;
    }
    else
    {
        GpioD->port.byte = num2segments(digit/0x10);
        GpioC->port.b0 = 1;
    }
}

