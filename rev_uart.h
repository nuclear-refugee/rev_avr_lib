/**
 * @file rev_uart.h
 * @author LiYu
 * @date 2017.12.03
 * @brief Uart functions.
 *
 */
// TODO add file description

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
    size_5_bits, ///< Data size is 5-bit.
    size_6_bits, ///< Data size is 6-bit.
    size_7_bits, ///< Data size is 7-bit.
    size_8_bits, ///< Data size is 8-bit.
    size_9_bits, ///< Data size is 9-bit.
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

/**
 * @brief Return is uart Transmit Complete.
 */
uint8_t uart_is_tx_complete();
/**
 * @brief Return is uart Receive Complete.
 */
uint8_t uart_is_rx_complete();
/**
 * @brief Return is uart Data Register Empty
 *
 * The UDREn flag indicates if the transmit buffer (UDRn) is ready to receive
 * new data. If UDREn is one, the buffer is empty, and therefore ready to be
 * written. The UDREn flag can generate a Data Register Empty interrupt (see
 * description of the UDRIEn bit).
 * UDREn is set after a reset to indicate that the Transmitter is ready.
 */
uint8_t uart_is_data_empty();
/**
 * @brief Return is Frame Error happened
 *
 * Is set if the next character in the receive buffer had a Frame Error when
 * received. I.e. when the first stop bit of the next character in the receive
 * buffer is zero. This bit is valid until the receive buffer (UDRn) is read.
 * The FEn bit is zero when the stop bit of received data is one. Always set
 * this bit to zero when writing to UCSRnA.
 */
uint8_t uart_is_err_frame();
/**
 * @brief Return is Data OverRun happened
 *
 * This bit is set if a Data OverRun condition is detected. A data overrun
 * occurs when the receive buffer is full (two characters), it is a new
 * character waiting in the Receive Shift Register, and a new start bit is
 * detected. This bit is valid until the receive buffer (UDRn) is read. Always
 * set this bit to zero when writing to UCSRnA.
 */
uint8_t uart_is_err_overrun();
/**
 * @brief Return is Parity Error happened
 *
 * Is set if the next character in the receive buffer had a Parity Error when
 * received and the parity checking was enabled at that point (UPMn1 = 1).
 * This bit is valid until the receive buffer (UDRn) is read. Always set this
 * bit to zero when writing to UCSRnA.
 */
uint8_t uart_is_err_check();

#endif /* _REV_UART_H_ */
