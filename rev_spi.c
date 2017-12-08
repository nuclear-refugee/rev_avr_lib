#include "rev_SPI.h"
#include "rev_DEVICE.h"
#include "bit_op.h"

uint8_t spi_set_frequency(enum spi_freq_devider devider) {
    switch (devider) {
        case devider_4  : BITCLR(SPI_SPSR,SPI2X); BITCLR(SPI_SPCR,SPR1); BITCLR(SPI_SPCR,SPR0); break;
        case devider_16 : BITCLR(SPI_SPSR,SPI2X); BITCLR(SPI_SPCR,SPR1); BITSET(SPI_SPCR,SPR0); break;
        case devider_64 : BITCLR(SPI_SPSR,SPI2X); BITSET(SPI_SPCR,SPR1); BITCLR(SPI_SPCR,SPR0); break;
        case devider_128: BITCLR(SPI_SPSR,SPI2X); BITSET(SPI_SPCR,SPR1); BITSET(SPI_SPCR,SPR0); break;
        case devider_2  : BITSET(SPI_SPSR,SPI2X); BITCLR(SPI_SPCR,SPR1); BITCLR(SPI_SPCR,SPR0); break;
        case devider_8  : BITSET(SPI_SPSR,SPI2X); BITCLR(SPI_SPCR,SPR1); BITSET(SPI_SPCR,SPR0); break;
        case devider_32 : BITSET(SPI_SPSR,SPI2X); BITSET(SPI_SPCR,SPR1); BITCLR(SPI_SPCR,SPR0); break;
        default : return 1;
    }
    return 0;
};

uint8_t spi_set_datamode(enum spi_data_mode mode) {
    switch (mode) {
        case mode_LRSL: BITCLR(SPI_SPCR,CPOL); BITCLR(SPI_SPCR,CPHA); break;
        case mode_LFSL: BITSET(SPI_SPCR,CPOL); BITCLR(SPI_SPCR,CPHA); break;
        case mode_LRST: BITCLR(SPI_SPCR,CPOL); BITSET(SPI_SPCR,CPHA); break;
        case mode_LFST: BITSET(SPI_SPCR,CPOL); BITSET(SPI_SPCR,CPHA); break;
        default : return 1;
    }
    return 0;
};

uint8_t spi_set_dataorder(enum spi_data_order order) {
    switch (order) {
        case order_LSB: BITSET(SPI_SPCR,DORD); break;
        case order_MSB: BITCLR(SPI_SPCR,DORD); break;
        default : return 1;
    }
    return 0;
};

uint8_t spi_master_init() {
    BITSET(SPI_SPCR,MSTR);
    REGPUT(SPI_DDR,
           (1<<PIN_MISO)|(1<<PIN_MOSI)|(1<<PIN_SCK)|(1<<PIN_SS),
           (1<<PIN_MOSI)|(1<<PIN_SCK)|(1<<PIN_SS) );
    REGPUT(SPI_PORT,
           (1<<PIN_MISO)|(1<<PIN_MOSI)|(1<<PIN_SCK)|(1<<PIN_SS),
           (1<<PIN_MOSI)|(1<<PIN_SS) );
    return 0;
};

uint8_t spi_slave_init() {
    BITCLR(SPI_SPCR,MSTR);
    REGPUT(SPI_DDR,
           (1<<PIN_MISO)|(1<<PIN_MOSI)|(1<<PIN_SCK)|(1<<PIN_SCK),
           (1<<PIN_MISO) );
    REGPUT(SPI_PORT,
           ((1<<PIN_MISO)|(1<<PIN_MOSI)|(1<<PIN_SCK)|(1<<PIN_SCK)),
           0 );
    return 0;
};

uint8_t spi_en(uint8_t isEnable) {
    if (isEnable == 1) {
        BITSET(SPI_SPCR,SPE);
    } else if (isEnable == 0) {
        BITCLR(SPI_SPCR,SPE);
    } else {
        return 1;
    }
    return 0;
};

uint8_t spi_en_int(uint8_t isEnable) {
    if (isEnable == 1) {
        BITSET(SPI_SPCR,SPIE);
    } else if (isEnable == 0) {
        BITCLR(SPI_SPCR,SPIE);
    } else {
        return 1;
    }
    return 0;
};

uint8_t spi_swap(uint8_t data) {
	SPDR = data;
	while(!(SPI_SPSR & (1<<SPIF)))
		;
	return SPDR;
}
