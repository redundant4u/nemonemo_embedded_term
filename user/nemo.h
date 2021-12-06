#include "stm32f10x.h"
#include "core_cm3.h"
#include "misc.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_rcc.h"
#include "stm32f10x_usart.h"
#include "stm32f10x_adc.h"
#include "stm32f10x_dma.h"
#include "lcd.h"
#include "touch.h"
#include <time.h>

#define START_TEXT_X 70
#define START_TEXT_Y 100

#define START_SELECTOR_X 40
#define START_SELECTOR_Y 100

#define STAGE_PAGE1_X 100
#define STAGE_PAGE1_Y 70

#define STAGE_MAX 6

#define TEXT_SIZE 20
#define PADDING_SIZE 20


// stateScreen
enum { SCR_MAIN = 0, SCR_PAGE, SCR_GAME };

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
void mainScreen(void);
void gameScreen(void);

// stageScreen.c
void joystickStageScreen(uint32_t EXTI_Line, GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin);
void stageScreen(void);