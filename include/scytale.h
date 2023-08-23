#ifndef _SCYTALE_H
#define _SCYTALE_H

#include <stdint.h>
#include <stdio.h>

void scytale_encrypt( const uint8_t *input, uint8_t *digest, uint32_t textSize, uint32_t key);
void scytale_decrypt( const uint8_t *digest, uint8_t *output, uint32_t textSize, uint32_t key);

#endif