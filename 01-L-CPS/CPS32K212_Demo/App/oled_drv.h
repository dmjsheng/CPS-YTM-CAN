#ifndef OLED_DRV_H
#define OLED_DRV_H

#include "cps32k21x_i2c.h"
#include "cps32k21x_gpio.h"
#include "cps32k21x_rcc.h"
#include <stdint.h>

#define OLED_I2C_ADDR       0x78u

void Init_OLED(void);
void OLED_Clear(void);
void OLED_ShowChar(uint8_t x, uint8_t line, char ch);
void OLED_ShowString(uint8_t x, uint8_t line, const char *str);
void OLED_ShowHex8(uint8_t x, uint8_t line, uint8_t val);
void OLED_ShowHex16(uint8_t x, uint8_t line, uint16_t val);
void OLED_ShowDec(uint8_t x, uint8_t line, uint32_t val, uint8_t len);

#endif /* OLED_DRV_H */
