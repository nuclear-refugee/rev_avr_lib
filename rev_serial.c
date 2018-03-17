//Last Build : 2016/11/8 4pm
#include "rev_DEVICE.h"
#include "rev_serial.h"
#include <stdio.h>

static FILE STDIO_BUFFER = FDEV_SETUP_STREAM(rev_serial_putchar, rev_serial_getchar, _FDEV_SETUP_RW);

int rev_serial_putchar(char c, FILE *stream) {
    while((UCSR0A&(1<<UDRE0))==0)
        ;
    UDR0 = c;
    return 0;
}

int rev_serial_getchar(FILE *stream) {
    while((UCSR0A&(1<<RXC0))==0)
        ;
	return UDR0;
}

char rev_serial_init(void) {
    unsigned int baud = F_CPU/16/S_BAUD-1;
	S_UBRRH = (unsigned char)(baud>>8);
	S_UBRRL = (unsigned char)baud;

	S_UCSRB |= (1<<RXEN) | (1<<TXEN);
	S_UCSRC |= (3<<UCSZ0);

	stdout = &STDIO_BUFFER;
	stdin = &STDIO_BUFFER;

	return 0;
}
