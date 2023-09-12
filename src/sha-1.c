/**
 * @file sha-1.c
 * @brief SHA-1 implementation.
 * Message size < 2^64
 * Block size = 512 bits
 * Word size = 32 bits
 * Message digest size = 160 bits
 * @author Nicolas Misbert 
 * @version NIST.FIPS.180-4
 * @date 11/09/2023
 */
#include <stdint.h>
#include "sha-1.h"

// Section 5.3.1 : SHA-1 Initial Hash Value
void sha1_H( uint32_t H0[5] )
{
    H0[0] = 0x67452301;
    H0[1] = 0xefcdab89;
    H0[2] = 0x98badcfe;
    H0[3] = 0x10325476;
    H0[4] = 0xc3d2e1f0;
}

// Section 4.2.1 : SHA-1 Constants
uint32_t sha1_K( int t )
{
    if( (0 <= t) && (t <= 19) ) {
        return 0x5a827999;
    } else if( (20 <= t) && (t <= 39) ) {
        return 0x6ed9eba1;
    } else if( (40 <= t) && (t <= 59) ) {
        return 0x8f1bbcdc;
    } else if( (60 <= t) && (t <= 79) ) {
        return 0xca62c1d6;
    } else {
        return 0;
    }
}

/** Section 4.1.1 : SHA-1 Functions (Ch)
 * @param[in] x A 32-bit word
 * @param[in] y A 32-bit word
 * @param[in] z A 32-bit word
 * @return A 32-bit word output
 */
uint32_t sha1_Ch ( uint32_t x, uint32_t y, uint32_t z )
{
    return (x & y) ^ (~x & z);
}

/** Section 4.1.1 : SHA-1 Functions (Parity)
 * @param[in] x A 32-bit word
 * @param[in] y A 32-bit word
 * @param[in] z A 32-bit word
 * @return A 32-bit word output
 */
uint32_t sha1_Parity ( uint32_t x, uint32_t y, uint32_t z )
{
    return x ^ y ^ z;
}

/** Section 4.1.1 : SHA-1 Functions (Maj)
 * @param[in] x A 32-bit word
 * @param[in] y A 32-bit word
 * @param[in] z A 32-bit word
 * @return A 32-bit word output
 */
uint32_t sha1_Maj ( uint32_t x, uint32_t y, uint32_t z )
{
    return (x & y) ^ (x & z) ^ (y & z);
}

/** Section 4.1.1 : SHA-1 Functions (f_t)
 * @param[in] x A 32-bit word
 * @param[in] y A 32-bit word
 * @param[in] z A 32-bit word
 * @param[in] t function step
 * @return A 32-bit word output
 */
uint32_t sha1_f ( uint32_t x, uint32_t y, uint32_t z, int t )
{
    if( (0 <= t) && (t <= 19) ) {
        return sha1_Ch( x, y, z );
    } else if( (20 <= t) && (t <= 39) ) {
        return sha1_Parity( x, y, z );
    } else if( (40 <= t) && (t <= 59) ) {
        return sha1_Maj( x, y, z );
    } else if( (60 <= t) && (t <= 79) ) {
        return sha1_Parity( x, y, z );
    } else {
        return 0;
    }
}

int sha1_step ( const uint8_t Mi[SHA_1_N], const uint32_t Hi[5], uint32_t Ho[5] )
{
    uint32_t W[80]; 
    // 1. Prepare the message schedule 
    for( int t = 0; t < 80; t++ ) {
        if( (0 <= t) && (t <= 15) ) {
            W[t] = (((uint32_t)Mi[t+3] << 24) & 0xff000000)
                 + (((uint32_t)Mi[t+2] << 16) & 0x00ff0000) 
                 + (((uint32_t)Mi[t+1] <<  8) & 0x0000ff00) 
                 + (uint32_t)Mi[t+0] & 0x000000ff;
        } else if( (16 <= t) & (t <= 79) ) {
            W[t] = sha_ROTL_32( W[t-3] ^ W[t-8] ^ W[t-14] ^ W[t-16], 1 );
        } else {
            return -1;
        }
    }
    // 2. Initialize the five working variables 
    uint32_t a = Hi[0], b = Hi[1], c = Hi[2], d = Hi[3], e = Hi[4];
    uint32_t T = 0;
    // 3. 
    for( int t = 0; t < 80; t++ ) {
        T = sha_ROTL_32( a, 5 ) + sha1_f( b, c, d, t ) + e + sha1_K( t ) + W[t];
        e = d;
        d = c;
        c = sha_ROTL_32( b, 30 );
        b = a;
        a = T;
    }
    // 4. Intermediate hash value
    Ho[0] = a + Hi[0];
    Ho[1] = b + Hi[1];
    Ho[2] = c + Hi[2];
    Ho[3] = d + Hi[3];
    Ho[4] = e + Hi[4];
    return 0;
}

