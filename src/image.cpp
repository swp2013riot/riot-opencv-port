#include "image.h"


int width = 0;
int height = 0;
int components_per_pixel; // = 3  or 1 for GRACYSCALE images */
int color_space;        // = JCS_RGB or JCS_GRAYSCALE*/



/*read jpeg*/
unsigned char* image_read_jpeg_file( char *filename )
{
   //int** imageMat = NULL;
   unsigned char *raw_image = NULL;
	/* these are standard libjpeg structures for reading(decompression) */
	struct jpeg_decompress_struct cinfo;
	struct jpeg_error_mgr jerr;
	/* libjpeg data structure for storing one row, that is, scanline of an image */
	JSAMPROW row_pointer[1];
	
	FILE *infile = fopen( filename, "rb" );
	unsigned long location = 0;
	int i = 0;
	
	if ( !infile )
	{
		printf("Error opening jpeg file %s\n!", filename );
		//return -1;
	}
	/* here we set up the standard libjpeg error handler */
	cinfo.err = jpeg_std_error( &jerr );
	/* setup decompression process and source, then read JPEG header */
	jpeg_create_decompress( &cinfo );
	/* this makes the library read from infile */
	jpeg_stdio_src( &cinfo, infile );
	/* reading the image header which contains image information */
	jpeg_read_header( &cinfo, TRUE );
	/* Uncomment the following to output image information, if needed. */


   /*get input image width and height*/
   width = cinfo.image_width;
   height = cinfo.image_height;
   components_per_pixel = cinfo.num_components;
   color_space = cinfo.jpeg_color_space;


	/* decompression of the jpeg */
	jpeg_start_decompress( &cinfo );

	/* allocate memory to hold the uncompressed image */
	raw_image = (unsigned char*)malloc( cinfo.output_width*cinfo.output_height*cinfo.num_components );


	/* now actually read the jpeg into the raw buffer */
	row_pointer[0] = (unsigned char *)malloc( cinfo.output_width*cinfo.num_components );
	
   /* read one scan line at a time */
	while( cinfo.output_scanline < cinfo.image_height )
	{
		jpeg_read_scanlines( &cinfo, row_pointer, 1 );
		for( i=0; i<cinfo.image_width*cinfo.num_components;i++) 
			raw_image[location++] = row_pointer[0][i];
	}

	/* wrap up decompression, destroy objects, free pointers and close open files */
	jpeg_finish_decompress( &cinfo );
	jpeg_destroy_decompress( &cinfo );
	free( row_pointer[0] );
	fclose( infile );


	return raw_image;
}

/*write jpeg*/
int image_write_jpeg_file( char *filename, unsigned char* raw_image )
{
	struct jpeg_compress_struct cinfo;
	struct jpeg_error_mgr jerr;
	
	/* this is a pointer to one row of image data */
	JSAMPROW row_pointer[1];
	FILE *outfile = fopen( filename, "wb" );
	
	if ( !outfile )
	{
		printf("Error opening output jpeg file %s\n!", filename );
		//return -1;
	}
	cinfo.err = jpeg_std_error( &jerr );
	jpeg_create_compress(&cinfo);
	jpeg_stdio_dest(&cinfo, outfile);

	/* Setting the parameters of the output file here */
	cinfo.image_width = width;	
	cinfo.image_height = height;
	cinfo.input_components = components_per_pixel;
//	cinfo.in_color_space = color_space;



    /* default compression parameters, we shouldn't be worried about these */
	jpeg_set_defaults( &cinfo );
	/* Now do the compression .. */
	jpeg_start_compress( &cinfo, TRUE );
	/* like reading a file, this time write one row at a time */
	while( cinfo.next_scanline < cinfo.image_height )
	{
		row_pointer[0] = &raw_image[ cinfo.next_scanline * cinfo.image_width *  cinfo.input_components];
		jpeg_write_scanlines( &cinfo, row_pointer, 1 );
	}
	/* similar to read file, clean up after we're done compressing */
	jpeg_finish_compress( &cinfo );
	jpeg_destroy_compress( &cinfo );
	fclose( outfile );
	/* success code is 1! */


	return 0;
}



/*create dynamic 2d Array*/
unsigned char** image_matrix_create(int dim_x, int dim_y)
{  
   unsigned char** image_matrix;  
   image_matrix = (unsigned char**) malloc(dim_x*sizeof(unsigned char*));  
   for (int i = 0; i < dim_x; i++)  
      image_matrix[i] = (unsigned char*) malloc(dim_y*sizeof(unsigned char));  

   return image_matrix;  
}   

/*free 2d Array*/
int image_matrix_free (unsigned char** image_matrix)
{
   for (int i = 0; i < width; i++)
   {  
      free(image_matrix[i]);  
   }  
   free(image_matrix);

   return 0;
}

/*convert raw_image to nxn Matrix*/
unsigned char** image_rawimage_to_imageatrix(unsigned char *raw_image)
{

   unsigned char** image_matrix = image_matrix_create(width,height);
   int i = 0;
   int j = 0;
   int tmp = 0;
   for( j = 0; j < height; j++)
   {
      for( i = 0; i < width; i++ )
      {
         image_matrix[j][i] = raw_image[tmp+i];
      }
      tmp = tmp + i;
   }
   return image_matrix;
}

/*convert nxn Matrix to raw_image */
unsigned char* image_matrix_to_raw(unsigned char** imageMatrix)
{
   unsigned char * raw_image_return = (unsigned char*)malloc( width*height*2 );
   int i = 0;
   int j = 0;
   int tmp = 0;
   for( j = 0; j < height; j++)
   {
      for( i = 0; i < width; i++ )
      {
         raw_image_return[tmp+i] = imageMatrix[j][i];
      }
      tmp = tmp + i;
   }
   return raw_image_return;
}


/*print nxn Matrix*/
int image_matrix_print(unsigned char** image_matrix)
{
   int i = 0;
   int j = 0;
   for( j = 0; j < height; j++)
   {
      for( i = 0; i < width; i++ )
      {
         printf("%d\t",image_matrix[j][i]);
      }
      printf("\n");
   }
   return 0;
}

int image_get_height()
{
   return height;
}

int image_get_width()
{
   return width;
}


/*create an gray image with a black stripe */
void image_create_stripe(unsigned char** emtpy_matrix, int dim_x, int dim_y, int stripe_line)
{
   int i = 0;
   int j = 0;  
   for( j = 0; j < dim_x; j++)
   {
      for( i = 0; i < dim_y; i++ )
      {
         emtpy_matrix[j][i] = 190;     // gray image
      }

   }
      for( i = 0; i < 10; i++ )
      {
         emtpy_matrix[stripe_line][i] = 0;  // black stripe
      }

}







