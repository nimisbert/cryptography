#ifndef BITSET_H
#define BITSET_H

unsigned long long bit_mask( unsigned long long b );
unsigned long long bit_set( unsigned long long b, int idx );
unsigned long long bit_clear( unsigned long long b, int idx );
unsigned long long bit_test( unsigned long long b, int idx );
unsigned long long bit_rotr( unsigned long long b, int shift, int size );
unsigned long long bit_rotl( unsigned long long b, int shift, int size );
unsigned long long bit_at( unsigned long long b, int idx, int size );
unsigned long long bit_set_at( unsigned long long b, int idx, int size );
unsigned long long bit_clear_at( unsigned long long b, int idx, int size );
void          bit_disp( unsigned long long b, int size );
void          bit_psid( unsigned long long b, int size );

#endif 