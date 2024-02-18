#include <stdio.h>
#include "des.h"
#include "bitset.h"

unsigned long long des_IP( unsigned long long input ) {
    unsigned long long out = 0;
    for( int i=0; i<64; i++ ) {
        if( bit_at(input, (IPBox[i]-1), 64) ) {
            out = bit_set_at(out, i, 64);
        } else {
            out = bit_clear_at(out, i, 64);
        }
    }
    return out;
}

unsigned long long des_iIP( unsigned long long input ) {
    unsigned long long out = 0;
    for( int i=0; i<64; i++ ) {
        if( bit_at(input, (iIPBox[i]-1), 64) == 1 ) {
            out = bit_set_at(out, i, 64);
        } else {
            out = bit_clear_at(out, i, 64);
        }
    }
    return out;
}

unsigned long long des_PC1( unsigned long long input ) {
    unsigned long long out = 0;
    int i = 0, j = 0;
    for( i=0; i<64; i++ ) {
        if( (i%8!=0) || (i==0) ) {                  //< MSB bit of each byte is ignored
            if( bit_at(input, PC1Box[j]-1, 64) ) {
                out = bit_set_at(out, j, 56);
            } else {
                out = bit_clear_at(out, j, 56);
            }
            j++;
        }
    }
    return out & 0x00ffffffffffffff;
}

unsigned long long des_PC2( unsigned long long input ) {
    unsigned long out = 0;
    int i = 0;
    for( i=0; i<48; i++ ) {
        if( bit_at(input, PC2Box[i]-1, 56) ) {
            out = bit_set_at(out, i, 48);
        } else {
            out = bit_clear_at(out, i, 48);
        }
    }
    return out & 0x0000ffffffffffff;
}

unsigned long long des_E( unsigned long long input ) {
    unsigned long out = 0;
    int i = 0;
    for( i=0; i<48; i++ ) {
        if( bit_at(input, EBox[i]-1, 32) ) {
            out = bit_set_at(out, i, 48);
        } else {
            out = bit_clear_at(out, i, 48);
        }
    }
    return out & 0x0000ffffffffffff;
}

unsigned long long des_P( unsigned long long input ) {
    unsigned long long out = 0;
    int i = 0;
    for( i=0; i<32; i++ ) {
        if( bit_at(input, PBox[i]-1, 32) ) {
            out = bit_set_at(out, i, 32);
        } else {
            out = bit_clear_at(out, i, 32);
        }
    }
    return out & 0x00000000ffffffff;
}

unsigned char des_S( unsigned char input, int n ) {
    unsigned char r = ((input >> 0) & 0x01)
                    | ((input >> 4) & 0x02);
    unsigned char c = (input >> 1) & 0x0f;
    return SBox[n][r][c];
}

void des_KS( unsigned long long Kin, unsigned long long Kout[16] ) {
    unsigned long long K=0, C=0, D=0;
    K = des_PC1(Kin);
    D = 0x000000000fffffff & K;
    C = 0x000000000fffffff & ((unsigned long long)K >> 28);
    for( int i=0; i<16; i++ ) {
        D = bit_rotl(D, ShiftBox[i], 28);
        C = bit_rotl(C, ShiftBox[i], 28);
        Kout[i] = des_PC2(((C<<28) | D) & 0x00ffffffffffffff);
    }
    return; 
}

unsigned long long des_f( unsigned long long R, unsigned long long K ) {
    unsigned long long E=0, EK=0, out=0;
    unsigned long long Si=0;
    E = des_E(R);
    EK = E^K;
    for( int i=0; i<8; i++ ) {
        Si = des_S((EK >> (6*(7-i))),i);
        out |= (((unsigned long long) Si) << (4*(7-i)));
    }
    return des_P(out);
}

unsigned long long des_e( unsigned long long input, unsigned long long key ) {
    unsigned long long IP=0, L=0, R=0, temp = 0, K[16];
    int i = 0;
    IP = des_IP(input);
    R = IP       & 0x00000000ffffffff;
    L = (IP>>32) & 0x00000000ffffffff;
    (void) des_KS( key, K );
    for( i=0; i<16; i++ ) {
        temp = L ^ des_f(R, K[i]);
        L = R;
        R = temp;
    }
    return des_iIP((R<<32) | L);
}

unsigned long long des_d( unsigned long long input, unsigned long long key ) {
    unsigned long long IP = 0, L = 0, R = 0, temp = 0, K[16];
    IP = des_IP(input);
    R = IP       & 0x00000000ffffffff;
    L = (IP>>32) & 0x00000000ffffffff;
    (void) des_KS( key, K );
    for( int i=15; i>=0; i-- ) {
        temp = L ^ des_f(R, K[i]);
        L = R;
        R = temp;
    }
    return des_iIP((R<<32) | L);
}