#include "nemo.h"
#include "bgm.h"

int bgmNumber = SUPER_MARIO_UNDERGROUND;
extern int stateScreen;

void joystickBGMScreen(uint32_t EXTI_Line, GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin)
{
    if (EXTI_GetITStatus(EXTI_Line) != RESET)
    {
        if (GPIO_ReadInputDataBit(GPIOx, GPIO_Pin) == Bit_RESET)
        {
            switch (GPIO_Pin)
            {
            case GPIO_Pin_5: // Up
                bgmNumber--;
                break;
            case GPIO_Pin_2: // Down
                bgmNumber++;
                break;
            }
            bgmNumber = (bgmNumber + BGM_COUNT) % BGM_COUNT;
            bgmScreen();
        }
        EXTI_ClearITPendingBit(EXTI_Line);
    }
}

void selectBGMScreen(uint32_t EXTI_Line, GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin)
{
    if (EXTI_GetITStatus(EXTI_Line) != RESET)
    {
        if (GPIO_ReadInputDataBit(GPIOx, GPIO_Pin) == Bit_RESET)
        {
            switch (bgmNumber)
            {
            case 0:
                bgmStart(0);
                break;
            }
        }
        EXTI_ClearITPendingBit(EXTI_Line);
    }
}

void bgmScreen(void)
{
    char *BGM_LIST = {"Super Mario Dungeon"};
    LCD_Clear(WHITE);

    for(int i = 0; i < 1; i++)
    {
        LCD_ShowString(START_TEXT_X, START_TEXT_Y + TEXT_SIZE * i, BGM_LIST[i], BLACK, WHITE);
    }
    LCD_ShowString(START_SELECTOR_X, START_SELECTOR_Y + TEXT_SIZE * bgmNumber, ">>", BLACK, WHITE);
}