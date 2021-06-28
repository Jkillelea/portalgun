#ifndef _MAIN_H_
#define _MAIN_H_

#include <stdint.h>

/* Number of digits in the display */
#define DISPLAY_SIZE (4)

extern volatile uint16_t g_DisplayNumber;
extern volatile uint8_t  g_DisplayRenderBuffer[DISPLAY_SIZE];

uint8_t num2segments(unsigned num);
void selectDigit(int digit);

#endif // _MAIN_H_
