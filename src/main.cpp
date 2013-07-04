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

struct MixData bgmodel[500];



   unsigned char *raw_image = NULL;
   unsigned char *raw_image_return = NULL;
   unsigned char** imageMat0 = NULL;
   unsigned char** imageMat1 = NULL;
   unsigned char** imageMat2 = NULL;
   unsigned char** imageMat3 = NULL;
   unsigned char** imageMat4 = NULL;
   unsigned char** imageMat5 = NULL;
   unsigned char** imageMatReturn = NULL;
	char infilename[] = "test_input0.jpg";
	char outfilename[] = "fg_image.jpg";

   // open bw jpeg
   raw_image = read_jpeg_file( infilename );

   //create Images, size is 10x10
   imageMat0=create2dintArray(10,10);
   imageMat1=create2dintArray(10,10);
   imageMat2=create2dintArray(10,10);
   imageMat3=create2dintArray(10,10);
   imageMat4=create2dintArray(10,10);
   imageMat5=create2dintArray(10,10);
   
   //st image color. bg=gray, fg=white
   int i = 0;
   int j = 0;  
   for( j = 0; j < 10; j++)
   {
      for( i = 0; i < 10; i++ )
      {
         imageMat0[j][i] = 255;
      }

   }
      for( i = 0; i < 10; i++ )
      {
         imageMat0[1][i] = 10;
      }

   for( j = 0; j < 10; j++)
   {
      for( i = 0; i < 10; i++ )
      {
         imageMat1[j][i] = 255;
      }

   }
      for( i = 0; i < 10; i++ )
      {
         imageMat1[2][i] = 10;
      }
      
   for( j = 0; j < 10; j++)
   {
      for( i = 0; i < 10; i++ )
      {
         imageMat2[j][i] = 255;
      }

   }
      for( i = 0; i < 10; i++ )
      {
         imageMat2[3][i] = 10;
      }
   for( j = 0; j < 10; j++)
   {
      for( i = 0; i < 10; i++ )
      {
         imageMat3[j][i] = 255;
      }

   }
      for( i = 0; i < 10; i++ )
      {
         imageMat3[4][i] = 10;
      }
   for( j = 0; j < 10; j++)
   {
      for( i = 0; i < 10; i++ )
      {
         imageMat4[j][i] = 255;
      }

   }
      for( i = 0; i < 10; i++ )
      {
         imageMat4[5][i] = 10;
      }
   for( j = 0; j < 10; j++)
   {
      for( i = 0; i < 10; i++ )
      {
         imageMat5[j][i] = 255;
      }

   }
      for( i = 0; i < 10; i++ )
      {
         imageMat5[6][i] = 10;
      }      



   // print the matrix
//   printImageMatrix(imageMat0);
//   printImageMatrix(imageMat1);
//   printImageMatrix(imageMat2);
//   printImageMatrix(imageMat3);
//   printImageMatrix(imageMat4);
//   printImageMatrix(imageMat5);
   imageMatReturn=create2dintArray(get_height(),get_width());




   process8uC1( imageMat0,
                imageMatReturn,
                learningRate,
                bgmodel,
                defaultNMixtures,
                defaultBackgroundRatio,
                defaultVarThreshold,
                defaultNoiseSigma,get_height(),get_width() );    

   process8uC1( imageMat1,
                imageMatReturn,
                learningRate,
                bgmodel,
                defaultNMixtures,
                defaultBackgroundRatio,
                defaultVarThreshold,
                defaultNoiseSigma,get_height(),get_width() );  
                                     
   process8uC1( imageMat2,
                imageMatReturn,
                learningRate,
                bgmodel,
                defaultNMixtures,
                defaultBackgroundRatio,
                defaultVarThreshold,
                defaultNoiseSigma,get_height(),get_width() );   

   process8uC1( imageMat3,
                imageMatReturn,
                learningRate,
                bgmodel,
                defaultNMixtures,
                defaultBackgroundRatio,
                defaultVarThreshold,
                defaultNoiseSigma,get_height(),get_width() );    

   process8uC1( imageMat4,
                imageMatReturn,
                learningRate,
                bgmodel,
                defaultNMixtures,
                defaultBackgroundRatio,
                defaultVarThreshold,
                defaultNoiseSigma,get_height(),get_width() );    
        
   process8uC1( imageMat5,
                imageMatReturn,
                learningRate,
                bgmodel,
                defaultNMixtures,
                defaultBackgroundRatio,
                defaultVarThreshold,
                defaultNoiseSigma,get_height(),get_width() ); 




                                                                                                                                      
   //print the fg matrix
   printImageMatrix(imageMatReturn);
   //bgsubstraction(int** input_matrix, int** output_bg_matrix, int** output_fg_matrix);

   // convert matrix to raw
   raw_image_return=convertMatrix2Raw(imageMatReturn);

   //write out jpeg
   write_jpeg_file( outfilename, raw_image_return );



   
   //free mem
   free2dintArray(imageMat0);
   free2dintArray(imageMat1);
   free2dintArray(imageMat2);
   free2dintArray(imageMat3);
   free2dintArray(imageMat4);
   free2dintArray(imageMat5);

   free( raw_image );
   //free( bgmodel );
   free( raw_image_return );
   printf("\ndone\n");
	return 0;
}

