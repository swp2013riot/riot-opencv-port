#include <stdio.h>
#include <stdlib.h>
#include <jpeglib.h>


void image_create_white_stripe(unsigned char** emtpy_matrix, int dim_x, int dim_y, int stripe_line);

unsigned char* image_matrix_to_raw(unsigned char** my2dArray);

unsigned char** image_rawimage_to_imageatrix(unsigned char* raw_image);

int image_matrix_print(unsigned char** Matrix);

unsigned char** image_matrix_create(int dim_x, int dim_y);

int image_matrix_free (unsigned char** my2dArray);

unsigned char* image_read_jpeg_file( char *filename);

int image_write_jpeg_file( char *filename, unsigned char* raw_image );

int image_get_height();

int image_get_width();
