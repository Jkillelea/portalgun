#ifndef _DISPLAY_SEGMENTS_H_
#define _DISPLAY_SEGMENTS_H_

#include "stdint.h"

// pinout to degment translation
#define SEG_A  (1 << 0)
#define SEG_B  (1 << 1)
#define SEG_C  (1 << 2)
#define SEG_D  (1 << 3)
#define SEG_E  (1 << 4)
#define SEG_DP (1 << 5)
#define SEG_G  (1 << 6)
#define SEG_F  (1 << 7)

/* Lookup table to convert render integers between 0x0 and 0xF*/
extern uint8_t SEGMENT_LUT[];

#endif // _DISPLAY_SEGMENTS_H_
