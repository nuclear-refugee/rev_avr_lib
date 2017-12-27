#include "rev_gpio_spi.h"
#include "rev_DEVICE.h"
#include "bit_op.h"
#include "rev_spi.h"

static enum spi_data_mode sspi_data_mode = mode_LRSL;

void sspi_set_datamode(enum spi_data_mode mode) {
    sspi_data_mode = mode;
}

// TODO inpleent SCK duration
uint8_t sck_dur = 0;

static inline void sck_high() {
    BITSET(GSPI_PORT, PIN_GSPI_SCK);
}
static inline void sck_low() {
    BITCLR(GSPI_PORT, PIN_GSPI_SCK);
}
static inline void mosi_high() {
    BITSET(GSPI_PORT, PIN_MOSI);
}
static inline void mosi_low() {
    BITCLR(GSPI_PORT, PIN_MOSI);
}
static inline void put_bit(uint8_t b) {
    if(b){
        mosi_high();
    } else {
        mosi_low();
    }
}
static inline uint8_t get_bit() {
    return BITCLR(GSPI_PORT, PIN_MISO);
}

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
    uint8_t res = 0;
    switch (sspi_data_mode) {
        case mode_LRSL: {
            put_bit(data&(1<<7));
            sck_high();
            res |= get_bit()<<7;
            sck_low();
            put_bit(data&(1<<6));
            sck_high();
            res |= get_bit()<<6;
            sck_low();
            put_bit(data&(1<<5));
            sck_high();
            res |= get_bit()<<5;
            sck_low();
            put_bit(data&(1<<4));
            sck_high();
            res |= get_bit()<<4;
            sck_low();
            put_bit(data&(1<<3));
            sck_high();
            res |= get_bit()<<3;
            sck_low();
            put_bit(data&(1<<2));
            sck_high();
            res |= get_bit()<<2;
            sck_low();
            put_bit(data&(1<<1));
            sck_high();
            res |= get_bit()<<1;
            sck_low();
            put_bit(data&(1<<0));
            sck_high();
            res |= get_bit()<<0;
            sck_low();
            return res;
        }
        case mode_LRST:
            break;
        case mode_LFSL:
            break;
        case mode_LFST:
            break;
    }
    // uint8_t bitmask=128;
    // uint8_t res=0;
    // // software spi
    // while(bitmask!=0) {
    //     // handle MOSI
    //     if (data&bitmask) {
    //         BITSET(GSPI_PORT, PIN_GSPI_MOSI); // transmit 1
    //     } else {
    //         BITCLR(GSPI_PORT, PIN_GSPI_MOSI); // transmit 0
    //     }
    //     _delay_loop_1(sck_dur);
    //     // handle MISO
    //     if(GSPI_PORT & (1<<PIN_GSPI_MISO)){
    //         res |= bitmask;
    //     }
    //     // handle SCK
    //     BITSET(GSPI_PORT, PIN_GSPI_SCK); // SCK high
    //     _delay_loop_1(sck_dur);
    //     _delay_loop_1(3); // make low and high pulse equaly long
    //     bitmask = bitmask>>1;
    //     BITCLR(GSPI_PORT, PIN_GSPI_SCK); // SCK low
    // }
    // return(res);
}
