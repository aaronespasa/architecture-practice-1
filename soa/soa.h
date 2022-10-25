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