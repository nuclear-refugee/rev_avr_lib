#ifndef __ASA_ADC00_H__
#define __ASA_ADC00_H__

#include <inttypes.h>

#define ADC00_STATUS_SIMPLING 0
#define ADC00_STATUS_HOLDING  1

void ASA_ADC00_spi_init();
void ASA_ADC00_powerup(uint8_t ASA_ID);
uint8_t ASA_ADC00_set_channel(uint8_t ASA_ID, uint8_t channel);
uint8_t ASA_ADC00_set_status(uint8_t ASA_ID, uint8_t status);





uint8_t ASA_ADC00_get(uint8_t ASA_ID, uint8_t channel, void* data_p);
void ASA_ADC00_spi_init();



// char ASA_DAC00_set(char ASA_ID, char LSByte, char Mask, char shift, char Data);
// char ASA_DAC00_put(char ASA_ID, char LSByte, char Mask, char shift, char Data);
// char ASA_DAC00_get(char ASA_ID, char LSByte, char Mask, char shift, char Data);


#endif // __ASA_ADC00_H__
