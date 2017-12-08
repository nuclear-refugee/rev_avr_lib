#ifndef __ASA_M128_H__
#define __ASA_M128_H__

#include "..\rev_DEVICE.h"

/**
 * @brief Defines for serial
 * usually use UART0 for serial
 */
#define ID_PIN  PINB
#define ID_DDR  DDRB
#define ID_PORT PORTB
#define ID_MASK (1<<PB5)|(1<<PB6)|(1<<PB7)
#define ID_SHIFT 5

// ASA_SPI CS : PF4
#define ASA_CS PF4
#define ASA_CS_PIN  PINF
#define ASA_CS_DDR  DDRF
#define ASA_CS_PORT PORTF
#define ASA_CS_MASK (1<<ASA_CS)
#define ASA_CS_SHIFT PF4

#endif /* __ASA_M128_H__ */
