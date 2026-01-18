#pragma once 

#include <stdint.h>

/**
 * @brief Transmits the IR command sequence to control the light.
 * * This function selects the appropriate pre-defined data sequence (ON or OFF)
 * and transmits it using the NEC IR protocol.
 * * @note This function is blocking and will disable interrupts for the duration 
 * of the transmission (~68ms) to ensure precise timing.
 * * @param value Control flag:
 * - 0: Transmit "Turn OFF" command.
 * - Non-zero (e.g., 1): Transmit "Turn ON" command.
 */
void IR_turnOnLight(uint8_t value);