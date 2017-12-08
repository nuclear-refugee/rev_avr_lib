#include "ASA_DEVICE.h"
#include "ASA_general.h"

void ASA_ID_set(uint8_t data) {
    ASA_REGPUT(ID_PORT, data, ID_MASK, ID_SHIFT);
};

void ASA_ID_init() {
    ASA_REGPUT(ID_DDR, 7, ID_MASK, ID_SHIFT);
};
