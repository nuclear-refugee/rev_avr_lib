#ifndef __ASA_GENERAL_H__
#define __ASA_GENERAL_H__

#define ASA_REGPUT(dest, data, mask, shift) (dest = (((dest)&(~mask)) | ((data <<shift) & mask)))
#define ASA_REGGET(dest, mask, shift) (((dest) & (mask)) >> shift)

#include <inttypes.h>

/**
* @brief ASA_ID_set()
*/
inline void ASA_ID_set(uint8_t data);
/**
* @brief ASA_ID_init()
*/
inline void ASA_ID_init();

#endif /* _ASA_GENERAL_H_ */
