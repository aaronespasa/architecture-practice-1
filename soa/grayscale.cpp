#include <iostream>
#include <vector>
#include <cmath>
#include <chrono>

#include "soa.h"

using namespace std;

struct PixelNormalized {
    vector<vector<float>> blue;
    vector<vector<float>> green;
    vector<vector<float>> red;
    vector<vector<float>> gray;
};

//This function is used to normalize the pixel values
//from 0 to 255 to 0.0 to 1.0
float Normalize( uint8_t& mypixel) {
    return mypixel / 255.0;
}

//This function is used to correct the linear intensity of the pixel
float Intensidad_lineal ( float& mypixel ) {
    if (mypixel  <= 0.04045) {
        return mypixel / 12.92;
    } else {
        return std::pow(((mypixel + 0.055) / 1.055), 2.4);
    }     
}

//This function converges the 3 values of the pixel to a single value(gray)
float Transformacion_lineal( float& mypixel_red, float& mypixel_green, float& mypixel_blue) {
    return 0.2126 * mypixel_red + 0.7152 * mypixel_green + 0.0722 * mypixel_blue;
}

//This function is used to apply the gamma correction of the pixel
float correccion_gamma ( float& mypixel ) {
    if (mypixel  <= 0.0031308) {
        return mypixel * 12.92;
    }
    else{
        return 1.055 * std::pow(mypixel, 1/2.4) - 0.055;
    }     
}

//This function is used to denormalize the pixel value
uint8_t Denormalize(float& mypixel_gray) {
    return mypixel_gray * 255;
}

int ImageSOA::ToGrayScale() {
    auto start = std::chrono::high_resolution_clock::now();
    
    PixelNormalized bmpPixelsDataNormalized;
    bmpPixelsDataNormalized.blue.resize(bmpPixelsData.blue.size(), vector<float>(bmpPixelsData.blue[0].size()));
    bmpPixelsDataNormalized.green.resize(bmpPixelsData.green.size(), vector<float>(bmpPixelsData.green[0].size()));
    bmpPixelsDataNormalized.red.resize(bmpPixelsData.red.size(), vector<float>(bmpPixelsData.red[0].size()));
    bmpPixelsDataNormalized.gray.resize(bmpPixelsData.blue.size(), vector<float>(bmpPixelsData.blue[0].size()));
    
    for (long unsigned int i = 0; i < bmpPixelsData.blue.size(); i++) { //Read all pixels and convert them to grayscale
        for (long unsigned int j = 0; j < bmpPixelsData.blue[0].size(); j++) {
            bmpPixelsDataNormalized.blue[i][j] = Normalize(bmpPixelsData.blue[i][j]);       //Normalize the pixel value
            bmpPixelsDataNormalized.green[i][j] = Normalize(bmpPixelsData.green[i][j]);     //Normalize the pixel value
            bmpPixelsDataNormalized.red[i][j] = Normalize(bmpPixelsData.red[i][j]);         //Normalize the pixel value
            bmpPixelsDataNormalized.blue[i][j] = Intensidad_lineal(bmpPixelsDataNormalized.blue[i][j]);
            bmpPixelsDataNormalized.green[i][j] = Intensidad_lineal(bmpPixelsDataNormalized.green[i][j]);
            bmpPixelsDataNormalized.red[i][j] = Intensidad_lineal(bmpPixelsDataNormalized.red[i][j]);
            bmpPixelsDataNormalized.gray[i][j]= Transformacion_lineal(bmpPixelsDataNormalized.red[i][j],bmpPixelsDataNormalized.green[i][j],bmpPixelsDataNormalized.blue[i][j]);
            bmpPixelsDataNormalized.gray[i][j] = correccion_gamma(bmpPixelsDataNormalized.gray[i][j]);
            uint8_t pixel_gray = Denormalize(bmpPixelsDataNormalized.gray[i][j]);          //Denormalize the pixel value
            bmpPixelsData.blue[i][j] = pixel_gray;
            bmpPixelsData.green[i][j] = pixel_gray;
            bmpPixelsData.red[i][j] = pixel_gray;
        }
    }
    return std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::high_resolution_clock::now() - start).count();
}