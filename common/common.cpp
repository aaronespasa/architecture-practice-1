#include <iostream>
#include <string>

#include "common.h"

void checkBMPHeader(BMPHeader &header) {
    // Check if the file is a bitmap file
    if (header.type != 0x4D42) {
        throw std::runtime_error("Not a bitmap file");
    }

    // Check the number of planes
    if (header.planes_count != 1) {
        std::string error_message = "Number of planes must be 1 but got " + std::to_string(header.planes_count) + " instead";
        throw std::runtime_error(error_message);
    }

    // Check the number of bits per pixel
    if (header.bits_per_pixel != 24) {
        std::string error_message = "Number of bits per pixel must be 24 but got " + std::to_string(header.bits_per_pixel) + " instead";
        throw std::runtime_error(error_message);
    }

    // Check if the bitmap is uncompressed
    if (header.compression != 0) {
        throw std::runtime_error("The bitmap must be uncompressed");
    }
}