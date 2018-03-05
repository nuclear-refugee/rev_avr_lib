/**
 * @file ASA_UARTM.h
 * @author LiYu
 * @date 2018.03.06
 * @brief ASA_UARTM functions prototype.
 *
 * TODO Add description of ASA_UARTM and the packet.
 */

#ifndef __ASA_UARTM_H__
#define __ASA_UARTM_H__

#include "../rev_uart.h"
#include <inttypes.h>

/**
* @brief Transmit the Bytes nums of data of pointer Data_p to the assigned 
*        register of RAdd in the slave device whitch id is UID.
*/
uint8_t ASA_UARTM_trm(uint8_t UID, uint8_t RAdd, uint8_t Bytes, void *Data_p);

/**
 * @brief Read the Bytes nums of data to pointer Data_p by the assigned 
 *        register of RAdd in the slave device whitch id is UID.
 */
 uint8_t ASA_UARTM_rec(uint8_t UID, uint8_t RAdd, uint8_t Bytes, void *Data_p);
 
/**
* @brief Set the assigned register of RAdd in the slave device whitch id is UID.
*/
uint8_t ASA_UARTM_ftm(uint8_t UID, uint8_t RAdd, uint8_t Mask, uint8_t shift, uint8_t Data);

/**
* @brief Get the assigned register of RAdd in the slave device whitch id is UID.
*/
uint8_t ASA_UARTM_frc(uint8_t UID, uint8_t RAdd, uint8_t Mask, uint8_t shift, uint8_t *Data_p);

#endif /* __ASA_UARTM_H__ */
