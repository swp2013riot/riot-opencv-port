#include <stdio.h>
#include <stdlib.h>
#include <jpeglib.h>


void bgsubstraction(int** input_matrix, int** output_bg_matrix, int** output_fg_matrix);

unsigned char* convertMatrix2Raw(int** my2dArray);

int** convertRaw2Matrix(unsigned char* raw_image);

int printImageMatrix(int** Matrix);

int** create2dintArray(int arraySizeX, int arraySizeY);

int free2dintArray (int** my2dArray);

unsigned char* read_jpeg_file( char *filename);

int write_jpeg_file( char *filename, unsigned char* raw_image );
