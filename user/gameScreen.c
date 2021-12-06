#include "nemo.h"

#define BOARD_END_X 210
#define BOARD_END_Y 280

#define BOARD_UNIT 16
#define BOARD_ROW_SIZE 10

#define PROBLEM_MAX_X 10
#define PROBLEM_MAX_Y 3

#define PROBLEM_UP_PADDING 5
#define PROBLEM_LEFT_PADDING 40

extern int stateScreen;

int START_X = BOARD_END_X - BOARD_UNIT * BOARD_ROW_SIZE;
int START_Y = BOARD_END_Y - BOARD_UNIT * BOARD_ROW_SIZE;

int current_xPoint = 1;
int current_yPoint = 1;

void gameScreen(void)
{
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
            case GPIO_Pin_4:
                //Right
                current_xPoint++;
                break;
            case GPIO_Pin_3:
                //Left
                current_xPoint--;
                break;
            case GPIO_Pin_5:
                //Up
                current_yPoint --;
                break;
            case GPIO_Pin_2:
                //Down
                current_yPoint ++;
                break;
            }
            if (current_xPoint > BOARD_ROW_SIZE)
                current_xPoint =1;
            if (current_xPoint < 1)
                current_xPoint = BOARD_ROW_SIZE;
            if (current_yPoint > BOARD_ROW_SIZE)
                current_yPoint =1;
            if (current_yPoint < 1)
                current_yPoint = BOARD_ROW_SIZE;
            selectBlock(xPast, yPast);
        }
        EXTI_ClearITPendingBit(EXTI_Line);
    }
}

void selectBlock(int xPast, int yPast)
{
  LCD_Fill(START_X + (xPast-1)*BOARD_UNIT, START_Y + (yPast-1)*BOARD_UNIT, START_X + (xPast)*BOARD_UNIT, START_Y + (yPast)*BOARD_UNIT, WHITE);
  LCD_Fill(START_X + (current_xPoint-1)*BOARD_UNIT, START_Y + (current_yPoint-1)*BOARD_UNIT, START_X + (current_xPoint)*BOARD_UNIT, START_Y + (current_yPoint)*BOARD_UNIT, RED);
  LCD_DrawRectangle(START_X + (xPast-1)*BOARD_UNIT, START_Y + (yPast-1)*BOARD_UNIT, START_X + (xPast)*BOARD_UNIT, START_Y + (yPast)*BOARD_UNIT);
  LCD_DrawRectangle(START_X + (current_xPoint-1)*BOARD_UNIT, START_Y + (current_yPoint-1)*BOARD_UNIT, START_X + (current_xPoint)*BOARD_UNIT, START_Y + (current_yPoint)*BOARD_UNIT);
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
        {0, 3, 3}
    };

    for (int x = 0; x < PROBLEM_MAX_X; x++)
    {
        for (int y = 0; y < PROBLEM_MAX_Y; y++)
        {
            if (problem_up[x][y] != 0)
                LCD_ShowNum(
                    START_X + PROBLEM_UP_PADDING + (BOARD_UNIT * x),
                    START_Y - (BOARD_UNIT * 3) + (BOARD_UNIT * y),
                    problem_up[x][y], 1, BLACK, WHITE
                );
        }
    }

    // NOTE: LCD_ShowNum의 y값이 256 이상되면 오버 플로우가 일어나는거 같음
    for (int x = 0; x < PROBLEM_MAX_X; x++)
    {
        for (int y = 0; y < PROBLEM_MAX_Y; y++)
        {
            if (problem_left[x][y] != 0)
                LCD_ShowNum(START_X - PROBLEM_LEFT_PADDING + (BOARD_UNIT * y),
                START_Y + (BOARD_UNIT * x),
                problem_left[x][y], 1, BLACK, WHITE
            );
        }
    }
}