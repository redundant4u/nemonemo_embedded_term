#include "stm32f10x.h"
#include "bgm.h"

uint32_t Music = 0;
uint32_t Sound = 0;

void bgmStart(void)
{
  int notes[] = {
    MI, MI, MI, SHORT, MI, MI, MI, SHORT, MI, SOL, DO, RE, MI, LONG,
    PA, PA, PA, PA, PA, MI, MI, MI, MI, RE, RE, MI, RE, SHORT, SOL, SHORT,
    MI, MI, MI, SHORT, MI, MI, MI, SHORT, MI, SOL, DO, RE, MI, LONG,
    PA, PA, PA, PA, PA, MI, MI, MI, SOL, SOL, PA, RE, DO, LONG,
    
    LONG

    //SOL, RA, SOL, MI, HIGH_DO, RA, SOL, SOL, RA, SOL, RA, SOL, HIGH_DO, SI,
    //PA, SOL, PA, RE, SI, RA, SOL, SOL, RA, SOL, RA, SOL, RA, MI,
    //SOL, RA, SOL, MI, HIGH_DO, RA, SOL, SOL, RA, SOL, RA, SOL, HIGH_DO, SI,
    //PA, SOL, PA, RE, SI, RA, SOL, SOL, RA, SOL, RA, SOL, RE, HIGH_DO,
    //RA, RA, DO, RA, SOL, MI, SOL, PA, RA, SOL, PA, MI,
    //RE, MI, SOL, RA, SI, SI, SI, DO, DO, SI, RA, SOL, PA, RE
  };
            
  for (int i = 0; i < sizeof(notes) / sizeof(int); i++)
  {
    //screenDelay();
    if(notes[i] == LONG)
    {
      Music = REST;
      for(int j = 0; j < 2200000; j++) {}
    } else if(notes[i] == SHORT){
      Music = REST;
      for(int j = 0; j < 1000000; j++) {}
    } else {
      Music = notes[i];
      for(int j = 0; j < 600000; j++) {}
      Music = REST;
      for(int j = 0; j < 600000; j++) {}
    }
  }
}