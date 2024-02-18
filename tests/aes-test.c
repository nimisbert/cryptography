#include <stdio.h>
#include <assert.h>
#include "aes.h"

#define Nb_128 4
#define Nb_192 6
#define Nb_256 8
#define Nk_128 4
#define Nk_192 6
#define Nk_256 8
#define Nr_128 10
#define Nr_192 12
#define Nr_256 14

typedef struct aes_test_vectors {
    unsigned char key[4*8];
    unsigned char plainText[4*8];
    unsigned char cipherText[4*8];
} aes_test_vectors_t;

// Appendix A 
unsigned char keyA128[4*Nk_128] = "\x2b\x7e\x15\x16\x28\xae\xd2\xa6\xab\xf7\x15\x88\x09\xcf\x4f\x3c";
unsigned char keyA192[4*Nk_192] = "\x8e\x73\xb0\xf7\xda\x0e\x64\x52\xc8\x10\xf3\x2b\x80\x90\x79\xe5\x62\xf8\xea\xd2\x52\x2c\x6b\x7b";
unsigned char keyA256[4*Nk_256] = "\x60\x3d\xeb\x10\x15\xca\x71\xbe\x2b\x73\xae\xf0\x85\x7d\x77\x81\x1f\x35\x2c\x07\x3b\x61\x08\xd7\x2d\x98\x10\xa3\x09\x14\xdf\xf4";
// Appendix B
aes_test_vectors_t testB = {
    "\x2b\x7e\x15\x16\x28\xae\xd2\xa6\xab\xf7\x15\x88\x09\xcf\x4f\x3c",
    "\x32\x43\xf6\xa8\x88\x5a\x30\x8d\x31\x31\x98\xa2\xe0\x37\x07\x34",
    "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00"
};
unsigned char appendixBReferenceOutput[4*Nb_128] = "\x39\x25\x84\x1d\x02\xdc\x09\xfb\xdc\x11\x85\x97\x19\x6a\x0b\x32";


void display_extendedKey( unsigned long extendedCipherKey[8*(14+1)], int Nb, int Nk, int Nr ) {
    printf("Extended Cipher Key %d-bit :",Nk*4*8);
    for( int i = Nk; i < Nb*(Nr+1); i++) {
        if( (i % Nk == 0) && (i != 0) ) {
            printf("\r\n");
        }
        printf(" %8lx", extendedCipherKey[i]);
    }
    printf("\r\n");
}

void printHex( unsigned char *c, int l)
{
    for( int i = 0; i<l; i++) {
        printf("%02x", c[i]);
    }
    return;
}

int main( void ) {
// Appendix A
    unsigned long extendedKey[Nb_256*(Nr_256+1)];
    aes_key_expansion( keyA128, extendedKey, Nb_128, Nk_128, Nr_128 );
    display_extendedKey( extendedKey, Nb_128, Nk_128, Nr_128 );
    aes_key_expansion( keyA192, extendedKey, Nb_192, Nk_192, Nr_192 );
    //display_extendedKey( extendedKey, Nb_192, Nk_192, Nr_def );
    aes_key_expansion( keyA256, extendedKey, Nb_256, Nk_256, Nr_256 );
    //display_extendedKey( extendedKey, Nb_256, Nk_256, Nr_def );
// Appendix B 
    aes_e( testB.plainText, testB.cipherText, testB.key, Nb_128, Nk_128, Nr_128 );
    //aes_d( testB.cipherText, testB.plainText, testB.key, Nb_128, Nk_128, Nr_def );
    printf("cipherText  : "); printHex( testB.plainText , Nb_128*4); printf("\r\n");
    printf("cipherText  : "); printHex( testB.cipherText , Nb_128*4); printf("\r\n");
    printf("shouldBe    : "); printHex( appendixBReferenceOutput , Nb_128*4); printf("\r\n");
    return 0;
}
