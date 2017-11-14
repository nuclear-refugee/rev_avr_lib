#ifndef __bit_op_h__
#define __bit_op_h__

#define BITSET(ADDRESS,BIT)    (ADDRESS |= (1<<BIT))
#define BITCLR(ADDRESS,BIT)    (ADDRESS &= ~(1<<BIT))
#define BITCHK(ADDRESS,BIT)    ((ADDRESS & (1<<BIT))==(1<<BIT))

#define REGPUT(ADDRESS, MASK, DATA) (ADDRESS = ((ADDRESS)&(~MASK)) | ((DATA) & (MASK)))

#endif
