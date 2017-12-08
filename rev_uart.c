#include "rev_uart.h"
#include "rev_DEVICE.h"
#include "bit_op.h"

uint8_t uart_init() {
	uart_en_rx(1);
	uart_en_tx(1);
	uart_set_baud(BAUD);
	uart_set_data_size(size_8_bits);
    return 0;
};

uint8_t uart_set_baud(uint16_t baud) {
    unsigned int baudrate = F_CPU/16/baud-1;
    UBRRH = (unsigned char)(baudrate>>8);
    UBRRL = (unsigned char)baudrate;
    return 0;
};

uint8_t uart_set_check(enum uart_check check) {
    switch (check) {
        case check_disable: BITCLR(UCSRB,UPM1); BITCLR(UCSRB,UPM0); break;
        case check_even:    BITSET(UCSRB,UPM1); BITCLR(UCSRB,UPM0); break;
        case check_odd:     BITSET(UCSRB,UPM1); BITSET(UCSRB,UPM0); break;
        default: return 1;
    }
    return 0;
};

uint8_t uart_set_stop_bits(enum uart_stop_bits stop_bits) {
    switch (stop_bits) {
        case stop_bits_1: BITCLR(UCSRB,USBS); break;
        case stop_bits_2: BITSET(UCSRB,USBS); break;
        default: return 1;
    }
    return 0;
};

uint8_t uart_set_data_size(enum uart_data_size size) {
    switch (size) {
		case size_5_bits: BITCLR(UCSRB,UCSZ2); BITCLR(UCSRB,UCSZ1); BITCLR(UCSRB,UCSZ0); break;
		case size_6_bits: BITCLR(UCSRB,UCSZ2); BITCLR(UCSRB,UCSZ1); BITSET(UCSRB,UCSZ0); break;
		case size_7_bits: BITCLR(UCSRB,UCSZ2); BITSET(UCSRB,UCSZ1); BITCLR(UCSRB,UCSZ0); break;
		case size_8_bits: BITCLR(UCSRB,UCSZ2); BITSET(UCSRB,UCSZ1); BITSET(UCSRB,UCSZ0); break;
		case size_9_bits: BITSET(UCSRB,UCSZ2); BITSET(UCSRB,UCSZ1); BITSET(UCSRB,UCSZ0); break;
		default: return 1;
    }
	return 0;
};

uint8_t uart_set_clock(enum uart_clock clock) {
	switch (clock) {
		case clock_TRRF: BITCLR(UCSRB,UCPOL); break;
		case clock_TFRR: BITSET(UCSRB,UCPOL); break;
		default: return 1;
	}
	return 0;
};

uint8_t uart_put(uint8_t data) {
	loop_until_bit_is_set(UCSRA, UDRE);
    UDR = data;
    return 0;
};

uint8_t uart_get() {
	loop_until_bit_is_set(UCSRA, RXC);
	return UDR;
};

uint8_t uart_put_wt(uint8_t data) {
	uint8_t count = 0;
	while (bit_is_clear(UCSRA, UDRE) && count < 100) {
		count++;
		asm("nop");
	}
	if (count >= 100) {
		return 1;
	} else {
		UDR = data;
		return 0;
	}
};

uint8_t uart_get_wt(uint8_t* data_p) {
	uint8_t count = 0;
	while (bit_is_clear(UCSRA, RXC) && count < 100) {
		count++;
		asm("nop");
	}
	if (count >= 100) {
		return 1;
	} else {
		*data_p = UDR;
		return 0;
	}
};

uint8_t uart_put9(uint16_t data) {
	loop_until_bit_is_set(UCSRA, UDRE);
	BITCLR(UCSRB,TXB8);
	if ( data & 0x0100 )
		BITSET(UCSRB,TXB8);
	UDR = data;
	return 0;
};

uint16_t uart_get9() {
	loop_until_bit_is_set(UCSRA, RXC);
	return (bit_is_set(UCSRB, RXB8) << 8 | UDR);
};

uint8_t uart_put9_wt(uint8_t data) {
	uint8_t count = 0;
	while (bit_is_clear(UCSRA, UDRE) && count < 100) {
		count++;
		asm("nop");
	}
	if (count >= 100) {
		return 1;
	} else {
		BITCLR(UCSRB,TXB8);
		if ( data & 0x0100 )
			BITSET(UCSRB,TXB8);
		UDR = data;
		return 0;
	}
};

uint8_t uart_get9_wt(uint16_t* data_p) {
	uint8_t count = 0;
	while (bit_is_clear(UCSRA, RXC) && count < 100) {
		count++;
		asm("nop");
	}
	if (count >= 100) {
		return 1;
	} else {
		*data_p = (bit_is_set(UCSRB, RXB8) << 8 | UDR);
		return 0;
	}
};

uint8_t uart_en_int_rx(uint8_t isEnable) {
	if (isEnable) {
		BITSET(UCSRB, RXCIE);
	} else {
		BITCLR(UCSRB, RXCIE);
	}
	return 0;
};

uint8_t uart_en_int_tx(uint8_t isEnable) {
	if (isEnable) {
		BITSET(UCSRB, TXCIE);
	} else {
		BITCLR(UCSRB, TXCIE);
	}
	return 0;
}

uint8_t uart_en_int_empty(uint8_t isEnable) {
	if (isEnable) {
		BITSET(UCSRB, UDRIE);
	} else {
		BITCLR(UCSRB, UDRIE);
	}
	return 0;
}

uint8_t uart_en_tx(uint8_t isEnable) {
	if (isEnable) {
		BITSET(UCSRB, TXEN);
	} else {
		BITCLR(UCSRB, TXEN);
	}
	return 0;
}

uint8_t uart_en_rx(uint8_t isEnable) {
	if (isEnable) {
		BITSET(UCSRB, RXEN);
	} else {
		BITCLR(UCSRB, RXEN);
	}
	return 0;
}

uint8_t uart_en_2x(uint8_t isEnable) {
	if (isEnable) {
		BITSET(UCSRA, U2X);
	} else {
		BITCLR(UCSRA, U2X);
	}
	return 0;
}

uint8_t uart_en_MPCM(uint8_t isEnable) {
	if (isEnable) {
		BITSET(UCSRB, MPCM);
	} else {
		BITCLR(UCSRB, MPCM);
	}
	return 0;
}

uint8_t uart_en_sync(uint8_t isEnable) {
	if (isEnable) {
		BITSET(UCSRC, UMSEL);
	} else {
		BITCLR(UCSRC, UMSEL);
	}
	return 0;
}

uint8_t uart_is_tx_complete() {
	return bit_is_set(UCSRA, TXC) ? 1 : 0;
};

uint8_t uart_is_rx_complete() {
	return bit_is_set(UCSRA, RXC) ? 1 : 0;
};

uint8_t uart_is_data_empty() {
	return bit_is_set(UCSRA, UDRE) ? 1 : 0;
};

uint8_t uart_is_err_frame() {
	return bit_is_set(UCSRA, FE) ? 1 : 0;
};

uint8_t uart_is_err_overrun() {
	return bit_is_set(UCSRA, DOR) ? 1 : 0;
};

uint8_t uart_is_err_check() {
	return bit_is_set(UCSRA, UPE) ? 1 : 0;
};
