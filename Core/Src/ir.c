#include "ir.h"
#include "main.h"

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

/* --- Static Function Prototypes --- */

/**
 * @brief Generates the 38kHz carrier signal (Mark) for a specific duration.
 * * Sets the PWM duty cycle to ~33% (Compare value 730) to generate the IR burst.
 * * @param us Duration in microseconds.
 */
static void mark(uint16_t us);

/**
 * @brief Generates a Space (silence) for a specific duration.
 * * Sets the PWM duty cycle to 0% to stop the IR transmission.
 * * @param us Duration in microseconds.
 */
static void space(uint16_t us);

/**
 * @brief Transmits a single bit according to the NEC protocol timing.
 * * - Logic '1': 560us Mark + 1690us Space
 * - Logic '0': 560us Mark + 560us Space
 * * @param bit The bit value to send (0 or 1).
 */
static void sendBit(uint8_t bit);

/**
 * @brief Sends the entire IR data packet (Header + Data + Stop bit).
 * * This function enters a critical section (disables interrupts) to ensure
 * precise timing required by the IR protocol.
 * * @param dataTosend Pointer to the array of bits (0s and 1s) to transmit.
 */
static void sendDataSequence(const uint8_t* dataTosend);

/**
 * @brief Provides a blocking delay in microseconds with high precision.
 * * Uses the DWT Cycle Counter (Data Watchpoint and Trace). 
 * Ensure DWT is initialized in main.c before using this.
 * * @param us Number of microseconds to wait.
 */
static void delay_us(uint32_t us);

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

void IR_turnOnLight(uint8_t value)
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