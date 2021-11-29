#include "lcd.h"
#include "stdio.h"
#include "stdlib.h"
#include "stm32f10x.h"
#include "stm32f10x_rcc.h"
#include "stm32f10x_gpio.h"
#include "font.h"

/* Private variable ---------------------------------------------------------*/

uint16_t DeviceCode;

/* Private typedef -----------------------------------------------------------*/

/* private function---------------------------------------------------------- */

static void LCD_WR_REG(uint16_t LCD_Reg)
{
	// TODO implement using GPIO_ResetBits/GPIO_SetBits
	// 10주차 강의자료 11페이지 참고

	// Command
	GPIO_ResetBits(GPIOC, GPIO_Pin_6);  // LCD_CS(0)
	GPIO_SetBits(GPIOD, GPIO_Pin_15);   // LCD_RD(1)
	GPIO_ResetBits(GPIOD, GPIO_Pin_13); // LCD_RS(0)
	GPIO_ResetBits(GPIOD, GPIO_Pin_14); // LCD_WR(0)

	GPIO_Write(GPIOE, LCD_Reg);

	// TODO implement using GPIO_ResetBits/GPIO_SetBits
	GPIO_SetBits(GPIOC, GPIO_Pin_6);  // LCD_CS(1)
	GPIO_SetBits(GPIOD, GPIO_Pin_14); // LCD_WR(1)
}

static void LCD_WR_DATA(uint16_t LCD_Data)
{
	// TODO implement using GPIO_ResetBits/GPIO_SetBits

	// Data
	GPIO_ResetBits(GPIOC, GPIO_Pin_6);  // LCD_CS(0)
	GPIO_SetBits(GPIOD, GPIO_Pin_15);   // LCD_RD(1)
	GPIO_SetBits(GPIOD, GPIO_Pin_13); // LCD_RS(1)
	GPIO_ResetBits(GPIOD, GPIO_Pin_14); // LCD_WR(0)
	
	GPIO_Write(GPIOE, LCD_Data);

	// TODO implement using GPIO_ResetBits/GPIO_SetBits
	GPIO_SetBits(GPIOC, GPIO_Pin_6);  // LCD_CS(1)
	GPIO_SetBits(GPIOD, GPIO_Pin_14); // LCD_WR(1)
}

static uint16_t LCD_ReadReg(uint16_t LCD_Reg)
{
	uint16_t temp;
	GPIO_InitTypeDef GPIO_InitStructure;

	LCD_WR_REG(LCD_Reg);

	// To Read from Data Line
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_All;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_Init(GPIOE, &GPIO_InitStructure);

	GPIO_ResetBits(GPIOC, GPIO_Pin_6);  // LCD_CS(0);
	GPIO_SetBits(GPIOD, GPIO_Pin_13);   // LCD_RS(1);
	GPIO_ResetBits(GPIOD, GPIO_Pin_15); // LCD_RD(0);
	temp = GPIO_ReadInputData(GPIOE);
	GPIO_SetBits(GPIOD, GPIO_Pin_15); // LCD_RD(1);
	GPIO_SetBits(GPIOC, GPIO_Pin_6);  // LCD_CS(1);

	// Read Done, Reset
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_All;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_Init(GPIOE, &GPIO_InitStructure);
	return temp;
}

static void LCD_WriteReg(uint16_t LCD_Reg, uint16_t LCD_RegValue)
{
	LCD_WR_REG(LCD_Reg);
	LCD_WR_DATA(LCD_RegValue);
}

static void LCD_WriteRAM_Prepare(void)
{
	LCD_WR_REG(0x22);
}

static void LCD_WriteRAM(u16 RGB_Code)
{
	LCD_WR_DATA(RGB_Code);
}

static void LCD_Configuration(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOE, ENABLE);

	/*DB00~DB16*/
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_All;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_Init(GPIOE, &GPIO_InitStructure);

	/* LCD_RS  LCD_WR  LCD_RD*/
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_Init(GPIOD, &GPIO_InitStructure);

	/* LCD_CS */
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_Init(GPIOC, &GPIO_InitStructure);
}

static void LCD_Delay(uint32_t nCount)
{
	__IO uint16_t i;
	for (i = 0; i < (nCount * 5); i++)
	{
		;
	}
}

static u32 mypow(u8 m, u8 n)
{
	u32 result = 1;
	while (n--)
		result *= m;
	return result;
}

void LCD_Init(void)
{
	LCD_Configuration();
	LCD_WriteReg(0x0000, 0x0001);
	LCD_Delay(50);

	DeviceCode = LCD_ReadReg(0x0000);
	if (DeviceCode == DEVICE_CODE_NEW_LCD)
	{
		// New LCD Module
		LCD_WriteReg(0x00e5, 0x78F0);
		LCD_WriteReg(0x0001, 0x0100);
		LCD_WriteReg(0x0002, 0x0700);
		LCD_WriteReg(0x0003, 0x1030);
		LCD_WriteReg(0x0004, 0x0000);
		LCD_WriteReg(0x0008, 0x0202);
		LCD_WriteReg(0x0009, 0x0000);
		LCD_WriteReg(0x000a, 0x0000);
		LCD_WriteReg(0x000c, 0x0001);
		LCD_WriteReg(0x000d, 0x0000);
		LCD_WriteReg(0x000f, 0x0000);
		//Power On sequence //
		LCD_WriteReg(0x0010, 0x0000);
		LCD_WriteReg(0x0011, 0x0007);
		LCD_WriteReg(0x0012, 0x0000);
		LCD_WriteReg(0x0013, 0x0000);
		LCD_WriteReg(0x0007, 0x0001);
		LCD_Delay(5);
		LCD_WriteReg(0x0010, 0x1690);
		LCD_WriteReg(0x0011, 0x0227);
		LCD_Delay(5);
		LCD_WriteReg(0x0012, 0x009d);
		LCD_Delay(5);
		LCD_WriteReg(0x0013, 0x1900);
		LCD_WriteReg(0x0029, 0x0025);
		LCD_WriteReg(0x002b, 0x000d);
		LCD_Delay(5);
		LCD_WriteReg(0x0020, 0x0000);
		LCD_WriteReg(0x0021, 0x0000);
		LCD_Delay(5);

		LCD_WriteReg(0x0030, 0x0007);
		LCD_WriteReg(0x0031, 0x0303);
		LCD_WriteReg(0x0032, 0x0003);
		LCD_WriteReg(0x0035, 0x0206);
		LCD_WriteReg(0x0036, 0x0008);
		LCD_WriteReg(0x0037, 0x0406);
		LCD_WriteReg(0x0038, 0x0304);
		LCD_WriteReg(0x0039, 0x0007);
		LCD_WriteReg(0x003c, 0x0602);
		LCD_WriteReg(0x003d, 0x0008);
		LCD_Delay(5);
		LCD_WriteReg(0x0050, 0x0000);
		LCD_WriteReg(0x0051, 0x00ef);
		LCD_WriteReg(0x0052, 0x0000);
		LCD_WriteReg(0x0053, 0x013f);

		LCD_WriteReg(0x0060, 0xa700);
		LCD_WriteReg(0x0061, 0x0001);
		LCD_WriteReg(0x006a, 0x0000);
		LCD_WriteReg(0x0080, 0x0000);
		LCD_WriteReg(0x0081, 0x0000);
		LCD_WriteReg(0x0082, 0x0000);
		LCD_WriteReg(0x0083, 0x0000);
		LCD_WriteReg(0x0084, 0x0000);
		LCD_WriteReg(0x0085, 0x0000);

		LCD_WriteReg(0x0090, 0x0010);
		LCD_WriteReg(0x0092, 0x0600);

		LCD_WriteReg(0x0007, 0x0133);
	}
	else
	{
		// Old LCD Module
		/*-----   Start Initial Sequence ------*/
		LCD_WriteReg(0x00, 0x0001); /*Start internal OSC */
		LCD_WriteReg(0x01, 0x3B3F); /*Driver output control */
		LCD_WriteReg(0x02, 0x0600); /* set 1 line inversion	*/
		/*-------- Power control setup --------*/
		LCD_WriteReg(0x0C, 0x0007); /* Adjust VCIX2 output voltage */
		LCD_WriteReg(0x0D, 0x0006); /* Set amplitude magnification of VLCD63 */
		LCD_WriteReg(0x0E, 0x3200); /* Set alternating amplitude of VCOM */
		LCD_WriteReg(0x1E, 0x00BB); /* Set VcomH voltage */
		LCD_WriteReg(0x03, 0x6A64); /* Step-up factor/cycle setting  */
		/*-------- RAM position control --------*/
		LCD_WriteReg(0x0F, 0x0000); /* Gate scan position start at G0 */
		LCD_WriteReg(0x44, 0xEF00); /* Horizontal RAM address position */
		LCD_WriteReg(0x45, 0x0000); /* Vertical RAM address start position*/
		LCD_WriteReg(0x46, 0x013F); /* Vertical RAM address end position */
		/* ------ Adjust the Gamma Curve -------*/
		LCD_WriteReg(0x30, 0x0000);
		LCD_WriteReg(0x31, 0x0706);
		LCD_WriteReg(0x32, 0x0206);
		LCD_WriteReg(0x33, 0x0300);
		LCD_WriteReg(0x34, 0x0002);
		LCD_WriteReg(0x35, 0x0000);
		LCD_WriteReg(0x36, 0x0707);
		LCD_WriteReg(0x37, 0x0200);
		LCD_WriteReg(0x3A, 0x0908);
		LCD_WriteReg(0x3B, 0x0F0D);
		/*--------- Special command -----------*/
		LCD_WriteReg(0x28, 0x0006); /* Enable test command	*/
		LCD_WriteReg(0x2F, 0x12EB); /* RAM speed tuning	 */
		LCD_WriteReg(0x26, 0x7000); /* Internal Bandgap strength */
		LCD_WriteReg(0x20, 0xB0E3); /* Internal Vcom strength */
		LCD_WriteReg(0x27, 0x0044); /* Internal Vcomh/VcomL timing */
		LCD_WriteReg(0x2E, 0x7E45); /* VCOM charge sharing time */
		/*--------- Turn On display ------------*/
		LCD_WriteReg(0x10, 0x0000); /* Sleep mode off */
		LCD_Delay(3);				/* Wait 30mS  */
		LCD_WriteReg(0x11, 0x6870); /* Entry mode setup. 262K type B, take care on the data bus with 16it only */
		LCD_WriteReg(0x07, 0x0033); /* Display ON	*/

		LCD_Delay(5);
	}
	LCD_Clear(WHITE);
}

void LCD_Clear(uint16_t Color)
{
	uint32_t index = 0;
	LCD_SetCursor(0x00, 0x0000);
	LCD_WriteRAM_Prepare();
	for (index = 0; index < 76800; index++)
	{
		LCD_WR_DATA(Color);
	}
}

void LCD_Fill(uint8_t xsta, uint16_t ysta, uint8_t xend, uint16_t yend,
			  uint16_t colour)
{
	u32 n;

	LCD_WindowMax(xsta, ysta, xend, yend);
	LCD_SetCursor(xsta, ysta);
	LCD_WriteRAM_Prepare();
	n = (u32)(yend - ysta + 1) * (xend - xsta + 1);
	while (n--)
	{
		LCD_WR_DATA(colour);
	}

	LCD_WindowMax(0, 0, 240, 320);
}

void LCD_SetCursor(u16 Xpos, u16 Ypos)
{
	if (DeviceCode == DEVICE_CODE_NEW_LCD)
	{
		LCD_WriteReg(0x0020, Xpos);
		LCD_WriteReg(0x0021, Ypos);
	}
	else
	{
		LCD_WriteReg(0x004E, Xpos);
		LCD_WriteReg(0X004F, Ypos);
	}
}
// REV 1.0 @MODIFIED
void LCD_WindowMax(unsigned int x, unsigned int y, unsigned int x_end,
				   unsigned int y_end)
{
        LCD_WriteReg(0x50, x);
        LCD_WriteReg(0x51, x_end);
        LCD_WriteReg(0x52, y);
        LCD_WriteReg(0x53, y_end);
        
        LCD_SetCursor(x, y);
}

void LCD_DrawPoint(uint16_t xsta, uint16_t ysta)
{
	LCD_SetCursor(xsta, ysta);
	LCD_WR_REG(0x22);
	LCD_WR_DATA(POINT_COLOR);
}

void LCD_DrawLine(uint16_t xsta, uint16_t ysta, uint16_t xend, uint16_t yend)
{
	u16 x, y, t;
	if ((xsta == xend) && (ysta == yend))
		LCD_DrawPoint(xsta, ysta);
	else if (abs(yend - ysta) > abs(xend - xsta))
	{
		if (ysta > yend)
		{
			t = ysta;
			ysta = yend;
			yend = t;
			t = xsta;
			xsta = xend;
			xend = t;
		}
		for (y = ysta; y < yend; y++)
		{
			x = (u32)(y - ysta) * (xend - xsta) / (yend - ysta) + xsta;
			LCD_DrawPoint(x, y);
		}
	}
	else
	{
		if (xsta > xend)
		{
			t = ysta;
			ysta = yend;
			yend = t;
			t = xsta;
			xsta = xend;
			xend = t;
		}
		for (x = xsta; x <= xend; x++)
		{
			y = (u32)(x - xsta) * (yend - ysta) / (xend - xsta) + ysta;
			LCD_DrawPoint(x, y);
		}
	}
}

void LCD_DrawCircle(uint16_t x0, uint16_t y0, uint8_t r)
{
	int a, b;
	int di;
	a = 0;
	b = r;
	di = 3 - (r << 1);
	while (a <= b)
	{
		LCD_DrawPoint(x0 - b, y0 - a); // 3
		LCD_DrawPoint(x0 + b, y0 - a); // 0
		LCD_DrawPoint(x0 - a, y0 + b); // 1
		LCD_DrawPoint(x0 - b, y0 - a); // 7
		LCD_DrawPoint(x0 - a, y0 - b); // 2
		LCD_DrawPoint(x0 + b, y0 + a); // 4
		LCD_DrawPoint(x0 + a, y0 - b); // 5
		LCD_DrawPoint(x0 + a, y0 + b); // 6
		LCD_DrawPoint(x0 - b, y0 + a);
		a++;

		if (di < 0)
			di += 4 * a + 6;
		else
		{
			di += 10 + 4 * (a - b);
			b--;
		}
		LCD_DrawPoint(x0 + a, y0 + b);
	}
}

void LCD_DrawRectangle(uint16_t xsta, uint16_t ysta, uint16_t xend,
					   uint16_t yend)
{
	LCD_DrawLine(xsta, ysta, xend, ysta);
	LCD_DrawLine(xsta, ysta, xsta, yend);
	LCD_DrawLine(xsta, yend, xend, yend);
	LCD_DrawLine(xend, ysta, xend, yend);
}

void LCD_ShowChar(u8 x, u16 y, u8 num, u8 size, u16 PenColor, u16 BackColor)
{
#define MAX_CHAR_POSX 232
#define MAX_CHAR_POSY 304
	u8 temp;
	u8 pos, t;
	if (x > MAX_CHAR_POSX || y > MAX_CHAR_POSY)
		return;
	// REV 1.0 @MODIFIED
	LCD_WindowMax(x, y, x + (size / 2 - 1), y + (size - 1));
	LCD_SetCursor(x, y);

	LCD_WriteRAM_Prepare();
	num = num - ' ';
	for (pos = 0; pos < size; pos++)
	{
		if (size == 12)
			temp = asc2_1206[num][pos];
		else
			temp = asc2_1608[num][pos];
		for (t = 0; t < size / 2; t++)
		{
			if (temp & 0x01)
			{
				LCD_WR_DATA(PenColor);
			}
			else
				LCD_WR_DATA(BackColor);
			temp >>= 1;
		}
	}
	LCD_WindowMax(0x0000, 0x0000, 240, 320);
}

void LCD_ShowCharString(uint16_t x, uint16_t y, const uint8_t *p,
						uint16_t PenColor, uint16_t BackColor)
{
	uint8_t size = 16;

	if (x > MAX_CHAR_POSX)
	{
		x = 0;
		y += size;
	}
	if (y > MAX_CHAR_POSY)
	{
		y = x = 0;
		LCD_Clear(WHITE);
	}
	LCD_ShowChar(x, y, *p, size, PenColor, BackColor);
}

void LCD_ShowNum(u8 x, u8 y, u32 num, u8 len, u16 PenColor, u16 BackColor)
{
	u8 size = 16;
	u8 t, temp;
	u8 enshow = 0;
	for (t = 0; t < len; t++)
	{
		temp = (num / mypow(10, len - t - 1)) % 10;
		if (enshow == 0 && t < (len - 1))
		{
			if (temp == 0)
			{
				LCD_ShowChar(x + (size / 2) * t, y, ' ', size, PenColor, BackColor);
				continue;
			}
			else
				enshow = 1;
		}
		LCD_ShowChar(x + (size / 2) * t, y, temp + '0', size, PenColor, BackColor);
	}
}

void LCD_ShowString(u16 x0, u16 y0, u8 *pcStr, u16 PenColor, u16 BackColor)
{
	while (*pcStr != '\0')
	{
		if (*pcStr > 0x80)
		{
			LCD_ShowHzString(x0, y0, pcStr, PenColor, BackColor);
			pcStr += 2;
			x0 += 16;
		}
		else
		{
			LCD_ShowCharString(x0, y0, pcStr, PenColor, BackColor);
			pcStr += 1;
			x0 += 8;
		}
	}
}

static u16 findHzIndex(u8 *hz)
{
	u16 i = 0;
	FNT_GB16 *ptGb16 = (FNT_GB16 *)GBHZ_16;
	while (ptGb16[i].Index[0] > 0x80)
	{
		if ((*hz == ptGb16[i].Index[0]) && (*(hz + 1) == ptGb16[i].Index[1]))
		{
			return i;
		}
		i++;
		if (i > (sizeof((FNT_GB16 *)GBHZ_16) / sizeof(FNT_GB16) - 1))
		{
			break;
		}
	}
	return 0;
}

static void WriteOneHz(u16 x0, u16 y0, u8 *pucMsk, u16 PenColor, u16 BackColor)
{
	u16 i, j;
	u16 mod[16];
	u16 *pusMsk;
	u16 y;

	u16 size = 16;

	pusMsk = (u16 *)pucMsk;

	for (i = 0; i < 16; i++)
	{
		mod[i] = *pusMsk;
		mod[i] = ((mod[i] & 0xff00) >> 8) | ((mod[i] & 0x00ff) << 8);
		pusMsk = pusMsk + 1;
	}
	y = y0;
	LCD_WindowMax(x0, y0, x0 + size, y0 + size);
	LCD_SetCursor(x0, y0);
	LCD_WriteRAM_Prepare();
	for (i = 0; i < 16; i++)
	{
		for (j = 0; j < 16; j++)
		{
			if ((mod[i] << j) & 0x8000)
			{
				LCD_WriteRAM(PenColor);
			}
			else
			{
				LCD_WriteRAM(BackColor);
			}
		}
		y++;
	}
	LCD_WindowMax(0x0000, 0x0000, 240, 320);
}

void LCD_ShowHzString(u16 x0, u16 y0, u8 *pcStr, u16 PenColor, u16 BackColor)
{
#define MAX_HZ_POSX 224
#define MAX_HZ_POSY 304
	u16 usIndex;
	u8 size = 16;
	FNT_GB16 *ptGb16 = 0;
	ptGb16 = (FNT_GB16 *)GBHZ_16;

	if (x0 > MAX_HZ_POSX)
	{
		x0 = 0;
		y0 += size;
	}
	if (y0 > MAX_HZ_POSY)
	{
		y0 = x0 = 0;
		LCD_Clear(WHITE);
	}

	usIndex = findHzIndex(pcStr);
	WriteOneHz(x0, y0, (u8 *)&(ptGb16[usIndex].Msk[0]), PenColor, BackColor);
}

u16 LCD_RGBtoBGR(u16 Color)
{
	u16 r, g, b, bgr;

	b = (Color >> 0) & 0x1f;
	g = (Color >> 5) & 0x3f;
	r = (Color >> 11) & 0x1f;

	bgr = (b << 11) + (g << 5) + (r << 0);

	return (bgr);
}

void LCD_DrawPicture(u16 StartX, u16 StartY, u16 Xend, u16 Yend, u8 *pic)
{
	static u16 i = 0, j = 0;
	u16 *bitmap = (u16 *)pic;

	LCD_WindowMax(StartX, StartY, Xend, Yend);
	LCD_SetCursor(StartX, StartY);
	LCD_WriteRAM_Prepare();
	for (j = 0; j < Yend - StartY; j++)
	{
		for (i = 0; i < Xend - StartX; i++)
			LCD_WriteRAM(*bitmap++);
	}

	LCD_WindowMax(0, 0, 240, 320);
}
