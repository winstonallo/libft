#ifndef BIT_H
#define BIT_H

#include <stdint.h>

// Rotates `val` to the left by `by` bits.
uint32_t rotl_32(uint32_t val, uint32_t by) __attribute__ ((always_inline));

// Rotates `val` to the right by `by` bits.
uint32_t rotr_32(uint32_t val, uint32_t by) __attribute__ ((always_inline));

#endif