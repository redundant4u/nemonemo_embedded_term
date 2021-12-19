#include "nemo.h"
#include "game.h"

extern int stateScreen;
volatile uint32_t Delay;

void delayScreen(__IO uint32_t nTime)
{
    SysTick_CounterCmd(SysTick_Counter_Enable);

    Delay = nTime;
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
            case SCR_CLEAR:
                LCD_Clear(WHITE);
                stageScreen(SCREEN_DISPLAY);
                stateScreen = SCR_PAGE;
            }
        }
        EXTI_ClearITPendingBit(EXTI_Line);
    }
}