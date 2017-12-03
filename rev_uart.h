#ifndef _REV_UART_H_
#define _REV_UART_H_

#include <inttypes.h>

uint8_t uart_set_baud(uint16_t baud);
uint8_t uart_set_sync();
enum uart_check {
    check_disable,
    check_even,
    check_odd,
};
uint8_t uart_set_check(enum uart_check check);

enum uart_stop_bits {
    stop_bits_1,
    stop_bits_2
};
uint8_t uart_set_stop_bits(enum uart_stop_bits stop_bits);

enum uart_data_size {
    data_size_5_bits,
    data_size_6_bits,
    data_size_7_bits,
    data_size_8_bits,
    data_size_9_bits,
};
uint8_t uart_set_data_size(enum uart_data_size size);

enum uart_clock {
    clock_TRRF, ///< Transmitted at Rising edge of XCK, Received at Falling edge of XCK, UCPOL = 0
    clock_TFRR, ///< Transmitted at Falling edge of XCK, Received at Rising edge of XCK, UCPOL = 1
};

/**
 * @brief Set uart clock polarity. (Only used in synchronous mode)
 *
 * default is Transmitted at Rising edge of XCK, Received at Falling edge of
 * XCK, UCPOL = 0
 */
uint8_t uart_set_clock(enum uart_clock clock);

/**
 * @brief Put uart data in 8 bit
 *
 */
uint8_t uart_put(uint8_t data);

/**
 * @brief get uart data in 8 bit.
 *
 */
uint8_t uart_get();

/**
 * @brief Put uart data in 8 bit with timeout.
 * NOTE (default timeout = 100 asm("nop") time)
 *
 */
uint8_t uart_put_wt(uint8_t data);

/**
 * @brief Get uart data in 8 bit with timeout. Received data will be put in data_p.
 * NOTE (default timeout = 100 asm("nop") time)
 *
 */
uint8_t uart_get_wt(uint8_t* data_p);

/**
 * @brief put uart data in 9 bit
 *
 */
uint8_t uart_put9(uint16_t data);

/**
 * @brief Get uart data in 9 bit.
 *
 */
uint16_t uart_get9();

/**
 * @brief Put uart data in 9 bits with timeout.
 * NOTE (default timeout = 100 asm("nop") time)
 *
 */
uint8_t uart_put9_wt(uint8_t data);

/**
 * @brief Get uart data in 9 bits with timeout. Received data will be put in data_p.
 * NOTE (timeout = 100 asm("nop") time)
 *
 */
uint8_t uart_get9_wt(uint16_t* data_p);

#endif
