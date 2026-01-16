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
static uint8_t lightState = 0;
static char txData[16];

void Uart_parseData(char* line){
	int h_temp, m_temp, s_temp;
	uint8_t  hours, minutes, seconds;

	if(sscanf(line, "T:%f;H:%f", &temperature, &humidity) == 2)
	{
		Ui_UpdateTempData(temperature, humidity);
	}
	else if(sscanf(line, "PC:%hhu", &pcState) == 1)
	{
		Ui_UpdatePcState(pcState);
	}
	else if(sscanf(line, "H%d:M%d:S%d", &h_temp, &m_temp, &s_temp) == 3)
	{
		hours = (uint8_t)h_temp;
		minutes = (uint8_t)m_temp;
		seconds = (uint8_t)s_temp;
		RTC_setTime(hours, minutes, seconds);
	}
	else if(sscanf(line, "L:%hhu", &lightState) == 1)
	{
		Ui_UpadateLightState(lightState);
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

void Uart_SynchronizeTime()
{
	snprintf(txData, sizeof(txData), "TIME:?\r\n");

	if(!transmit_it_flag){
		transmit_it_flag = 1;
		HAL_UART_Transmit_IT(&huart1, (uint8_t*)txData, strlen(txData));
	}
}

void Uart_sendLightState(uint8_t lightState)
{
	snprintf(txData, sizeof(txData), "L:%s\r\n", lightState ? "On" : "Off");

	if(!transmit_it_flag){
		transmit_it_flag = 1;
		HAL_UART_Transmit_IT(&huart1, (uint8_t*)txData, strlen(txData));
	}
}

