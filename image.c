#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "image.h"

ImagePPM *readPPM(char *filename)
{
    FILE* input = fopen(filename, "r");
    if (input==NULL) {
        return NULL;
    }
    int red, green, blue;
    //printf("Reading..\n");
    ImagePPM* pointer = (ImagePPM*)malloc(sizeof(ImagePPM));
    fscanf(input, "%s", pointer->magic);
    fscanf(input, "%d %d %d", &pointer->numCols, &pointer->numRows, &pointer->maxVal);
    //printf("%d %d\n%d\n", pointer->numCols, pointer->numRows, pointer->maxVal);
    pointer->pixels = malloc(sizeof(Pixel*)*pointer->numRows);
    for (int i = 0; i < pointer->numRows; i++) {
        pointer->pixels[i] = malloc(sizeof(Pixel) * pointer->numCols);
        for (int j = 0; j < pointer->numCols; j++) {
            fscanf(input, "%d %d %d", &red, &green, &blue);
            pointer->pixels[i][j].red = red;
            pointer->pixels[i][j].green = green;
            pointer->pixels[i][j].blue = blue;
            //printf("% 3d % 3d % 3d	 ", pointer->pixels[i][j].red, pointer->pixels[i][j].green, pointer->pixels[i][j].blue);
        }
        //printf("\n");
    }
    fclose(input);
    return pointer;
}


int writePPM(ImagePPM *pImagePPM, char *filename)
{
    FILE* output = fopen(filename, "w");
    if (output == NULL) {
        return 0;
    }
    //printf("opened %s successfully\n", filename);
    fprintf(output, "%s\n", pImagePPM->magic);
    fprintf(output, "%d %d\n", pImagePPM->numCols, pImagePPM->numRows);
    fprintf(output, "%d\n", pImagePPM->maxVal);
    //printf("Made it here!\n");
    for (int i = 0; i < pImagePPM->numRows; i++) {
        fprintf(output," ");
        for (int j = 0; j < pImagePPM->numCols; j++) {
            fprintf(output, "%3d %3d %3d	 ", pImagePPM->pixels[i][j].red, pImagePPM->pixels[i][j].green, pImagePPM->pixels[i][j].blue);
        }
        fprintf(output,"\n");
    }
    fclose(output);
    return 1;
}


void freePPM(ImagePPM *pImagePPM)
{
    for (int i = 0; i < pImagePPM->numRows; i++) {
        free(pImagePPM->pixels[i]);
    }
    free(pImagePPM->pixels);
    free(pImagePPM);
    return;
}


// R' = floor(0.393R + 0.769G + 0.189B)
// G' = floor(0.349R + 0.686G + 0.168B)
// B' = floor(0.272R + 0.534G + 0.131B)

ImagePPM *convertToSepia(ImagePPM *pImagePPM)
{
    int r, g, b;
    ImagePPM* grown = (ImagePPM*)malloc(sizeof(ImagePPM));
    strcpy(grown->magic, pImagePPM->magic);
    grown->numRows = pImagePPM->numRows;
    grown->numCols = pImagePPM->numCols;
    grown->maxVal = pImagePPM->maxVal;
    grown->pixels = malloc(sizeof(Pixel*)*pImagePPM->numRows);
    for (int i = 0; i < pImagePPM->numRows; i++) {
        grown->pixels[i] = malloc(sizeof(Pixel) * pImagePPM->numCols);
        for (int j = 0; j < pImagePPM->numCols; j++) {
            r = floor((0.393 * pImagePPM->pixels[i][j].red) + (0.769 * pImagePPM->pixels[i][j].green) + (0.189 * pImagePPM->pixels[i][j].blue));
            g = floor((0.349 * pImagePPM->pixels[i][j].red) + (0.686 * pImagePPM->pixels[i][j].green) + (0.168 * pImagePPM->pixels[i][j].blue));
            b = floor((0.272 * pImagePPM->pixels[i][j].red) + (0.534 * pImagePPM->pixels[i][j].green) + (0.131 * pImagePPM->pixels[i][j].blue));
            if (r >= grown->maxVal) {
                r = grown->maxVal;
            }
            if (g >= grown->maxVal) {
                g = grown->maxVal;
            }
            if (b >= grown->maxVal) {
                b = grown->maxVal;
            }
            grown->pixels[i][j].red = r;
            grown->pixels[i][j].green = g;
            grown->pixels[i][j].blue = b;
        }
    }
    return grown;
}


ImagePPM *growPPM(ImagePPM *pImagePPM)
{
    ImagePPM* big = (ImagePPM*)(malloc(sizeof(ImagePPM)));
    strcpy(big->magic, pImagePPM->magic);
    big->numRows = 2 * pImagePPM->numRows;
    big->numCols = 2 * pImagePPM->numCols;
    big->maxVal = pImagePPM->maxVal;
    big->pixels = malloc(sizeof(Pixel*) * big->numRows);
    for (int z = 0; z < big->numRows; z++) {
        big->pixels[z] = malloc(sizeof(Pixel) * big->numCols);
    }
    for (int i = 0; i < pImagePPM->numRows; i++) {
        for (int j = 0; j < pImagePPM->numCols; j++) {
            big->pixels[2*i][2*j].red = pImagePPM->pixels[i][j].red;
            big->pixels[2*i][2*j].green = pImagePPM->pixels[i][j].green;
            big->pixels[2*i][2*j].blue = pImagePPM->pixels[i][j].blue;
            big->pixels[2*i][(2*j)+1].red = pImagePPM->pixels[i][j].red;
            big->pixels[2*i][(2*j)+1].green = pImagePPM->pixels[i][j].green;
            big->pixels[2*i][(2*j)+1].blue = pImagePPM->pixels[i][j].blue;
            big->pixels[(2*i)+1][2*j].red = pImagePPM->pixels[i][j].red;
            big->pixels[(2*i)+1][2*j].green = pImagePPM->pixels[i][j].green;
            big->pixels[(2*i)+1][2*j].blue = pImagePPM->pixels[i][j].blue;
            big->pixels[(2*i)+1][(2*j)+1].red = pImagePPM->pixels[i][j].red;
            big->pixels[(2*i)+1][(2*j)+1].green = pImagePPM->pixels[i][j].green;
            big->pixels[(2*i)+1][(2*j)+1].blue = pImagePPM->pixels[i][j].blue;

        }
    }
    return big;
}
