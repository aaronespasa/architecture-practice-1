#ifndef AOS_H
#define AOS_H

#include <string>
#include <vector>

#include "../common/common.h"

class ImageAOS {
    public:
        std::vector<Pixel> ReadBitmapFile(std::string filename);
};


#endif