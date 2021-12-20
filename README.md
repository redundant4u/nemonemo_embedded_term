# nemonemo_embedded_term
Nonogram Game Project using STM32 Board

# Overview
- Board: STM32F107VCT6
- Module
    - 3.2" TFT LCD
    - Joystick(on board)
    - Button(on board)
    - Buzzer
    - Bluetooth(FB755AC)
- IDE: [IAR Embedded Workbench for Arm](https://www.iar.com/kr/products/architectures/arm/iar-embedded-workbench-for-arm/)
- [Interrupt handler](https://github.com/redundant4u/nemonemo_embedded_term/blob/master/user/handler.c)
    - Timer handler for buzzer and delay method
    - USART2 handler for bluetooth commnuication
    - EXTI handler for joystick, button input
- Diagram
    <img src="https://user-images.githubusercontent.com/38307839/146780691-545e3c98-d0c7-48e4-a41d-2eca9a2f87cd.png" alt="diagram"/>
- Preview
    <img src="https://user-images.githubusercontent.com/38307839/146781554-4f6874dc-ac79-4190-970a-2b73b60ab880.png" alt="preview" />