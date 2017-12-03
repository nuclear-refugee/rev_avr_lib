#ifndef _REV_UART_H_
#define _REV_UART_H_

#include <inttypes.h>

#ifndef BAUD
#define BAUD 38400
#endif

/**
 * @brief Initialize uart with define BAUD. (default is 38400)
 *
 * data is 8bits, check is disable, sync is disable, stop bits is 1.
 */
uint8_t uart_init();

/**
 * @brief Set uart baud. (default is 38400)
 */
uint8_t uart_set_baud(uint16_t baud);

enum uart_check {
    check_disable, ///< Check mode is disabled,
    check_even,    ///< Check mode is enabled, Even Parity
    check_odd,     ///< Check mode is enabled, Odd Parity
};
/**
 * @brief Set uart check mode. (default is none)
 *
 * If enabled, the Transmitter will automatically generate and send the parity
 * of the transmitted data bits within each frame. The Receiver will generate a
 * parity value for the incoming data and compare it to the UPMn0 setting. If a
 * mismatch is detected, the UPEn flag in UCSRnA will be set.
 */
uint8_t uart_set_check(enum uart_check check);

enum uart_stop_bits {
    stop_bits_1, ///< Stop bits is 1.
    stop_bits_2, ///< Stop bits is 2.
};
/**
 * @brief Set uart stop bits. (default is 1)
 */
uint8_t uart_set_stop_bits(enum uart_stop_bits stop_bits);

enum uart_data_size {
    data_size_5_bits, ///< Data size is 5-bit.
    data_size_6_bits, ///< Data size is 6-bit.
    data_size_7_bits, ///< Data size is 7-bit.
    data_size_8_bits, ///< Data size is 8-bit.
    data_size_9_bits, ///< Data size is 9-bit.
};
/**
 * @brief Set uart data size. (default is 8)
 */
uint8_t uart_set_data_size(enum uart_data_size size);

enum uart_clock {
    clock_TRRF, ///< Transmitted at Rising edge of XCK, Received at Falling edge of XCK, UCPOL = 0
    clock_TFRR, ///< Transmitted at Falling edge of XCK, Received at Rising edge of XCK, UCPOL = 1
};
/**
 * @brief Set uart clock polarity.
 * NOTE (Only used in synchronous mode)
 *
 * default is Transmitted at Rising edge of XCK, Received at Falling edge of
 * XCK, UCPOL = 0
 */
uint8_t uart_set_clock(enum uart_clock clock);

/**
 * @brief Put uart data in 8 bit
 */
uint8_t uart_put(uint8_t data);

/**
 * @brief get uart data in 8 bit.
 */
uint8_t uart_get();

/**
 * @brief Put uart data in 8 bit with timeout.
 * NOTE (default timeout = 100 asm("nop") time)
 */
uint8_t uart_put_wt(uint8_t data);

/**
 * @brief Get uart data in 8 bit with timeout. Received data will be put in data_p.
 * NOTE (default timeout = 100 asm("nop") time)
 */
uint8_t uart_get_wt(uint8_t* data_p);

/**
 * @brief put uart data in 9 bit
 */
uint8_t uart_put9(uint16_t data);

/**
 * @brief Get uart data in 9 bit.
 */
uint16_t uart_get9();

/**
 * @brief Put uart data in 9 bits with timeout.
 * NOTE (default timeout = 100 asm("nop") time)
 */
uint8_t uart_put9_wt(uint8_t data);

/**
 * @brief Get uart data in 9 bits with timeout. Received data will be put in data_p.
 * NOTE (timeout = 100 asm("nop") time)
 */
uint8_t uart_get9_wt(uint16_t* data_p);


/**
 * @brief Enable/Disable RX Complete Interrupt
 */
uint8_t uart_en_int_rx(uint8_t isEnable);
/**
 * @brief Enable/Disable TX Complete Interrupt
 */
uint8_t uart_en_int_tx(uint8_t isEnable);
/**
 * @brief Enable/Disable Data Register Empty Interrupt
 */
uint8_t uart_en_int_empty(uint8_t isEnable);
/**
 * @brief Enable/Disable Transmitter
 *
 * The Transmitter will override normal port operation for the TxDn pin when
 * enabled. The disabling of the Transmitter (writing TXENn to zero) will not
 * become effective until ongoing and pending transmissions are completed,
 * i.e., when the Transmit Shift Register and transmit buffer register do not
 * contain data to be transmitted. When disabled, the transmitter will no longer
 * override the TxDn port.
 */
uint8_t uart_en_tx(uint8_t isEnable);
/**
 * @brief Enable/Disable Receiver
 *
 * The Receiver will override normal port operation for the RxDn pin when
 * enabled. Disabling the Receiver will flush the receive buffer invalidating
 * the FEn, DORn and UPEn flags.
 */
uint8_t uart_en_rx(uint8_t isEnable);
/**
 * @brief Enable/Disable double transmission speed.
 * NOTE (Only has effect for asynchronous operation)
 *
 * Will reduce the divisor of the baud rate divider from 16 to 8 effectively
 * doubling the transfer rate for asynchronous communication.
 */
uint8_t uart_en_2x(uint8_t isEnable);
/**
 * @brief Enable/Disable Multi-Processor Communication Mode
 *
 * When enable, all the incoming frames received by the USART Receiver that do
 * not contain address information will be ignored. The transmitter is
 * unaffected by this setting.
 */
uint8_t uart_en_MPCM(uint8_t isEnable);
/**
 * @brief Enable/Disable Synchronous Operation.
 * NOTE (default is asynchronous)
 */
uint8_t uart_en_sync(uint8_t isEnable);

#endif
