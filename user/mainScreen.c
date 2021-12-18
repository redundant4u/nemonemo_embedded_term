#include "nemo.h"

#define MENU_COUNT 2
#define START_TEXT_X 70
#define START_TEXT_Y 100
#define START_ARROW_X 40
#define START_ARROW_Y 100

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
            case UP:
                menuNumber--;
                clearMainScreenArrow(menuNumber + 1);
                break;
            case DOWN:
                menuNumber++;
                clearMainScreenArrow(menuNumber - 1);
                break;
            }
            menuNumber = (menuNumber + MENU_COUNT) % MENU_COUNT;
            
            drawMainScreenArrow();
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
                mainScreen(SCREEN_CLEAR);
                stageScreen(SCREEN_DISPLAY);
                stateScreen = SCR_PAGE;

                delayScreen(20);
                break;
            }
        }
        EXTI_ClearITPendingBit(EXTI_Line);
    }
}

void clearMainScreenArrow(int clearNumber)
{
    LCD_Fill(
        START_ARROW_X, START_ARROW_Y + MAINSCREEN_TEXT_SIZE * clearNumber,
        START_ARROW_X + 16, START_ARROW_Y + MAINSCREEN_TEXT_SIZE * clearNumber + 16,
        WHITE
    );
}

void drawMainScreenArrow(void)
{
    LCD_ShowString(START_ARROW_X, START_ARROW_Y + MAINSCREEN_TEXT_SIZE * menuNumber, ">>", BLACK, WHITE);
}

void mainScreen(int mode)
{
    char *MENU_TEXT[MENU_COUNT] = {"Game Start", "Bluetooth"};
    int color[2] = { BLACK, WHITE };

    for (int i = 0; i < MENU_COUNT; i++)
    {
        LCD_ShowString(START_TEXT_X, START_TEXT_Y + MAINSCREEN_TEXT_SIZE * i, MENU_TEXT[i], color[mode], WHITE);
    }
    LCD_ShowString(START_ARROW_X, START_ARROW_Y + MAINSCREEN_TEXT_SIZE * menuNumber, ">>", color[mode], WHITE);
}