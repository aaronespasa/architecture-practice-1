#include <iostream>
#include <string>
#include <vector>

#include "../common/common.h"
#include "aos.h"

int main () {
    ImageAOS imgaos;

    std::vector<Pixel> pixelsData = imgaos.ReadBitmapFile("../images/amphora.bmp");

    for(int i = 0; i < 5; i++) {
        std::cout << "Pixel " << i << ": " << std::to_string(pixelsData[i].red) << " " << std::to_string(pixelsData[i].green) << " " << std::to_string(pixelsData[i].blue) << std::endl;
    }

    return 0;
}