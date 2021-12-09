#include "format.h"


struct GIF* new_GIF(const char *fileName, struct BMP *B){

    GIF *gif;
    gif = malloc(sizeof(struct GIF));

    gif->imageFile = fopen(fileName, "wb");

    // MODIFY -------------
    uint8_t gct[128 * 3] = {
        0xFF, 0xFF, 0x00, 
        0xFF, 0x00, 0x00, 
        0x00, 0x00, 0xFF, 
        0xFF, 0xFF, 0x00
    };

    // --------------------

    gif->W = (uint16_t) B->width;
    gif->H = (uint16_t) B->height;

    uint8_t header[] = {0x47, 0x49, 0x46, 0x38, 0x39, 0x61};    
    uint8_t lsd[] = {(gif->W)&(0x00ff), ((gif->W)>>8)&(0x00ff), (gif->H)&(0x00ff), ((gif->H)>>8)&(0x00ff), 0xE6, 0x00, 0x00};
    uint8_t gce[] = {0x21, 0xF9, 0x04, 0x00, 0x00, 0x00, 0x00, 0x00};
    uint8_t id[] = {0x2C, 0x00, 0x00, 0x00, 0x00, (gif->W)&(0x00ff), ((gif->W)>>8)&(0x00ff), (gif->H)&(0x00ff), ((gif->H)>>8)&(0x00ff), 0x00};

    //uint8_t data[] = {0x07, 0x12, 0x80, 0x01, 0x01, 0x02, 0x02, 0x01, 0x00, 0x00, 0x02, 0x02, 0x00, 0x00, 0x01, 0x02, 0x02, 0x01, 0x01, 0x81, 0x00};

    uint8_t data[] = {0x07};


    int gct_i = 0;

    for(int i = 0; i < 256; i++) for(int j = 0; j < 256; j++) for(int k = 0; k < 256; k++) gif->GCT[i][j][k] = -1;

    for(int i = 0; i < B->height; i++){
        for(int j = 0; j < B->width; j++){

            int x = (int) B->pixels[(B->width)*(3)*i + 3*j], y = (int) B->pixels[(B->width)*(3)*i + 3*j + 1], z = (int) B->pixels[(B->width)*(3)*i + 3*j + 2];

            //printf("%d %d %d\n", x, y, z);

            if(gif->GCT[x][y][z] == -1){

                gif->GCT[x][y][z] = gct_i;
                
                gct[gct_i*3] = z;
                gct[gct_i*3 + 1] = y;
                gct[gct_i*3 + 2] = x;

                gct_i++;

                if(gct_i > 127){
                    i = B->height;
                    break;
                }
            }
            
        }
    }


    uint8_t trailer[] = {0x00, 0x3B};


    //FILE *F = fopen("s.gif", "wb");

    fwrite(header,  sizeof(uint8_t), sizeof(header), gif->imageFile);
    fwrite(lsd,  sizeof(uint8_t), sizeof(lsd), gif->imageFile);
    fwrite(gct,  sizeof(uint8_t), sizeof(gct), gif->imageFile);
    fwrite(gce,  sizeof(uint8_t), sizeof(gce), gif->imageFile);
    fwrite(id,  sizeof(uint8_t), sizeof(id), gif->imageFile);

    fwrite(data,  sizeof(uint8_t), sizeof(data), gif->imageFile);

    for(int i = 0; i < B->height; i++){
        for(int j = 0; j < B->width; j++){
            fwrite((uint8_t []) {0x02, 0x80, (uint8_t) gif->GCT[B->pixels[(B->width)*(3)*i + 3*j]][B->pixels[(B->width)*(3)*i + 3*j + 1]][B->pixels[(B->width)*(3)*i + 3*j + 2]]}, sizeof(uint8_t), 3, gif->imageFile);
        }
    }


    fwrite(trailer, sizeof(uint8_t), sizeof(trailer), gif->imageFile);

    fclose(gif->imageFile);

    return 0;
}
