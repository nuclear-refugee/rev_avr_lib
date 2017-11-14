#ifndef __REV_DEVICE_H__
#define __REV_DEVICE_H__

#include <avr\io.h>
#include <avr\interrupt.h>
#include <stdio.h>
#include <util\delay.h>
#include <inttypes.h>

#if defined (__AVR_ATmega128__)
#include "rev_MEGA128.h"
#elif defined (__AVR_ATmega88__)
#include "rev_MEGA88.h"
#else
#  if !defined(__COMPILING_AVR_LIBC__)
#    warning "device type not defined"
#  endif
#endif


#endif
