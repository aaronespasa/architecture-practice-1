#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <stdint.h>

#include "soa.h"
#include "../common/common.h"

void ImageSOA::ReadBitmapFile(std::string filename) {
    // Create a file-reading object to read the bitmap file
    std::ifstream bmpFile(filename.c_str(), std::ios::in | std::ios::binary);

    /* 1. Read the bitmap file header */

    // Check if the file has been found
    if (!bmpFile) {
        throw std::runtime_error("File not found");
    }

    // Read the bitmap file header
    bmpFile.read((char *)&bmpHeader, sizeof(BMPHeader));

    // Check if the file is a bitmap file
    checkBMPHeader(bmpHeader);

    /* 2. Read the bitmap pixels and store them in a vector of pixels */
    bmpFile.seekg(bmpHeader.offset_data);

    // Iterate over the rows of the bitmap
    uint8_t blue = 0, green = 0, red = 0;
    bmpPixelsData.blue.resize(bmpHeader.height, std::vector<uint8_t>(bmpHeader.width));
    bmpPixelsData.green.resize(bmpHeader.height, std::vector<uint8_t>(bmpHeader.width));
    bmpPixelsData.red.resize(bmpHeader.height, std::vector<uint8_t>(bmpHeader.width));
    for (int i = 0; i < bmpHeader.height; i++) {
        // Fill the vector with the pixels of the row
        for(int j = 0; j < bmpHeader.width; j++) {
            bmpFile.read((char *) &blue, sizeof(blue));
            bmpFile.read((char *) &green, sizeof(green));
            bmpFile.read((char *) &red, sizeof(red));
            bmpPixelsData.blue[i][j] = blue;
            bmpPixelsData.green[i][j] = green;
            bmpPixelsData.red[i][j] = red;
        }

        // Skip the padding bytes. Each row must be a multiple of 4 bytes.
        bmpFile.seekg(bmpHeader.width % 4, std::ios_base::cur);
    }

    /* 3. Close the file and return the vector of pixels */
    bmpFile.close();
}

void ImageSOA::WriteBitmapFile(std::string filename) {
    // Create a file-writing object to write the bitmap file
    std::ofstream bmpFile(filename.c_str(), std::ios::out | std::ios::binary);

    /* 1. Write the bitmap file header and info header */
    bmpFile.write((char *)&bmpHeader, sizeof(BMPHeader));

    /* 2. Write the bitmap pixels */
    bmpFile.seekp(bmpHeader.offset_data);

    // Iterate over the rows of the bitmap
    for (int i = 0; i < bmpHeader.height; i++) {
        // Write the pixels of the row
        for(int j = 0; j < bmpHeader.width; j++) {
            bmpFile.write((char *)&bmpPixelsData.blue[i][j], sizeof(uint8_t));
            bmpFile.write((char *)&bmpPixelsData.green[i][j], sizeof(uint8_t));
            bmpFile.write((char *)&bmpPixelsData.red[i][j], sizeof(uint8_t));
        }

        // Write the padding bytes. Each row must be a multiple of 4 bytes.
        int padding = bmpHeader.width % 4;
        for (int j = 0; j < padding; j++) {
            bmpFile.write((char *) &padding, 1);
        }
    }

    /* 3. Close the file */
    bmpFile.close();
}