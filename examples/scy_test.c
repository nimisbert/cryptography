#include <stdio.h>
#include <string.h>

#include <ciphers.h>
#define Nb 22 // 21 + 1 for '\0'

int main( void )
{
// Init 
    char clear_text[Nb], cipher_text[Nb], decoded_text[Nb];
    int  key = 3;
    memset( clear_text, 0, Nb*sizeof(char));
    memset( cipher_text, 0, Nb*sizeof(char));
    memset( decoded_text, 0, Nb*sizeof(char));
    sprintf( clear_text, "MESSAGER_TRES_MESQUIN");
// Test 
    int err_e = scytale_encrypt( clear_text, cipher_text, strlen(clear_text), key);
    int err_d = scytale_decrypt( cipher_text, decoded_text, strlen(cipher_text), key);
// Output 
    printf("Message clair : %.*s (%2d)\r\n", Nb, clear_text, 0);        // Alice
    printf("Message codee : %.*s (%2d)\r\n", Nb, cipher_text, err_e);   // Alice To Bob
    printf("Message decod : %.*s (%2d)\r\n", Nb, decoded_text, err_d);  // Bob
    return 0;
}
