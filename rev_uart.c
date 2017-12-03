#include "rev_DEVICE.h"
#include "rev_uart.h"

uint8_t uart_init();

uint8_t uart_set_baud(uint16_t baud);

uint8_t uart_set_check(enum uart_check check);

uint8_t uart_set_stop_bits(enum uart_stop_bits stop_bits);

uint8_t uart_set_data_size(enum uart_data_size size);

uint8_t uart_set_clock(enum uart_clock clock);

uint8_t uart_put(uint8_t data);

uint8_t uart_get();

uint8_t uart_put_wt(uint8_t data);

uint8_t uart_get_wt(uint8_t* data_p);

uint8_t uart_put9(uint16_t data);

uint16_t uart_get9();

uint8_t uart_put9_wt(uint8_t data);

uint8_t uart_get9_wt(uint16_t* data_p);

uint8_t uart_en_int_rx(uint8_t isEnable);

uint8_t uart_en_int_tx(uint8_t isEnable);

uint8_t uart_en_int_empty(uint8_t isEnable);

uint8_t uart_en_tx(uint8_t isEnable);

uint8_t uart_en_rx(uint8_t isEnable);

uint8_t uart_en_2x(uint8_t isEnable);

uint8_t uart_en_MPCM(uint8_t isEnable);

uint8_t uart_en_sync(uint8_t isEnable);

uint8_t uart_is_tx_complete();

uint8_t uart_is_rx_complete();

uint8_t uart_is_data_empty();

uint8_t uart_is_err_frame();

uint8_t uart_is_err_overrun();

uint8_t uart_is_err_check();
