#include <stdio.h>
#include <stdlib.h>
#include "image.h"


int main()
{


   unsigned char *raw_image = NULL;
   unsigned char *raw_image_return = NULL;
   int** imageMat = NULL;
   int** imageMatReturn = NULL;


	char *infilename = "test10bw.jpg", *outfilename = "test_out.jpg";

   // open bw jpeg
   raw_image = read_jpeg_file( infilename );

   // convert raw image to matrix
   imageMat = convertRaw2Matrix(raw_image );

   // print the matrix
   printImageMatrix(imageMat);

   //bgsubstraction(int** input_matrix, int** output_bg_matrix, int** output_fg_matrix);

   // convert matrix to raw
   raw_image_return=convertMatrix2Raw(imageMat);

   // write out jpeg
   write_jpeg_file( outfilename, raw_image_return );

   /*
   imageMatReturn = convertRaw2Matrix(raw_image_return );
   printImageMatrix(imageMat);
   */
   
   //free mem
   free2dintArray(imageMat);


	return 0;
}

