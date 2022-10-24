#ifndef AOS_H
#define AOS_H

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
        void ReadBitmapFile(string filename);
        void WriteBitmapFile(string filename);
        void GenerateHistogram(string filename);
        void ToGrayScale();
        void ApplyGaussianBlur();

        BmpPixels GetBitmapPixelsData();
    private:
        BMPFileHeader bmpFileHeader;
        BMPInfoHeader bmpInfoHeader;
        BmpPixels bmpPixelsData;
};

#endif