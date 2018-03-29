/**
 * @file ASA_UART_PAC.c
 * @author LiYu
 * @date 2018.03.06
 * @brief ASA_uart functions implement.
 */

#include "ASA_UART_PAC.h"
#include "ASA_general.h"
#include "../buffer.h"
#include <stdarg.h>
#include <stdlib.h>

// NOTE The HEADER is not assigned in the datasheet yet, so the value
//      is temporary now!!
#define UART_HEADER 0xF0 ///< The HEADER of ASA_UART packet.

#define UART_WR_BIT 7 ///< The bit to controll write command or read command in RAdd.

// NOTE The UART_UID is not assigned in the datasheet yet, so the value
//      is temporary now!!
#define UART_UID 0x12 ///< The bit to controll write command or read command in RAdd.

#define BUFFERSIZE 255

Buf_t BufIn  = {{0},0,0};
Buf_t BufOut = {{0},0,0};
UartDecoder_t UartDecoder;

inline void uart_rx_handle() {
    if (buf_is_full(BufIn)) {
        return;
    } else {
        buf_write(&BufIn, uart_get());
    }
}

inline void uart_tx_handle() {
    if (buf_is_null(BufOut)) {
        return;
    } else {
        uart_put( buf_read(&BufOut) );
    }
}

uint8_t uart_decode_buf_step() {
    // NOTE This function will call global variable "UartDecoder"
    if (UartDecoder.state == state_done) {
        return DECODE_OK;
    }

    uint8_t ch;
    static uint8_t bytes = 0;
    static uint8_t chksum = 0;

    if (buf_is_null(BufIn)) {
        return BUF_NULL;
    }
    switch (UartDecoder.state) {
        case state_header: {
            ch = buf_read(&BufIn);

            if (ch != UART_HEADER) {
                return ERROR_HEADER;
            }
            // variable initialize
            chksum = UART_HEADER;
            bytes  = 0;

            UartDecoder.state = state_uid;
            break;
        }
        case state_uid: {
            ch = buf_read(&BufIn);
            chksum = chksum + ch;

            if (ch != UART_UID) {
                chksum = 0;
                UartDecoder.state = state_header;
                return ERROR_UID;
            }
            UartDecoder.state = state_wradd;
            break;
        }
        case state_wradd: {
            ch = buf_read(&BufIn);
            chksum = chksum + ch;

            UartDecoder.wr      = ch >> UART_WR_BIT;
            UartDecoder.address = ch & (~(1<<UART_WR_BIT));

            UartDecoder.state = state_bytes;
            break;
        }
        case state_bytes: {
            ch = buf_read(&BufIn);
            chksum = chksum + ch;

            UartDecoder.bytes = ch;

            if (UartDecoder.wr) { // write mode
                UartDecoder.state = state_data;
            } else {
                UartDecoder.state = state_chksum;
            }
            break;
        }
        case state_data: {
            ch = buf_read(&BufIn);
            chksum = chksum + ch;

            UartDecoder.data[bytes] = ch;
            bytes++;

            if (bytes == UartDecoder.bytes) {
                UartDecoder.state = state_chksum;
                break;
            }
            break;
        }
        case state_chksum: {
            ch = buf_read(&BufIn);

            if (ch!= chksum) {
                UartDecoder.state = state_header;
                return ERROR_CHKSUM;
            }
            UartDecoder.state = state_done;
            break;
        }
        case state_done: {
            break;
        }
    }
    return DECODE_OK;
}

uint8_t uart_encoder(uint8_t UID, uint8_t RW, uint8_t addr, uint8_t bytes, void *Data_p) {
    // if (buf_size(BufOut)+3+bytes > BUFFSIZE-1) {
    //     return 1;
    // }
    buf_write(&BufOut, UART_HEADER);
    buf_write(&BufOut, (RW<<UART_WR_BIT) | addr);
    buf_write(&BufOut, bytes);
    for (uint8_t i = 0; i < bytes; i++) {
        buf_write(&BufOut, *(uint8_t*)Data_p);
    }

    return 0;
}
