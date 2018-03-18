/**
 * @file ASA_UARTS.h
 * @author LiYu
 * @date 2018.03.06
 * @brief ASA_UARTS functions prototype.
 */

#ifndef __ASA_UARTS_H__
#define __ASA_UARTS_H__

#include "../rev_uart.h"
#include <inttypes.h>

enum uarts_status {
    status_header, ///< get header
    status_uid,    ///< get uid
    status_wradd,  ///< decode W/R and address
    status_bytes,  ///< get byte
    status_data,   ///< get data if in write mode
    status_chksum, ///< check the chksum of the packet is correct or wrong
    status_done    ///< check the chksum of the packet is correct or wrong
};

/**
 * @brief The decoder of uart. It will be call by uarts_decode_buf_step. And You
 *        can use the UartDecoder.status to discribe the status of UartDecoder,
 *        then do the corresponding motion in your code.
 */
struct UartDecoder {
    enum uarts_status status;
    uint8_t uid;
    uint8_t wr;
    uint8_t address;
    uint8_t bytes;
    uint8_t data[10];
};

typedef struct UartDecoder UartDecoder_t;

/**
 * @brief The decoder of uart. It will be call by uarts_decode_buf_step. And You
 *        can use the UartDecoder.status to discribe the status of UartDecoder,
 *        then do the corresponding motion in your code.
 */
UartDecoder_t UartDecoder;

/**
 * @brief Handle the RX, it will get data from RX and put into BufIn,
 *        or do nothing when BufIn is full.
 */
void uarts_rx_handle();

/**
 * @brief Handle the TX, it will send data in BufOut to TX,
 *        or do nothing when BufOut is null.
 */
void uarts_tx_handle();

// Defines of return value of uarts_decode_buff_step
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
 *        UartDecoder.status is status_header. It should put in main of slave
 *        device.
 * 
 * NOTE This function will call global variable "UartDecoder"
 */
uint8_t uarts_decode_buf_step();

#endif /* __ASA_UARTS_H__ */
