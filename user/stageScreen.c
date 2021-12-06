#include "nemo.h"

int stageNumber = 0;
extern int stateScreen;

void joystickStageScreen(uint32_t EXTI_Line, GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin)
{
    if (EXTI_GetITStatus(EXTI_Line) != RESET)
    {
        if (GPIO_ReadInputDataBit(GPIOx, GPIO_Pin) == Bit_RESET)
        {
            switch (GPIO_Pin)
            {
                // TODO :: dsdfsdfsd
                // NOTE : dsfsdff
            case GPIO_Pin_4:
                //Right
                stageNumber++;
                break;
            case GPIO_Pin_3:
                //Left
                stageNumber--;
                break;
            case GPIO_Pin_5:
                //Up
                stageNumber -= 3;
                break;
            case GPIO_Pin_2:
                //Down
                stageNumber += 3;
                break;
            }
            if (stageNumber >= STAGE_MAX)
                stageNumber -= STAGE_MAX;
            if (stageNumber < 0)
                stageNumber += STAGE_MAX;
            stageScreen();
        }
        EXTI_ClearITPendingBit(EXTI_Line);
    }
}

void selectStageScreen(uint32_t EXTI_Line, GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin)
{
    if (EXTI_GetITStatus(EXTI_Line) != RESET)
    {
        if (GPIO_ReadInputDataBit(GPIOx, GPIO_Pin) == Bit_RESET)
        {
            switch (stageNumber)
            {
            case 0:
              gameScreen();
              stateScreen = SCR_GAME;
              break;
              /*
            case 1:
            case 2:
            case 3:
            case 4:
            case 5:
            */
            }
        }
        EXTI_ClearITPendingBit(EXTI_Line);
    }
}

void stageScreen(void)
{
    int PointX[3] = {20, 90, 170};
    int PointY[2] = {120, 190};
    int lineLength = 50;

    int StageSel[6][2] = {{0, 0}, {1, 0}, {2, 0}, {0, 1}, {1, 1}, {2, 1}};

    LCD_Clear(WHITE);
    LCD_ShowString(STAGE_PAGE1_X, STAGE_PAGE1_Y, "PAGE 1", BLACK, WHITE);
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 2; j++)
        {
            //LCD_DrawRectangle(PointX[i], PointY[j], PointX[i]+lineLength, PointY[j]+lineLength);
            LCD_Fill(PointX[i], PointY[j], PointX[i] + lineLength, PointY[j] + lineLength, GREEN);
        }
    }
    LCD_Fill(PointX[StageSel[stageNumber][0]], PointY[StageSel[stageNumber][1]], PointX[StageSel[stageNumber][0]] + lineLength, PointY[StageSel[stageNumber][1]] + lineLength, BLUE);
}