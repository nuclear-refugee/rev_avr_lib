/**
 * @file ASA_UARTM.c
 * @author LiYu
 * @date 2018.03.06
 * @brief ASA_UARTM functions implement.
 *
 * TODO Add description of ASA_UARTM and the packet.
 */

#include "ASA_UARTM.h"
#include "ASA_general.h"

// NOTE The HEADER is not assigned in the datasheet yet, so the value 
//      is temporary now!!
#define UART_HEADER 0xF0 //<<< The HEADER of ASA_UART packet.

#define UART_WR 7 //<<< The bit to controll write command or read command in RAdd.

uint8_t ASA_UARTM_trm(uint8_t UID, uint8_t RAdd, uint8_t Bytes, void *Data_p) {
    if (0) {
        // TODO handle UID exception, if there is.
        return 1;
    } else if (RAdd & (1<<UART_WR)) {
        return 2;
    } else if (0) {
        // TODO handle Bytes exception, if there is.
        return 3;
    }
    uint8_t chksum = 0;
    
    uart_put(UART_HEADER);
    chksum += UART_HEADER;
    
    uart_put(UID);
    chksum += UID;
    
    // The bit UART_WR shold be 1 to send write command.
    uart_put( RAdd | (1<<UART_WR) );
    chksum += RAdd | (1<<UART_WR);
    
    uart_put(Bytes);
    chksum += Bytes;
    
    for (uint16_t i = 0; i < Bytes; i++) {
        uart_put( ((uint8_t*)Data_p)[i] );
        chksum += ((uint8_t*)Data_p)[i];
    }
    uart_put(chksum);
    return 0;
}

uint8_t ASA_UARTM_rec(uint8_t UID, uint8_t RAdd, uint8_t Bytes, void *Data_p) {
    if (0) {
        // TODO handle UID exception, if there is.
        return 1;
    } else if (RAdd & (1<<UART_WR)) {
        return 2;
    } else if (0) {
        // TODO handle Bytes exception, if there is.
        return 3;
    }
    uint8_t chksum = 0;
    
    uart_put(UART_HEADER);
    chksum += UART_HEADER;
    
    uart_put(UID);
    chksum += UID;
    
    // The bit UART_WR shold be 0 to send read command
    uart_put( RAdd );
    chksum += RAdd;
    
    uart_put(Bytes);
    chksum += Bytes;
    
    uart_put(chksum);
    
    for (uint16_t i = 0; i < Bytes; i++) {
        ((uint8_t*)Data_p)[i] = uart_get();
    }
    return 0;
}

uint8_t ASA_UARTM_ftm(uint8_t UID, uint8_t RAdd, uint8_t Mask, uint8_t shift, uint8_t Data) {
    if (0) {
        // TODO handle UID exception, if there is.
        return 1;
    } else if (RAdd & (1<<UART_WR)) {
        return 2;
    } else if (shift >= 8) {
        return 4;
    }
    
    uint8_t res, rec;
    
    res = ASA_UARTM_rec(UID, RAdd, 1, &rec);
    ASA_REGPUT(Data, rec, Mask, shift);
    res = ASA_UARTM_trm(UID, RAdd, 1, &Data);
    
    return 0;
};

uint8_t ASA_UARTM_frc(uint8_t UID, uint8_t RAdd, uint8_t Mask, uint8_t shift, uint8_t *Data_p) {
    if (0) {
        // TODO handle UID exception, if there is.
        return 1;
    } else if (RAdd & (1<<UART_WR)) {
        return 2;
    } else if (shift >= 8) {
        return 4;
    }
    
    uint8_t res, rec;
    
    res = ASA_UARTM_rec(UID, RAdd, 1, &rec);
    *Data_p = ASA_REGGET(rec, Mask, shift);
    return 0;
};
