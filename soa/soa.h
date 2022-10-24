#ifndef SOA_H
#define SOA_H

#include <string>
#include <vector>
#include <stdint.h>

#include "../common/common.h"

using namespace std;

struct BmpPixels {
    vector<vector<uint8_t>> blue;
    vector<vector<uint8_t>> green;
    vector<vector<uint8_t>> red;
};

class ImageSOA {
    public:
        void ReadBitmapFile(string filename);
        void WriteBitmapFile(string filename);
        void GenerateHistogram(string filename);
        void ToGrayScale();
        void ApplyGaussianBlur();

        BmpPixels GetBitmapPixelsData();
    private:
        BMPHeader bmpHeader;
        BmpPixels bmpPixelsData;
};

#endif