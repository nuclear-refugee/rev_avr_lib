#include "ASA_uart.h"
#include "ASA_general.h"

char ASA_UARTM_trm(char isOneSLA, char isOneReg, char UARTID, char RegAdd, char Bytes, void *Data_p) {
    if ( isOneSLA!=0 || isOneSLA!=1) return 1;
    if ( isOneReg!=0 || isOneReg!=1) return 2;
    // if ( RegAdd>127 ) return 3;

    if ( !isOneSLA ) uart_put(UARTID);
    if ( !isOneReg ) uart_put(RegAdd);
    for (uint16_t i = 0; i < Bytes; i++) {
        uart_put( ((char*)Data_p)[i] );
    }
    return 0;
};

char ASA_UARTM_rec(char isOneSLA, char isOneReg, char UARTID, char RegAdd, char Bytes, void *Data_p) {
    if ( isOneSLA!=0 || isOneSLA!=1) return 1;
    if ( isOneReg!=0 || isOneReg!=1) return 2;
    // if ( RegAdd>127 ) return 3;

    if ( !isOneSLA ) uart_put(UARTID);
    if ( !isOneReg ) uart_put(RegAdd);
    for (uint16_t i = 0; i < Bytes; i++) {
        ((char*)Data_p)[i] = uart_get();
    }
    return 0;
};

char ASA_UARTM_ftm(char isOneSLA, char isOneReg, char UARTID, char RegAdd, char Mask, char shift, char Data) {
    if ( isOneSLA!=0 || isOneSLA!=1) return 1;
    if ( isOneReg!=0 || isOneReg!=1) return 2;
    // if ( RegAdd>127 ) return 3;

    char rec;
    ASA_UARTM_rec(isOneSLA, isOneReg, UARTID, RegAdd, 1, &rec);
    ASA_REGPUT(Data, rec, Mask, shift);
    ASA_UARTM_trm(isOneSLA, isOneReg, UARTID, RegAdd, 1, &Data);
    return 0;
};

char ASA_UARTM_frc(char isOneSLA, char isOneReg, char UARTID, char RegAdd, char Mask, char shift, char* Data_p) {
    if ( isOneSLA!=0 || isOneSLA!=1) return 1;
    if ( isOneReg!=0 || isOneReg!=1) return 2;
    // if ( RegAdd>127 ) return 3;

    char rec;
    ASA_UARTM_rec(isOneSLA, isOneReg, UARTID, RegAdd, 1, &rec);
    *Data_p = ASA_REGGET(rec, Mask, shift);
    return 0;
};
