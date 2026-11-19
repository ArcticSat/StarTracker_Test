

# Hardware
## Components
- STM32f303k8 Nucleo
- Digilent PmodRS485
- ST16-RT Star Tracker
- Breadboard
- Connectors
	- jumpers for mcu -> Pmod
	- DB9 to jumpers for Pmod -> ST16: need to desolder from Iris EGSE


# CubeMX Setup

## System Core

### SYS
- Timebase source: TIM1

### GPIO

| Pin | Mode        | Parameters |
| --- | ----------- | ---------- |
| PA3 | GPIO_Output | RS485_DE   |
| PA4 | GPIO_Output | RS485_nRE  |
## Connectivity

### USART1
For RS485
- Mode: Asynchronous

| Pin  | Mode      | Parameters                 |
| ---- | --------- | -------------------------- |
| PA9  | USART1_TX |                            |
| PA10 | USART1_RX | DMA Enabled DMA1 Channel 5 |

### USART2
Virtual Com Port

| Pin  | Mode      | Parameters |
| ---- | --------- | ---------- |
| PA2  | USART1_TX | VCP_TX     |
| PA15 | USART1_RX | VCP_RX     |

## Middleware and Software

### FreeRTOS
- Interface: CMSIS_V1


# Wiring Pinout

## MCU-PmodRS485

| PmodRS485 Pin (J2) | Signal | Nucleo Pin | Notes                     |
| ------------------ | ------ | ---------- | ------------------------- |
| **1**              | `nRE`  | **A3**     | Active LOW to receive     |
| **2**              | `TxD`  | **D0**     | Pmod TX → STM32 RX        |
| **3**              | `RxD`  | **D1**     | Pmod RX ← STM32 TX        |
| **4**              | `DE`   | **A2**     | Active HIGH to transmit   |
| **5**              | `GND`  | **GND**    | Common ground             |
| **6**              | `VCC`  | **3.3V**   | Recommended per datasheet |

## Star Tracker

| Star Tracker Pin | Signal    | Pin                 |
| ---------------- | --------- | ------------------- |
| 1                | GND       | Common GND          |
| 2                | 12V       | 12V Supply          |
| 3                | RS485_1_A | Pmod Screw Terminal |
| 4                | RS485_0_A | Pmod Screw Terminal |
| 5                | GND       | Common GND          |
| 6                | GND       | Common GND          |
| 7                | RS485_1_B | Pmod Screw Terminal |
| 8                | RS485_0_B | Pmod Screw Terminal |
| 9                | 12V       | 12V Supply          |



## STM32CubeIDE Setup

Copied from CDH software to STM32 project
- nsp_slip.c and .h
- ST_16_driver.c and .h
- st16_test.c and .h

Made rs485_hal.c to map HAL_UART to PmodRS-485 pins and mss_uart
Commented out queue-related things in st16_test











