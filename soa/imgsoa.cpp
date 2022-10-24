#include <iostream>
#include "soa.h"

int main() {
    ImageSOA imgsoa;

    imgsoa.ReadBitmapFile("../images/balloon.bmp");
    // imgsoa.ToGrayScale();

    imgsoa.WriteBitmapFile("../images/balloonsoa.bmp");

    return 0;
}