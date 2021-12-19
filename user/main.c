#include "nemo.h"

// 현재 스크린 위치 표시
int stateScreen = SCR_MAIN;

int main(void)
{
  // 모듈 사용을 위한 초기화
  configure();

  // LCD 초기화
  LCD_Init();
  LCD_Clear(WHITE);

  // 메인 스크린 표시
  mainScreen(SCREEN_DISPLAY);

  // 상시 음악 재생
  while (1)
  {
    bgmStart();
  }
}