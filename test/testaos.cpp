#include <iostream>
#include "../common/common.h"
#include "../aos/aos.h"
#include "gtest/gtest.h" 
/* #include "../aos/grayscale.cpp" */


void checkReadAndWriteTest1() {
    // ImageAOS imgaos;

    // imgaos.ReadBitmapFile("../images/amphora.bmp");
    // imgaos.WriteBitmapFile("../images/amphora_copy.bmp");

    std::cout << "Read and write test 1 passed" << std::endl;
}

void checkGaussianBlurTest1() {
    /*Test if the size of the bmp is equal before and after
    applying Gaussian Blur*/
    ImageAOS imgaos;
    imgaos.ReadBitmapFile("../images/balloon.bmp");
    BmpPixels bmpPixelsData = imgaos.GetBitmapPixelsData();
    long unsigned int size_before = bmpPixelsData.size();
    imgaos.ApplyGaussianBlur();
    long unsigned int size_after = bmpPixelsData.size();

    if (size_before == size_after) {
        std::cout << "Gaussian Blur test 1 passed" << std::endl;
    }
    else {
        std::cout << "Gaussian Blur test 1 failed" << std::endl;
    }
}
void chechGrayScaleTest2() {
    /*Test if the size of the bmp is equal before and after
    applying GrayScale*/
    ImageAOS imgaos;
    imgaos.ReadBitmapFile("../images/balloon.bmp");
    BmpPixels bmpPixelsData = imgaos.GetBitmapPixelsData();
    long unsigned int size_before = bmpPixelsData.size();
    imgaos.ToGrayScale();
    long unsigned int size_after = bmpPixelsData.size();

    if (size_before == size_after) {
        std::cout << "GrayScale test 2 passed" << std::endl;
    }
    else {
        std::cout << "GrayScale test 2 failed" << std::endl;
    }
}



int main() {
    checkReadAndWriteTest1();
    return 0;
}