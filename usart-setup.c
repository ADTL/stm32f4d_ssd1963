#include "stm32f4xx.h"
#include "stm32f4xx_gpio.h"
#include "stm32f4xx_rcc.h"
#include "stm32f4xx_usart.h"
#include <stdio.h>
#include "xprintf.h"
#include "usart-setup.h"

/***************************************************************************//**
 * @brief  Print "Hello, World!" via USART1
 ******************************************************************************/
void USART_Setup(void)
{
    char nullator;
    SetupClock();
    SetupUSART();

    xdev_out(USART1_out);
    xdev_in(USART1_in);
    
    /* Output a message on Hyperterminal using printf function */
    xputs("USART1 enable\r\n");
}

/***************************************************************************//**
 * @brief Setup clocks
 ******************************************************************************/
void SetupClock()
{
      /* Enable USART1 and GPIOB clock                                        */
      RCC_APB2PeriphClockCmd (RCC_APB2Periph_USART1, ENABLE);
      RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);

}
/***************************************************************************//**
 * @brief Init USART1
 ******************************************************************************/
void SetupUSART()
{
	GPIO_InitTypeDef  GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;

	/* Configure USART1 Rx (PB7) as af                         */
	GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_7;
	GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);

	/* Configure USART1 Tx (PB6) as af            */
	GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_6;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
	GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_AF;
	GPIO_Init(GPIOB, &GPIO_InitStructure);

	/* Setup AF fuctions for Tx, Rx pins */
	GPIO_PinAFConfig(GPIOB, GPIO_PinSource6, GPIO_AF_USART1);
	GPIO_PinAFConfig(GPIOB, GPIO_PinSource7, GPIO_AF_USART1);

	/* USART1 configured as follow:
		- BaudRate = 115200 baud
		- Word Length = 8 Bits
		- One Stop Bit
		- No parity
		- Hardware flow control disabled (RTS and CTS signals)
		- Receive and transmit enabled
		- USART Clock disabled
		- USART CPOL: Clock is active low
		- USART CPHA: Data is captured on the middle
		- USART LastBit: The clock pulse of the last data bit is not output to
						 the SCLK pin
	*/
	USART_InitStructure.USART_BaudRate            = 115200;
	USART_InitStructure.USART_WordLength          = USART_WordLength_8b;
	USART_InitStructure.USART_StopBits            = USART_StopBits_1;
	USART_InitStructure.USART_Parity              = USART_Parity_No ;
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode                = USART_Mode_Rx | USART_Mode_Tx;
	USART_Init(USART1, &USART_InitStructure);
	USART_Cmd(USART1, ENABLE);
}

void USART1_out(char c) {
	while (USART_GetFlagStatus(USART1, USART_FLAG_TC) == RESET);
	USART_SendData(USART1, (uint8_t) c);
}
char USART1_in(void) {
	while (USART_GetFlagStatus(USART1, USART_FLAG_RXNE) == RESET);
	return USART_ReceiveData(USART1);
}
