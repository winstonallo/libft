#ifndef BIT_H
#define BIT_H

#define ROTL_32(val, by) (((by) & 31) == 0 ? (val) : ((val) << ((by) & 31)) | ((val) >> (32 - ((by) & 31))))
#define ROTR_32(val, by) (((by) & 31) == 0 ? (val) : ((val) >> ((by) & 31)) | ((val) << (32 - ((by) & 31))))

#define BSWAP_32(val) ((((val) & 0xFF000000U) >> 24) | (((val) & 0x00FF0000U) >> 8) | (((val) & 0x0000FF00U) << 8) | (((val) & 0x000000FFU) << 24))
#define BSWAP_64(val)                                                                                                                                          \
    ((((val) & 0xFF00000000000000ULL) >> 56) | (((val) & 0x00FF000000000000ULL) >> 40) | (((val) & 0x0000FF0000000000ULL) >> 24) |                             \
     (((val) & 0x000000FF00000000ULL) >> 8) | (((val) & 0x00000000FF000000ULL) << 8) | (((val) & 0x0000000000FF0000ULL) << 24) |                               \
     (((val) & 0x000000000000FF00ULL) << 40) | (((val) & 0x00000000000000FFULL) << 56))

#endif
