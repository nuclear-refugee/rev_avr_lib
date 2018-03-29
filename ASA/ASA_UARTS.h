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

/******************************************************************************
 *  Decoder Section
 ******************************************************************************/
/**
 * @brief The state of UartDecoder.
 */
enum uarts_state {
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
typedef enum uarts_state uarts_state_t;

/**
 * @brief The decoder of uart. It will be call by uarts_decode_buf_step. And You
 *        can use the UartDecoder.state to discribe the state of UartDecoder,
 *        then do the corresponding motion in your code.
 */
struct UartDecoder {
    uarts_state_t state;
    uint8_t uid;
    uint8_t wr;
    uint8_t address;
    uint8_t bytes;
    uint8_t data[10];
};

typedef struct UartDecoder UartDecoder_t;

/**
 * @brief The decoder of uart. It will be call by uarts_decode_buf_step. And You
 *        can use the UartDecoder.state to discribe the state of UartDecoder,
 *        then do the corresponding motion in your code.
 */
extern UartDecoder_t UartDecoder;

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
 *        UartDecoder.state is state_header. It should put in main of slave
 *        device.
 *
 * NOTE This function will call global variable "UartDecoder"
 */
uint8_t uarts_decode_buf_step();

/******************************************************************************
   Register Section
*******************************************************************************/
uint8_t* UartsReg_p;  ///< Register Array start pointer.
uint8_t  UartsRegLen; ///< Register Array length.

uint8_t uarts_reg_init(uint8_t len, const uint8_t* data_p);
uint8_t uarts_reg_put (uint8_t addr, uint8_t data);
uint8_t uarts_reg_get (uint8_t addr, uint8_t* data_p);
uint8_t uarts_regs_put(uint8_t addr, uint8_t byte, uint8_t* data_p);
uint8_t uarts_regs_get(uint8_t addr, uint8_t byte, uint8_t* data_p);

#endif /* __ASA_UARTS_H__ */
