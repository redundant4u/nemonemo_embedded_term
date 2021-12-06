#include "nemo.h"

#define BOARD_END_X 230
#define BOARD_END_Y 310

#define BOARD_UNIT 16
#define BOARD_ROW_SIZE 10

int start_x = BOARD_END_X - BOARD_UNIT * BOARD_ROW_SIZE;
int start_y = BOARD_END_Y - BOARD_UNIT * BOARD_ROW_SIZE;

int stateScreen = SCR_MAIN;

int xPoint =1;
int yPoint =1;

void selectBlock(int xPast, int yPast);

void Delay(int n)
{
  time_t current = clock();
  while (clock() - current < n)
    ;
}

void joystickGameScreen(uint32_t EXTI_Line, GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin)
{
    if (EXTI_GetITStatus(EXTI_Line) != RESET)
    {
        if (GPIO_ReadInputDataBit(GPIOx, GPIO_Pin) == Bit_RESET)
        {
            int xPast = xPoint;
            int yPast = yPoint;
            switch (GPIO_Pin)
            {
            case GPIO_Pin_4:
                //Right
                xPoint++;
                break;
            case GPIO_Pin_3:
                //Left
                xPoint--;
                break;
            case GPIO_Pin_5:
                //Up
                yPoint --;
                break;
            case GPIO_Pin_2:
                //Down
                yPoint ++;
                break;
            }
            if (xPoint > BOARD_ROW_SIZE)
                xPoint =1;
            if (xPoint < 1)
                xPoint = BOARD_ROW_SIZE;
            if (yPoint > BOARD_ROW_SIZE)
                yPoint =1;
            if (yPoint < 1)
                yPoint = BOARD_ROW_SIZE;
            selectBlock(xPast, yPast);
        }
        EXTI_ClearITPendingBit(EXTI_Line);
    }
}

void gameScreen()
{
  LCD_Clear(WHITE);
  selectBlock(xPoint, yPoint);
  stateScreen = SCR_GAME;
  for(int i=start_x; i<BOARD_END_X; i+=BOARD_UNIT)
  {
    for(int j = start_y; j<BOARD_END_Y; j+=BOARD_UNIT)
    {
      LCD_DrawRectangle(i, j, i+BOARD_UNIT, j+BOARD_UNIT);
    }
  }
  
  LCD_ShowNum(start_x - 8, start_y, 1, 1, BLACK, WHITE);
  LCD_ShowNum(start_x + 5, start_y - 16, 5, 1, BLACK, WHITE);
}

void selectBlock(int xPast, int yPast){
  //TODO :: 선택된 칸 테두리 그리는 거 생각
  LCD_Fill(start_x + (xPast-1)*BOARD_UNIT, start_y + (yPast-1)*BOARD_UNIT, start_x + (xPast)*BOARD_UNIT, start_y + (yPast)*BOARD_UNIT, WHITE);
  LCD_Fill(start_x + (xPoint-1)*BOARD_UNIT, start_y + (yPoint-1)*BOARD_UNIT, start_x + (xPoint)*BOARD_UNIT, start_y + (yPoint)*BOARD_UNIT, RED);
  LCD_DrawRectangle(start_x + (xPast-1)*BOARD_UNIT, start_y + (yPast-1)*BOARD_UNIT, start_x + (xPast)*BOARD_UNIT, start_y + (yPast)*BOARD_UNIT);
  LCD_DrawRectangle(start_x + (xPoint-1)*BOARD_UNIT, start_y + (yPoint-1)*BOARD_UNIT, start_x + (xPoint)*BOARD_UNIT, start_y + (yPoint)*BOARD_UNIT);
}

int main(void)
{
  configure();

  LCD_Init();
  LCD_Clear(WHITE);

  mainScreen();

  while (1)
  {
  }
}