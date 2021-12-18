#include <string.h>
#include "nemo.h"
#include "game.h"

#define TRUE 1
#define FALSE 0

extern int stateScreen;
extern int stageNumber;

int current_xPoint = 1;
int current_yPoint = 1;

int boardState[BOARD_ROW_SIZE][BOARD_ROW_SIZE] = {
    FALSE,
};

void gameScreen(void)
{
    memset(boardState, 0, 100);
    int percent = checkCorrect();
    BluetoothSendInt(percent);
 
    LCD_Clear(WHITE);
    selectBlock(current_xPoint, current_yPoint);
    stateScreen = SCR_GAME;

    drawBoard();
    drawProblem();
}

void joystickGameScreen(uint32_t EXTI_Line, GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin)
{
    if (EXTI_GetITStatus(EXTI_Line) != RESET)
    {
        if (GPIO_ReadInputDataBit(GPIOx, GPIO_Pin) == Bit_RESET)
        {
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

void setBlockColor(void)
{
    if (boardState[current_yPoint - 1][current_xPoint - 1])
    {
        // Black -> White
        boardState[current_yPoint - 1][current_xPoint - 1] = FALSE;
        LCD_Fill(START_X + (current_xPoint - 1) * BOARD_UNIT, START_Y + (current_yPoint - 1) * BOARD_UNIT, START_X + (current_xPoint)*BOARD_UNIT, START_Y + (current_yPoint)*BOARD_UNIT, WHITE);
        LCD_DrawRectangle(START_X + (current_xPoint - 1) * BOARD_UNIT, START_Y + (current_yPoint - 1) * BOARD_UNIT, START_X + (current_xPoint)*BOARD_UNIT, START_Y + (current_yPoint)*BOARD_UNIT);
    }
    else
    {
        // White -> Black
        boardState[current_yPoint - 1][current_xPoint - 1] = TRUE;
        LCD_Fill(START_X + (current_xPoint - 1) * BOARD_UNIT, START_Y + (current_yPoint - 1) * BOARD_UNIT, START_X + (current_xPoint)*BOARD_UNIT, START_Y + (current_yPoint)*BOARD_UNIT, BLACK);
        LCD_DrawRectangle(START_X + (current_xPoint - 1) * BOARD_UNIT, START_Y + (current_yPoint - 1) * BOARD_UNIT, START_X + (current_xPoint)*BOARD_UNIT, START_Y + (current_yPoint)*BOARD_UNIT);
    }
}

void selectColorBlock(uint32_t EXTI_Line, GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin)
{
    if (EXTI_GetITStatus(EXTI_Line) != RESET)
    {
        if (GPIO_ReadInputDataBit(GPIOx, GPIO_Pin) == Bit_RESET)
        {
            setBlockColor();
            screenDelay();

            int percent = checkCorrect();
            BluetoothSendInt(percent);
            if (percent == 100)
            {
                stateScreen = SCR_CLEAR;
                printClearScreen();
            }
        }
        EXTI_ClearITPendingBit(EXTI_Line);
    }
}