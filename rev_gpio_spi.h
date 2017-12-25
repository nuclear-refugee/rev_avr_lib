#ifndef __REV_GSPI_H__
#define __REV_GSPI_H__

#define GSPI_PORT PORTA
#define GSPI_DDR  DDRA
#define GSPI_PIN  PINA
#define PIN_GSPI_SS   PA0
#define PIN_GSPI_CS   PA0
#define PIN_GSPI_SCK  PA1
#define PIN_GSPI_MOSI PA2
#define PIN_GSPI_MISO PA3

#include <inttypes.h>

void gspi_master_init();


// enum spi_freq_devider {
//     devider_2,   ///< set spi devider as 2
//     devider_4,   ///< set spi devider as 4
//     devider_8,   ///< set spi devider as 8
//     devider_16,  ///< set spi devider as 16
//     devider_32,  ///< set spi devider as 32
//     devider_64,  ///< set spi devider as 64
//     devider_128, ///< set spi devider as 128
// };
//
// /**
//  * @brief Set spi frequency.
//  *
//  */
// uint8_t spi_set_frequency(enum spi_freq_devider devider);
//
// enum spi_data_mode {
//     mode_LRSL = 0, ///< Leading edge Rising, Sampling at Leading  edge, CPOL = 0, CPHA = 0
//     mode_LFSL = 1, ///< Leading edge Fallng, Sampling at Leading  edge, CPOL = 1, CPHA = 0
//     mode_LRST = 2, ///< Leading edge Rising, Sampling at Trailing edge, CPOL = 0, CPHA = 1
//     mode_LFST = 3, ///< Leading edge Rising, Sampling at Trailing edge, CPOL = 1, CPHA = 1
// };
//
// /**
//  * @brief Set spi datamode.(Leading edge and Sampling edge)
//  *
//  * default is Leading edge Rising, Sampling at Leading  edge, CPOL = 0, CPHA = 0
//  */
// uint8_t spi_set_datamode(enum spi_data_mode mode);
//
// enum spi_data_order {
//     order_MSB = 0, ///< MSB of the data word is transmitted first, DORD = 0
//     order_LSB = 1, ///< LSB of the data word is transmitted first, DORD = 1
// };
// /**
//  * @brief Set spi data order to LSB or MSB. (default is MSB)
//  *
//  */
// uint8_t spi_set_dataorder(enum spi_data_order order);
//
// /**
//  * @brief Set spi as master.
//  *
//  */
// uint8_t spi_master_init();
//
// /**
//  * @brief Set spi as slave.
//  *
//  */
// uint8_t spi_slave_init();
//
// /**
//  * @brief Switch SPI to Enable or Disable.
//  *
//  */
// uint8_t spi_en(uint8_t isEnable);
//
// /**
//  * @brief Switch SPI interrupt to Enable or Disable.
//  *
//  */
// uint8_t spi_en_int(uint8_t isEnable);
//
// /**
//  * @brief Swap SPI data.
//  *
//  */
// uint8_t spi_swap(uint8_t data);

#endif /* __REV_GSPI_H__ */
