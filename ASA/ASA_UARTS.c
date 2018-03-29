/**
 * @file ASA_UARTS.c
 * @author LiYu
 * @date 2018.03.06
 * @brief ASA_UARTS functions implement.
 */

#include "ASA_UARTS.h"
#include "ASA_general.h"
#include "../buffer.h"
#include <stdarg.h>
#include <stdlib.h>

// NOTE The HEADER is not assigned in the datasheet yet, so the value
//      is temporary now!!
#define UART_HEADER 0xF0 ///< The HEADER of ASA_UART packet.

#define UART_WR 7 ///< The bit to controll write command or read command in RAdd.

// NOTE The UART_UID is not assigned in the datasheet yet, so the value
//      is temporary now!!
#define UART_UID 0x12 ///< The bit to controll write command or read command in RAdd.

#define BUFFERSIZE 255

Buf_t BufIn  = {{0},0,0};
Buf_t BufOut = {{0},0,0};
UartDecoder_t UartDecoder;

inline void uarts_rx_handle() {
    if (buf_is_full(BufIn)) {
        return;
    } else {
        buf_write(&BufIn, uart_get());
    }
}

inline void uarts_tx_handle() {
    if (buf_is_null(BufOut)) {
        return;
    } else {
        uart_put( buf_read(&BufOut) );
    }
}

uint8_t uarts_decode_buf_step() {
    // NOTE This function will call global variable "UartDecoder"
    if (UartDecoder.state == state_done) {
        return 0;
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

            UartDecoder.wr      = ch >> UART_WR;
            UartDecoder.address = ch & (~(1<<UART_WR));

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


/******************************************************************************
 *  Register Section
 ******************************************************************************/
uint8_t* UartsReg_p;
uint8_t  UartsRegLen;

uint8_t uarts_reg_init(uint8_t len, const uint8_t* data_p) {
    UartsReg_p = malloc(len*sizeof(uint8_t));
    UartsRegLen = len;
    for (uint16_t i = 0; i < len; i++) {
        UartsReg_p[i] = data_p[i];
    }
    return 0;
};

uint8_t uarts_reg_put (uint8_t addr, uint8_t data) {
    if (addr>UartsRegLen) {
        return 1;
    }
    UartsReg_p[addr] = data;
    return 0;
};

uint8_t uarts_reg_get (uint8_t addr, uint8_t* data_p) {
    if (addr>UartsRegLen) {
        return 1;
    }
    *data_p = UartsReg_p[addr];
    return 0;
};

uint8_t uarts_regs_put(uint8_t addr, uint8_t byte, uint8_t* data_p) {
    if (addr+byte>UartsRegLen) {
        return 1;
    }
    for (uint16_t i = 0; i < byte; i++) {
        UartsReg_p[addr+i] = data_p[i];
    }
    return 0;
};

uint8_t uarts_regs_get(uint8_t addr, uint8_t byte, uint8_t* data_p) {
    if (addr+byte>UartsRegLen) {
        return 1;
    }
    for (uint16_t i = 0; i < byte; i++) {
        data_p[i] = UartsReg_p[addr+i];
    }
    return 0;
};
