#include "sha.h"

/** Section 5.1.1 : 512-bit message padding
 * @param[in] input[s] A clearText message
 * @param[in] s size of the clearText message
 * @param[in] l size of the full length message in bits
 * @param[out] output[SHA_1_N] A padded clearText message
 * @return error -1 no padding done, 0 padded
 */
int sha_padding_512( const uint8_t input[SHA_1_N], int s, uint64_t l, uint8_t output[SHA_1_N] )
{
    int k = 56 - s; // l + 1 + k = 448 mod 512, for bytes
    int j = 56;
    if( k > 0 ) {
        for( int i = 0; i < SHA_1_N; i++ ) {
            if( (i < s) && (i < k) ) {
                output[i] = input[i];
            } else if ( (i==s) && (i < k) ) {
                output[i] = 0x80;
            } else if ( (i > s) && (i < s+k) ) {
                output[i] = 0x00;
            } else {
                output[i] = (uint8_t)((l >> j) & 0x00000000000000ff); 
                j -= 8;
            }
        }
    } else {
        return -1;
    }
    return 0;
}

uint32_t sha_ROTL_32( uint32_t x, int n )
{
    return ( x << n ) | ( x >> (32 - n) );
}

uint32_t sha_ROTR_32( uint32_t x, int n )
{
    return ( x >> n ) | ( x << (32 - n) );
}