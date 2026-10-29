/*
 * it.c
 *
 *  Created on: 26-Oct-2026
 *      Author: adity
 */

#include "main.h"

extern UART_HandleTypeDef huart3;
void SysTick_Handler()
{
	HAL_IncTick();
	HAL_SYSTICK_IRQHandler();
}


// for every byte there will be 1 interrupt or due to error or due to completion of transmission
void USART3_IRQHandler(void)
{
	HAL_UART_IRQHandler(&huart3);
}
