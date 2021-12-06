#include "nemo.h"

extern int stateScreen;

void EXTI2_IRQHandler(void)
{
    // Joystic DOWN
    switch(stateScreen)
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

void EXTI3_IRQHandler(void)
{
    // Joystic LEFT
    switch(stateScreen)
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

void EXTI4_IRQHandler(void)
{
    // Joystic RIGHT
    switch(stateScreen)
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

void EXTI9_5_IRQHandler(void)
{
    // Joystic UP
    switch(stateScreen)
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

void EXTI15_10_IRQHandler(void)
{
    switch(stateScreen)
    {
        case SCR_MAIN:
            selectMainScreen(EXTI_Line11, GPIOD, GPIO_Pin_11);
            break;
        case SCR_PAGE:
          selectStageScreen(EXTI_Line11, GPIOD, GPIO_Pin_11);
            break;
        case SCR_GAME:
            
            break;
}
}