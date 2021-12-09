#include "format.h"


BMP* new_BMP(const char *fileName){

    BMP *bmp;
    bmp = malloc(sizeof(struct BMP));

    uint8_t **pixels = &(bmp->pixels);

    unsigned dateOffset_Offset = 0x0A;
    unsigned width_Offset = 0x12;
    unsigned height_Offset = 0x16;
    unsigned bpp_Offset = 0x1C;

    bmp->imageFile = fopen(fileName, "rb");

    unsigned dataOffset;
    fseek(bmp->imageFile, dateOffset_Offset, SEEK_SET);
    fread(&dataOffset, 4, 1, bmp->imageFile);

    fseek(bmp->imageFile, width_Offset, SEEK_SET);
    fread(&(bmp->width), 4, 1, bmp->imageFile);

    fseek(bmp->imageFile, height_Offset, SEEK_SET);
    fread(&(bmp->height), 4, 1, bmp->imageFile);

    fseek(bmp->imageFile, bpp_Offset, SEEK_SET);
    fread(&(bmp->bpp), 2, 1, bmp->imageFile);

    unsigned bytesPerPixel = ((unsigned)bmp->bpp) / 8;


    int prs = (int)(4 * ceil((float)(bmp->width) / 4.0f))*(bytesPerPixel);

    int uprs = (bmp->width)*(bytesPerPixel);

    int totalSize = uprs*(bmp->height);
    *pixels = (uint8_t*)malloc(totalSize);

    uint8_t *currentRowPointer = *pixels +((bmp->height-1)*uprs);
    for (int i = 0; i < bmp->height; i++)
    {

        fseek(bmp->imageFile, dataOffset+(i*prs), SEEK_SET);

        fread(currentRowPointer, 1, uprs, bmp->imageFile);

        currentRowPointer -= uprs;
    }

    fclose(bmp->imageFile);


    return bmp;
}
