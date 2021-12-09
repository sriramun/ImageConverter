#include "format.h"


int main(int argc, char *argv[]){

    BMP* bmp = new_BMP(argv[1]);

    GIF* gif = new_GIF(argv[2], bmp);

    return 0;
}
