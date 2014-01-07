// System.c - "Системные функции"

#include <stdint.h>
//#include "stm32f4_discovery.h"

#include "System.h"

/**
  * @brief  Inserts a delay time.
  * @param  nTime: specifies the delay time length, in 1 ms.
  * @retval None
  */
void delay_ms ( uint32_t nTime )
{
    volatile uint32_t counter = nTime * 4000;
    while (counter--);
}
