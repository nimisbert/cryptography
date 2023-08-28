#ifndef POLYBIUS_SQUARE_H
#define POLYBIUS_SQUARE_H

#include <stdint.h>

void polybius_encrypt( const uint8_t *input, uint8_t *digest, uint32_t textSize, uint8_t key);
void polybius_decrypt( const uint8_t *digest, uint8_t *output, uint32_t textSize, uint8_t key);


#endif