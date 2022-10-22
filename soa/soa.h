#ifndef SOA_H
#define SOA_H

#include <vector>
#include <stdint.h>

struct Pixel {
    std::vector<uint8_t> blue;
    std::vector<uint8_t> green;
    std::vector<uint8_t> red;
};

#endif