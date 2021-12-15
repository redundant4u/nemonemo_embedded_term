#include "stm32f10x.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_rcc.h"
#include "stm32f10x_exti.h"
#include "stm32f10x_usart.h"
#include "stm32f10x_adc.h"
#include "stm32f10x_dma.h"
#include "stm32f10x_tim.h"
#include "core_cm3.h"
#include "misc.h"
#include "lcd.h"
#include "touch.h"

#define UP      (uint16_t) 0x0020
#define LEFT    (uint16_t) 0x0008
#define DOWN    (uint16_t) 0x0004
#define RIGHT   (uint16_t) 0x0010

#define STAGE_MAX 6

#define MAINSCREEN_TEXT_SIZE        20

#define SCREEN_DISPLAY  0
#define SCREEN_CLEAR    1


// stateScreen
enum { SCR_MAIN = 0, SCR_PAGE, SCR_GAME, SCR_BGM };

// config.c
void configure();

// handler.c
void EXTI2_IRQHandler(void);
void EXTI3_IRQHandler(void);
void EXTI4_IRQHandler(void);
void EXTI9_5_IRQHandler(void);
void EXTI15_10_IRQHandler(void);

// mainScreen.c
void joystickMainScreen(uint32_t EXTI_Line, GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin);
void selectMainScreen(uint32_t EXTI_Line, GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin);
void clearMainScreenArrow(int clearNumber);
void drawMainScreenArrow(void);
void mainScreen(int mode);

// stageScreen.c
void joystickStageScreen(uint32_t EXTI_Line, GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin);
void selectStageScreen(uint32_t EXTI_Line, GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin);
void clearStageScreen(void);
void stageScreen(int mode);
void selectBlock(int xPast, int yPast);
void drawBoard(void);
void drawProblem(void);

// gameScreen.c
void joystickGameScreen(uint32_t EXTI_Line, GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin);
void selectGameScreen(uint32_t EXTI_Line, GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin);
void gameScreen(void);

// bgm.c
void bgmStart(void);

// util.c
void screenDelay(void);
void backScreen(uint32_t EXTI_Line, GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin);