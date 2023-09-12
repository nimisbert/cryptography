#ifndef SHA_COMMON_H
#define SHA_COMMON_H
#include <stdint.h>

#define SHA_1_N 64

int      sha_padding_512 ( const uint8_t input[SHA_1_N], int s, uint64_t l, uint8_t output[SHA_1_N] );
uint32_t sha_ROTL_32 ( uint32_t x, int n );
uint32_t sha_ROTL_32 ( uint32_t x, int n );

#endif