#include "nemo.h"

extern int stateScreen;
volatile uint32_t Delay;

void screenDelay(void)
{
    SysTick_CounterCmd(SysTick_Counter_Enable);

    Delay = 20; // 5ms
    while(Delay != 0);

    SysTick_CounterCmd(SysTick_Counter_Disable);
    SysTick_CounterCmd(SysTick_Counter_Clear);
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
                LCD_Clear(WHITE);
                stageScreen(SCREEN_DISPLAY);
                stateScreen--;
                break;
            }
        }
        EXTI_ClearITPendingBit(EXTI_Line);
    }
}