#include "nemo.h"

#define START_TEXT_X 50
#define START_TEXT_Y 50
#define TEXT_SIZE 40

extern int stateScreen;

// 문제 100% 완성률일시, 보여지는 clear 문자 표시
void clearScreen(){
    LCD_Clear(WHITE);
    LCD_ShowString(START_TEXT_X, START_TEXT_Y + TEXT_SIZE * 2,"Congratulation !!!", BLACK, WHITE);
    LCD_ShowString(START_TEXT_X, START_TEXT_Y + TEXT_SIZE * 3,"CLICK TO QUIT", BLACK, WHITE);
}

// clearScreen용 버튼 동작 함수
void selectClearScreen(uint32_t EXTI_Line, GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin)
{
    if (EXTI_GetITStatus(EXTI_Line) != RESET)
    {
        if (GPIO_ReadInputDataBit(GPIOx, GPIO_Pin) == Bit_RESET)
        {
            // 문제 100% 완성률이면 stageScreen으로 이동
            if (checkCorrect())
            {
                LCD_Clear(WHITE);
                stageScreen(SCREEN_DISPLAY);
                stateScreen = SCR_PAGE;
                BluetoothSendInt(-1);
            }
        }
        EXTI_ClearITPendingBit(EXTI_Line);
    }
}