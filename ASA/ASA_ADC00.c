/**
 * @file ASA_ADC00.c
 * @author PooZhiPig
 * @date 2018.01.26
 * @brief ASA_ADC00 function implement.
 *
 * ASA_ADC00 use ic "ADS7883".
 */

#include "ASA_ADC00.h"
#include "ASA_DEVICE.h"
#include "ASA_general.h"
#include "ASA_spi.h"
#include "../rev_spi.h"


// channel control pins defines
#define CH_PORT  BUS_DIO_PORT
#define CH_DDR   BUS_DIO_DDR
#define CH_PIN   BUS_DIO_PIN
#define CH_SHIFT BUS_DIO2
#define CH_MASK  (_BV(BUS_DIO2)|_BV(BUS_DIO3))

// channel control pins defines
#define STAT_PORT  BUS_DIO_PORT
#define STAT_DDR   BUS_DIO_DDR
#define STAT_PIN   BUS_DIO_PIN
#define STAT_SHIFT BUS_DIO1
#define STAT_MASK  _BV(BUS_DIO1)

inline void set_ch(uint8_t channel);
inline void set_hold();
inline void set_sampling();

void ASA_ADC00_spi_init() {
    ASA_SPIM_cs_init();
    spi_master_init();
    spi_set_frequency(devider_16);
    spi_set_datamode(mode_LRSL);
    spi_en(1);
    ASA_ID_init();

};

void ASA_ADC00_powerup(uint8_t ASA_ID) {
    ASA_REGPUT(  CH_PORT,   CH_MASK,   CH_MASK,   CH_SHIFT);
    ASA_REGPUT(STAT_PORT, STAT_MASK, STAT_MASK, STAT_SHIFT);
    ASA_ID_set(ASA_ID);
    ASA_SPIM_cs(1);
    // ADS7883 will exit power low after 10 SCK falling edges
    spi_swap(0x00);
    spi_swap(0x00);

    ASA_SPIM_cs(0);
    ASA_ID_set(0);
}

uint8_t ASA_ADC00_set_channel(uint8_t ASA_ID, uint8_t channel) {
    if (ASA_ID>7) {
        return 1;
    } else if (channel>3) {
        return 2;
    }
    ASA_ID_set(ASA_ID);
    ASA_SPIM_cs(1);
    set_ch(channel);
    ASA_SPIM_cs(0);
    ASA_ID_set(0);
    return 0;
}

uint8_t ASA_ADC00_set_status(uint8_t ASA_ID, uint8_t status) {
    if (ASA_ID>7) {
        return 1;
    } else if (status>1) {
        return 2;
    }
    ASA_ID_set(ASA_ID);
    ASA_SPIM_cs(1);
    if (status == ADC00_STATUS_HOLDING) {
        set_hold();
    } else if (status == ADC00_STATUS_SIMPLING) {
        set_sampling();
    }

    ASA_SPIM_cs(0);
    ASA_ID_set(0);

    return 0;
}


uint8_t ASA_ADC00_get(uint8_t ASA_ID, uint8_t channel, void* data_p) {
    if (ASA_ID>7) {
        return 1;
    } else if (channel>2) {
        return 2;
    }
    ASA_ID_set(ASA_ID);
    ASA_SPIM_cs(1);

    // switch to sampling channel
    set_ch(3);
    // switch to target channel
    set_ch(channel);

    uint8_t H = spi_swap(0);
    uint8_t L = spi_swap(0);
    *(uint16_t*)data_p = (H<<6) + (L>>2);
    ASA_SPIM_cs(0);
    ASA_ID_set(0);
    return 0;
}

/**
 * @brief Set the channel ADC00, will set PF7,8 as channel 0~2
 */
inline void set_ch(uint8_t channel) {
    ASA_REGPUT(CH_PORT, channel, CH_MASK, CH_SHIFT);
}

inline void set_hold() {
    ASA_REGPUT(STAT_PORT, ADC00_STATUS_HOLDING, STAT_MASK, STAT_SHIFT);
}

inline void set_sampling() {
    ASA_REGPUT(STAT_PORT, ADC00_STATUS_SIMPLING, STAT_MASK, STAT_SHIFT);
}
