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
        int notes[][2] = undergroundBGM();
        while(1)
        {
            for (int i = 0; i < sizeof(notes) / sizeof(notes[0]); i++)
            {
                Music = notes[i][0];
                delay(notes[i][1]);

                if(notes[i][0] != REST)
                {
                    Music = REST;
                }
            }
        }
        break;
    }
}

int* undergroundBGM(void)
{
    int notes[][2] = {
        { SOL, 500 }, { SOL, 500 }, { MI, 500 }, { MI, 500 }, { PA, 500 }, { PA, 500 }, { REST, 5000 },
        { SOL, 500 }, { SOL, 500 }, { MI, 500 }, { MI, 500 }, { PA, 500 }, { PA, 500 }, { REST, 5000 },
        { DO, 500 }, { DO, 500 }, { PA, 500 }, { PA, 500 }, { RA_SHARP, 500 }, { RA_SHARP, 500 }, { REST, 5000 },
        { DO, 500 }, { DO, 500 }, { PA, 500 }, { PA, 500 }, { RA_SHARP, 500 }, { RA_SHARP, 500 }, { REST, 5000 },
        { RA_SHARP, 400 }, { RA, 500 }, { SOL_SHARP, 500 }, { SOL, 500 },
        { RA_SHARP, 2000 }, { RA, 2000 }, { RE_SHARP, 2000 }, { RE, 2000 }, { SOL_SHARP, 2000 },
        { SOL, 500 }, { DO, 500 }, { SI, 500 }, { RA_SHARP, 500 }, { PA, 500 }, { MI, 500 }, { RE_SHARP, 500 }, { REST, 5000 },
        { RA_SHARP, 5000 }, { PA_SHARP, 5000 }, { PA, 500 }, { MI, 500, 500 }, { RE_SHARP, 500 }, { REST, 5000 }
    };

    return (int*) notes;
}