/**
 * @file ASA_UARTS.c
 * @author LiYu
 * @date 2018.03.06
 * @brief buffer functions implement.
 *
 */

#include "../buffer.h"

inline uint8_t buf_is_full(Buf_t buf) {
    // NOTE if you change BUFFSIZE to other num you should get the rem of (buf.e+1)
    return (buf.e+1 == buf.s);
}

inline uint8_t buf_is_null(Buf_t buf) {
    return (buf.e == buf.s);
}

inline uint8_t buf_read(Buf_t *buf_p) {
    buf_p->s ++;
    return buf_p->data[ buf_p->s - 1 ];
}

inline uint8_t buf_read2(Buf_t *buf_p, uint8_t* data_p) {
    if ( buf_is_null(*buf_p) ) {
        return 1;
    } else {
        buf_p->s ++;
        *data_p = buf_p->data[ buf_p->s - 1 ];
        return 0;
    }
}

inline void buf_write(Buf_t* buf_p, uint8_t data) {
    buf_p->data[ buf_p->e ] = data;
    buf_p->e ++;
}

inline uint8_t buf_write2(Buf_t* buf_p, uint8_t data) {
    if ( buf_is_full(*buf_p) ) {
        return 1;
    } else {
        buf_p->e ++;
        buf_p->data[ buf_p->e ] = data;
        return 0;
    }
}
