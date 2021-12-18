
#include "nemo.h"

#define STAGE_PADDING_SIZE  50
#define STAGE_PAGE1_X       100
#define STAGE_PAGE1_Y       70

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
            case RIGHT:
                stageNumber++;
                break;
            case LEFT:
                stageNumber--;
                break;
            case UP:
                stageNumber -= 3;
                break;
            case DOWN:
                stageNumber += 3;
                break;
            }

            if (stageNumber >= STAGE_MAX) stageNumber -= STAGE_MAX;
            if (stageNumber < 0)          stageNumber += STAGE_MAX;

            stageScreen(SCREEN_DISPLAY);
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
            stageScreen(SCREEN_CLEAR);
            gameScreen();
            stateScreen = SCR_GAME;

            screenDelay();

        }
        EXTI_ClearITPendingBit(EXTI_Line);
    }
}

void stageScreen(int mode)
{
    int pointX[3] = { 20, 90, 170 };
    int pointY[2] = { 120, 190 };
    int textColor[2] = { BLACK, WHITE };
    int stageColor[2] = { GREEN, WHITE };
    int selectColor[2] = { BLUE, WHITE };

    int stageSel[6][2] = { {0, 0}, {1, 0}, {2, 0}, {0, 1}, {1, 1}, {2, 1} };

    LCD_ShowString(STAGE_PAGE1_X, STAGE_PAGE1_Y, "PAGE 1", textColor[mode], WHITE);
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 2; j++)
        {
            LCD_Fill(
                pointX[i],
                pointY[j],
                pointX[i] + STAGE_PADDING_SIZE, pointY[j] + STAGE_PADDING_SIZE,
                stageColor[mode]
            );
        }
    }
    LCD_Fill(
        pointX[stageSel[stageNumber][0]],
        pointY[stageSel[stageNumber][1]],
        pointX[stageSel[stageNumber][0]] + STAGE_PADDING_SIZE,
        pointY[stageSel[stageNumber][1]] + STAGE_PADDING_SIZE,
        selectColor[mode]
    );
}