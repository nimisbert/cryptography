#include "galois256.h"

unsigned char gf256_add( unsigned char a, unsigned char b ) {
    return a ^ b;
}

unsigned char gf256_mul( unsigned char a, unsigned char b ) {
    unsigned short p = 0x00;
    const unsigned short at = a, bt = b;
    for( int bit = 7; bit >= 0; bit--) {
        if( bt & (1<<bit) ) {
            p = p ^ (at << bit);
        }
    }
    unsigned char irr  = 0x1b;
    const unsigned short high = 0x0100;
    for( int bit = 7; bit >= 0; bit--) {
        if( p & ( high << bit )) {
            p = p ^ (irr << bit);
        }
    }
    return (unsigned char)p;
} 

unsigned char gf256_pow( unsigned char a, unsigned char p ) {
    unsigned char e = a;
    if( p <= 0) {
        e = 0x01;
    } else if (p > 0) {
        for( int i = 1; i<p; i++) {
            e = gf256_mul( e, a);
        }
    }
    return e;
}
