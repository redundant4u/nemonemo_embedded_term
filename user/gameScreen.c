#include "nemo.h"

#define BOARD_END_X 210
#define BOARD_END_Y 280

#define BOARD_UNIT 16
#define BOARD_ROW_SIZE 10

#define PROBLEM_MAX_X 10
#define PROBLEM_MAX_Y 3

#define PROBLEM_UP_PADDING 5
#define PROBLEM_LEFT_PADDING 40

int START_X = BOARD_END_X - BOARD_UNIT * BOARD_ROW_SIZE;
int START_Y = BOARD_END_Y - BOARD_UNIT * BOARD_ROW_SIZE;

void gameScreen(void)
{
    drawBoard();
    drawProblem();
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