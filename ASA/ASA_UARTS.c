/**
 * @file ASA_UARTS.c
 * @author LiYu
 * @date 2018.03.06
 * @brief ASA_UARTS functions implement.
 */

#include "ASA_UARTS.h"
#include "ASA_general.h"
#include "../buffer.h"
#include <stdlib.h>

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

uint8_t uarts_reg_put(uint8_t addr, uint8_t data) {
    if (addr>UartsRegLen) {
        return 1;
    }
    UartsReg_p[addr] = data;
    return 0;
};

uint8_t uarts_reg_get(uint8_t addr, uint8_t* data_p) {
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
