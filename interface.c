#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "image.h"

int main(int argc, char **argv)
{
	if (argc != 4)
	{
		printf("Usage: %s copy input.ppm output.ppm\n", argv[0]);
		printf("       %s sepia input.ppm output.pgm\n", argv[0]);
		printf("       %s grow input.ppm output.ppm\n", argv[0]);
		return 1;
	}

	char *command = argv[1];
	char *inputFilename = argv[2];
	char *outputFilename = argv[3];

	if (strcmp(command, "copy") == 0)
	{
		ImagePPM *pImagePPM = readPPM(inputFilename);
		if (pImagePPM == NULL)
		{
			printf("Unable to read the PPM file: %s\n", inputFilename);
			return 2;
		}
		int success = writePPM(pImagePPM, outputFilename);
		if (!success)
		{
			printf("Unable to write to the file: %s\n", outputFilename);
			freePPM(pImagePPM);
			return 3;
		}
		freePPM(pImagePPM);
	}
	else if (strcmp(command, "sepia") == 0)
	{
		ImagePPM *pOrig = readPPM(inputFilename);
		if (pOrig == NULL)
		{
			printf("Unable to read the PPM file: %s\n", inputFilename);
			return 4;
		}
		ImagePPM *pSepia = convertToSepia(pOrig);
		int success = writePPM(pSepia, outputFilename);
		if (!success)
		{
			printf("Unable to write to the file: %s\n", outputFilename);
			freePPM(pOrig);
			freePPM(pSepia);
			return 5;
		}
		freePPM(pOrig);
		freePPM(pSepia);
	}
	else if (strcmp(command, "grow") == 0)
	{
		ImagePPM *pOrig = readPPM(inputFilename);
		if (pOrig == NULL)
		{
			printf("Unable to read the PGM file: %s\n", inputFilename);
			return 6;
		}
		ImagePPM *pGrow = growPPM(pOrig);
		int success = writePPM(pGrow, outputFilename);
		if (!success)
		{
			printf("Unable to write to the file: %s\n", outputFilename);
			freePPM(pOrig);
			freePPM(pGrow);
			return 7;
		}
		freePPM(pOrig);
		freePPM(pGrow);
	}
	else
	{
	   printf("Unrecognized command\n");
	   return 8;
	}

	return 0;
}
