#ifndef __ASA_GENERAL_H__
#define __ASA_GENERAL_H__

#define ASA_REGPUT(dest, data, mask, shift) (dest = (((dest)&(~mask)) | ((data <<shift) & mask)))
#define ASA_REGGET(dest, mask, shift) (((dest) & (mask)) >> shift)

#include <inttypes.h>
#include "ASA_DEVICE.h"

/**
* @brief ASA_ID_set()
*/
void ASA_ID_set(uint8_t data);
/**
* @brief ASA_ID_init()
*/
void ASA_ID_init();

#endif /* _ASA_GENERAL_H_ */
