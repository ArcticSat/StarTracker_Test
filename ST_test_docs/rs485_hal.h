#ifndef RS485_HAL_H
#define RS485_HAL_H

#include <stdint.h>
#include <stddef.h>

// Define a dummy struct to satisfy the compiler
typedef struct  mss_uart_instance mss_uart_instance_t;

struct mss_uart_instance{
    /* CMSIS related defines identifying the UART hardware. */
//    UART_TypeDef *          hw_reg;     /*!< Pointer to UART registers. */
//    IRQn_Type               irqn;       /*!< UART's Cortex-M3 NVIC interrupt number. */
    uint32_t                baudrate;   /*!< Operating baud rate. */
    uint8_t                 lineconfig; /*!< Line configuration parameters. */
    uint8_t                 status;     /*!< Sticky line status. */

    /* transmit related info (used with interrupt driven transmit): */
    const uint8_t * tx_buffer;          /*!< Pointer to transmit buffer. */
    uint32_t        tx_buff_size;       /*!< Transmit buffer size. */
    uint32_t        tx_idx;             /*!< Index within transmit buffer of next byte to transmit.*/

};

extern mss_uart_instance_t g_mss_uart0;

// FUNCTION PROTOTYPES

void rs485_tx_enable(void);

void rs485_rx_enable(void);

void prvUARTSend(mss_uart_instance_t *pxUART, const uint8_t *pcBuffer, size_t xBufferLength);

void hal_uart_send(const uint8_t *data, uint16_t len);

int hal_uart_receive(uint8_t *data, uint16_t max_len, uint32_t timeout_ms);

#endif
