#include "nemo.h"
#include "bgm.h"

// timer interrupt를 위한 전역 변수
uint32_t Music = 0;
uint32_t Sound = 0;

// 노래 재생 함수
void bgmStart(void)
{
  // 노래 음표 변수
  // SHORT: 짧게 쉬기
  // LONG: 길게 쉬기
  int notes[] = {
    MI, MI, MI, SHORT, MI, MI, MI, SHORT, MI, SOL, DO, RE, MI, LONG,
    PA, PA, PA, PA, PA, MI, MI, MI, MI, RE, RE, MI, RE, SHORT, SOL, SHORT,
    MI, MI, MI, SHORT, MI, MI, MI, SHORT, MI, SOL, DO, RE, MI, LONG,
    PA, PA, PA, PA, PA, MI, MI, MI, SOL, SOL, PA, RE, DO, LONG,
    
    LONG
  };

  // 노래 음표 갯수 만큼 반복 
  for (int i = 0; i < sizeof(notes) / sizeof(int); i++)
  {
    // delayScreen: 노래 음표마다 끊어서 연주하기 위해 delay interrupt 활용
    if(notes[i] == LONG)
    {
      Music = REST;
      delayScreen(100);
    } else if(notes[i] == SHORT){
      Music = REST;
      delayScreen(50);
    } else {
      Music = notes[i];
      delayScreen(20);
      Music = REST;
      delayScreen(20);
    }
  }
}