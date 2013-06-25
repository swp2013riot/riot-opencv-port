#include <stdio.h>  // fopen, fclose usw.
#include <stdlib.h> // malloc()

class Image {
    int rows, cols;
    char * pixels;
public:
    void set_values (int,int);
    int area () {return (rows*cols);}
};

void Image::set_values (int r, int c)
{
    rows = r;
    cols = c;
}


void readImg (char * filename) {
    
    FILE *fp;
    int width, height;
    unsigned char *pixels;
    unsigned char pixel;
    unsigned char *buffer;
    unsigned long fileLen;
    
    fp=fopen(filename,"rb+");
    
    if(fp == NULL)
    {
        printf("Unable to open the image file!!!\n");
        fclose(fp);
        return;
    }
    
    printf("Successfully opened the image file\n");
    
    Image img;
    img.set_values(128, 128);
    
    printf("Writing to o/p completed\n");
    
    unsigned char arr [10][10];
    int m, n;
    
    for (m=0;m<10;m++) {
        for (n=0;n<10;n++) {
            fscanf(fp, "%c", &arr[m][n]);
            //printf("%d\n", arr[m][n]);
        }
    }
    
    printf("Writing to arr completed\n");
    
    // get file length
    fseek(fp,0,SEEK_END);   // sucht ende von fp
    fileLen=ftell(fp);         // current position in fp
    fseek(fp, 0, SEEK_SET); // sucht anfang von fp
    printf ("Size: %ld bytes.\n",fileLen);
    char ch;
    for (int i=0;i<10;i++) {
        ch = getc(fp);
        printf("%x\n",ch);
    }
    
    fclose(fp);
    
    // allocate memory
    buffer = (unsigned char *)malloc (fileLen);
    // find out image dimensions
    
        
}


int main(int argc, char * argv[]) {
    // argv[1]=shljapa.jpg
    
    readImg(argv[1]);
    
    return 0;
    
}