---
type: hw-context
last-verified: 2026-11-17
firmware-commit: a1b2c3d
---

## 0. Identity
- MCU: STM32F303K8Tx
- Board: Nucleo-F303K8
- Core: Cortex-M4,
- Toolchain: STM32CubeIDE
- SDK: STM32CubeIDE v2.1.1, HAL, CubeMX-generated init
- RTOS: FreeRTOS 10.0.1
	- LIBRARY_MAX_SYSCALL_INTERRUPT_PRIORITY = 5
	- CMSIS v1
- Debug: ST-LINK, SWD
- Build: asserts on, no semihosting

## 1. Clocks & Power
- HSI RC: 8 MHz crystal
- System Clock Mux:
	- SYSCLK 8 MHz, 
	- HCLK 8 MHz, 
	- APB1/2 8 MHz
- Kernel clocks:  
	- USART3 = PCLK1 8 MHz

## 2. Memory
- Allocation: Dynamic / Static
- TOTAL_HEAP_SIZE: 3072 Bytes
- Management scheme: heap_4

## 3. Pin map (relevant buses only)
| Pin | AF  | Function | Net     | External        | Notes              |
| --- | --- | -------- | ------- | --------------- | ------------------ |
| PA3 | AF4 | I2C1_SCL | SCL_3V3 | BME280, LSM6DSO | 2.2k ext PU to 3V3 |
| PB9 | AF4 | I2C1_SDA | SDA_3V3 | "               | "                  |

## 4. Peripherals in use
- I2C1: 400 kHz FM+, 7-bit addr, POLLING (no DMA, no IRQ), HAL timeout 100 ms
- SPI1: master, mode 0, 12.5 MHz, DMA1 streams 3/4 via DMAMUX1 req 37
- USART3: 115200 8N1, IT-driven RX ring buffer

## 5. Interrupts
| IRQ | Preempt | Handler does | FreeRTOS API from ISR? |
|-----|---------|--------------|------------------------|
| SPI1 | 6 | clears flag, gives semaphore | yes (FromISR) |
NVIC grouping: 4 bits preempt, 0 sub

## 6. External devices
- BME280 @ 0x76 (7-bit), needs 2 ms after POR, chip ID 0x60
- LSM6DSO @ 0x6A, INT1 → PD11 (unused in firmware)

## 7. NOT present / NOT enabled
- No DMA or interrupts on I2C1
- No external SDRAM, no QSPI XIP
- No cache maintenance needed for I2C path (polling, buffers in D2)
- RTC, USB, Ethernet unused

## 8. Project lore / known traps
- Rev B silkscreen mislabels PA9/PA10; rev C is correct
- Sensor browns out if USB-powered with <500 mA source
- HAL_I2C_Init must run after GPIO AF config or first txn NACKs

## 9. Instrumentation & constraints
- Have: 100 MHz 2-ch scope, Logic 8, RTT. No bus analyzer.
- Can reflash freely. Cannot rework PCB (4 assembled units).