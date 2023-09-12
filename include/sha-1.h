#ifndef SHA_1_H
#define SHA_1_H
#include <stdint.h>
#include "sha.h"

uint32_t sha1_Ch     ( uint32_t x, uint32_t y, uint32_t z );
uint32_t sha1_Parity ( uint32_t x, uint32_t y, uint32_t z );
uint32_t sha1_Maj    ( uint32_t x, uint32_t y, uint32_t z );
uint32_t sha1_f      ( uint32_t x, uint32_t y, uint32_t z, int t );
uint32_t sha1_K      ( int t );

void     sha1_H      ( uint32_t H0[5] );
int      sha1_step   ( const uint8_t Mi[SHA_1_N], const uint32_t Hi[5], uint32_t Ho[5] );

int      sha1_H_to_digest ( const uint32_t H[5], uint8_t digest[20] );

#endif