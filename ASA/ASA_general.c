#include "ASA_DEVICE.h"
#include "ASA_general.h"

inline void ASA_ID_set(uint8_t data) {
    ASA_REGPUT(ID_PORT, data, ID_MASK, ID_SHIFT);
};

inline void ASA_ID_init() {
    ASA_REGPUT(ID_DDR, ID_MASK, ID_MASK, ID_SHIFT);
};
