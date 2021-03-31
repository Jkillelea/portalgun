#ifndef _MAIN_H_
#define _MAIN_H_

#include <stdint.h>

extern volatile uint16_t g_DisplayNumber;
extern volatile uint8_t  g_DisplayRenderBuffer[4];

uint8_t num2segments(unsigned num);
void selectDigit(int digit);

#endif // _MAIN_H_
