# Destion - STM32F411 Control System

## Overview

**Destion** is an embedded control system built on the **STM32F411CEUX** microcontroller. It serves as the local control interface for an intelligent home automation system, providing real-time control of hardware components including LCD display, infrared remote handling, RTC timekeeping, and UART communication.

This project is designed as the **local control hub** that works in conjunction with the [**ESP32 WiFi Module**](https://github.com/Wojteyk/Destion_esp32_firmware) to create a complete IoT ecosystem.

## Key Features

### Hardware Control
- **LCD Display Interface** - 1.8" SPI TFT display with custom UI rendering
- **Infrared (IR) Control** - Remote control input handling for light control
- **Real-Time Clock (RTC)** - Precise timekeeping with synchronization capabilities
- **UART Communication** - Serial communication bridge for sensor data and commands
- **GPIO Management** - Digital input/output control for relays and switches
- **DMA Support** - Efficient data transfers for SPI operations

### User Interface
- **Graphical UI System** - Multi-page interface (Home, Settings pages)
- **Custom Font Rendering** - Optimized font display on LCD
- **Real-time Display Updates** - Responsive UI with minimal latency

### Communication
- **UART Protocol** - Bi-directional communication with other devices
- **Time Synchronization** - Automatic RTC synchronization support
- **Command Processing** - Line-based command reception and handling

## Project Structure

```
destion/
├── Core/
│   ├── Inc/              # Header files
│   │   ├── main.h
│   │   ├── fsm_controls.h       # Finite State Machine control logic
│   │   ├── uart_connection.h    # UART communication
│   │   ├── ir.h                 # Infrared control
│   │   ├── rtc.h                # Real-time clock
│   │   ├── tim.h                # Timer configuration
│   │   ├── spi.h, dma.h         # SPI and DMA drivers
│   │   └── screen/              # Display subsystem
│   │       ├── lcd.h            # LCD driver
│   │       ├── ui.h             # UI framework
│   │       ├── ui_hw.h          # UI hardware interface
│   │       └── font.h           # Font definitions
│   └── Src/              # Implementation files
│       ├── main.c
│       ├── fsm_controls.c
│       ├── uart_connection.c
│       ├── ir.c, rtc.c, tim.c
│       └── screen/
│           ├── lcd.c
│           ├── ui.c, ui_hw.c
│           └── font.c
├── Drivers/             # STM32 HAL and CMSIS libraries
│   ├── STM32F4xx_HAL_Driver/
│   └── CMSIS/
├── Startup/            # MCU startup code
└── Debug/              # Build artifacts
```

## Hardware Specifications

| Component | Details |
|-----------|---------|
| **MCU** | STM32F411CEUX (ARM Cortex-M4, 100 MHz) |
| **Flash** | 512 KB |
| **RAM** | 128 KB |
| **Display** | 1.8" SPI TFT LCD |
| **Communication** | UART, SPI |
| **Peripherals** | RTC, Timers, GPIO, DMA |

## Building and Flashing

### Prerequisites
- STM32CubeIDE or compatible ARM toolchain

### Build Instructions

**Using STM32CubeIDE:**
```bash
# Open the project in STM32CubeIDE
# Project → Build Project
```

### Flashing the Device

```bash
# Using STM32CubeProgrammer
STM32_Programmer_CLI -c port=SWD -d destion.elf -v
```

## Configuration

### System Clock
- **Frequency**: 100 MHz
- **HSE**: 25 MHz external oscillator

### Peripheral Configurations
- **UART**: 115200 baud, 8N1
- **SPI**: 18 MHz for LCD communication
- **RTC**: LSE 32.768 kHz (external crystal)

## Integration with ESP32 WiFi Module

This project communicates with the **ESP32 WiFi Configuration Module** through UART. The combined system architecture:

```
┌─────────────────────────────────────────────────────────────┐
│                      Cloud (Firebase)                       │
└──────────────────────┬──────────────────────────────────────┘
                       │
      ┌────────────────────────────────┐
      │   ESP32 WiFi Configuration     │
      │   - WiFi Provisioning          │
      │   - Firebase Cloud Integration │
      │   - IoT Protocol Handling      │
      └────────┬─────────────┬─────────┘
               │ UART        │
      ┌────────▼─────────────▼─────────┐
      │  Destion (STM32F411)            │
      │  - Local Hardware Control       │
      │  - Display & User Interface     │
      │  - Real-time Processing        │
      │  - IR Remote & RTC              │
      └─────────────────────────────────┘
```

### Communication Protocol
- **Interface**: UART (115200 baud)
- **Format**: Line-based ASCII commands
- **Purpose**: 
  - Destion sends sensor/state data to ESP32
  - ESP32 sends cloud commands/updates to Destion
  - Destion syncs RTC with ESP32 time data

For detailed communication specifications, see the [ESP32 WiFi README](https://github.com/Wojteyk/Destion_esp32_firmware).

## Related Projects

- **[ESP32 WiFi Module](https://github.com/Wojteyk/Destion_esp32_firmware)** - IoT connectivity and cloud integration
- **Mobile App** - Flutter-based companion application

---

**Last Updated**: January 2026  
