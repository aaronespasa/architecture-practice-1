#include <iostream>
#include <vector>
#include <chrono>

#include "aos.h"
#include <cmath>

using namespace std;

struct PixelNormalized {
    float blue;
    float green;
    float red;
    float gray;
};

//This function is used to normalize the pixel values
//from 0 to 255 to 0.0 to 1.0
PixelNormalized Normalize( Pixel& mypixel  ) {
    PixelNormalized pixelNormalized;

    pixelNormalized.blue = mypixel.blue / 255.0;
    pixelNormalized.green = mypixel.green / 255.0;
    pixelNormalized.red = mypixel.red / 255.0;

    return pixelNormalized;
}

//This function is used to correct the linear intensity of the pixel
PixelNormalized Intensidad_lineal ( PixelNormalized& mypixel ) {
    PixelNormalized pixelNormalized;
    if (mypixel.blue  <= 0.04045) {
        pixelNormalized.blue = mypixel.blue / 12.92;
    } else {
        pixelNormalized.blue = std::pow(((mypixel.blue + 0.055) / 1.055), 2.4);
    }

    if(mypixel.green  <= 0.04045){
        pixelNormalized.green = mypixel.green / 12.92;
    } else {
        pixelNormalized.green = std::pow(((mypixel.green + 0.055) / 1.055), 2.4);
    }
            
    if(mypixel.red  <= 0.04045){
        pixelNormalized.red = mypixel.red / 12.92;
    } else {
        pixelNormalized.red = std::pow(((mypixel.red + 0.055) / 1.055), 2.4);
    }

    return pixelNormalized;
}

//This function converges the 3 values of the pixel to a single value(gray)

PixelNormalized Transformacion_lineal( PixelNormalized mypixel ) {
    mypixel.gray = 0.2126 * mypixel.red + 0.7152 * mypixel.green + 0.0722 * mypixel.blue;
    return mypixel;
}

//This function is used to apply the gamma correction of the pixel

PixelNormalized correccion_gamma ( PixelNormalized mypixel ) {
    if (mypixel.gray  <= 0.0031308) {
        mypixel.gray = mypixel.gray * 12.92;
    }
    else{
        mypixel.gray = 1.055 * std::pow(mypixel.gray, 1/2.4) - 0.055;
    }

    return mypixel;        
}

//This function is used to denormalize the pixel value
Pixel Denormalize( PixelNormalized& mypixel ) {
    Pixel new_pixel;
    mypixel.gray = mypixel.gray * 255;
    new_pixel.blue = mypixel.gray;
    new_pixel.green = mypixel.gray;
    new_pixel.red = mypixel.gray;

    return new_pixel;
}


int ImageAOS::ToGrayScale() {
    auto start = std::chrono::high_resolution_clock::now();

    vector<vector<PixelNormalized>> bmpPixelsDataNormalized(bmpPixelsData.size(), vector<PixelNormalized>(bmpPixelsData[0].size()));

    //Read all pixels and convert them to grayscale
    for (long unsigned int i = 0; i < bmpPixelsData.size(); i++) {
        for (long unsigned int j = 0; j < bmpPixelsData[0].size(); j++) {
            //asign result of  Normalize to bmpPixelsData[i][j]
            bmpPixelsDataNormalized[i][j] = Normalize(bmpPixelsData[i][j]);
            bmpPixelsDataNormalized[i][j] = Intensidad_lineal(bmpPixelsDataNormalized[i][j]);
            bmpPixelsDataNormalized[i][j] = Transformacion_lineal(bmpPixelsDataNormalized[i][j]);
            bmpPixelsDataNormalized[i][j] = correccion_gamma(bmpPixelsDataNormalized[i][j]);
            bmpPixelsData[i][j] = Denormalize(bmpPixelsDataNormalized[i][j]);
        }
    }

    return std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::high_resolution_clock::now() - start).count();
}