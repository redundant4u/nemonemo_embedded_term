#include "stm32f10x.h"
#include "core_cm3.h"
#include "misc.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_rcc.h"
#include "stm32f10x_usart.h"
#include "stm32f10x_adc.h"
#include "stm32f10x_dma.h"
#include "lcd.h"
#include "touch.h"

#include <time.h>

#define START_TEXT_X 70
#define START_TEXT_Y 100

#define START_SELECTOR_X 40
#define START_SELECTOR_Y 100

#define TEXT_SIZE 20
#define PADDING_SIZE 20

void RCC_Configure(void);
void GPIO_Configure(void);
void EXTI_Configure(void);
void NVIC_Configure(void);

void EXTI2_IRQHandler(void);
void EXTI9_5_IRQHandler(void);

void Delay(int n);

void startScreen(void);
void drawMenuSelector(int select);

int menuNumber = 0;

void RCC_Configure(void)
{
  // S1 Button PB8
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);

  // Joystick PC2, 3, 4, 5
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
}

void GPIO_Configure(void)
{
  // S1 Button PB8
  GPIO_InitTypeDef GPIO_InitStructure;
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD;
  GPIO_Init(GPIOB, &GPIO_InitStructure);

  // Joystick PC2, 3, 4, 5
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2 | GPIO_Pin_3 | GPIO_Pin_4 | GPIO_Pin_5;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD;
  GPIO_Init(GPIOC, &GPIO_InitStructure);
}

void EXTI_Configure(void)
{
  EXTI_InitTypeDef EXTI_InitStructure;

  /* Joystick Down */
  GPIO_EXTILineConfig(GPIO_PortSourceGPIOC, GPIO_PinSource2);
  EXTI_InitStructure.EXTI_Line = EXTI_Line2;
  EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
  EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;
  EXTI_InitStructure.EXTI_LineCmd = ENABLE;
  EXTI_Init(&EXTI_InitStructure);

  /* Joystick Up */
  GPIO_EXTILineConfig(GPIO_PortSourceGPIOC, GPIO_PinSource5);
  EXTI_InitStructure.EXTI_Line = EXTI_Line5;
  EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
  EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;
  EXTI_InitStructure.EXTI_LineCmd = ENABLE;
  EXTI_Init(&EXTI_InitStructure);
}

void NVIC_Configure(void)
{
  NVIC_InitTypeDef NVIC_InitStructure;
  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
  // Joystick Down
  NVIC_InitStructure.NVIC_IRQChannel = EXTI2_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);

  // Joystick Up
  NVIC_InitStructure.NVIC_IRQChannel = EXTI9_5_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);
}

void Delay(int n)
{
  time_t current = clock();
  while (clock() - current < n)
    ;
}

void EXTI2_IRQHandler(void)
{
  if (EXTI_GetITStatus(EXTI_Line2) != RESET)
  {
    if (GPIO_ReadInputDataBit(GPIOC, GPIO_Pin_2) == Bit_RESET)
    {
      menuNumber = (menuNumber + 1) % 2;
      // startScreen();
    }
    EXTI_ClearITPendingBit(EXTI_Line2);
  }
}

void EXTI9_5_IRQHandler(void)
{
  if (EXTI_GetITStatus(EXTI_Line5) != RESET)
  {
    if (GPIO_ReadInputDataBit(GPIOC, GPIO_Pin_5) == Bit_RESET)
    {
      menuNumber = (menuNumber + 1) % 2;
      // startScreen();
    }
    EXTI_ClearITPendingBit(EXTI_Line5);
  }
}

void startScreen()
{
  char *MENU_TEXT[2] = { "Game Start", "BGM On/Off" };
  LCD_Clear(WHITE);

  for (int i = 0; i < 2; i++)
  {
    LCD_ShowString(START_TEXT_X, START_TEXT_Y + TEXT_SIZE * i, MENU_TEXT[i], BLACK, WHITE);
  }
  // draw arrow
  LCD_ShowString(START_SELECTOR_X, START_SELECTOR_Y + TEXT_SIZE * menuNumber, ">>", BLACK, WHITE);
}

int main(void)
{
  SystemInit();
  RCC_Configure();
  GPIO_Configure();
  EXTI_Configure();
  NVIC_Configure();

  LCD_Init();
  LCD_Clear(WHITE);

  // startScreen();

  while (1)
  {
    LCD_ShowNum(10, 70, menuNumber, 10, BLACK, WHITE);
    Delay(1000);
  }
}