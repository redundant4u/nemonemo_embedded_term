#include "nemo.h"

void RCC_ConfigureBluetooth(void)
{
    // NOTE : move to config
    /* UART TX/RX port clock enable */
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
    /* USART clock enable */
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE);
    /* Alternate Function IO clock enable */
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);
}

void GPIO_ConfigureBluetooth(void)
{
    // NOTE : move to config
    GPIO_InitTypeDef GPIO_InitStructure;

    /* UART1 pin setting */
    // TX
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_Init(GPIOA, &GPIO_InitStructure);

    // RX
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD;
    GPIO_Init(GPIOA, &GPIO_InitStructure);

    /* UART2 pin setting */
    // TX
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_Init(GPIOA, &GPIO_InitStructure);

    // RX
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD;
    GPIO_Init(GPIOA, &GPIO_InitStructure);
}

void USART1_Init(void)
{
    USART_InitTypeDef USART1_InitStructure;
    // Enable the USART1 peripheral
    USART_Cmd(USART1, ENABLE);
    USART1_InitStructure.USART_BaudRate = 28800;
    USART1_InitStructure.USART_WordLength = USART_WordLength_8b;
    USART1_InitStructure.USART_StopBits = USART_StopBits_1;
    USART1_InitStructure.USART_Parity = USART_Parity_No;
    USART1_InitStructure.USART_Mode = (USART_Mode_Rx | USART_Mode_Tx);
    USART1_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
    USART_Init(USART1, &USART1_InitStructure);
    // Enable the USART1 RX interrupts using the function 'USART_ITConfig' and the argument value 'Receive Data register not empty interrupt'
    USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);
}

void USART2_Init(void)
{
    USART_InitTypeDef USART2_InitStructure;
    USART_Cmd(USART2, ENABLE);
    USART2_InitStructure.USART_BaudRate = 9600;
    USART2_InitStructure.USART_WordLength = USART_WordLength_8b;
    USART2_InitStructure.USART_StopBits = USART_StopBits_1;
    USART2_InitStructure.USART_Parity = USART_Parity_No;
    USART2_InitStructure.USART_Mode = (USART_Mode_Rx | USART_Mode_Tx);
    USART2_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
    USART_Init(USART2, &USART2_InitStructure);
    USART_ITConfig(USART2, USART_IT_RXNE, ENABLE);
}

void NVIC_ConfigureBluetooth(void)
{
    NVIC_InitTypeDef NVIC_InitStructure;
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
    // UART1
    NVIC_EnableIRQ(USART1_IRQn);
    NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);
    // UART2
    NVIC_EnableIRQ(USART2_IRQn);
    NVIC_InitStructure.NVIC_IRQChannel = USART2_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);
}

void USART1_IRQHandler(void)
{
    uint16_t data;
    while (USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET)
        ;

    data = (unsigned char)USART_ReceiveData(USART1);
    USART_SendData(USART2, data);
    USART_ClearITPendingBit(USART1, USART_IT_RXNE);
}

void USART2_IRQHandler(void)
{
    uint16_t data;
    while (USART_GetFlagStatus(USART2, USART_FLAG_TXE) == RESET)
        ;

    data = (unsigned char)USART_ReceiveData(USART2);
    USART_SendData(USART1, data);
    USART_ClearITPendingBit(USART2, USART_IT_RXNE);
}

void sendDataUART2(uint16_t data)
{
    /* Wait till TC is set */
    while ((USART1->SR & USART_SR_TC) == 0)
        ;
    USART_SendData(USART1, data);
}

void BluetoothSendString(char *str, int length)
{
    for (int i = 0; i < length - 1; i++)
    {
        while (USART_GetFlagStatus(USART2, USART_FLAG_TXE) == RESET)
            ;
        uint16_t data = str[i];
        USART_SendData(USART2, data);
    }
}

void BluetoothSendInt(int num)
{
    char str[10];              // 변환한 문자열을 저장할 배열
    sprintf(str, "%d\n", num); // %d를 지정하여 정수를 문자열로 저장

    for (int i = 0; i < str[i] != 0; i++)
    {
        while (USART_GetFlagStatus(USART2, USART_FLAG_TXE) == RESET)
            ;
        uint16_t data = str[i];
        USART_SendData(USART2, data);
    }
}

void bluetoothSetting(void)
{
    // Set Bluetooth Config
    char msgSetName[] = "AT+BTNAME=NemoLogic\r";
    char msgSetKey[] = "AT+BTKEY=1234\r";
    char msgScan[] = "AT+BTSCAN\r";
    // BluetoothSendString(msgSetName, sizeof(msgSetName));
    // BluetoothSendString(msgSetKey, sizeof(msgSetKey));
    BluetoothSendString(msgScan, sizeof(msgScan));
}

void initBluetooth(void)
{
    SystemInit();
    RCC_ConfigureBluetooth();
    GPIO_ConfigureBluetooth();
    USART1_Init();
    USART2_Init();
    NVIC_ConfigureBluetooth();
    bluetoothSetting();
}