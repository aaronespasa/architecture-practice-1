#include <iostream>
#include "soa.h"

int main() {
    ImageSOA imgsoa;

    imgsoa.ReadBitmapFile("../images/balloon.bmp");

    // imgsoa.GenerateHistogram("../histograms/balloon.hst");

    // imgsoa.ApplyGaussianBlur();
    // imgsoa.CopyBitmapFile("../images/balloon.bmp", "../images/balloon_copy.bmp");
    imgsoa.ToGrayScale();

    // print the first 5 pixels from imgsoa bmpPixelsData
    BmpPixels bmpPixelsData = imgsoa.GetBitmapPixelsData();
    for (int i = 0; i < 5; i++) {
        std::cout << "blue: " << std::to_string(bmpPixelsData.blue[0][i]) << std::endl;
        std::cout << "green: " << std::to_string(bmpPixelsData.green[0][i]) << std::endl;
        std::cout << "red: " << std::to_string(bmpPixelsData.red[0][i]) << std::endl;
    }

    imgsoa.WriteBitmapFile("../images/balloon_mono.bmp");

    return 0;
}