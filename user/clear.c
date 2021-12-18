#include "nemo.h"

#define START_TEXT_X 50
#define START_TEXT_Y 50
#define TEXT_SIZE 40

extern int stateScreen;

void printClearScreen(){
    LCD_Clear(WHITE);
    LCD_ShowString(START_TEXT_X, START_TEXT_Y,"congratulation !!!", GREEN, WHITE);
    LCD_ShowString(START_TEXT_X, START_TEXT_Y + TEXT_SIZE*4,"CLICK TO QUIT", GREEN, WHITE);
}

void selectClearScreen(uint32_t EXTI_Line, GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin)
{
    if (EXTI_GetITStatus(EXTI_Line) != RESET)
    {
        if (GPIO_ReadInputDataBit(GPIOx, GPIO_Pin) == Bit_RESET)
        {
            if (checkCorrect())
            {
                LCD_Clear(WHITE);
                stageScreen(SCREEN_DISPLAY);
                stateScreen = SCR_PAGE;
            }
        }
        EXTI_ClearITPendingBit(EXTI_Line);
    }
}