#include "rev_gpio_spi.h"
#include "rev_DEVICE.h"
#include "bit_op.h"

void gspi_master_init() {
    BITSET(SPI_SPCR,MSTR);
    REGPUT(SPI_DDR,
        (1<<PIN_GSPI_MISO)|(1<<PIN_GSPI_MOSI)|(1<<PIN_GSPI_SCK)|(1<<PIN_GSPI_SS),
        (1<<PIN_GSPI_MOSI)|(1<<PIN_GSPI_SCK)|(1<<PIN_GSPI_SS) );
    REGPUT(SPI_PORT,
        (1<<PIN_GSPI_MISO)|(1<<PIN_GSPI_MOSI)|(1<<PIN_GSPI_SCK)|(1<<PIN_GSPI_SS),
        (1<<PIN_GSPI_MOSI)|(1<<PIN_GSPI_SS) );
    _delay_loop_1(1);
}


void gspi_sck_pulse(void) {
    BITCLR(GSPI_PORT, PIN_GSPI_SCK); // SCK low
    _delay_loop_1(1);
    _delay_loop_1(1);
    BITSET(GSPI_PORT, PIN_GSPI_SCK); // SCK high
    _delay_loop_1(1);
    _delay_loop_1(1);
}

void spi_reset_pulse(void) {
    /* give a positive RESET pulse, we can't guarantee
    * that SCK was low during power up (see Atmel's
    * data sheets, search for "Serial Downloading in e.g atmega8
    * data sheet):
    * "... the programmer can not guarantee that SCK is held low during
    * Power-up. In this case, RESET must be given a positive pulse of at least two
    * CPU clock cycles duration after SCK has been set to 0."
    * */
    BITSET(GSPI_PORT, PIN_GSPI_CS); // reset = high = not active
    _delay_loop_1(1);
    _delay_loop_1(1);
    BITCLR(GSPI_PORT, PIN_GSPI_CS); // reset = low, stay active
    _delay_ms(20); // min stab delay
}
