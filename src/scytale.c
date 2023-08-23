/**
 * @file scytale.c
 * @brief A simple transposition cipher.
 * @author Nicolas Misbert
 * @version 0.1.0
 * @date 23/08/2023
 */
#include "scytale.h"

/** 
 * @brief Perform the scytale encryption.
 * @param[in] input[textSize]   The clear text to encrypt.
 * @param[out] digest[textSize] The resulting coded text.
 * @param[in] textSize          Size of the input and digest arrays.
 * @param[in] key               The cipher key for the encryption.
 */
void scytale_encrypt( const uint8_t *input, uint8_t *digest, uint32_t textSize, uint32_t key)
{
    for( uint32_t i = 0; i < key; i++) {
        for( uint32_t j = 0; j < textSize/key; j++) {
            digest[(textSize/key) * i + j] = input[key * j + i];
        }
    }
    return;
}

/** 
 * @brief Perform the scytale decryption.
 * @param[in] digest[textSize]  The coded text to decrypt.
 * @param[out] output[textSize] The resulting clear text.
 * @param[in] textSize          Size of the digest and output arrays.
 * @param[in] key               The cipher key for the encryption.
 */
void scytale_decrypt( const uint8_t *digest, uint8_t *output, uint32_t textSize, uint32_t key)
{
    for( uint32_t i = 0; i < key; i++) {
        for( uint32_t j = 0; j < textSize/key; j++) {
            output[key * j + i] = digest[(textSize/key) * i + j];
        }
    }
    return;
}