#include "nemo.h"

int stateScreen = SCR_MAIN;

#define PROBLEM_MAX_X 10
#define PROBLEM_MAX_Y 3

// void Delay(int n)
// {
//   time_t current = clock();
//   while (clock() - current < n)
//     ;
// }

int main(void)
{
  configure();

  LCD_Init();
  LCD_Clear(WHITE);

  // mainScreen();

  gameScreen();

  while (1)
  {
  }
}