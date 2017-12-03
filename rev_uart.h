#ifndef _REV_UART_H_
#define _REV_UART_H_

#include <inttypes.h>

void uart_set_baud(uint16_t baud);
void uart_set_sync();
enum uart_check {
    check_disable,
    check_even,
    check_odd,
};
void uart_set_check(enum uart_check check);

enum uart_stop_bits {
    stop_bits_1,
    stop_bits_2
};
void uart_set_stop_bits(enum uart_stop_bits stop_bits);

enum uart_data_size {
    data_size_5_bits,
    data_size_6_bits,
    data_size_7_bits,
    data_size_8_bits,
    data_size_9_bits,
};
void uart_set_data_size(enum uart_data_size size);

#endif
