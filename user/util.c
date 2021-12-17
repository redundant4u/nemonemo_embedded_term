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
                stageScreen(SCREEN_CLEAR);
                mainScreen(SCREEN_DISPLAY);
                stateScreen--;
                break;
            case SCR_GAME:
                // gameScreen(SCREEN_CLEAR);
                stageScreen(SCREEN_DISPLAY);
                stateScreen--;
                break;
            }
        }
        EXTI_ClearITPendingBit(EXTI_Line);
    }
}