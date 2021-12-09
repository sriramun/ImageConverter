#ifndef FORMAT_H
#define FORMAT_H

#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <stdio.h>
#include <math.h>

typedef struct BMP BMP;
typedef struct GIF GIF;


struct BMP{

    FILE *imageFile;

    unsigned width, height, bpp;
    unsigned char *pixels;
};

BMP* new_BMP(const char *fileName);


struct GIF{
    
    FILE *imageFile;

    uint8_t W, H;
    int GCT[256][256][256];

};

GIF* new_GIF(const char *fileName, struct BMP *B);

#endif