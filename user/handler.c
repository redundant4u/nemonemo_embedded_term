#include "nemo.h"

extern int stateScreen;

// 현재 어느 페이지에 속해있는지를 파악하여 해당하는 인터럽트 수행

// Joystic DOWN interrupt handler
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

// Joystic LEFT interrupt handler
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

// Joystic RIGHT interrupt handler
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

// Joystic UP interrupt handler
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

// S1, S2 Button interrupt handler
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
        case SCR_CLEAR:
            selectClearScreen(EXTI_Line11, GPIOD, GPIO_Pin_11);
            backScreen(EXTI_Line12, GPIOD, GPIO_Pin_12);
            break;
    }
}

extern uint32_t Music;
extern uint32_t Sound;

// buzzer interrupt handler
// Music 변수의 값이 바뀔 때 마다 Timer interrupt 실행
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

// delay interrupt handler
// Delay 변수의 변화가 있을때 SysTick interrupt가 발생해 0이 될 때까지 delay
void SysTick_Handler(void)
{
    if(Delay != 0x00)
    {
        Delay--;
    }
}