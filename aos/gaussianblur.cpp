#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <stdint.h>
#include <chrono>
#include "../common/common.h"
#include "aos.h"


using namespace std;


int ImageAOS::ApplyGaussianBlur() {
    auto start = std::chrono::high_resolution_clock::now();

    uint8_t kernel[5][5] = {
        {1, 4, 7, 4, 1},
        {4, 16, 26, 16, 4},
        {7, 26, 41, 26, 7},
        {4, 16, 26, 16, 4},
        {1, 4, 7, 4, 1}
    };

    int w = 273;

    // 1. Copy the original image (bmpPixelsData) to a new image called temporalPixelsForConvolution &
    //    resize temporalPixelsForConvolution to be 4 pixels bigger in each side and fill it with 0s.
    vector<vector<Pixel>> temporalPixelsForConvolution(bmpPixelsData.size() + 4, vector<Pixel>(bmpPixelsData[0].size() + 4));

    for (long unsigned int i = 0; i < bmpPixelsData.size(); i++)
        for (long unsigned int j = 0; j < bmpPixelsData[0].size(); j++)
            temporalPixelsForConvolution[i + 2][j + 2] = bmpPixelsData[i][j];

    // 2. Iterate over the temporalPixelsForConvolution starting: i = 2, j = 2
    //    and ending: i = temporalPixelsForConvolution.size() - 2, j = temporalPixelsForConvolution[0].size() - 2
    for(long unsigned int i = 2; i < bmpPixelsData.size() + 2; i++){
        for(long unsigned int j = 2; j < bmpPixelsData[0].size() + 2;j++){
            // 3. For each pixel, apply the convolution operation and store the result in the original image (bmpPixelsData)
            // store it in bmpPixelsData[i-2][j-2]
            int blue = 0, green = 0, red = 0;
            for(int8_t s = -2; s < 3; s++){
                for(int8_t t = -2; t < 3; t++){
                    blue += temporalPixelsForConvolution[i+s][j+t].blue * kernel[s+2][t+2];
                    green += temporalPixelsForConvolution[i+s][j+t].green * kernel[s+2][t+2];
                    red += temporalPixelsForConvolution[i+s][j+t].red * kernel[s+2][t+2];
                }
            }
            bmpPixelsData[i-2][j-2].blue = blue/w;
            bmpPixelsData[i-2][j-2].green = green/w;
            bmpPixelsData[i-2][j-2].red = red/w;
        }
    }

    return std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::high_resolution_clock::now() - start).count();
}