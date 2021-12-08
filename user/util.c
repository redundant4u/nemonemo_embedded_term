#include <time.h>

void Delay(int ms)
{
  time_t current = clock();
  while (clock() - current < ms);
}