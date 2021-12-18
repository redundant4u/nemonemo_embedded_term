#include "game.h"
#include "lcd.h"

extern int stageNumber;
extern int boardState[BOARD_ROW_SIZE][BOARD_ROW_SIZE];
const Game game[3] = {
    { // 1. korea
        {
            {1,0,0,0,0, 0,0,0,0,0},
            {0,0,0,0,0, 0,0,0,0,0},
              {0,0,0,0,0, 0,0,0,0,0},
                {0,0,0,0,0, 0,0,0,0,0},
                  {0,0,0,0,0, 0,0,0,0,0},
                    {0,0,0,0,0, 0,0,0,0,0},
                      {0,0,0,0,0, 0,0,0,0,0},
                        {0,0,0,0,0, 0,0,0,0,0},
                          {0,0,0,0,0, 0,0,0,0,0},
                            {0,0,0,0,0, 0,0,0,0,0}
            //{0,0,0,1,0, 0,0,1,1,1},
            //{0,0,1,0,0, 0,0,0,1,1},
            //{0,1,1,0,0, 1,0,0,0,1},
            //{1,1,1,0,0, 0,0,0,0,0},
            //{1,1,1,1,0, 0,0,0,0,0},
            //{1,1,1,1,1, 1,0,0,0,0},
            //{1,1,1,1,1, 1,1,0,0,0},
            //{0,1,1,1,0, 1,1,0,0,1},
            //{0,0,1,1,1, 1,1,0,1,1},
            //{0,0,0,1,1, 1,0,1,1,1}
        },
        {
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
        },
        {
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
        }
    },
    {// 2.cherry
        {
            {0,0,0,0,0, 0,1,1,1,1},
            {0,0,0,0,0, 1,1,0,0,1},
            {0,0,0,0,1, 0,1,1,0,0},
            {0,0,0,1,1, 0,0,1,0,0},
            {0,0,1,0,0, 0,0,1,0,0},
            {0,1,1,1,0, 0,1,1,1,0},
            {1,0,0,1,1, 1,0,0,1,1},
            {1,0,1,1,1, 1,0,1,1,1},
            {1,1,1,1,0, 1,1,1,1,1},
            {0,1,1,0,0, 0,1,1,1,0},

        },
        {
            {0,0,3},
            {0,1,2},
            {0,2,3},
            {0,1,4},
            {0,2,2},
            {0,1,3},
            {3,1,2},
            {1,4,3}, 
            {0,1,5},
            {0,2,3}
        },
        {
            {0,0,4},
            {0,2,1},
            {0,1,2},
            {0,2,1},
            {0,1,1},
            {0,3,3},
            {1,3,2},
            {1,4,3}, 
            {0,4,5},
            {0,2,3}
        }
    },
    {//3. black cat
        {
            {0,0,1,0,1, 0,0,0,0,0},
            {0,1,1,1,1, 0,0,0,0,0},
            {1,0,1,1,1, 0,0,0,1,0},
            {1,1,1,1,1, 0,0,1,0,0},
            {0,1,1,1,0, 0,0,1,1,0},
            {0,0,1,1,1, 1,0,0,1,1},
            {0,0,1,1,1, 1,1,0,0,1},
            {0,1,1,1,1, 1,1,0,0,1},
            {0,1,1,0,1, 1,1,0,1,1},
            {1,1,0,1,1, 1,1,1,1,0}
        },
        {
            {0,2,1},
            {1,2,3},
            {0,0,9},
            {0,7,1},
            {0,4,5},
            {0,0,5},
            {0,0,4},
            {0,2,1},
            {1,2,2},
            {0,0,4}
        },
        {
            {0,1,1},
            {0,0,4},
            {1,3,1},
            {0,5,1},
            {0,3,2},
            {0,4,2},
            {0,5,1},
            {0,6,1},
            {2,3,2},
            {0,2,6}
        }
    }
};

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
    for (int x = 0; x < PROBLEM_MAX_X; x++)
    {
        for (int y = 0; y < PROBLEM_MAX_Y; y++)
        {
            if (game[stageNumber].problem_up[x][y] != 0)
                LCD_ShowNum(
                    START_X + PROBLEM_UP_PADDING + (BOARD_UNIT * x),
                    START_Y - (BOARD_UNIT * 3) + (BOARD_UNIT * y),
                    game[stageNumber].problem_up[x][y], 1, BLACK, WHITE);
        }
    }

    for (int x = 0; x < PROBLEM_MAX_X; x++)
    {
        for (int y = 0; y < PROBLEM_MAX_Y; y++)
        {
            if (game[stageNumber].problem_left[x][y] != 0)
                LCD_ShowNum(START_X - PROBLEM_LEFT_PADDING + (BOARD_UNIT * y),
                            START_Y + (BOARD_UNIT * x),
                            game[stageNumber].problem_left[x][y], 1, BLACK, WHITE);
        }
    }
}

int checkCorrect(void)
{
    int correctCount = 0;
    for (int i = 0; i < BOARD_ROW_SIZE; i++)
    {
        for (int j = 0; j < BOARD_ROW_SIZE; j++)
        {
            if (boardState[i][j] == game[stageNumber].correct[i][j])
                correctCount++;
        }
    }
    return correctCount;
}