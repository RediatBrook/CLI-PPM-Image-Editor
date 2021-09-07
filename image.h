#ifndef _IMAGE_H_
#define _IMAGE_H_

typedef struct _pixel {
    int red;
    int green;
    int blue;
} Pixel;

typedef struct _imagePPM {
    char magic[3]; // magic P3
    int numRows; // number of rows
    int numCols; // number of columns
    int maxVal; // max value of pixel colors
    Pixel **pixels; // actual pixel data, a 2D array
} ImagePPM;

ImagePPM *readPPM(char *filename);
int writePPM(ImagePPM *pImagePPM, char *filename);
void freePPM(ImagePPM *pImagePPM);

ImagePPM *convertToSepia(ImagePPM *pImagePPM);
ImagePPM *growPPM(ImagePPM *pImagePPM);

#endif
