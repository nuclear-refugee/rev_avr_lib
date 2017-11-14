#ifndef __REV_SERIAL_H__
#define __REV_SERIAL_H__

#include <stdio.h>
#include <inttypes.h>

/**
 * @brief Putchar to serial.
 *
 */
int rev_serial_putchar(char c, FILE *stream);

/**
 * @brief Getchar from serial
 *
 */
int rev_serial_getchar(FILE *stream);

/**
 * @brief Initlize UART for serial usage
 *
 */
char rev_serial_init(void);

#endif
