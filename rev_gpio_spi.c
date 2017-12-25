#include "rev_gpio_spi.h"
#include "rev_DEVICE.h"
#include "bit_op.h"

// TODO inpleent SCK duration
uint8_t sck_dur = 0;

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
    _delay_loop_1(sck_dur);
    _delay_loop_1(sck_dur);
    BITSET(GSPI_PORT, PIN_GSPI_SCK); // SCK high
    _delay_loop_1(sck_dur);
    _delay_loop_1(sck_dur);
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
    _delay_loop_1(sck_dur);
    _delay_loop_1(sck_dur);
    BITCLR(GSPI_PORT, PIN_GSPI_CS); // reset = low, stay active
    _delay_ms(20); // min stab delay
}

uint8_t gspi_swap(uint8_t data) {
    uint8_t bitmask=128;
    uint8_t res=0;
    // software spi
    while(bitmask!=0) {
        // handle MOSI
        if (data&bitmask) {
            BITSET(GSPI_PORT, PIN_GSPI_MOSI); // transmit 1
        } else {
            BITCLR(GSPI_PORT, PIN_GSPI_MOSI); // transmit 0
        }
        _delay_loop_1(sck_dur);
        // handle MISO
        if(GSPI_PORT & (1<<PIN_GSPI_MISO)){
            res |= bitmask;
        }
        // handle SCK
        BITSET(GSPI_PORT, PIN_GSPI_SCK); // SCK high
        _delay_loop_1(sck_dur);
        _delay_loop_1(3); // make low and high pulse equaly long
        bitmask = bitmask>>1;
        BITCLR(GSPI_PORT, PIN_GSPI_SCK); // SCK low
    }
    return(res);
}
