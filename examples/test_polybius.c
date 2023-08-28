#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include "polybius.h"

#define TEXT_SIZE 13
void print_as_hex( uint8_t *array, int8_t size );

int main( void )
{
// Init 
    uint8_t clearText[TEXT_SIZE], cipherText[TEXT_SIZE], decodedText[TEXT_SIZE], key = 3;
    memset( clearText, 0, TEXT_SIZE*sizeof(uint8_t));
    memset( cipherText, 0, TEXT_SIZE*sizeof(uint8_t));
    memset( decodedText, 0, TEXT_SIZE*sizeof(uint8_t));
    sprintf((char*)clearText, "Hello world!");
// Encrypt & Decrypt 
    polybius_encrypt( clearText, cipherText, TEXT_SIZE, key);
    polybius_decrypt( cipherText, decodedText, TEXT_SIZE, key);
// Print result
    printf("Message clair : ");     print_as_hex( clearText, TEXT_SIZE );   // Alice 
    printf("\r\nMessage codee : "); print_as_hex( cipherText, TEXT_SIZE );  // Alice To Bob
    printf("\r\nMessage decod : "); print_as_hex( decodedText, TEXT_SIZE ); // Bob
    return 0;
}

void print_as_hex( uint8_t *array, int8_t size )
{
    for( int i = 0; i < size; i++ ) { printf("%02x ", array[i]); };
    return;
}