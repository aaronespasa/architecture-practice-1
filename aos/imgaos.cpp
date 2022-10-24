#include <iostream>
#include <string>
#include <vector>

#include "../common/common.h"
#include "aos.h"

int main () {
    ImageAOS imgaos;

    imgaos.CopyBitmapFile("../images/balloon.bmp", "../images/balloon_copy.bmp");
    // imgaos.ReadBitmapFile("../images/balloon.bmp");
    // imgaos.GenerateHistogram("../histograms/ballon.hst");
    // imgaos.ToGrayScale();
    // imgaos.ApplyGaussianBlur();

    // BmpPixels bmpPixelsData = imgaos.GetBitmapPixelsData();

    // for (int i = 0; i < 5; i++) {
    //     std::cout << "Pixel " << i << ": " << std::to_string(bmpPixelsData[0][i].red) << " " << std::to_string(bmpPixelsData[0][i].green) << " " << std::to_string(bmpPixelsData[0][i].blue) << std::endl;
    // }

    // imgaos.WriteBitmapFile("../images/balloon-mono.bmp");

    return 0;
}