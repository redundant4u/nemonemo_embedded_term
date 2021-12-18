#define BOARD_UNIT      16
#define BOARD_ROW_SIZE  10

#define PROBLEM_MAX_X   10
#define PROBLEM_MAX_Y   3

#define BOARD_END_X     210
#define BOARD_END_Y     270

#define PROBLEM_UP_PADDING      5
#define PROBLEM_LEFT_PADDING    40

#define START_X         (BOARD_END_X - BOARD_UNIT * BOARD_ROW_SIZE)
#define START_Y         (BOARD_END_Y - BOARD_UNIT * BOARD_ROW_SIZE)

typedef struct _Game {
    int correct[BOARD_ROW_SIZE][BOARD_ROW_SIZE];
    int problem_up[PROBLEM_MAX_X][PROBLEM_MAX_Y];
    int problem_left[PROBLEM_MAX_X][PROBLEM_MAX_Y];
} Game;