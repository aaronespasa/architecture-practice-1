#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#include "aos.h"
#include "../common/common.h"

std::vector<Pixel> ImageAOS::ReadBitmapFile(std::string filename) {
    // Create a file-reading object to read the bitmap file
    std::ifstream bmpFile(filename.c_str(), std::ios::in | std::ios::binary);

    /*
     * 1. Read the bitmap file header:
     *      - Check if the file has been found
     *      - Check if the file is a bitmap file
     *      - Check the number of planes
     *      - Check the number of bits per pixel
     *      - Check if the bitmap is uncompressed
     */

    // Check if the file has been found
    if (!bmpFile) {
        throw std::runtime_error("File not found");
    }

    // Read the bitmap file header
    BMPFileHeader bmpFileHeader;
    bmpFile.read((char *) &bmpFileHeader, sizeof(BMPFileHeader));

    // Check if the file is a bitmap file
    if (bmpFileHeader.type != 0x4D42) {
        throw std::runtime_error("Not a bitmap file");
    }

    // Read the bitmap info header
    BMPInfoHeader bmpInfoHeader;
    bmpFile.read((char *) &bmpInfoHeader, sizeof(BMPInfoHeader));

    // Check the number of planes
    if (bmpInfoHeader.planes_count != 1) {
        std::string error_message = "Number of planes must be 1 but got " + std::to_string(bmpInfoHeader.planes_count) + " instead";
        throw std::runtime_error(error_message);
    }

    // Check the number of bits per pixel
    if (bmpInfoHeader.bits_per_pixel != 24) {
        std::string error_message = "Number of bits per pixel must be 24 but got " + std::to_string(bmpInfoHeader.bits_per_pixel) + " instead";
        throw std::runtime_error(error_message);
    }

    // Check if the bitmap is uncompressed
    if (bmpInfoHeader.compression != 0) {
        throw std::runtime_error("The bitmap must be uncompressed");
    }

    /*
     * 2. Read the bitmap pixels and store them in a vector of pixels
     */
    bmpFile.seekg(bmpFileHeader.offset_data, std::ios::beg);

    // Create a vector of pixels
    std::vector<Pixel> bmpPixelsData(bmpInfoHeader.height);

    // Read the pixels from the bitmap file
    Pixel pixel;
    for (int i = 0; i < bmpInfoHeader.height; i++) {
        bmpFile.read((char *)&pixel, sizeof(pixel));

        // Store the pixel in the vector
        bmpPixelsData[i] = pixel;
    }

    /*
     * 3. Close the file and return the vector of pixels
     */
    bmpFile.close();

    return bmpPixelsData;
}
    