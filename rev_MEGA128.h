#ifndef __REV_MEGA128_H__
#define __REV_MEGA128_H__

/**
 * @brief Defines for serial
 * usually use UART0 for serial
 */
#define S_BAUD  38400
#define S_UDR	UDR0
#define S_UBRRH	UBRR0H
#define S_UBRRL	UBRR0L
#define S_UCSRA	UCSR0A
#define S_UCSRB	UCSR0B
#define S_UCSRC	UCSR0C

/**
 * @brief Defines for spi
 * usually 1 spi channel in avr
 */
#define SPI_SPCR  SPCR
#define SPI_SPSR  SPSR
#define SPI_PORT  PORTB
#define SPI_PIN	  PINB
#define SPI_DDR   DDRB
#define PIN_MISO  PB3
#define PIN_MOSI  PB2
#define PIN_SCK	  PB1
#define PIN_SS    PB0

/**
 * @brief Defines for uart
 * usually use usart1 as default uart
 */
#define UDR	    UDR1
#define UCSRA   UCSR1A
#define UCSRB   UCSR1B
#define UCSRC   UCSR1C
#define UBRRH   UBRR1H
#define UBRRL   UBRR1L

//TWI
#define TWI_PORT	PORTD
#define TWI_PIN		PIND
#define TWI_DDR		DDRD
#define TWI_SCL		PD0
#define TWI_SDA		PD1



//DIO
#define DIO_PORT	PORTF
#define DIO_PIN		PINF
#define DIO_DDR		DDRF
#define DIO_RW_PORT	PORTG
#define DIO_RW_PIN	PING
#define DIO_RW_DDR	DDRG
#define DIO0		PF4
#define DIO1		PF5
#define DIO2		PF6
#define DIO3		PF7
#define DIO_RD		PG3
#define DIO_WR		PG4

//ASA_ID
#define ADDR_PORT	PORTB
#define ADDR_PIN	PINB
#define ADDR_DDR	DDRB
#define ADDR0       PB5
#define ADDR1       PB6
#define ADDR2       PB7


#endif
