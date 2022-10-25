#include <iostream>
#include "soa.h"

int main() {
    ImageSOA imgsoa;

    imgsoa.ReadBitmapFile("../images/balloon.bmp");

    // imgsoa.GenerateHistogram("../histograms/balloon.hst");

    // imgsoa.ApplyGaussianBlur();
    // imgsoa.CopyBitmapFile("../images/balloon.bmp", "../images/balloon_copy.bmp");
    imgsoa.ToGrayScale();

    // imgsoa.WriteBitmapFile("../images/balloon_blur.bmp");

    return 0;
}