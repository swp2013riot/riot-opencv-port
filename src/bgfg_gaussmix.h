// static void process8uC1( const Mat& image, Mat& fgmask, double learningRate,                        Mat& bgmodel, int nmixtures, double backgroundRatio, double varThreshold, double noiseSigma );

void process8uC1( unsigned char** image,
                         unsigned char** fgmask,
                         double learningRate,
                         unsigned char** bgmodel,
                         int nmixtures,
                         double backgroundRatio,
                         double varThreshold,
                         double noiseSigma );
                        
                        
