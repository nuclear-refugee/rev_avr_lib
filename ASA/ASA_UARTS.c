/**
 * @file ASA_UARTS.c
 * @author LiYu
 * @date 2018.03.06
 * @brief ASA_UARTS functions implement.
 */

#include "ASA_UARTS.h"
#include "ASA_general.h"
#include "buffer.h"

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
    if (UartDecoder.status == status_done) {
        return 0;
    }
    
    uint8_t ch;
    static uint8_t bytes = 0;
    static uint8_t chksum = 0;
    
    if (buf_is_null(BufIn)) {
        return BUF_NULL;
    }
    switch (UartDecoder.status) {
        case status_header: {
            ch = buf_read(&BufIn);
            
            if (ch != UART_HEADER) {
                return ERROR_HEADER;
            }
            // variable initialize
            chksum = UART_HEADER;
            bytes  = 0;
            
            UartDecoder.status = status_uid;
            break;
        }
        case status_uid: {
            ch = buf_read(&BufIn);
            chksum = chksum + ch;
            
            if (ch != UART_UID) {
                chksum = 0;
                UartDecoder.status = status_header;
                return ERROR_UID;
            }
            UartDecoder.status = status_wradd;
            break;
        }
        case status_wradd: {
            ch = buf_read(&BufIn);
            chksum = chksum + ch;
            
            UartDecoder.wr      = ch >> UART_WR;
            UartDecoder.address = ch & (~(1<<UART_WR));
            
            UartDecoder.status = status_bytes;
            break;
        }
        case status_bytes: {
            ch = buf_read(&BufIn);
            chksum = chksum + ch;
            
            UartDecoder.bytes = ch;
            
            if (UartDecoder.wr) { // write mode
                UartDecoder.status = status_data;
            } else {
                UartDecoder.status = status_chksum;
            }
            break;
        }
        case status_data: {
            ch = buf_read(&BufIn);
            chksum = chksum + ch;
            
            UartDecoder.data[bytes] = ch;
            bytes++;
            
            if (bytes == UartDecoder.bytes) {
                UartDecoder.status = status_chksum;
                break;
            }
            break;
        }
        case status_chksum: {
            ch = buf_read(&BufIn);
            
            if (ch!= chksum) {
                UartDecoder.status = status_header;
                return ERROR_CHKSUM;
            }
            UartDecoder.status = status_done;
            break;
        }
        case status_done: {
            break;
        }
    }
    return DECODE_OK;
}
