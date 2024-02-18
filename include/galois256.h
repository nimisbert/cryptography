#ifndef GALOIS_256
#define GALOIS_256

// === functions [src/helpers/galois.c] === //
unsigned char gf256_add( unsigned char a, unsigned char b );
unsigned char gf256_mul( unsigned char a, unsigned char b );
unsigned char gf256_pow( unsigned char a, unsigned char p );

#endif 
