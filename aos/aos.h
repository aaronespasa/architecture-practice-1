#ifndef AOS_H
#define AOS_H

#include <string>
#include <vector>
#include <stdint.h>

#include "../common/common.h"

using namespace std;

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
        BmpPixels bmpPixelsData;
};

#endif