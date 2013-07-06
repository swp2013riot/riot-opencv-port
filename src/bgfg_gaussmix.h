/* needed for background model */
struct MixData {
   float sortKey;
   float weight;
   float mean;
   float var;
};

/* does background subtraction for 1-channel 8-bit grayscale image */
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
