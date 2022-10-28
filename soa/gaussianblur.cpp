#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <stdint.h>
#include <chrono>

#include "../common/common.h"
#include "soa.h"

using namespace std;

int ImageSOA::ApplyGaussianBlur() {
    auto start = std::chrono::high_resolution_clock::now();
    uint8_t kernel[5][5] = {{1, 4, 7, 4, 1}, {4, 16, 26, 16, 4}, {7, 26, 41, 26, 7}, {4, 16, 26, 16, 4}, {1, 4, 7, 4, 1}};
    int w = 273;
    BmpPixels temporalPixelsForConvolution; // Create a temporal matrix of pixels where the 0s will be added
    temporalPixelsForConvolution.blue.resize(bmpPixelsData.blue.size() + 4, vector<uint8_t>(bmpPixelsData.blue[0].size() + 4));
    temporalPixelsForConvolution.green.resize(bmpPixelsData.green.size() + 4, vector<uint8_t>(bmpPixelsData.green[0].size() + 4));
    temporalPixelsForConvolution.red.resize(bmpPixelsData.red.size() + 4, vector<uint8_t>(bmpPixelsData.red[0].size() + 4));
    for (long unsigned int i = 0; i < bmpPixelsData.blue.size(); i++) {
        for (long unsigned int j = 0; j < bmpPixelsData.blue[0].size(); j++) {
            temporalPixelsForConvolution.blue[i + 2][j + 2] = bmpPixelsData.blue[i][j];
            temporalPixelsForConvolution.green[i + 2][j + 2] = bmpPixelsData.green[i][j];
            temporalPixelsForConvolution.red[i + 2][j + 2] = bmpPixelsData.red[i][j]; } }
    for(long unsigned int i = 2; i < bmpPixelsData.blue.size() + 2; i++){
        for(long unsigned int j = 2; j < bmpPixelsData.blue[0].size() + 2;j++){
            int blue = 0, green = 0, red = 0; // Initialize the values of the new pixel
            for(int8_t s = -2; s < 3; s++){ // Apply the convolution operation
                for(int8_t t = -2; t < 3; t++){
                    blue += temporalPixelsForConvolution.blue[i+s][j+t] * kernel[s+2][t+2];
                    green += temporalPixelsForConvolution.green[i+s][j+t] * kernel[s+2][t+2];
                    red += temporalPixelsForConvolution.red[i+s][j+t] * kernel[s+2][t+2]; } }
            bmpPixelsData.blue[i-2][j-2] = blue/w; // Update the blue color of the pixel of the original matrix
            bmpPixelsData.green[i-2][j-2] = green/w; // Update the green color of the pixel of the original matrix
            bmpPixelsData.red[i-2][j-2] = red/w; // Update the red color of the pixel of the original matrix
        }
    }
    return std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::high_resolution_clock::now() - start).count();
}