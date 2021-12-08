#include "nemo.h"

#include <time.h>

extern int stateScreen;

void Delay(int ms)
{
  time_t current = clock();
  while (clock() - current < ms);
}

void backScreen(uint32_t EXTI_Line, GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin)
{
    if (EXTI_GetITStatus(EXTI_Line) != RESET)
    {
        if (GPIO_ReadInputDataBit(GPIOx, GPIO_Pin) == Bit_RESET)
        {
            switch (stateScreen)
            {
            case SCR_MAIN:
                break;
            case SCR_PAGE:
                mainScreen();
                break;
            }
        }
        EXTI_ClearITPendingBit(EXTI_Line);
    }
}