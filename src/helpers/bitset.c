#include "bitset.h"
#include <stdio.h>
#include <math.h>

unsigned long long bit_mask( unsigned long long b ) {
    return ((unsigned long long)1) << b;
}

unsigned long long bit_set( unsigned long long b, int idx ) {
    return b |= bit_mask(idx);
}

unsigned long long bit_clear( unsigned long long b, int idx ) {
    return b &= ~bit_mask(idx);
}

unsigned long long bit_test( unsigned long long b, int idx ) {
    return b & bit_mask(idx) ? 1:0;
}

unsigned long long bit_rotr( unsigned long long b, int shift, int size ) {
    unsigned long long m = pow(2,size)-1;
    if ((shift &= (size-1)) == 0) {
        return b;
    }
    return ((b >> shift) | (b << (size-shift))) & m;
}

unsigned long long bit_rotl( unsigned long long b, int shift, int size ) {
    unsigned long long m = pow(2,size)-1;
    if ((shift &= (size-1)) == 0) {
        return b;
    }
    return ((b << shift) | (b >> (size-shift))) & m;
}

unsigned long long bit_at( unsigned long long b, int idx, int size ) {
    return b & bit_mask(size-1-idx) ? 1:0;
}

unsigned long long bit_set_at( unsigned long long b, int idx, int size ) {
    return b |= bit_mask(size-1-idx);
}

unsigned long long bit_clear_at( unsigned long long b, int idx, int size ) {
    return b &= ~bit_mask(size-1-idx);
}

void bit_psid( unsigned long long b, int size ) {
    for(int i=0; i<size; i++) {
        fprintf(stdout, "%d", (int)bit_at(b, i, size));
        if( (i % 8 == 0) && (i != 0) ) {
            (void)fprintf(stdout, " ");
        }
    }
    return;
}

void bit_disp( unsigned long long b, int size ) {
    for(int i=0; i<size; i++) {
        fprintf(stdout, "%d", (int)bit_test(b, i));
        if( (i % 8 == 0) && (i != 0) ) {
            (void)fprintf(stdout, " ");
        }
    }
    return;
}