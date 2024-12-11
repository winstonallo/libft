#ifndef BIT_H
#define BIT_H

#include <stdint.h>

#define ROTL_32(val, by) (((by) & 31) == 0 ? (val) : ((val) << ((by) & 31)) | ((val) >> (32 - ((by) & 31))))

#define ROTR_32(val, by) (((by) & 31) == 0 ? (val) : ((val) >> ((by) & 31)) | ((val) << (32 - ((by) & 31))))

#endif
