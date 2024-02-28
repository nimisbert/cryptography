#ifndef AES_H
#define AES_H

// === functions [src/ciphers/aes/aes.c] === //

/**
 * \brief application of the S-BOX on a byte (page.13:table.4)
 * \param a byte to substitute 
 * \return substituted 8-bit block 
**/
unsigned char aes_substitute( unsigned char a );

/**
 * \brief SubBytes() function (Section 5.1.1)
 * \param s state array of bytes 
 * \param Nb size of the state 
**/
void aes_sub_bytes( unsigned char s[4][8], int Nb );

/**
 * \brief ShiftRows() function (Section 5.1.2)
 * \param s state array of bytes 
 * \param Nb size of the state
**/
void aes_shift_rows( unsigned char s[4][8], int Nb );

/**
 * \brief MixColumns() function (Section 5.1.3)
 * \param s state array of bytes
 * \param Nb size of the state
**/
void aes_mix_columns( unsigned char s[4][8], int Nb );

/**
 * \brief AddRoundKey() function (Section 5.1.4)
 * \param s state array of bytes
 * \param w array of key schedule words
 * \param Nb size of the state
 * \param round round number (between 0 < round < Nr)
**/
void aes_add_round_key( unsigned char s[4][8], unsigned long w[8], int Nb, int round );

/**
 * \brief SubWord() function (Section 5.2)
 * \param w key schedule word 
 * \return substituted key word
**/
unsigned long aes_sub_word( unsigned long w );

/**
 * \brief RotWord() function (Section 5.2)
 * \param w key schedule word
 * \return rotated key word
**/
unsigned long aes_rot_word( unsigned long w );

/**
 * \brief Rcon() round constant function (Section 5.2)
 * \param i round
 * \return round constant word
**/
unsigned long aes_rcon( int i );

/**
 * \brief KeyExpansion() algorithm
 * \param key input cipher key
 * \param w expanded key schedule
 * \param Nb number of bytes of the input block 
 * \param Nk number of bytes of the key 
 * \param Nr number of rounds 
**/
void aes_key_expansion( const unsigned char key[4*8], unsigned long w[(8*(14+1)) + (8 % 4) ], int Nb, int Nk, int Nr );

/**
 * \brief encrypt function (Section 5.1)
 * \param P clear text input block
 * \param C cipher text output block
 * \param K cipher key input 
 * \param Nb number of bytes of the input block 
 * \param Nk number of bytes of the key
 * \param Nr number of rounds 
 * 
**/
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