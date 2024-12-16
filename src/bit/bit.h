#ifndef BIT_H
#define BIT_H

#include <stdint.h>

#define ROTL_32(val, by) (((by) & 31) == 0 ? (val) : ((val) << ((by) & 31)) | ((val) >> (32 - ((by) & 31))))
#define ROTR_32(val, by) (((by) & 31) == 0 ? (val) : ((val) >> ((by) & 31)) | ((val) << (32 - ((by) & 31))))

#define BSWAP_32(val) (((val) & 0xFF000000U) >> 24) | (((val) & 0x00FF0000U) >> 8) | (((val) & 0x0000FF00U) << 8) | (((val) & 0x000000FFU) << 24)

#endif
