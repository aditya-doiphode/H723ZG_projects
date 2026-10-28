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
uint8_t convert_to_capital(uint8_t data);

//char *tx_data = "Aditya\r\n";

UART_HandleTypeDef huart3;

int main()
{
	HAL_Init();
	//SystemClockConfig();		// application dependent
	USART3_Init();
//	if(HAL_UART_Transmit(&huart3, (uint8_t *)tx_data, (uint16_t)strlen(tx_data), HAL_MAX_DELAY) != HAL_OK)
//	{
//		Error_handler();
//	}

	uint8_t rcvd_data;
	uint8_t data_buffer[100];
	uint32_t count = 0;
	while(1)
	{
		/* receiving data byte by byte over UART */
		HAL_UART_Receive(&huart3, &rcvd_data, 1, HAL_MAX_DELAY);
		if(rcvd_data == '\r' || rcvd_data == '\n')
		{
			HAL_UART_Transmit(&huart3, data_buffer, count, HAL_MAX_DELAY);
			HAL_UART_Transmit(&huart3, (uint8_t *)"\r\n", 2, HAL_MAX_DELAY);
			count = 0;
		}
		else if(count < sizeof(data_buffer))
		{
			data_buffer[count++] = convert_to_capital(rcvd_data);
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


/* convert to upper case */
uint8_t convert_to_capital(uint8_t data)
{
	if(data >= 'a' && data <= 'z')
	{
		data = data - 32;
	}
	return data;
}


void Error_handler()
{
	while(1);
}
