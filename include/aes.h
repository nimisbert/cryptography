#ifndef AES_H
#define AES_H

// === functions [src/ciphers/aes/aes.c] === //
unsigned char aes_substitute( unsigned char a );
void aes_sub_bytes( unsigned char s[4][8], int Nb );
void aes_shift_rows( unsigned char s[4][8], int Nb );
void aes_mix_columns( unsigned char s[4][8], int Nb );
void aes_add_round_key( unsigned char s[4][8], unsigned long w[8], int Nb, int round );
unsigned long aes_sub_word( unsigned long w );
unsigned long aes_rot_word( unsigned long w );
unsigned long aes_rcon( int i );
void aes_key_expansion( const unsigned char key[4*8], unsigned long w[(8*(14+1)) + (8 % 4) ], int Nb, int Nk, int Nr );
void aes_e( const unsigned char P[4*8], unsigned char C[4*8], const unsigned char K[4*8], int Nb, int Nk, int Nr );
void aes_e_128( const unsigned char input[4*4], unsigned char output[4*4], const unsigned char K[4*4] );
void aes_e_192( const unsigned char input[4*6], unsigned char output[4*6], const unsigned char K[4*6] );
void aes_e_256( const unsigned char input[4*8], unsigned char output[4*8], const unsigned char K[4*8] );

unsigned char aes_inverse_substitute( unsigned char a );
void aes_inv_sub_bytes( unsigned char s[4][8], int Nb );
void aes_inv_mix_columns( unsigned char s[4][8], int Nb );
void aes_inv_shift_rows( unsigned char s[4][8], int Nb );
void aes_d( const unsigned char C[4*8], unsigned char P[4*8], const unsigned char K[4*8], int Nb, int Nk, int Nr );
void aes_d_128( const unsigned char input[4*4], unsigned char output[4*4], const unsigned char K[4*4] );
void aes_d_192( const unsigned char input[4*6], unsigned char output[4*6], const unsigned char K[4*6] );
void aes_d_256( const unsigned char input[4*8], unsigned char output[4*8], const unsigned char K[4*8] );

// === Substitution Boxes [src/ciphers/aes/box.c] === //
const unsigned char SBox[16][16];
const unsigned char iSBox[16][16];

#endif