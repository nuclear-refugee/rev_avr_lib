/**
 * @file buff.h
 * @author LiYu
 * @date 2018.03.06
 * @brief buffer functions prototype.
 *
 */

#ifndef __BUFFER_H__
#define __BUFFER_H__

#include <inttypes.h>

#define BUFFSIZE 255;

struct BUFFER {
    uint8_t data[255];
    uint8_t s; ///< The start index of data array
    uint8_t e; ///< The end index of data array
};

typedef struct BUFFER Buf_t;

inline uint8_t buf_is_full(Buf_t buf);

inline uint8_t buf_is_null(Buf_t buf);

inline uint8_t buf_read(Buf_t *buf_p);

inline uint8_t buf_read2(Buf_t *buf_p, uint8_t* data_p);

inline void buf_write(Buf_t* buf_p, uint8_t data);

inline uint8_t buf_write2(Buf_t* buf_p, uint8_t data);

#endif /* __BUFFER_H__ */
