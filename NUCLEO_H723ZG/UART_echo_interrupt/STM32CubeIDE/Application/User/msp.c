/*
 * msp.c
 *
 *  Created on: 26-Oct-2026
 *      Author: adity
 */
#include "main.h"


// low level processor specific initialization.
void HAL_MspInit()
{
	// set priority grouping
	HAL_NVIC_SetPriorityGrouping(NVIC_PRIORITYGROUP_4);

	// enable system exceptions proccessor specific system control block
	SCB->SHCSR |= (0x7 << 16);	// enabled system fault, memory fault, bus fault

	// configure priority for exceptions
	// memory management priority 0 i.e highest priority
	HAL_NVIC_SetPriority(MemoryManagement_IRQn, 0,0);
	HAL_NVIC_SetPriority(BusFault_IRQn, 0,0);
	HAL_NVIC_SetPriority(UsageFault_IRQn, 0,0);
}

void HAL_UART_MspInit(UART_HandleTypeDef *huart)
{
	GPIO_InitTypeDef gpio_uart;
	// here we will do low level initialization
	// enable clock
	__HAL_RCC_USART3_CLK_ENABLE();
	__HAL_RCC_GPIOD_CLK_ENABLE();

	//do pin muxing PD8
	gpio_uart.Pin = GPIO_PIN_8;
	gpio_uart.Mode = GPIO_MODE_AF_PP;
	gpio_uart.Pull = GPIO_PULLUP;
	gpio_uart.Speed = GPIO_SPEED_FREQ_LOW;
	gpio_uart.Alternate = GPIO_AF7_USART3;

	HAL_GPIO_Init(GPIOD, &gpio_uart);

	gpio_uart.Pin = GPIO_PIN_9;
	HAL_GPIO_Init(GPIOD, &gpio_uart);

	// enable IRQ and set priority
	HAL_NVIC_EnableIRQ(USART3_IRQn);
	HAL_NVIC_SetPriority(USART3_IRQn, 15, 0);

}
