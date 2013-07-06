#include <stdio.h>
#include <stdlib.h>
#include <jpeglib.h>

/*read jpeg*/
unsigned char* image_read_jpeg_file( char *filename);

/*write jpeg*/
int image_write_jpeg_file( char *filename, unsigned char* raw_image );

/*create dynamic 2d Array of the specified size*/
unsigned char** image_matrix_create(int dim_x, int dim_y);

/*free 2d Array*/
int image_matrix_free (unsigned char** my2dArray);

/*convert raw image to nxn Matrix*/
unsigned char** image_rawimage_to_imagematrix(unsigned char* raw_image);

/*convert 2d Array to raw image*/
unsigned char* image_matrix_to_raw(unsigned char** my2dArray);

/*print matrix*/
int image_matrix_print(unsigned char** Matrix);

/*get image height*/
int image_get_height();

/*get image width*/
int image_get_width();

/*create a gray image with a black stripe*/
void image_create_stripe(unsigned char** emtpy_matrix, int dim_x, int dim_y, int stripe_line);