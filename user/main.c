#include "nemo.h"

int stateScreen = SCR_MAIN;

int main(void)
{
  configure();

  LCD_Init();
  LCD_Clear(WHITE);

  mainScreen();

  while (1)
  {
    bgmStart();
  }
}