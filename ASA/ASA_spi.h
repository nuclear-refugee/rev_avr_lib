#ifndef __ASA_SPI_H__
#define __ASA_SPI_H__

#include "../rev_spi.h"

/**
* @brief Init ASA_SPI_CS pin 
*/
void ASA_SPIM_cs_init();

/**
* @brief set ASA_SPI_CS
*/
void ASA_SPIM_cs(uint8_t isEnable);

/**
* @brief Replace of ASA_SPI_trm()
*/
char ASA_SPIM_trm(char isOneSLA, char isOneReg, char SPIID, char RegAdd, char Bytes, void *Data_p);
/**
 * @brief Replace of ASA_SPI_rec()
 */
char ASA_SPIM_rec(char isOneSLA, char isOneReg, char SPIID, char RegAdd, char Bytes, void *Data_p);
/**
* @brief Replace of ASA_SPI_ftm()
*/
char ASA_SPIM_ftm(char isOneSLA, char isOneReg, char SPIID, char RegAdd, char Mask, char shift, char Data);
/**
* @brief Replace of M128_SPI_frc()
*/
char ASA_SPIM_frc(char isOneSLA, char isOneReg, char SPIID, char RegAdd, char Mask, char shift, char* Data_p);

#endif /* __ASA_SPI_H__ */
