// static void process8uC1( const Mat& image, Mat& fgmask, double learningRate,                        Mat& bgmodel, int nmixtures, double backgroundRatio, double varThreshold, double noiseSigma );


struct MixData {
   float sortKey;
   float weight;
   float mean;
   float var;
};


void process8uC1( unsigned char** image,
                         unsigned char** fgmask,
                         double learningRate,
                         MixData* bgmodel,
                         int nmixtures,
                         double backgroundRatio,
                         double varThreshold,
                         double noiseSigma,
                         int image_rows,
                         int image_cols );
