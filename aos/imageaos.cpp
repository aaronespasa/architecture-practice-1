#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <stdint.h>

#include "aos.h"
#include "../common/common.h"


void ImageAOS::ReadBitmapFile(std::string filename) {
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
    bmpFile.seekg(bmpFileHeader.offset_data);

    // Iterate over the rows of the bitmap
    for (int i = 0; i < bmpInfoHeader.height; i++) {
        // Create a vector of pixels for each row
        std::vector<Pixel> bmpPixelsRowData(bmpInfoHeader.width);

        // Fill the vector with the pixels of the row
        for(int j = 0; j < bmpInfoHeader.width; j++) {
            Pixel pixel;
            bmpFile.read((char *) &pixel, sizeof(Pixel));
            
            bmpPixelsRowData[j] = pixel;
        }

        // Skip the padding bytes. Each row must be a multiple of 4 bytes.
        bmpFile.seekg(bmpInfoHeader.width % 4, std::ios_base::cur);

        // Store the pixel in the vector
        bmpPixelsData.push_back(bmpPixelsRowData);
    }

    /*
     * 3. Close the file and return the vector of pixels
     */
    bmpFile.close();
}

void ImageAOS::WriteBitmapFile(std::string filename) {
    // Create a file-writing object to write the bitmap file
    std::ofstream bmpFile(filename.c_str(), std::ios::out | std::ios::binary);

    /*
     * 1. Write the bitmap file header
     */
    BMPFileHeader bmpFileHeader;
    bmpFileHeader.type = 0x4D42;
    bmpFileHeader.size = 54 + bmpPixelsData.size() * bmpPixelsData[0].size() * 3;
    bmpFileHeader.reserved = 0;
    bmpFileHeader.offset_data = 54;

    bmpFile.write((char *) &bmpFileHeader, sizeof(BMPFileHeader));

    /*
     * 2. Write the bitmap info header
     */
    BMPInfoHeader bmpInfoHeader;
    bmpInfoHeader.size = 40;
    bmpInfoHeader.width = bmpPixelsData[0].size();
    bmpInfoHeader.height = bmpPixelsData.size();
    bmpInfoHeader.planes_count = 1;
    bmpInfoHeader.bits_per_pixel = 24;
    bmpInfoHeader.compression = 0;
    bmpInfoHeader.img_size = bmpPixelsData.size() * bmpPixelsData[0].size() * 3;
    bmpInfoHeader.x_pixels_per_meter = 0;
    bmpInfoHeader.y_pixels_per_meter = 0;
    bmpInfoHeader.colors_used = 0;
    bmpInfoHeader.colors_important = 0;

    bmpFile.write((char *) &bmpInfoHeader, sizeof(BMPInfoHeader));

    /*
     * 3. Write the bitmap pixels
     */
    // Iterate over the rows of the bitmap
    for (int i = 0; i < bmpInfoHeader.height; i++) {
        // Write the pixels of the row
        for(int j = 0; j < bmpInfoHeader.width; j++) {
            bmpFile.write((char *) &bmpPixelsData[i][j], sizeof(Pixel));
        }

        // Write the padding bytes. Each row must be a multiple of 4 bytes.
        int padding = bmpInfoHeader.width % 4;
        for (int j = 0; j < padding; j++) {
            bmpFile.write((char *) &padding, 1);
        }
    }

    /*
     * 4. Close the file
     */
    bmpFile.close();
}

BmpPixels ImageAOS::GetBitmapPixelsData() {
    return bmpPixelsData;
}