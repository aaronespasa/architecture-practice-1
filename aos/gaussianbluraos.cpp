#include <iostream>
#include <string>
#include <vector>
#include "../common/common.h"
#include "aos.h"

ImageAOS imgaos;

void ImageAOS::ApplyGaussianBlur(string filename) {
    std::cout << "Applying Gaussian Blur to AOS image:" <<filename << std::endl;
    imgaos.ReadBitmapFile("../images/amphora.bmp");
    BmpPixels pixelMatrix = imgaos.GetBitmapPixelsData();

    int len_row = sizeof(pixelMatrix)/sizeof(pixelMatrix[0]);
    int len_col = sizeof(pixelMatrix[0])/sizeof(pixelMatrix[0][0]);

    for(int i = 0; i < len_row ;i++){
        for(int j = 0; j < len_col;j++){
            std::cout << "Pixel [" << i << "]["<< j <<"]: " << std::to_string(pixelMatrix[i][j].red) << std::endl;
        }
    }


}