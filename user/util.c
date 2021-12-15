#include "nemo.h"

extern int stateScreen;

void screenDelay(void)
{
    for(int i = 0; i < 1000000; i++) {}
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
                mainScreen(SCREEN_CLEAR);
                break;
            case SCR_GAME:
                stageScreen(SCREEN_CLEAR);
                break;
            }
        }
        EXTI_ClearITPendingBit(EXTI_Line);
    }
}