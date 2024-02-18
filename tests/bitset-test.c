#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include "bitset.h"

int main( void ) {
    assert(bit_set(0x00, 0)  == 0x01);
    assert(bit_test(0x100, 8) == 0x01);
    assert(bit_test(0x80, 7) == 0x01);
    assert(bit_set(0x00, 8)  == 0x100);
    assert(bit_set(0x00, 16) == 0x10000);
    assert(bit_set(0x00, 24) == 0x1000000);
    assert(bit_set(0x00, 32) == 0x100000000);
    assert(bit_set(0x00, 40) == 0x10000000000);
    assert(bit_set(0x00, 48) == 0x1000000000000);
    assert(bit_set(0x00, 56) == 0x100000000000000);
    assert(bit_set(0x00, 64) == 0x01); // overflow up to 64, bit array [63:0];
    assert(bit_rotr(0x0000000000000001, 1, 64) == 0x8000000000000000);
    assert(bit_rotl(0x8000000000000000, 1, 64) == 0x1);
    assert(bit_rotr(0x0000000000000001, 1, 32) == 0x80000000);
    assert(bit_rotl(0x0000000080000000, 1, 32) == 0x1);
    return 0;
}