/*
 * time.h
 *
 *  Created on: 29 lis 2025
 *      Author: wojte
 */

#pragma once

#include "rtc.h"

extern RTC_TimeTypeDef sTime;
extern RTC_DateTypeDef sDate;

/**
 * @brief Retrieves the current time and date from the RTC peripheral.
 * @details Calls HAL_RTC_GetTime and HAL_RTC_GetDate to update the global
 * time and date structures with the latest values from the hardware.
 */
void RTC_getTime(void);

/**
 * @brief Sets the Real-Time Clock to the specified time.
 * @details Updates the hardware RTC registers with the new time settings
 * and immediately triggers a UI update to reflect the change on the screen.
 *
 * @param hours   The hour to set (0-23).
 * @param minutes The minute to set (0-59).
 * @param seconds The second to set (0-59).
 */
void RTC_setTime(uint8_t hours, uint8_t minutes, uint8_t seconds);
