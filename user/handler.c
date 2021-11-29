#include "nemo.h"

void EXTI2_IRQHandler(void)
{
  // Joystic DOWN
  joystickMainScreen(EXTI_Line2, GPIOC, GPIO_Pin_2);
}

void EXTI9_5_IRQHandler(void)
{
  // Joystic UP
  joystickMainScreen(EXTI_Line5, GPIOC, GPIO_Pin_5);
}

void EXTI4_IRQHandler(void)
{
  // Joystic RIGHT
  joystickMainScreen(EXTI_Line4, GPIOC, GPIO_Pin_4);
}

void EXTI3_IRQHandler(void)
{
  // Joystic LEFT 
  joystickMainScreen(EXTI_Line3, GPIOC, GPIO_Pin_3);
}