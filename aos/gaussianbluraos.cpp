#include <iostream>
#include <string>
#include <vector>
#include <stdint.h>
#include "../common/common.h"
#include "aos.h"

using namespace std;


void ImageAOS::ApplyGaussianBlur() {
    uint8_t kernel[5][5] = {
        {1, 4, 7, 4, 1},
        {4, 16, 26, 16, 4},
        {7, 26, 41, 26, 7},
        {4, 16, 26, 16, 4},
        {1, 4, 7, 4, 1}
    };

    uint16_t w = 273;

    // 1. Copy the original image (bmpPixelsData) to a new image called temporalPixelsForConvolution &
    //    resize temporalPixelsForConvolution to be 4 pixels bigger in each side and fill it with 0s.
    vector<vector<Pixel>> temporalPixelsForConvolution(bmpPixelsData.size() + 4, vector<Pixel>(bmpPixelsData[0].size() + 4));

    for (long unsigned int i = 0; i < bmpPixelsData.size(); i++)
        for (long unsigned int j = 0; j < bmpPixelsData[0].size(); j++)
            temporalPixelsForConvolution[i + 2][j + 2] = bmpPixelsData[i][j];


    // 2. Iterate over the temporalPixelsForConvolution starting: i = 2, j = 2
    //    and ending: i = temporalPixelsForConvolution.size() - 2, j = temporalPixelsForConvolution[0].size() - 2
    for(long unsigned int i = 2; i < temporalPixelsForConvolution.size() - 2; i++){
        for(long unsigned int j = 2; j < temporalPixelsForConvolution[0].size() - 2;j++){
            // 3. For each pixel, apply the convolution operation and store the result in the original image (bmpPixelsData)
            // store it in bmpPixelsData[i-2][j-2]
            bmpPixelsData[i-2][j-2].red = 9999;
        }
    }



}

