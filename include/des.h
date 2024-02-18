#ifndef DES_H
#define DES_H

// === functions [src/ciphers/des/des.c] === //
unsigned long long des_IP( unsigned long long input );
unsigned long long des_iIP( unsigned long long input );
unsigned long long des_PC1( unsigned long long input );
unsigned long long des_PC2( unsigned long long input );
unsigned long long des_E( unsigned long long input );
unsigned long long des_P( unsigned long long input );
unsigned char      des_S( unsigned char input, int n );
void               des_KS( unsigned long long Kin, unsigned long long Kout[16] ); 
unsigned long long des_f( unsigned long long R, unsigned long long K );
unsigned long long des_e( unsigned long long input, unsigned long long key );
unsigned long long des_d( unsigned long long input, unsigned long long key );

// === Substitution Boxes [src/ciphers/des/box.c] === //
unsigned char IPBox[64];
unsigned char iIPBox[64];
unsigned char PC1Box[56];
unsigned char PC2Box[48];
unsigned char EBox[48];
unsigned char PBox[32];
unsigned char SBox[8][4][16];
unsigned char ShiftBox[16];

#endif