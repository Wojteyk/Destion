/*
 * uart_connection.c
 *
 *  Created on: Nov 12, 2025
 *      Author: wojte
 */
#include "uart_connection.h"
#include <stdio.h>
#include "screen/ui.h"
#include "usart.h"

uint8_t transmit_it_flag = 0;

static float temperature = 0;
static float humidity = 0;
static uint8_t pcState = 0;

static char txData[16];

void Uart_parseData(char* line){

	if(sscanf(line, "T:%f;H:%f", &temperature, &humidity) == 2)
	{
		Ui_UpdateDHTData(temperature, humidity);
	}
	else if(sscanf(line, "PC:%hhu", &pcState) == 1)
	{
		Ui_UpadatePcState(pcState);
	}
}

void Uart_sendPcState(uint8_t pcState)
{
	snprintf(txData, sizeof(txData), "PC:%s\r\n", pcState ? "On" : "Off");

	if(!transmit_it_flag){
		transmit_it_flag = 1;
		HAL_UART_Transmit_IT(&huart1, (uint8_t*)txData, strlen(txData));
	}
}

void Uart_synchornizePcState()
{
	snprintf(txData, sizeof(txData), "PC:?\r\n");

	if(!transmit_it_flag){
		transmit_it_flag = 1;
		HAL_UART_Transmit_IT(&huart1, (uint8_t*)txData, strlen(txData));
	}
}
