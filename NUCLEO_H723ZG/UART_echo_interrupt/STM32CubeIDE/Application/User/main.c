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

#define SIZE 100
#define TRUE 1
#define FALSE 0

uint8_t rcvd_data;
uint8_t data_buffer[SIZE];
uint32_t count = 0;
uint8_t reception_complete =  FALSE;
UART_HandleTypeDef huart3;


int main()
{
	HAL_Init();
	//SystemClockConfig();		// application dependent
	USART3_Init();

	while(1)
	{
		if(reception_complete != TRUE)
		{
			HAL_UART_Receive_IT(&huart3, (uint8_t *)&rcvd_data, 1);
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

// for every 1 byte received a callback is generated
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
	if(rcvd_data == '\r' || rcvd_data == '\n')
	{
		reception_complete = TRUE;
		data_buffer[count] = '\r';
		HAL_UART_Transmit_IT(&huart3, data_buffer, SIZE);
	}
	else if(count < SIZE)
	{
		data_buffer[count++] = rcvd_data;
	}
}


void Error_handler()
{
	while(1);
}
