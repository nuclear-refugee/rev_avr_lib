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

uint8_t* UartsReg_p;  ///< Register Array start pointer.
uint8_t  UartsRegLen; ///< Register Array length.

uint8_t uarts_reg_init(uint8_t len, const uint8_t* data_p);
uint8_t uarts_reg_put (uint8_t addr, uint8_t data);
uint8_t uarts_reg_get (uint8_t addr, uint8_t* data_p);
uint8_t uarts_regs_put(uint8_t addr, uint8_t byte, uint8_t* data_p);
uint8_t uarts_regs_get(uint8_t addr, uint8_t byte, uint8_t* data_p);

#endif /* __ASA_UARTS_H__ */
