/*
 * uart_connection.h
 *
 *  Created on: Nov 12, 2025
 *      Author: wojte
 */

#pragma once

#include "usart.h"

/**
 * @brief Flag indicating if a UART transmission is currently in progress.
 * @details This flag is set when HAL_UART_Transmit_IT is called and cleared
 * in the UART transmit complete callback. It prevents starting a new transmission
 * while a previous one is ongoing.
 */
extern uint8_t transmit_it_flag;

/**
 * @brief Parses a data line received over UART.
 * @details The input string should be in the correct format.
 * This function extracts the data values and updates the UI.
 *
 * @param line Null-terminated string containing the sensor data.
 */
void Uart_parseData(char* line);

/**
 * @brief Sends the current PC state over UART.
 * @details This function formats the PC state as a string ("PC:On" or "PC:Off")
 * and transmits it using HAL_UART_Transmit_IT. It will only start the transmission
 * if no previous transmission is in progress.
 *
 * @param state The current PC state, where 0 = Off, 1 = On.
 */
void Uart_sendPcState(uint8_t pcState);

/**
 * @brief Requests the current PC state to synchronize status.
 * @details This function initiates a non-blocking UART transmission sending
 * a query command ("PC:?") to the host. It checks the internal busy flag
 * to ensure no other transmission is currently in progress before sending.
 */
void Uart_synchornizePcState(void);

/**
 * @brief Requests the current system time from the host.
 * @details This function initiates a non-blocking UART transmission sending
 * a query command ("TIME:?") to the host. It utilizes HAL_UART_Transmit_IT
 * and respects the internal transmission flag to prevent data collision.
 */
void Uart_SynchronizeTime(void);

/**
 * @brief Sends the current light state over UART.
 * @details This function formats the light state as a string ("L:On" or "L:Off")
 * and transmits it using HAL_UART_Transmit_IT. It will only start the transmission
 * if no previous transmission is in progress.
 *
 * @param state The current L state, where 0 = Off, 1 = On.
 */
void Uart_sendLightState(uint8_t lightState);
