#include <stdio.h>
#include <stdlib.h>
#include "image.h"
#include "bgfg_gaussmix.h"

int main()
{

static const int defaultNMixtures = 5;
static const double learningRate = 0.1;
static const double defaultBackgroundRatio = 0.7;
static const double defaultVarThreshold = 2.5*2.5;
static const double defaultNoiseSigma = 30*0.5;





   unsigned char *raw_image = NULL;
   unsigned char *raw_image_return = NULL;
   unsigned char** imageMat = NULL;
   unsigned char** imageMatReturn = NULL;

   unsigned char** bgmodel=NULL;

	char infilename[] = "test10bw.jpg";
	char outfilename[] = "test_out.jpg";

   // open bw jpeg
   raw_image = read_jpeg_file( infilename );

   // convert raw image to matrix
   imageMat = convertRaw2Matrix(raw_image );

   // print the matrix
   printImageMatrix(imageMat);
   imageMatReturn=create2dintArray(10,10);
   bgmodel = create2dintArray(10,10);



process8uC1( imageMat,
                         imageMatReturn,
                         learningRate,
                         bgmodel,
                         defaultNMixtures,
                         defaultBackgroundRatio,
                         defaultVarThreshold,
                         defaultNoiseSigma );



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
   free( raw_image );

	return 0;
}

