#include "nemo.h"

extern int stateScreen;

// Joystic DOWN
void EXTI2_IRQHandler(void)
{
    switch (stateScreen)
    {
    case SCR_MAIN:
        joystickMainScreen(EXTI_Line2, GPIOC, GPIO_Pin_2);
        break;
    case SCR_PAGE:
        joystickStageScreen(EXTI_Line2, GPIOC, GPIO_Pin_2);
        break;
    case SCR_GAME:
        joystickGameScreen(EXTI_Line2, GPIOC, GPIO_Pin_2);
        break;
    }
}

// Joystic LEFT
void EXTI3_IRQHandler(void)
{
    switch (stateScreen)
    {
    case SCR_MAIN:
        joystickMainScreen(EXTI_Line3, GPIOC, GPIO_Pin_3);
        break;
    case SCR_PAGE:
        joystickStageScreen(EXTI_Line3, GPIOC, GPIO_Pin_3);
        break;
    case SCR_GAME:
        joystickGameScreen(EXTI_Line3, GPIOC, GPIO_Pin_3);
        break;
    }
}

// Joystic RIGHT
void EXTI4_IRQHandler(void)
{
    switch (stateScreen)
    {
    case SCR_MAIN:
        joystickMainScreen(EXTI_Line4, GPIOC, GPIO_Pin_4);
        break;
    case SCR_PAGE:
        joystickStageScreen(EXTI_Line4, GPIOC, GPIO_Pin_4);
        break;
    case SCR_GAME:
        joystickGameScreen(EXTI_Line4, GPIOC, GPIO_Pin_4);
        break;
    }
}

// Joystic UP
void EXTI9_5_IRQHandler(void)
{
    switch (stateScreen)
    {
    case SCR_MAIN:
        joystickMainScreen(EXTI_Line5, GPIOC, GPIO_Pin_5);
        break;
    case SCR_PAGE:
        joystickStageScreen(EXTI_Line5, GPIOC, GPIO_Pin_5);
        break;
    case SCR_GAME:
        joystickGameScreen(EXTI_Line5, GPIOC, GPIO_Pin_5);
        break;
    }
}

// S1, S2 Button
void EXTI15_10_IRQHandler(void)
{
    switch (stateScreen)
    {
        case SCR_MAIN:
            selectMainScreen(EXTI_Line11, GPIOD, GPIO_Pin_11);
            backScreen(EXTI_Line12, GPIOD, GPIO_Pin_12);
            break;
        case SCR_PAGE:
            selectStageScreen(EXTI_Line11, GPIOD, GPIO_Pin_11);
            backScreen(EXTI_Line12, GPIOD, GPIO_Pin_12);
            break;
        case SCR_GAME:
            selectColorBlock(EXTI_Line11, GPIOD, GPIO_Pin_11);
            backScreen(EXTI_Line12, GPIOD, GPIO_Pin_12);
            break;
    }
}

extern uint32_t Music;
extern uint32_t Sound;

// buzzer
void TIM2_IRQHandler(void)
{
    if (TIM_GetITStatus(TIM2, TIM_IT_Update) != RESET)
    {
        TIM_ClearITPendingBit(TIM2, TIM_IT_Update);
        Sound++;

        if (Music <= Sound)
        {
            GPIOB->ODR ^= GPIO_Pin_0;
            Sound = 0;
        }
    }
}

extern volatile uint32_t Delay;

void SysTick_Handler(void)
{
    if(Delay != 0x00)
    {
        Delay--;
    }
}