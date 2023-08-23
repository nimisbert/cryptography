#include <stdio.h>
#include <stdint.h>
#include <string.h>

#include "scytale.h"

int main( void )
{
// Init 
    char clearText[22], cipherText[22], decodedText[22], key = 3;
    memset( clearText, 0, strlen((const char *)clearText)*sizeof(uint8_t));
    memset( cipherText, 0, strlen((const char *)cipherText)*sizeof(uint8_t));
    memset( decodedText, 0, strlen((const char *)decodedText)*sizeof(uint8_t));
    sprintf( (char*)clearText, "MESSAGER_TRES_MESQUIN");
// Cryptage 
    scytale_encrypt( clearText, cipherText, strlen((const char *)clearText), key);
    scytale_decrypt( cipherText, decodedText, strlen((const char *)clearText), key);

    printf("Message clair : %.*s\r\n", 22, clearText);    // Alice
    printf("Message codee : %.*s\r\n", 22, cipherText);   // Alice To Bob
    printf("Message decod : %.*s\r\n", 22, decodedText);  // Bob
    return 0;
}
