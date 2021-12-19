#include <string.h>
#include "nemo.h"
#include "game.h"

#define TRUE 1
#define FALSE 0

extern int stateScreen;
extern int stageNumber;

// 사용자 좌표(x, y) 위치 표시
int current_xPoint = 1;
int current_yPoint = 1;

// 사용자가 그린 네모네모로직 boardState 표시
// 네모네모로직 문제 정답과 비교하기 위한 변수
int boardState[BOARD_ROW_SIZE][BOARD_ROW_SIZE] = {
    FALSE,
};

// gameScreen 그리기 함수
void gameScreen(void)
{
    // gameScreen 페이지로 올 때 마다 사용자의 boardState 초기화
    memset(boardState, 0, 100);

    // 현재 문제 완성률 데이터를 보내기 위한 블루투스 부분
    int percent = checkCorrect();
    BluetoothSendInt(percent);
 
    LCD_Clear(WHITE);
    selectBlock(current_xPoint, current_yPoint);
    stateScreen = SCR_GAME;

    drawBoard();
    drawProblem();
}

// gameScreen용 조이스틱 동작 함수
void joystickGameScreen(uint32_t EXTI_Line, GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin)
{
    if (EXTI_GetITStatus(EXTI_Line) != RESET)
    {
        if (GPIO_ReadInputDataBit(GPIOx, GPIO_Pin) == Bit_RESET)
        {
            // 사용자가 컨트롤한 조이스틱 방향에 따라 current_xPoint, current_yPoint 갱신 후
            // 해당 위치에 빨간색으로 표시하여 사용자가 시각적으로 알아볼 수 있기 위한 표시
            int xPast = current_xPoint;
            int yPast = current_yPoint;

            switch (GPIO_Pin)
            {
            case RIGHT:
                current_xPoint++;
                break;
            case LEFT:
                current_xPoint--;
                break;
            case UP:
                current_yPoint--;
                break;
            case DOWN:
                current_yPoint++;
                break;
            }

            if (current_xPoint > BOARD_ROW_SIZE)
                current_xPoint = 1;
            if (current_xPoint < 1)
                current_xPoint = BOARD_ROW_SIZE;
            if (current_yPoint > BOARD_ROW_SIZE)
                current_yPoint = 1;
            if (current_yPoint < 1)
                current_yPoint = BOARD_ROW_SIZE;

            selectBlock(xPast, yPast);
        }
        EXTI_ClearITPendingBit(EXTI_Line);
    }
}

// 사용자가 현재 위치한 좌표에 빨간색으로 표시하는 함수
void selectBlock(int xPast, int yPast)
{
    if (boardState[yPast - 1][xPast - 1])
    {
        LCD_Fill(
            START_X + (xPast - 1) * BOARD_UNIT,
            START_Y + (yPast - 1) * BOARD_UNIT,
            START_X + (xPast)*BOARD_UNIT,
            START_Y + (yPast)*BOARD_UNIT,
            BLACK);
    }
    else
    {
        LCD_Fill(
            START_X + (xPast - 1) * BOARD_UNIT,
            START_Y + (yPast - 1) * BOARD_UNIT,
            START_X + (xPast)*BOARD_UNIT,
            START_Y + (yPast)*BOARD_UNIT,
            WHITE);
    }

    LCD_Fill(
        START_X + (current_xPoint - 1) * BOARD_UNIT,
        START_Y + (current_yPoint - 1) * BOARD_UNIT,
        START_X + (current_xPoint)*BOARD_UNIT,
        START_Y + (current_yPoint)*BOARD_UNIT,
        RED);
    LCD_DrawRectangle(
        START_X + (xPast - 1) * BOARD_UNIT,
        START_Y + (yPast - 1) * BOARD_UNIT,
        START_X + (xPast)*BOARD_UNIT,
        START_Y + (yPast)*BOARD_UNIT);
    LCD_DrawRectangle(
        START_X + (current_xPoint - 1) * BOARD_UNIT,
        START_Y + (current_yPoint - 1) * BOARD_UNIT,
        START_X + (current_xPoint)*BOARD_UNIT,
        START_Y + (current_yPoint)*BOARD_UNIT);
}

// 사용자가 정답 표시를 위한 함수
// 정답 버튼 클릭 시(S1 Button) 흰색에서 검은색으로 변경 혹은 그 반대
void setBlockColor(void)
{
    // 정답 표시 해제
    if (boardState[current_yPoint - 1][current_xPoint - 1])
    {
        // Black -> White
        boardState[current_yPoint - 1][current_xPoint - 1] = FALSE;
        LCD_Fill(START_X + (current_xPoint - 1) * BOARD_UNIT, START_Y + (current_yPoint - 1) * BOARD_UNIT, START_X + (current_xPoint)*BOARD_UNIT, START_Y + (current_yPoint)*BOARD_UNIT, WHITE);
        LCD_DrawRectangle(START_X + (current_xPoint - 1) * BOARD_UNIT, START_Y + (current_yPoint - 1) * BOARD_UNIT, START_X + (current_xPoint)*BOARD_UNIT, START_Y + (current_yPoint)*BOARD_UNIT);
    }
    // 정답 표시
    else
    {
        // White -> Black
        boardState[current_yPoint - 1][current_xPoint - 1] = TRUE;
        LCD_Fill(START_X + (current_xPoint - 1) * BOARD_UNIT, START_Y + (current_yPoint - 1) * BOARD_UNIT, START_X + (current_xPoint)*BOARD_UNIT, START_Y + (current_yPoint)*BOARD_UNIT, BLACK);
        LCD_DrawRectangle(START_X + (current_xPoint - 1) * BOARD_UNIT, START_Y + (current_yPoint - 1) * BOARD_UNIT, START_X + (current_xPoint)*BOARD_UNIT, START_Y + (current_yPoint)*BOARD_UNIT);
    }
}

// gameScreen용 버튼 동작 함수
void selectColorBlock(uint32_t EXTI_Line, GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin)
{
    if (EXTI_GetITStatus(EXTI_Line) != RESET)
    {
        if (GPIO_ReadInputDataBit(GPIOx, GPIO_Pin) == Bit_RESET)
        {
            setBlockColor(); // 사용자 정답 표시를 위한 함수
            delayScreen(20); // 버튼 디바운싱을 위한 systick delay

            // 사용자가 버튼을 누를 때 마다 네모네모로직 문제 완성률을 휴대폰으로 갱신
            int percent = checkCorrect();
            BluetoothSendInt(percent);

            // 문제 100% 완성률이면 clear 문자 표시
            if (percent == 100)
            {
                stateScreen = SCR_CLEAR;
                clearScreen();
            }
        }
        EXTI_ClearITPendingBit(EXTI_Line);
    }
}