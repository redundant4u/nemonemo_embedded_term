#ifndef __LCD_H_
#define __LCD_H_

#include "stdint.h"
#include "stm32f10x.h"
#include "stm32f10x_gpio.h"

#define DEVICE_CODE_NEW_LCD 0x9325

#define POINT_COLOR BLACK
#define BACK_COLOR 0xFFFF

/*--------Color---------------*/
#define WHITE 0xFFFF
#define BLACK 0x0000
#define BLUE 0x001F
#define RED 0xF800
#define MAGENTA 0xF81F
#define GREEN 0x07E0
#define CYAN 0x7FFF
#define YELLOW 0xFFE0
#define BROWN 0XBC40
#define BRRED 0XFC07
#define GRAY 0X8430
#define LGRAY 0XC618

void LCD_Init(void);
void LCD_Clear(uint16_t Color);
void LCD_Fill(uint8_t xsta, uint16_t ysta, uint8_t xend, uint16_t yend, uint16_t colour);

void LCD_SetCursor(u16 Xpos, u16 Ypos);
void LCD_WindowMax(unsigned int x, unsigned int y, unsigned int x_end, unsigned int y_end);

void LCD_DrawPoint(uint16_t xsta, uint16_t ysta);
void LCD_DrawLine(uint16_t xsta, uint16_t ysta, uint16_t xend, uint16_t yend);
void LCD_DrawCircle(uint16_t x0, uint16_t y0, uint8_t r);
void LCD_DrawRectangle(uint16_t xsta, uint16_t ysta, uint16_t xend, uint16_t yend);

void LCD_ShowChar(u8 x, u16 y, u8 num, u8 size, u16 PenColor, u16 BackColor);
void LCD_ShowCharString(uint16_t x, uint16_t y, const uint8_t *p, uint16_t PenColor, uint16_t BackColor);
void LCD_ShowString(u16 x0, u16 y0, u8 *pcStr, u16 PenColor, u16 BackColor);
void LCD_ShowNum(u8 x, u8 y, u32 num, u8 len, u16 PenColor, u16 BackColor);
void LCD_ShowString(u16 x0, u16 y0, u8 *pcStr, u16 PenColor, u16 BackColor);

void LCD_ShowHzString(u16 x0, u16 y0, u8 *pcStr, u16 PenColor, u16 BackColor);
u16 LCD_RGBtoBGR(u16 Color);
void LCD_DrawPicture(u16 StartX, u16 StartY, u16 Xend, u16 Yend, u8 *pic);

#endif
