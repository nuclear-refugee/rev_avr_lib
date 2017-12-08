#include "ASA_spi.h"
#include "ASA_general.h"

#define REGPUT(ADDRESS, MASK, DATA) (ADDRESS = (((ADDRESS)&(~MASK)) | ((DATA) & (MASK))))

void ASA_SPIM_cs_init() {
    ASA_REGPUT(ASA_CS_DDR, 1, ASA_CS_MASK, ASA_CS_SHIFT);
}

void ASA_SPIM_cs(uint8_t isEnable) {
    if(isEnable>1)
    return;
    ASA_REGPUT(ASA_CS_PORT, isEnable, ASA_CS_MASK, ASA_CS_SHIFT);
}

char ASA_SPIM_trm(char isOneSLA, char isOneReg, char UARTID, char RegAdd, char Bytes, void *Data_p) {
    if ( isOneSLA!=0 || isOneSLA!=1) return 1;
    if ( isOneReg!=0 || isOneReg!=1) return 2;
    // if ( RegAdd>127 ) return 3;

    if ( !isOneSLA ) spi_swap(UARTID);
    if ( !isOneReg ) spi_swap(RegAdd);
    for (uint16_t i = 0; i < Bytes; i++) {
        spi_swap( ((char*)Data_p)[i] );
    }
    return 0;
};

char ASA_SPIM_rec(char isOneSLA, char isOneReg, char UARTID, char RegAdd, char Bytes, void *Data_p) {
    if ( isOneSLA!=0 || isOneSLA!=1) return 1;
    if ( isOneReg!=0 || isOneReg!=1) return 2;
    // if ( RegAdd>127 ) return 3;

    if ( !isOneSLA ) spi_swap(UARTID);
    if ( !isOneReg ) spi_swap(RegAdd);
    for (uint16_t i = 0; i < Bytes; i++) {
        ((char*)Data_p)[i] = spi_swap(255);
    }
    return 0;
};

char ASA_SPIM_ftm(char isOneSLA, char isOneReg, char UARTID, char RegAdd, char Mask, char shift, char Data) {
    if ( isOneSLA!=0 || isOneSLA!=1) return 1;
    if ( isOneReg!=0 || isOneReg!=1) return 2;
    // if ( RegAdd>127 ) return 3;

    char rec;
    ASA_SPIM_rec(isOneSLA, isOneReg, UARTID, RegAdd, 1, &rec);
    ASA_REGPUT(Data, rec, Mask, shift);
    ASA_SPIM_trm(isOneSLA, isOneReg, UARTID, RegAdd, 1, &Data);
    return 0;
};

char ASA_SPIM_frc(char isOneSLA, char isOneReg, char UARTID, char RegAdd, char Mask, char shift, char* Data_p) {
    if ( isOneSLA!=0 || isOneSLA!=1) return 1;
    if ( isOneReg!=0 || isOneReg!=1) return 2;
    // if ( RegAdd>127 ) return 3;

    char rec;
    ASA_SPIM_rec(isOneSLA, isOneReg, UARTID, RegAdd, 1, &rec);
    *Data_p = ASA_REGGET(rec, Mask, shift);
    return 0;
};
