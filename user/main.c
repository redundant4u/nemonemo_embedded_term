#include "nemo.h"

int stateScreen = SCR_MAIN;

int main(void)
{
  configure();

  LCD_Init();
  LCD_Clear(WHITE);

  mainScreen(SCREEN_DISPLAY);

  while (1)
  {
    bgmStart();
  }
}