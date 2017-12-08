#ifndef __ASA_UART_H__
#define __ASA_UART_H__

#include "../rev_uart.h"

/**
* @brief Replace of ASA_UARTM_trm()
*/
char ASA_UARTM_trm(char isOneSLA, char isOneReg, char UARTID, char RegAdd, char Bytes, void *Data_p);
/**
 * @brief Replace of ASA_UARTM_rec()
 */
char ASA_UARTM_rec(char isOneSLA, char isOneReg, char UARTID, char RegAdd, char Bytes, void *Data_p);
/**
* @brief Replace of ASA_UARTM_ftm()
*/
char ASA_UARTM_ftm(char isOneSLA, char isOneReg, char UARTID, char RegAdd, char Mask, char shift, char Data);
/**
* @brief Replace of M128_UARTM_frc()
*/
char ASA_UARTM_frc(char isOneSLA, char isOneReg, char UARTID, char RegAdd, char Mask, char shift, char* Data_p);

#endif /* __ASA_UART_H__ */
