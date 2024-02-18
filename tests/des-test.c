#include <stdio.h>
#include <assert.h>
#include "bitset.h"
#include "des.h"

typedef struct des_test_vectors {
    unsigned long key;
    unsigned long plainText;
    unsigned long cipherText;
} des_test_vectors_t;

#define N_TEST 5
des_test_vectors_t tests[N_TEST] = {
// IP & E Test Set
    { 0x0101010101010101, 0x95F8A5E5DD31D900, 0x8000000000000000 },
    { 0x0101010101010101, 0xDD7F121CA5015619, 0x4000000000000000 },
    { 0x0101010101010101, 0x2E8653104F3834EA, 0x2000000000000000 },
    { 0x0101010101010101, 0x4BD388FF6CD81D4F, 0x1000000000000000 },
    { 0x0101010101010101, 0x20B9E767B2FB1456, 0x0800000000000000 }

};

int main( void ) {
    for( int t = 0; t < N_TEST; t++ ) {
        assert( des_e(tests[0].plainText, tests[0].key ) == tests[0].cipherText );
        assert( des_d(tests[0].cipherText, tests[0].key ) == tests[0].plainText );
    }
    return 0;
}

