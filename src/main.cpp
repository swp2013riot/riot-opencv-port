#include <stdio.h>
#include <stdlib.h>
#include "image.h"
#include "bgfg_gaussmix.h"
#include <list>

using namespace std;

int main()
{
   /*init Values MOG Background Subtractor*/
   static const int defaultNMixtures = 5;
   static const double learningRate = 0.1;
   static const double defaultBackgroundRatio = 0.7;
   static const double defaultVarThreshold = 2.5*2.5;
   static const double defaultNoiseSigma = 30*0.5;

   //background model
   //size is frame.height*frame.width*nmixtures*(2 + 2*nchannels)
   // 10*10*5(2+2*1)=2000
   //@todo dynamic init
   struct MixData bgmodel[2000];


   /**/
   list<unsigned char**> frame_list;

   unsigned char *raw_image = NULL;
   unsigned char *raw_image_return = NULL;

   unsigned char** image_fg = NULL;
	char infilename[] = "test_input0.jpg";
	char outfilename[] = "fg_image.jpg";

   // open bw jpeg
   raw_image = image_read_jpeg_file( infilename );


   /*this example creates some test images*/

   /*create a frame list*/
   for(int i= 0; i<6; i++)
   {
      frame_list.push_front(image_matrix_create(10,10));

   }

   /*paint some stripes into the images*/
   int line=0;
   for (list<unsigned char**>::const_iterator it = frame_list.begin(); it != frame_list.end(); ++it)
   {

      image_create_stripe(*it,10, 10, line );
      //image_matrix_print(*it);printf("\n");
      line++;
   }


   /*create emtpy fg image*/
   image_fg=image_matrix_create(image_get_height(),image_get_width());


   /*extract the fg_image*/
   for (list<unsigned char**>::const_iterator frame = frame_list.begin(); frame != frame_list.end(); ++frame)
   {

   process8uC1( *frame,
                image_fg,
                learningRate,
                bgmodel,
                defaultNMixtures,
                defaultBackgroundRatio,
                defaultVarThreshold,
                defaultNoiseSigma,image_get_height(),image_get_width() );    
   }

                                                                                                                                      
   //print the fg image
   image_matrix_print(image_fg);
   
   // convert matrix to raw
   raw_image_return=image_matrix_to_raw(image_fg);

   //write out jpeg
   image_write_jpeg_file( outfilename, raw_image_return );

   /*free mem*/
   for (list<unsigned char**>::const_iterator frame = frame_list.begin(); frame != frame_list.end(); ++frame)
   {
      image_matrix_free( *frame);
   }

   frame_list.clear();
   free( raw_image );
   free( raw_image_return );
   printf("\ndone\n");
	return 0;
}

