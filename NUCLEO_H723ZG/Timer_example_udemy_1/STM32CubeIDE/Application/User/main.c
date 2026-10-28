/*
 * main.c
 *
 *  Created on: 26-Oct-2026
 *      Author: adity
 */

#include "stm32h7xx_hal.h"
#include "main.h"
#include "string.h"

void SystemClockConfig();
void USART3_Init();
void Error_handler();

char *tx_data = "Aditya\r\n";

UART_HandleTypeDef huart3;

int main()
{
	HAL_Init();
	//SystemClockConfig();		// application dependent
	USART3_Init();
	while(1)
	{
	if(HAL_UART_Transmit(&huart3, (uint8_t *)tx_data, (uint16_t)strlen(tx_data), HAL_MAX_DELAY) != HAL_OK)
	{
		Error_handler();
	}
	}

}

void SystemClockConfig()
{

}


// HIgh level peripheral initialization
void USART3_Init()
{
	huart3.Instance = USART3;	// give base  adddres available i.e offset
	huart3.Init.BaudRate = 115200;
	huart3.Init.WordLength = UART_WORDLENGTH_8B;
	huart3.Init.StopBits = UART_STOPBITS_1;
	huart3.Init.Parity = UART_PARITY_NONE;
	huart3.Init.HwFlowCtl = UART_HWCONTROL_NONE;
	huart3.Init.Mode = UART_MODE_TX_RX;
	huart3.Init.OverSampling = UART_OVERSAMPLING_16;

	// call init and pass the handle function
	if(HAL_UART_Init(&huart3) != HAL_OK)
	{
		Error_handler();
	}
}

void Error_handler()
{
	while(1);
}
