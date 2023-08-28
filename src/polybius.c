/**
 * @file polybius.c
 * @brief A simple substitution cipher.
 * @author Nicolas Misbert 
 * @version 0.1.0
 * @date 28/08/2023
 */
#include "polybius.h"

#ifndef POLYBIUS_ALPHABET_SIZE 
#define POLYBIUS_ALPHABET_SIZE 256
#endif 

/**
 * @brief Perform a polybius substitution.
 * @param[in] p The character to substitute.
 * @param[in] k The cipher Key for the encryption.
 * @return The substituted character.
 */
uint8_t polybius_subBytes( uint8_t p, uint8_t k)
{
    return ((p + k) % POLYBIUS_ALPHABET_SIZE);
}

/**
 * @brief Perform the inverse of the polybius substitution.
 * @param[in] c The substituted character.
 * @param[in] k The cipher Key for the decryption.
 * @return The clear text character.
 */
uint8_t polybius_invSubBytes( uint8_t c, uint8_t k)
{
    return ((c - k) % POLYBIUS_ALPHABET_SIZE);
}

/** 
 * @brief Perform the polybius encryption.
 * @param[in] input[textSize]   The clear text to encrypt.
 * @param[out] digest[textSize] The resulting coded text.
 * @param[in] textSize          Size of the input and digest arrays.
 * @param[in] key               The cipher key for the encryption.
 */
void polybius_encrypt( const uint8_t *input, uint8_t *digest, uint32_t textSize, uint8_t key)
{
    for( int i = 0; i < textSize; i++) {
        digest[i] = polybius_subBytes( input[i], key);
    }
    return;
} 

/** 
 * @brief Perform the polybius decryption.
 * @param[in] digest[textSize]  The coded text to decrypt.
 * @param[out] output[textSize] The resulting clear text.
 * @param[in] textSize          Size of the digest and output arrays.
 * @param[in] key               The cipher key for the encryption.
 */
void polybius_decrypt( const uint8_t *digest, uint8_t *output, uint32_t textSize, uint8_t key)
{
    for( int i = 0; i < textSize; i++) {
        output[i] = polybius_invSubBytes( digest[i], key);
    }
    return;
}