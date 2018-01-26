#ifndef __ASA_M128_H__
#define __ASA_M128_H__

#include "..\rev_DEVICE.h"

/**
 * @brief ASA BUS ID pins defines
 */
#define ID_PIN  PINB
#define ID_DDR  DDRB
#define ID_PORT PORTB
#define ID_MASK ((1<<PB5)|(1<<PB6)|(1<<PB7))
#define ID_SHIFT 5

/**
 * @brief ASA BUS DIO pin defines
 */
#define BUS_DIO0 PF4
#define BUS_DIO1 PF5
#define BUS_DIO2 PF6
#define BUS_DIO3 PF7
#define BUS_DIO_PIN PINF
#define BUS_DIO_DDR DDRF
#define BUS_DIO_PORT PORTF
#define BUS_DIO_MASK _BV(BUS_DIO0)|_BV(BUS_DIO1)|_BV(BUS_DIO2)|_BV(BUS_DIO3)
#define BUS_DIO_SHIFT BUS_DIO0

/**
 * @brief ASA BUS CS pin defines
 */
#define ASA_CS PF4
#define ASA_CS_PIN  PINF
#define ASA_CS_DDR  DDRF
#define ASA_CS_PORT PORTF
#define ASA_CS_MASK (1<<ASA_CS)
#define ASA_CS_SHIFT ASA_CS

// 6 Pin GPIO 特用功能
// DIO0 - PF4 - ASA SPI CS
// DIO1 - PF5 - ASA 485 I/O 切換
// DIO2 - PF6 - ASA介面卡主動中斷訊號(無隔離)
// DIO3 - PF7 - ASA介面卡主動中斷訊號(無隔離)
// DIO4 - PG3 - /RD
// DIO5 - PG4 - /WR - Software reset

#endif /* __ASA_M128_H__ */
