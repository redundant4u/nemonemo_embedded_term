#include "nemo.h"

// NOTE: Define Position
#define MENU_COUNT 2
enum
{
    MENU_START,
    MENU_BGM,
    MENU_BLUETOOTH
};

int menuNumber = MENU_START;
extern int stateScreen;

void joystickMainScreen(uint32_t EXTI_Line, GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin)
{
    if (EXTI_GetITStatus(EXTI_Line) != RESET)
    {
        if (GPIO_ReadInputDataBit(GPIOx, GPIO_Pin) == Bit_RESET)
        {
            switch (GPIO_Pin)
            {
            case GPIO_Pin_5: // Up
                menuNumber--;
                break;
            case GPIO_Pin_2: // Down
                menuNumber++;
                break;
            }
            menuNumber = (menuNumber + MENU_COUNT) % MENU_COUNT;
            mainScreen();
        }
        EXTI_ClearITPendingBit(EXTI_Line);
    }
}

void selectMainScreen(uint32_t EXTI_Line, GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin)
{
    if (EXTI_GetITStatus(EXTI_Line) != RESET)
    {
        if (GPIO_ReadInputDataBit(GPIOx, GPIO_Pin) == Bit_RESET)
        {
            switch (menuNumber)
            {
            case MENU_START:
                stageScreen();
                stateScreen = SCR_PAGE;
                break;
            case MENU_BGM:
                bgmScreen();
                stateScreen = SCR_BGM;
                break;
            }
        }
        EXTI_ClearITPendingBit(EXTI_Line);
    }
}

void mainScreen(void)
{
    char *MENU_TEXT[MENU_COUNT] = {"Game Start", "Bluetooth"};
    LCD_Clear(WHITE);

    for (int i = 0; i < MENU_COUNT; i++)
    {
        LCD_ShowString(START_TEXT_X, START_TEXT_Y + TEXT_SIZE * i, MENU_TEXT[i], BLACK, WHITE);
    }
    LCD_ShowString(START_SELECTOR_X, START_SELECTOR_Y + TEXT_SIZE * menuNumber, ">>", BLACK, WHITE);
}