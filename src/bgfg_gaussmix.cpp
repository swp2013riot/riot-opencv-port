#include "bgfg_gaussmix.h"
#include "float.h"
#include <algorithm> 
#include <math.h>
#include <stdio.h>

typedef unsigned char uchar;

/*static void process8uC1( const Mat& image,*/
/*                        Mat& fgmask,*/
/*                        double learningRate,*/
/*                        Mat& bgmodel,*/
/*                        int nmixtures,*/
/*                        double backgroundRatio,*/
/*                        double varThreshold,*/
/*                        double noiseSigma )*/


static const double defaultNoiseSigma = 30*0.5;
static const double defaultInitialWeight = 0.05;

template<typename VT> struct MixData
{
    float sortKey;
    float weight;
    VT mean;
    VT var;
};


void process8uC1( unsigned char** image,
                         unsigned char** fgmask,
                         double learningRate,
                         unsigned char** bgmodel,
                         int nmixtures,
                         double backgroundRatio,
                         double varThreshold,
                         double noiseSigma )
{
    //int x, y, k, k1, rows = image.rows, cols = image.cols;
    int x, y, k, k1, rows = 10, cols = 10;
    float alpha = (float)learningRate, T = (float)backgroundRatio, vT = (float)varThreshold;
    int K = nmixtures;
    MixData<float>* mptr = (MixData<float>*)bgmodel;

    const float w0 = (float)defaultInitialWeight;
    const float sk0 = (float)(w0/(defaultNoiseSigma*2));
    const float var0 = (float)(defaultNoiseSigma*defaultNoiseSigma*4);
    const float minVar = (float)(noiseSigma*noiseSigma);

    for( y = 0; y < rows; y++ )
    {
        //const uchar* src = image.ptr<uchar>(y);
        //uchar* dst = fgmask.ptr<uchar>(y);

        if( alpha > 0 )
        {
            for( x = 0; x < cols; x++, mptr += K )
            {
                float wsum = 0;printf("1: x: %d\t%d\n", x,y);
                //float pix = src[x];
                float pix = image[y][x];printf("2: x: %d\t%d\n", x,y);
                int kHit = -1, kForeground = -1;

                for( k = 0; k < K; k++ )
                {printf("3: x: %d\t%d\n", x,y);
                    float w = mptr[k].weight;
                    wsum += w;
                    if( w < FLT_EPSILON )
                        break;
                    float mu = mptr[k].mean;
                    float var = mptr[k].var;
                    float diff = pix - mu;
                    float d2 = diff*diff;printf("4: x: %d\t%d\n", x,y);
                    if( d2 < vT*var )
                    {printf("5: x: %d\t%d\n", x,y);
                        wsum -= w;
                        float dw = alpha*(1.f - w);
                        mptr[k].weight = w + dw;
                        mptr[k].mean = mu + alpha*diff;
                        var = std::max(var + alpha*(d2 - var), minVar);
                        mptr[k].var = var;
                        mptr[k].sortKey = w/sqrt(var);

                        for( k1 = k-1; k1 >= 0; k1-- )
                        {
                            if( mptr[k1].sortKey >= mptr[k1+1].sortKey )
                                break;
                            std::swap( mptr[k1], mptr[k1+1] );
                        }

                        kHit = k1+1;
                        break;
                    }
                }

                if( kHit < 0 ) // no appropriate gaussian mixture found at all, remove the weakest mixture and create a new one
                {
                    kHit = k = std::min(k, K-1);
                    wsum += w0 - mptr[k].weight;
                    mptr[k].weight = w0;
                    mptr[k].mean = pix;
                    mptr[k].var = var0;
                    mptr[k].sortKey = sk0;
                }
                else
                    for( ; k < K; k++ )
                        wsum += mptr[k].weight;

                float wscale = 1.f/wsum;
                wsum = 0;
                for( k = 0; k < K; k++ )
                {printf("8: x: %d\n",k);
                    wsum += mptr[k].weight *= wscale;
                    mptr[k].sortKey *= wscale;printf("9: x: %d\n",k);
                    if( wsum > T && kForeground < 0 )
                        kForeground = k+1;printf("10: x: %d\n",k);
                }

                //dst[x] = (uchar)(-(kHit >= kForeground));
                fgmask[y][x] = (uchar)(-(kHit >= kForeground));
            }
        }
        else
        {
            for( x = 0; x < cols; x++, mptr += K )
            {
                //float pix = src[x];
                float pix = image[y][x];
                int kHit = -1, kForeground = -1;

                for( k = 0; k < K; k++ )
                {
                    if( mptr[k].weight < FLT_EPSILON )
                        break;
                    float mu = mptr[k].mean;
                    float var = mptr[k].var;
                    float diff = pix - mu;
                    float d2 = diff*diff;
                    if( d2 < vT*var )
                    {
                        kHit = k;
                        break;
                    }
                }

                if( kHit >= 0 )
                {
                    float wsum = 0;
                    for( k = 0; k < K; k++ )
                    {
                        wsum += mptr[k].weight;
                        if( wsum > T )
                        {
                            kForeground = k+1;
                            break;
                        }
                    }
                }

                //dst[x] = (uchar)(kHit < 0 || kHit >= kForeground ? 255 : 0);
                fgmask[y][x] = (uchar)(kHit < 0 || kHit >= kForeground ? 255 : 0);
            }
        }
    }
}
