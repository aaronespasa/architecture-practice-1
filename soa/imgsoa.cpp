#include <iostream>
#include "soa.h"

int main() {
    ImageSOA imgsoa;

    imgsoa.CopyBitmapFile("../images/balloon.bmp", "../images/balloon_copy.bmp");
    // imgsoa.ToGrayScale();

    return 0;
}