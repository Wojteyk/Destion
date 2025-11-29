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


void RTC_getTime();

void RTC_setTime(uint8_t hours, uint8_t minutes, uint8_t seconds);
