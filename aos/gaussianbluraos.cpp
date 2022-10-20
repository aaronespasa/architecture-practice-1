#include <iostream>
#include <string>
#include <vector>
#include "../common/common.h"
#include "aos.h"

ImageAOS imgaos;

void ImageAOS::ApplyGaussianBlur(string filename) {
    std::cout << "Applying Gaussian Blur to AOS image:" <<filename << std::endl;
    imgaos.ReadBitmapFile("../images/amphora.bmp");;

    int len_row = sizeof(bmpPixelsData)/sizeof(bmpPixelsData[0]);
    int len_col = sizeof(bmpPixelsData[0])/sizeof(bmpPixelsData[0][0]);

    for(int i = 0; i < len_row ;i++){
        for(int j = 0; j < len_col;j++){
            std::cout << "Pixel [" << i << "]["<< j <<"]: " << std::to_string(bmpPixelsData[i][j].red) << std::endl;
        }
    }


}