#ifndef AOS_H
#define AOS_H

#include <chrono>
#include <string>
#include <vector>
#include <stdint.h>

#include "../common/common.h"

using namespace std;

struct Pixel {
    uint8_t blue;
    uint8_t green;
    uint8_t red;
};

typedef vector<vector<Pixel>> BmpPixels;

class ImageAOS {
    public:
        int ReadBitmapFile(string filename);
        int WriteBitmapFile(string filename);
        std::vector<int> CopyBitmapFile(string source, string destination);
        int GenerateHistogram(string filename);
        int ToGrayScale();
        int ApplyGaussianBlur();

        BmpPixels GetBitmapPixelsData();
    private:
        BMPHeader bmpHeader;
        BmpPixels bmpPixelsData;
};

#endif