// Direct, bit-level access to registers. Performance is comparable to using the
// defines used in avr/sfr_defs.h

#ifndef _AVR_REGISTERS_H_
#define _AVR_REGISTERS_H_

#include <stdint.h>
#include <avr/sfr_defs.h>

typedef union {
    uint8_t byte;
    struct {
        uint8_t b0 : 1;
        uint8_t b1 : 1;
        uint8_t b2 : 1;
        uint8_t b3 : 1;
        uint8_t b4 : 1;
        uint8_t b5 : 1;
        uint8_t b6 : 1;
        uint8_t b7 : 1;
    };
} RegisterBits_t;

typedef struct {
    RegisterBits_t pin;
    RegisterBits_t ddr;
    RegisterBits_t port;
} GPIOControl;
#define GpioB ((volatile GPIOControl *) 0x23)
#define GpioC ((volatile GPIOControl *) 0x26)
#define GpioD ((volatile GPIOControl *) 0x29)

typedef enum {
    GPIO_IN  = 0,
    GPIO_OUT = 1,
} GPIODirection;

typedef union {
    uint8_t byte;
    struct {
        uint8_t spr0 : 1;
        uint8_t spr1 : 1;
        uint8_t cpha : 1;
        uint8_t cpol : 1;
        uint8_t mstr : 1;
        uint8_t dord : 1;
        uint8_t spe  : 1;
        uint8_t spie : 1;
    };
} SPICR_t;
#define SpiCtrl ((volatile SPICR_t *) 0x4C)

typedef union {
    uint8_t byte;
    struct {
        uint8_t spi2x : 1;
        uint8_t b1    : 1;
        uint8_t b2    : 1;
        uint8_t b3    : 1;
        uint8_t b4    : 1;
        uint8_t b5    : 1;
        uint8_t wcol  : 1;
        uint8_t spif  : 1;
    };
} SPSR_t;
#define SpiStatus ((volatile SPSR_t *) 0x4D)

#define SpiData (*(volatile uint8_t *) 0x4E) // data register is just a byte

#endif // _AVR_REGISTERS_H_
