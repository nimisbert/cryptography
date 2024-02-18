#include "aes.h"
#include "galois256.h"

unsigned char aes_substitute( unsigned char a ) {
    return SBox[ (a>>4) & 0x0f ][ a & 0x0f ];
}

void aes_sub_bytes( unsigned char s[4][8], int Nb ) {
    for( int r = 0; r < 4; r++ ) {
        for( int c = 0; c < Nb; c++ ) {
            s[r][c] = aes_substitute( s[r][c] );
        }
    }
}

void aes_shift_rows( unsigned char s[4][8], int Nb ) {
    unsigned char t[4][8];
    for( int r = 0; r < 4; r++) {
        for( int c = 0; c < Nb; c++) {
            t[r][c] = s[r][c];
        }
    }
    for( int r = 0; r < 4; r++) {
        for( int c = 0; c < Nb; c++) {
            s[r][c] = t[r][(c+r)%Nb];
        }
    }
    return;
}

void aes_mix_columns( unsigned char s[4][8], int Nb ) {
    unsigned char t[4][8];
    for( int i = 0; i < 4; i++ ) {
        for( int j = 0; j < Nb; j++ ) {
            t[i][j] = s[i][j];
        }
    }
    for( int c = 0; c < Nb; c++ ) {
        s[0][c] = gf256_mul( t[0][c] , 0x02 ) ^ gf256_mul( t[1][c] , 0x03 ) ^ t[2][c] ^ t[3][c];
        s[1][c] = t[0][c] ^ gf256_mul( t[1][c] , 0x02 ) ^ gf256_mul( t[2][c] , 0x03 ) ^ t[3][c];
        s[2][c] = t[0][c] ^ t[1][c] ^ gf256_mul( t[2][c] , 0x02 ) ^ gf256_mul( t[3][c] , 0x03 );
        s[3][c] = gf256_mul( t[0][c] , 0x03 ) ^ t[1][c] ^ t[2][c] ^ gf256_mul( t[3][c] , 0x02 );
    }
}

void aes_add_round_key( unsigned char s[4][8], unsigned long w[8], int Nb, int round ) {
    for( int c = 0; c<Nb; c++) {
        s[0][c] = s[0][c] ^ ((w[round * Nb + c] >> 24) & 0xff);
        s[1][c] = s[1][c] ^ ((w[round * Nb + c] >> 16) & 0xff);
        s[2][c] = s[2][c] ^ ((w[round * Nb + c] >>  8) & 0xff);
        s[3][c] = s[3][c] ^ ((w[round * Nb + c] >>  0) & 0xff);
    }
    return;
}

unsigned long aes_sub_word( unsigned long w ) {
    unsigned char t[4];
    for( int i = 0; i<4; i++ ) {
        t[i] = aes_substitute((w >> (8*i)) & 0x000000ff);
    }
    return (t[3] << 24) + (t[2] << 16) + (t[1] << 8) + (t[0] << 0);
}

unsigned long aes_rot_word( unsigned long w ) {
    unsigned char a[4];
    a[0] = (w >> 24) & 0xff;
    a[1] = (w >> 16) & 0xff;
    a[2] = (w >>  8) & 0xff;
    a[3] = (w >>  0) & 0xff;
    return (a[1] << 24) + (a[2] << 16) + (a[3] << 8) + (a[0] << 0);
}

unsigned long aes_rcon( int i ) {
    return 0xff000000 & (gf256_pow( 0x02, i-1 ) << 24 );
}

void aes_key_expansion( const unsigned char key[4*8], unsigned long w[(8*(14+1)) + (8 % 4) ], int Nb, int Nk, int Nr ) {
    int i = 0;
    unsigned long temp = 0x00000000;
    while( i < Nk ) {
        w[i] = ((key[4*i  ] <<24) & 0xff000000) + 
               ((key[4*i+1] <<16) & 0x00ff0000) + 
               ((key[4*i+2] << 8) & 0x0000ff00) + 
               ((key[4*i+3] << 0) & 0x000000ff); 
        i = i + 1;
    }
    i = Nk;
    while( i < (Nb*(Nr+1)) + (Nk % 4) ) {
        temp = w[i-1];
        if( i % Nk == 0) {
            temp = aes_sub_word( aes_rot_word( temp )) ^ aes_rcon( i / Nk ); 
        } else if ( Nk > 6 && i % Nk == 4) {
            temp = aes_sub_word( temp );    
        }
        w[i] = (w[i-Nk] ^ temp) & 0x00000000ffffffff;
        i = i + 1;
    }
    return;
}

void aes_e( const unsigned char P[4*8], unsigned char C[4*8], const unsigned char K[4*8], int Nb, int Nk, int Nr )
{
// Init
    unsigned char state[4][8];
    unsigned long w[8*(14+1)];
    aes_key_expansion( K, w, Nb, Nk, Nr );
//
    for( int i = 0; i < 4; i++) {
        for( int j = 0; j < Nb; j++) {
            state[j][i] = P[i*4 + j];
        }
    }
    aes_add_round_key( state, w, Nb, 0 );
    for( int round = 1; round < Nr; round++) {
        aes_sub_bytes( state, Nb );
        aes_shift_rows( state, Nb );
        aes_mix_columns( state, Nb );
        aes_add_round_key( state, w, Nb, round);
    }
    aes_sub_bytes( state, Nb );
    aes_shift_rows( state, Nb );
    aes_add_round_key( state, w, Nb, Nr );
// Output 
    for( int i = 0; i<4; i++) {
        for( int j = 0; j<Nb; j++) {
            C[j*4+i] = state[i][j];
        }
    }
    return;
}

unsigned char aes_inverse_substitute( unsigned char a ) 
{
    return iSBox[ (a >> 4) & 0x0F ][ a & 0x0F ];
}

void aes_inv_sub_bytes( unsigned char s[4][8], int Nb )
{
    for( int r = 0; r < 4; r++) {
        for( int c = 0; c < Nb; c++) {
            s[r][c] = aes_inverse_substitute( s[r][c] );      
        }
    }
    return;
}

void aes_inv_mix_columns( unsigned char s[4][8], int Nb )
{
    unsigned char t[4][8];
    for( int i = 0; i < 4; i++) {
        for( int j = 0; j < Nb; j++) {
            t[i][j] = s[i][j];
        }
    }
    for( int c = 0; c < Nb; c++) {
        s[0][c] = gf256_mul( t[0][c], 0x0e ) ^ gf256_mul( t[1][c], 0x0b ) ^ gf256_mul( t[2][c], 0x0d ) ^ gf256_mul( t[3][c], 0x09 );
        s[1][c] = gf256_mul( t[0][c], 0x09 ) ^ gf256_mul( t[1][c], 0x0e ) ^ gf256_mul( t[2][c], 0x0b ) ^ gf256_mul( t[3][c], 0x0d );
        s[2][c] = gf256_mul( t[0][c], 0x0d ) ^ gf256_mul( t[1][c], 0x09 ) ^ gf256_mul( t[2][c], 0x0e ) ^ gf256_mul( t[3][c], 0x0b );
        s[3][c] = gf256_mul( t[0][c], 0x0b ) ^ gf256_mul( t[1][c], 0x0d ) ^ gf256_mul( t[2][c], 0x09 ) ^ gf256_mul( t[3][c], 0x0e );   
    }
    return;
}

void aes_inv_shift_rows( unsigned char s[4][8], int Nb )
{
    unsigned char t[4][8];
    for( int r = 0; r < 4; r++) {
        for( int c = 0; c < Nb; c++) {
            t[r][c] = s[r][c];
        }
    }
    for( int r = 0; r < 4; r++) {
        for( int c = 0; c < Nb; c++) {
            s[r][(c+r)%Nb] = t[r][c];
        }
    }
    return;
}

void aes_d( const unsigned char C[4*8], unsigned char P[4*8], const unsigned char K[4*8], int Nb, int Nk, int Nr )
{
// Init
    unsigned char state[4][8];
    unsigned long w[8*(14+1)];
    aes_key_expansion( K, w, Nb, Nk, Nr );
//
    for( int i = 0; i<4; i++) {
        for( int j = 0; j<Nb; j++) {
            state[j][i] = C[i*4 + j];
        }
    }
    aes_add_round_key( state, w, Nb, Nr );
    for( int round = Nr-1; round >= 1; round--)
    {
        aes_inv_shift_rows( state, Nb );
        aes_inv_sub_bytes( state, Nb );
        aes_add_round_key( state, w, Nb, round);
        aes_inv_mix_columns( state, Nb );
    }

    aes_inv_sub_bytes( state, Nb );
    aes_inv_shift_rows( state, Nb );
    aes_add_round_key( state, w, Nb, 0);

// Output
    for( int i = 0; i<4; i++) {
        for( int j = 0; j<Nb; j++) {
            P[j*4 +i] = state[i][j];
        }
    }

    return;
}