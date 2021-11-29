#include "nemo.h"

void Delay(int n)
{
  time_t current = clock();
  while (clock() - current < n)
    ;
}

int main(void)
{
	configure();

  LCD_Init();
  LCD_Clear(WHITE);

  stageScreen();

  while (1)
  {
  }
}