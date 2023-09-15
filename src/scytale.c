/**
 * @file scytale.c
 * @brief A simple transposition cipher.
 * @author Nicolas Misbert
 * @version 0.1.0
 * @date 15/09/2023
 */
#include "ciphers.h"

/** 
 * @brief Perform the scytale encryption. o(n) where n is the text_length.
 * @param[in] clear_text  The clear text to encrypt.
 * @param[out] cipher_text The resulting coded text.
 * @param[in] text_length Length in bytes of the clear text. 
 * @param[in] key The cipher key for the encryption.
 * @return An error code.
 */
int scytale_encrypt( const char *clear_text, char *cipher_text, int text_length, int key )
{
    if( key == 0 ) {
        return -1; // cannot divide by zero
    }
    for( int i = 0; i < key; i++) {
        for( int j = 0; j < text_length/key; j++) {
            cipher_text[(text_length/key) * i + j] = clear_text[key * j + i];
        }
    }
    if( text_length == key ) {
        return 1; // clear text is identical to ciphered text
    } else {
        return 0; // ok
    }
}

/** 
 * @brief Perform the scytale decryption. o(n) where n is the text_length
 * @param[in] cipher_text The coded text to decrypt.
 * @param[out] clear_text The resulting clear text.
 * @param[in] text_length Length in bytes of the cipher text.
 * @param[in] key The cipher key for the encryption.
 * @return An error code.
 */
int scytale_decrypt( const char *cipher_text, char *clear_text, int text_length, int key )
{
    if ( key == 0 ) {
        return -1; // cannot divide by zero
    }
    for( int i = 0; i < key; i++) {
        for( int j = 0; j < text_length/key; j++) {
            clear_text[key * j + i] = cipher_text[(text_length/key) * i + j];
        }
    }
    if( text_length == key ) {
        return 1; // clear text is identical to ciphered text
    } else {
        return 0; // ok
    }
}