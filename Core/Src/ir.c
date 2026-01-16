#include "ir.h"
#include "main.h"
#include <stdbool.h>

extern TIM_HandleTypeDef htim1;

static const uint8_t IR_cmd_turn_on[] = {0, 0, 0, 0,
                                        0, 0, 0, 0,
                                        1, 1, 1, 1,
                                        0, 1, 1, 1,
                                        0, 0, 0, 0,
                                        0, 0, 0, 0,
                                        1, 1, 1, 1,
                                        1, 1, 1, 1};

static const uint8_t IR_cmd_turn_off[] = {0, 0, 0, 0,
                                        0, 0, 0, 0,
                                        1, 1, 1, 1,
                                        0, 1, 1, 1,
                                        1, 0, 0, 0,
                                        0, 0, 0, 0,
                                        0, 1, 1, 1,
                                        1, 1, 1, 1};                                    

static const size_t dataSize = 32;

static void mark(uint16_t us);

static void space(uint16_t us);

static void sendBit(uint8_t bit);

static void sendDataSequence(const uint8_t* dataTosend);

void mark(uint16_t us)
{
	 __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_1, 730);
    delay_us(us);
    __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_1, 0);
}

void space(uint16_t us)
{
	 __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_1, 0);
	delay_us(us);
}

void sendBit(uint8_t bit)
{
	mark(550);
	if(bit) space(1600);
	else space(550);
}

void sendDataSequence(const uint8_t* dataTosend)
{
	__disable_irq();
	mark(9000);
	space(4500);

	for(int i = 0; i < dataSize; i++)
	{
		sendBit(dataTosend[i]);
	}

	mark(500);
	space(0);
	__enable_irq();
}

void IR_turnOnLight(bool value)
{
    if(value)
    {
        sendDataSequence(IR_cmd_turn_on);
    }
    else
    {
        sendDataSequence(IR_cmd_turn_off);
    }
}

void delay_us(uint32_t us)
{
    uint32_t startTick = DWT->CYCCNT;
    uint32_t cyclesPerUs = SystemCoreClock / 1000000;
    uint32_t delayTicks = us * cyclesPerUs;

    while ((DWT->CYCCNT - startTick) < delayTicks);
}