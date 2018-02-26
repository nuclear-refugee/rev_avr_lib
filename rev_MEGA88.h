#ifndef __REV_MEGA88_H__
#define __REV_MEGA88_H__

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

#define TXEN TXEN0
#define RXEN RXEN0
#define UCSZ0 UCSZ00
// UCSRnA
// RXCn TXCn UDREn FEn DORn UPEn U2Xn MPCMn
#define RXC RXC0
#define TXC TXC0
#define UDRE UDRE0
#define FE FE0
#define DOR DOR0
#define UPE UPE0
#define U2X U2X0
#define MPCM MPCM0

// UCSRnB
// RXCIEn TXCIEn UDRIEn RXENn TXENn UCSZn2 RXB8n TXB8n
#define RXCIE RXCIE0
#define TXCIE TXCIE0
#define UDRIE UDRIE0
#define RXEN RXEN0
#define TXEN TXEN0
#define UCSZ2 UCSZ02
#define RXB8 RXB80
#define TXB8 TXB80

// UCSRnC
// – UMSELn UPMn1 UPMn0 USBSn UCSZn1 UCSZn0 UCPOLn
#define UMSEL UMSEL00
// NOTE UMSEL00 is diff drom datasheet
// the bit 6's name on datasheet is UMSEL0
// but in win-avr-gcc is UMSEL00
#define UPM1 UPM01
#define UPM0 UPM00
#define USBS USBS0
#define UCSZ1 UCSZ01
#define UCSZ0 UCSZ00
#define UCPOL UCPOL0


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
#define UDR	    UDR0
#define UCSRA   UCSR0A
#define UCSRB   UCSR0B
#define UCSRC   UCSR0C
#define UBRRH   UBRR0H
#define UBRRL   UBRR0L

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

#endif
