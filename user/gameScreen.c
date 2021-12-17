#include "nemo.h"

#define BOARD_END_X 210
#define BOARD_END_Y 270

#define BOARD_UNIT 16
#define BOARD_ROW_SIZE 10

#define PROBLEM_MAX_X 10
#define PROBLEM_MAX_Y 3

#define PROBLEM_UP_PADDING 5
#define PROBLEM_LEFT_PADDING 40

#define TRUE 1
#define FALSE 0

extern int stateScreen;
extern int stageNumber;

int START_X = BOARD_END_X - BOARD_UNIT * BOARD_ROW_SIZE;
int START_Y = BOARD_END_Y - BOARD_UNIT * BOARD_ROW_SIZE;

int current_xPoint = 1;
int current_yPoint = 1;

int boardState[BOARD_ROW_SIZE][BOARD_ROW_SIZE] = {
    FALSE,
};

int correct1[BOARD_ROW_SIZE][BOARD_ROW_SIZE] = {
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0}};
/*
        {0, 0, 0, 1, 0, 0, 0, 1, 1, 1},
        {0, 0, 1, 0, 0, 0, 0, 0, 1, 1},
        {0,1,1,0,0,1,0,0,0,1},
        {1,1,1,0,0,0,0,0,0,0},
        {1,1,1,1,0,0,0,0,0,0},
        {1,1,1,1,1,1,0,0,0,0},
        {1,1,1,1,1,1,1,0,0,0},
        {0,1,1,1,0,1,1,0,0,1},
        {0,0,1,1,1,1,1,0,1,1},
        {0,0,0,1,1,1,0,1,1,1}
};*/

void gameScreen(void)
{
    memset(boardState, 0, 100);
    // char msgGameStart[] = "0\n";
    // BluetoothSendString(msgGameStart, sizeof(msgGameStart));
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
    if (boardState[xPast - 1][yPast - 1])
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

void drawBoard(void)
{
    for (int i = START_X; i < BOARD_END_X; i += BOARD_UNIT)
    {
        for (int j = START_Y; j < BOARD_END_Y; j += BOARD_UNIT)
        {
            LCD_DrawRectangle(i, j, i + BOARD_UNIT, j + BOARD_UNIT);
        }
    }
}

void drawProblem(void)
{
    int problem_up[PROBLEM_MAX_X][PROBLEM_MAX_Y] = {
        {0, 0, 4},
        {0, 0, 6},
        {0, 0, 8},
        {0, 1, 6},
        {0, 2, 2},
        {0, 1, 5},
        {0, 0, 3},
        {0, 1, 1},
        {0, 2, 2},
        {0, 3, 3},
    };

    int problem_left[PROBLEM_MAX_X][PROBLEM_MAX_Y] = {
        {0, 1, 3},
        {0, 1, 2},
        {2, 1, 1},
        {0, 0, 3},
        {0, 0, 4},
        {0, 0, 6},
        {0, 0, 7},
        {3, 2, 1},
        {0, 5, 2},
        {0, 3, 3}};

    for (int x = 0; x < PROBLEM_MAX_X; x++)
    {
        for (int y = 0; y < PROBLEM_MAX_Y; y++)
        {
            if (problem_up[x][y] != 0)
            {
                LCD_ShowNum(
                    START_X + PROBLEM_UP_PADDING + (BOARD_UNIT * x),
                    START_Y - (BOARD_UNIT * 3) + (BOARD_UNIT * y),
                    problem_up[x][y], 1, BLACK, WHITE);
            }
        }
    }

    // NOTE: LCD_ShowNum의 y값이 256 이상되면 오버 플로우가 일어나는거 같음
    for (int x = 0; x < PROBLEM_MAX_X; x++)
    {
        for (int y = 0; y < PROBLEM_MAX_Y; y++)
        {
            if (problem_left[x][y] != 0)
            {
                LCD_ShowNum(
                    START_X - PROBLEM_LEFT_PADDING + (BOARD_UNIT * y),
                    START_Y + (BOARD_UNIT * x),
                    problem_left[x][y], 1, BLACK, WHITE);
            }
        }
    }
}

int checkCorrect()
{
    int correctCount = 0;
    for (int i = 0; i < BOARD_ROW_SIZE; i++)
    {
        for (int j = 0; j < BOARD_ROW_SIZE; j++)
        {
            if (boardState[i][j] == correct1[i][j])
                correctCount++;
        }
    }
    return correctCount;
}

void setBlockColor(void)
{
    if (boardState[current_xPoint - 1][current_yPoint - 1])
    {
        // Black -> White
        boardState[current_xPoint - 1][current_yPoint - 1] = FALSE;
        LCD_Fill(START_X + (current_xPoint - 1) * BOARD_UNIT, START_Y + (current_yPoint - 1) * BOARD_UNIT, START_X + (current_xPoint)*BOARD_UNIT, START_Y + (current_yPoint)*BOARD_UNIT, WHITE);
        LCD_DrawRectangle(START_X + (current_xPoint - 1) * BOARD_UNIT, START_Y + (current_yPoint - 1) * BOARD_UNIT, START_X + (current_xPoint)*BOARD_UNIT, START_Y + (current_yPoint)*BOARD_UNIT);
    }
    else
    {
        // White -> Black
        boardState[current_xPoint - 1][current_yPoint - 1] = TRUE;
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
