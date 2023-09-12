#include <stdio.h>
#include <stdint.h>
#include "sha.h"
#include "sha-1.h"

// Test sha-1
int main( void ) 
{
    // Init 
    char    message[3] = "abc";
    uint8_t padded[SHA_1_N];
    uint32_t H[5], digest[5];

    // Padding
    int err = sha_padding_512 ( (const uint8_t *)message, 3, 3*8, padded); 

    // Get H0
    sha1_H( H );
    sha1_step( padded, H, digest );

    // Some prints
    printf("sha-1 H0     : ");
    for( int i = 0; i < 5; i++ ) {
        printf(" %6x ", H[i] );
    }
    printf("\r\n");
    printf("sha-1 digest : ");
    for( int i = 0; i < 5; i++ ) {
        printf(" %6x ", digest[i] );
    }
    printf("\r\n");
    return 0;
}