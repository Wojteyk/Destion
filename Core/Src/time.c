/*
 * time.c
 *
 *  Created on: 29 lis 2025
 *      Author: wojte
 */
#include "time.h"

RTC_TimeTypeDef sTime;
RTC_DateTypeDef sDate;

void RTC_getTime()
{
	HAL_RTC_GetTime(&hrtc, &sTime, RTC_FORMAT_BIN);
	HAL_RTC_GetDate(&hrtc, &sDate, RTC_FORMAT_BIN);
}

void RTC_setTime(uint8_t hours, uint8_t minutes, uint8_t seconds)
{
	sTime.Hours = hours;
	sTime.Minutes = minutes;
	sTime.Seconds = seconds;
}
