/*
 * it.c
 *
 *  Created on: 26-Oct-2026
 *      Author: adity
 */

#include "stm32h7xx_hal.h"


void SysTick_Handler()
{
	HAL_IncTick();
	HAL_SYSTICK_IRQHandler();
}
