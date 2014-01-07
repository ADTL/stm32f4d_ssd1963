/*-----------------------------------------------------------------------------
* Author: Boris Vinogradov(nis) : no111u3@gmail.com
* File: work.c
* Type: C code file
* Project: STM32F4D USB OTG
* 2013
*-----------------------------------------------------------------------------*/
/* includes */
#include "stm32f4xx.h"
#include "usart-setup.h"
#include "xprintf.h"
#include "fsmc.h"
#include "ssd1963_43.h"
#include "stm32f4xx_gpio.h"

void print_id(void)
{
    volatile char * WF43_COMMAND_ptr = ((char *)0x60000000);
    volatile char * WF43_DATA_ptr = ((char *)(0x60000000 + (1 << 16)));
    
    volatile int t;
    int x;
    
    GPIO_SetBits(GPIOA,GPIO_Pin_1);
    for(t=0;t<1000000;t++);
    GPIO_ResetBits(GPIOA,GPIO_Pin_1);
    for(t=0;t<10000;t++);
    GPIO_SetBits(GPIOA,GPIO_Pin_1);
    for(t=0;t<1000000;t++);
    xputs("Reading display id...\r\n");
    *WF43_COMMAND_ptr = 0xa1;
    x = *WF43_DATA_ptr;
    xprintf("Display ID: %x\r\n", x);
    x = *WF43_DATA_ptr;
    xprintf("Display ID: %x\r\n", x);
    x = *WF43_DATA_ptr;
    xprintf("Display ID: %x\r\n", x);
    x = *WF43_DATA_ptr;
    xprintf("Display ID: %x\r\n", x);
    x = *WF43_DATA_ptr;
    xprintf("Display ID: %x\r\n", x);
}

/* main work function */
void work(void) {
    volatile int t;
    USART_Setup();
    xputs("LCD SDD1963 Test\r\n");
    FSMC_Init();
    SSD1963_reset_init();
    print_id();
    SSD1963_init();
    xputs("Display inited\r\n");
    TFT_putChar(0, 0, 'X');
    for(t=0;t<1000000;t++);
    FULL_ON(0xff0000);
    for(t=0;t<1000000;t++);
    FULL_ON(0x00ff00);
    for(t=0;t<1000000;t++);
    FULL_ON(0x0000ff);
    for(t=0;t<1000000;t++);
    /* infinity loop */
    while (1);
}