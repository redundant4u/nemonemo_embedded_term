#include "nemo.h"

int menuNumber = 0;

void joystickMainScreen(uint32_t EXTI_Line, GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin)
{
    if (EXTI_GetITStatus(EXTI_Line) != RESET)
    {
        if (GPIO_ReadInputDataBit(GPIOx, GPIO_Pin) == Bit_RESET)
        {
            menuNumber = (menuNumber + 1) % 2;
            startScreen();
        }
        EXTI_ClearITPendingBit(EXTI_Line);
    }
}

void startScreen(void)
{
    char *MENU_TEXT[2] = {"Game Start", "BGM On/Off"};
    LCD_Clear(WHITE);

    for (int i = 0; i < 2; i++)
    {
        LCD_ShowString(START_TEXT_X, START_TEXT_Y + TEXT_SIZE * i, MENU_TEXT[i], BLACK, WHITE);
    }
    // draw arrow
    LCD_ShowString(START_SELECTOR_X, START_SELECTOR_Y + TEXT_SIZE * menuNumber, ">>", BLACK, WHITE);
}