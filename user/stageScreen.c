
#include "nemo.h"

#define STAGE_PADDING_SIZE  50
#define STAGE_PAGE1_X       100
#define STAGE_PAGE1_Y       70

int stageNumber = 0; // 어느 스테이지를 선택하는지 알기위한 변수
extern int stateScreen;

// stageScreen용 조이스틱 동작 함수
void joystickStageScreen(uint32_t EXTI_Line, GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin)
{
    if (EXTI_GetITStatus(EXTI_Line) != RESET)
    {
        if (GPIO_ReadInputDataBit(GPIOx, GPIO_Pin) == Bit_RESET)
        {
            // 조이스틱 동작 마다 필요한 변수 조절 및 stage 이동 효과 표시하기
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

// stageScreen용 버튼 동작 함수
void selectStageScreen(uint32_t EXTI_Line, GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin)
{
    if (EXTI_GetITStatus(EXTI_Line) != RESET)
    {
        if (GPIO_ReadInputDataBit(GPIOx, GPIO_Pin) == Bit_RESET)
        {
            // stageNumber에 따라 해당하는 gameScreen 문제 페이지 이동 -> gameScreen에 extern int stageNumber 존재
            stageScreen(SCREEN_CLEAR);
            gameScreen();
            stateScreen = SCR_GAME;

            delayScreen(20); // 버튼 디바운싱을 위한 systick delay

        }
        EXTI_ClearITPendingBit(EXTI_Line);
    }
}

// stageScreen 그리기 함수
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