#include <iostream>
#include <vector>

#include "soa.h"
#include <cmath>

using namespace std;

struct PixelNormalized {

    vector<vector<uint8_t>> blue;
    vector<vector<uint8_t>> green;
    vector<vector<uint8_t>> red;
    vector<vector<uint8_t>> gray;
};

//This function is used to normalize the pixel values
//from 0 to 255 to 0.0 to 1.0
uint8_t Normalize( uint8_t& mypixel) {
    uint8_t pixelNormalized;

    pixelNormalized = mypixel/ 255.0;
   

    return pixelNormalized;
}

//This function is used to correct the linear intensity of the pixel
uint8_t Intensidad_lineal ( uint8_t& mypixel ) {
    if (mypixel  <= 0.04045) {
        mypixel = mypixel / 12.92;
    } else {
        mypixel = std::pow(((mypixel + 0.055) / 1.055), 2.4);
    }

    return mypixel;        
}

//This function converges the 3 values of the pixel to a single value(gray)

uint8_t Transformacion_lineal( uint8_t& mypixel_red, uint8_t& mypixel_green, uint8_t& mypixel_blue) {
    uint8_t pixel_gray;
     pixel_gray= 0.2126 * mypixel_blue + 0.7152 * mypixel_green + 0.0722 * mypixel_red;
    
    return pixel_gray;

}

//This function is used to apply the gamma correction of the pixel

uint8_t correccion_gamma ( uint8_t& mypixel ) {
    if (mypixel  <= 0.0031308) {
        mypixel = mypixel * 12.92;
    }
    else{
        mypixel = 1.055 * std::pow(mypixel, 1/2.4) - 0.055;
    }

    return mypixel;        
}

//This function is used to denormalize the pixel value
uint8_t Denormalize( uint8_t& mypixel, uint8_t& mypixel_gray) {
    
    mypixel_gray = mypixel_gray * 255;
    mypixel = floor(mypixel_gray + 0.5);
    

    return mypixel;
}


void ImageSOA::ToGrayScale() {
    PixelNormalized bmpPixelsDataNormalized;

    //Read all pixels and convert them to grayscale
    for (long unsigned int i = 0; i < bmpPixelsData.blue.size(); i++) {
        for (long unsigned int j = 0; j < bmpPixelsData.blue[0].size(); j++) {
            //asign result of  Normalize to bmpPixelsData[i][j]
            bmpPixelsDataNormalized.blue[i][j] = Normalize(bmpPixelsData.blue[i][j]);
            bmpPixelsDataNormalized.green[i][j] = Normalize(bmpPixelsData.green[i][j]);
            bmpPixelsDataNormalized.red[i][j] = Normalize(bmpPixelsData.red[i][j]);
            bmpPixelsDataNormalized.blue[i][j] = Intensidad_lineal(bmpPixelsDataNormalized.blue[i][j]);
            bmpPixelsDataNormalized.green[i][j] = Intensidad_lineal(bmpPixelsDataNormalized.green[i][j]);
            bmpPixelsDataNormalized.red[i][j] = Intensidad_lineal(bmpPixelsDataNormalized.red[i][j]);

            bmpPixelsDataNormalized.gray[i][j]= Transformacion_lineal(bmpPixelsDataNormalized.red[i][j],bmpPixelsDataNormalized.green[i][j],bmpPixelsDataNormalized.blue[i][j]);
            bmpPixelsDataNormalized.gray[i][j] = correccion_gamma(bmpPixelsDataNormalized.gray[i][j]);
            

            bmpPixelsData.blue[i][j] = Denormalize(bmpPixelsDataNormalized.blue[i][j],bmpPixelsDataNormalized.gray[i][j]);
            bmpPixelsData.green[i][j] = Denormalize(bmpPixelsDataNormalized.green[i][j],bmpPixelsDataNormalized.gray[i][j]);
            bmpPixelsData.red[i][j] = Denormalize(bmpPixelsDataNormalized.red[i][j],bmpPixelsDataNormalized.gray[i][j]);

        }
    }
}