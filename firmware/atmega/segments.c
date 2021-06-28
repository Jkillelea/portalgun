#include "display_segments.h"

/* Lookup table for digits */
uint8_t SEGMENT_LUT[] =
{
            [0x00] = SEG_A | SEG_B | SEG_C | SEG_D | SEG_E | SEG_F,
            [0x01] = SEG_B | SEG_C,
            [0x02] = SEG_A | SEG_B | SEG_G | SEG_E | SEG_D,
            [0x03] = SEG_A | SEG_B | SEG_G | SEG_C | SEG_D,
            [0x04] = SEG_F | SEG_B | SEG_G | SEG_C,
            [0x05] = SEG_A | SEG_F | SEG_G | SEG_C | SEG_D,
            [0x06] = SEG_A | SEG_F | SEG_E | SEG_D | SEG_C | SEG_G,
            [0x07] = SEG_A | SEG_B | SEG_C,
            [0x08] = SEG_A | SEG_B | SEG_C | SEG_D | SEG_E | SEG_F | SEG_G,
            [0x09] = SEG_A | SEG_B | SEG_C | SEG_G | SEG_F,
            [0x0a] = SEG_A | SEG_B | SEG_C | SEG_G | SEG_E | SEG_F,
            [0x0b] = SEG_F | SEG_G | SEG_E | SEG_D | SEG_C,
            [0x0c] = SEG_A | SEG_F | SEG_E | SEG_D,
            [0x0d] = SEG_B | SEG_C | SEG_G | SEG_D | SEG_E,
            [0x0e] = SEG_A | SEG_F | SEG_E | SEG_G | SEG_D,
            [0x0f] = SEG_A | SEG_F | SEG_E | SEG_G
};
