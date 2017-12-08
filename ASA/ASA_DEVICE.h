#ifndef __ASA_DEVICE_H__
#define __ASA_DEVICE_H__

#if defined (__AVR_ATmega128__)
#include "ASA_M128.h"
#elif defined (__AVR_ATmega88__)
#include "ASA_M88.h"
#else
#  if !defined(__COMPILING_AVR_LIBC__)
#    warning "device type not defined"
#  endif
#endif


#endif
