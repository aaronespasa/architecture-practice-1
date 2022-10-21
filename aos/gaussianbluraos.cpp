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

    int w = 273;
    // 1. Copy the original image (bmpPixelsData) to a new image called temporalPixelsForConvolution

    // 2. Add 0s surrounding the image. As the kernel is a 5x5 kernel, add 2 rows and 2 columns of 0s

    // 3. Iterate over the temporalPixelsForConvolution starting: i = 2, j = 2
    //    and ending: i = temporalPixelsForConvolution.size() - 2, j = temporalPixelsForConvolution[0].size() - 2

    for(long unsigned int i = 2; i < temporalPixelsForConvolution.size() - 2; i++){
        for(long unsigned int j = 2; j < temporalPixelsForConvolution[0].size() - 2;j++){
            // 4. For each pixel, apply the convolution operation and store the result in the original image (bmpPixelsData)
            // store it in bmpPixelsData[i-2][j-2]
        }
    }



}

