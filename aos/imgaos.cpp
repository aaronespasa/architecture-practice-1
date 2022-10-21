#include <iostream>
#include <string>
#include <vector>

#include "../common/common.h"
#include "aos.h"

int main () {
    ImageAOS imgaos;

    imgaos.ReadBitmapFile("../images/landscape.bmp");
    imgaos.ApplyGaussianBlur();
    // imgaos.ToGrayScale();

    BmpPixels bmpPixelsData = imgaos.GetBitmapPixelsData();

    for (int i = 0; i < 5; i++) {
        std::cout << "Pixel " << i << ": " << std::to_string(bmpPixelsData[0][i].red) << " " << std::to_string(bmpPixelsData[0][i].green) << " " << std::to_string(bmpPixelsData[0][i].blue) << std::endl;
    }

    imgaos.WriteBitmapFile("../images/landscape-blur.bmp");

    return 0;
}