#include "nemo.h"

void clearStageScreen(void)
{
  LCD_Fill(STAGE_PAGE1_X, STAGE_PAGE1_Y, STAGE_PAGE1_X + 16, STAGE_PAGE1_Y + 16, WHITE);
        int PointX[3] = {20, 90, 170};
        int PointY[2] = {120, 190};
        int lineLength = 50;

        for (int i = 0; i < 3; i++)
        {
          for (int j = 0; j < 2; j++)
          {
            LCD_Fill(PointX[i], PointY[j], PointX[i] + lineLength, PointY[j] + lineLength, WHITE);
          }
        }
}