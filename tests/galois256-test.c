#include <assert.h>
#include "galois256.h"

int main( void ) {
    assert(gf256_add(0xaa,0xbb) == 0x11);
    assert(gf256_mul(0xaa,0xbb) == 0x56);
    assert(gf256_pow(0xaa,0x02) == 0xb2);
    return 0;
}
