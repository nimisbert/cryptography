/**
 * @file ciphers.h
 * @brief Cipher functions header.
 * @author Nicolas Misbert
 * @version 0.1.0
 * @date 15/09/2023
 */
#ifndef CIPHERS_H
#define CIPHERS_H

int scytale_encrypt( const char *clear_text, char *cipher_text, int text_length, int key );
int scytale_decrypt( const char *cipher_text, char *clear_text, int text_length, int key );

#ifndef POL_Nb
#define POL_Nb 256
#endif
void polybius_encrypt( const char clear_text[POL_Nb], char cipher_text[POL_Nb], int key );
void polybius_decrypt( const char cipher_text[POL_Nb], char clear_text[POL_Nb], int key );

#ifndef VIG_Nb
#define VIG_Nb 41
#endif
#ifndef VIG_Nk
#define VIG_Nk 7
#endif 
void vigenere_encrypt( const char clear_text[VIG_Nb], char cipher_text[VIG_Nb], const char key[VIG_Nk] );
void vigenere_decrypt( const char cipher_text[VIG_Nb], char clear_text[VIG_Nb], const char key[VIG_Nk] );

#ifndef AES_Nb 
#define AES_Nb 4
#endif 
#ifndef AES_Nk 
#define AES_Nk 8
#endif 
#ifndef AES_Nr
#define AES_Nr 14
#endif 
void aes_encrypt( const char clear_text[4*AES_Nb], char cipher_text[4*AES_Nb], const char key[4*AES_Nk] );
void aes_decrypt( const char cipher_text[4*AES_Nb], char clear_text[4*AES_Nb], const char key[4*AES_Nk] );

#endif 