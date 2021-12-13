#include "nemo.h"

int stateScreen = SCR_MAIN;

int main(void)
{
  configure();

  LCD_Init();
  LCD_Clear(WHITE);

  mainScreen();
  bgmStart(0);

  while (1)
  {
  }
}