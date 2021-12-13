#include "stm32f10x.h"
#include "bgm.h"
#include "util.h"

uint32_t Music = 0;
uint32_t Sound = 0;

void bgmStart(int number)
{
    switch (number)
    {
    case SUPER_MARIO_UNDERGROUND:
    {
        int *notes = undergroundBGM();
        while(1)
        {
            for (int i = 0; i < 51; i++)
            {
                Music = notes[i];

                if(notes[i] != REST)
                {
                    for(int j = 0; i < 700000; j++) {}
                    Music = REST;
                } else {
                    for(int j = 0; j < 300000; j++) {}
                    Music = REST;
                    for(int j = 0; j < 300000; j++) {}
                }
            }
        }
        // break;
    }
    }
}

int* undergroundBGM(void)
{
    static int notes[] = {
        SOL, SOL, MI, MI, PA, PA, REST,
        SOL, SOL, MI, MI, PA, PA, REST,
        DO, DO, PA, PA, RA_SHARP, RA_SHARP, REST,
        DO, DO, PA, PA, RA_SHARP, RA_SHARP, REST,
        RA_SHARP, RA, SOL_SHARP, SOL,
        RA_SHARP, RA, RE_SHARP, RE, SOL_SHARP,
        SOL, DO, SI, RA_SHARP, PA, MI, RE_SHARP, REST,
        RA_SHARP, PA_SHARP, PA, MI, RE_SHARP, REST
    };

    return notes;
}