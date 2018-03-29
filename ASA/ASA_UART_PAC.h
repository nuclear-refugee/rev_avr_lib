/**
 * @file ASA_UARTPACK.h
 * @author LiYu
 * @date 2018.03.16
 * @brief The defines of ASA uart packet.
 */

#ifndef __ASA_UART_PAC_H__
#define __ASA_UART_PAC_H__

#define UART_HEADER 0xF0 ///< The HEADER of ASA_UART packet.
#define UART_WR_BIT 7

#include "../rev_uart.h"
#include <inttypes.h>


/**
 * @brief The state of UartDecoder.
 */
enum uart_state {
    state_header, ///< get header
    state_uid,    ///< get uid
    state_wradd,  ///< decode W/R and address
    state_bytes,  ///< get byte
    state_data,   ///< get data if in write mode
    state_chksum, ///< check the chksum of the packet is correct or wrong
    state_done    ///< check the chksum of the packet is correct or wrong
};

/**
 * @brief The state of UartDecoder.
 */
typedef enum uart_state uart_state_t;

/**
 * @brief The decoder of uart. It will be call by uart_decode_buf_step. And You
 *        can use the UartDecoder.state to discribe the state of UartDecoder,
 *        then do the corresponding motion in your code.
 */
struct UartDecoder {
    uart_state_t state;
    uint8_t uid;
    uint8_t wr;
    uint8_t address;
    uint8_t bytes;
    uint8_t data[10];
};

typedef struct UartDecoder UartDecoder_t;

/**
 * @brief The decoder of uart. It will be call by uart_decode_buf_step. And You
 *        can use the UartDecoder.state to discribe the state of UartDecoder,
 *        then do the corresponding motion in your code.
 */
extern UartDecoder_t UartDecoder;

/**
 * @brief Handle the RX, it will get data from RX and put into BufIn,
 *        or do nothing when BufIn is full.
 */
void uart_rx_handle();

/**
 * @brief Handle the TX, it will send data in BufOut to TX,
 *        or do nothing when BufOut is null.
 */
void uart_tx_handle();

// Defines of return value of uart_decode_buff_step
#define DECODE_OK    0
#define BUF_NULL     1
#define ERROR_HEADER 2
#define ERROR_UID    3
#define ERROR_WRADD  4
#define ERROR_BYTES  5
#define ERROR_DATA   6
#define ERROR_CHKSUM 7

/**
 * @brief It will decode BufIn and put the outcome in UartDecoder. You can
 *        know once decoding is done when return is DECODE_OK and
 *        UartDecoder.state is state_header. It should put in main of slave
 *        device.
 *
 * NOTE This function will call global variable "UartDecoder"
 */
uint8_t uart_decode_buf_step();

/**
 * @brief It will encode the args to asa_uart packet and put the packet into BufOut.
 */
uint8_t uart_encoder(uint8_t UID, uint8_t RW, uint8_t addr, uint8_t bytes, void *Data_p);

#endif /* __ASA_UART_PAC_H__ */
