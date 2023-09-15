/**
 * @file scy_main.c
 * @brief Scytale encryption for files.
 * @author Nicolas Misbert
 * @version 0.1.0
 * @date 15/09/2023
 */
#include <stdio.h>  // FILE
#include <stdlib.h> // malloc, free
#include <string.h> // memset
#include "ciphers.h"

int main( int argc, char *argv[] ) 
{
    FILE *infile, *outfile;
    int enc;
    char *s, *k, *e;
    unsigned long int fileSize;
    char *inbuf, *outbuf;
    unsigned long int key = 0;

    if ( argc != 5 ) {
        printf("Usage: scytale e/d infile outfile key\n\te = encrypt\td = decrypt\n");
        return 1;
    }
    s = argv[1];
    if ( s[1] == 0 && (*s == 'd' || *s == 'D' || *s == 'e' || *s == 'E') ) {
        enc = (*s == 'e' || *s == 'E');
    } else {
        printf("? %s\n", s); return 1;
    }

    k = argv[4];
    key = strtol(k, &e, 10);
    if (key == 0 || k == e) {
        printf("? invalid key");
    }

    if ((infile = fopen(argv[2], "rb")) == NULL ) {
        printf("? %s\n", argv[2]); return 1;
    }
    if ((outfile = fopen(argv[3], "wb")) == NULL ) {
        printf("? %s\n", argv[3]); return 1;
    }

    fseek(infile, 0L, SEEK_END);
    fileSize = ftell(infile);
    rewind(infile);

    if( (inbuf = (char *)malloc(fileSize*sizeof(char))) == NULL ) {
        printf("? infile too big."); fclose(infile); fclose(outfile); return 1;
    }
    if( (outbuf = (char *)malloc(fileSize*sizeof(char))) == NULL ) {
        printf("? infile+outfile too big.\n"); free(inbuf); fclose(infile); fclose(outfile); return 1;
    }
    memset( inbuf, 0, fileSize*sizeof(uint8_t));
    memset( outbuf, 0, fileSize*sizeof(uint8_t));

    if ( fread( inbuf, sizeof(uint8_t), fileSize*sizeof(uint8_t), infile) < 0) {
        printf("? empty infile.\n"); free(inbuf); free(outfile); fclose(infile); fclose(outfile); return 1;
    }

    if (enc) {
        scytale_encrypt( (const char*)inbuf, (char *)outbuf, fileSize, key);
    } else {
        scytale_decrypt( (const char*)inbuf, (char *)outbuf, fileSize, key);
    }

    if( fwrite( outbuf, sizeof(char), fileSize*sizeof(uint8_t), outfile) < 0 ) {
        printf("? error writing to outfile.\n"); free(inbuf); free(outfile); fclose(infile); fclose(outfile); return 1;
    } 

    free( inbuf );
    free( outbuf );
    fclose( infile );
    fclose( outfile );
    return 0;
}
