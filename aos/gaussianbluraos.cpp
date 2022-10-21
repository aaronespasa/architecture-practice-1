#include <iostream>
#include <string>
#include <vector>
#include <stdint.h>
#include "../common/common.h"
#include "aos.h"

using namespace std;

ImageAOS imgaos;



void ImageAOS::ApplyGaussianBlur() {
    
    uint8_t kernel[5][5] = {
        {1, 4, 7, 4, 1},
        {4, 16, 26, 16, 4},
        {7, 26, 41, 26, 7},
        {4, 16, 26, 16, 4},
        {1, 4, 7, 4, 1}
    };

    uint16_t w = 273;



    BmpPixels createTemporalPixelsForConvolution(BmpPixels originalBmp){
        BmpPixels temporalPixels;
        for (int i = 0; i < originalBmp.size(); i++) {
            vector<Pixel> row;
            for (int j = 0; j < originalBmp[i].size(); j++) {
                Pixel pixel;
                pixel.blue = 0;
                pixel.green = 0;
                pixel.red = 0;
                row.push_back(pixel);
            }
            temporalPixels.push_back(row);
        }
        return temporalPixels;
    }



    // 1. Copy the original image (bmpPixelsData) to a new image called temporalPixelsForConvolution

    int originalHeight = bmpPixelsData.size();
    int originalWidth = bmpPixelsData[0].size();
    BmpPixels temporalPixelsForConvolution = bmpPixelsData;



    // 2. Resize temporalPixelsForConvolution to be 4 pixels bigger in each side and fill it with 0s.
    
    temporalPixelsForConvolution.resize(originalHeight + 4);
    for (int i = 0; i < originalHeight + 4; i++) {
        temporalPixelsForConvolution[i].resize(originalWidth + 4);
    }
    for (int i = 0; i < originalHeight + 4; i++) {
        for (int j = 0; j < originalWidth + 4; j++) {
            temporalPixelsForConvolution[i][j].red = 0;
            temporalPixelsForConvolution[i][j].green = 0;
            temporalPixelsForConvolution[i][j].blue = 0;
        }
    }



    // 3. Iterate over the temporalPixelsForConvolution starting: i = 2, j = 2
    //    and ending: i = temporalPixelsForConvolution.size() - 2, j = temporalPixelsForConvolution[0].size() - 2

    for(long unsigned int i = 2; i < temporalPixelsForConvolution.size() - 2; i++){
        for(long unsigned int j = 2; j < temporalPixelsForConvolution[0].size() - 2;j++){
            // 4. For each pixel, apply the convolution operation and store the result in the original image (bmpPixelsData)
            // store it in bmpPixelsData[i-2][j-2]
            bmpPixelsData[i-2][j-2].red = 
        }
    }



}

