#include "../rev_DEVICE.h"
#include "../rev_serial.h"
#include "../rev_spi.h"
#include "../ASA/ASA_DAC00.h"
#include "../ASA/ASA_ADC00.h"

int main() {
    rev_serial_init();
    printf("ADC00 test2\n");
    ASA_ADC00_spi_init();
    uint8_t ADC00_ID = 1;
    uint16_t data1 = 0;
    uint16_t data2 = 0;
    uint8_t res = 0;
    DDRF = 0xF0;

    ASA_ADC00_powerup(ADC00_ID);

    res = ASA_ADC00_set_channel(ADC00_ID,2);

    res = ASA_ADC00_set_status(ADC00_ID,ADC00_STATUS_SIMPLING);
    while (1) {


        printf("data = %d %d\n", data1, data2);
    }

    return 0;
}
