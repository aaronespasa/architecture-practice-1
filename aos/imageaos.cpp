#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <stdint.h>
#include <chrono>

#include "aos.h"
#include "../common/common.h"

int ImageAOS::ReadBitmapFile(std::string filename) {
    auto start = std::chrono::high_resolution_clock::now();

    // Create a file-reading object to read the bitmap file
    std::ifstream bmpFile(filename.c_str(), std::ios::in | std::ios::binary);

    /* 1. Read the bitmap file header */

    // Check if the file has been found
    if (!bmpFile) {
        throw std::runtime_error("File not found");
    }

    // Read the bitmap file header
    bmpFile.read(reinterpret_cast<char*>(&bmpHeader), sizeof(BMPHeader));

    // Check if the file is a bitmap file
    checkBMPHeader(bmpHeader);

    // Read the extra information until the offset data
    extraHeaderInformation.resize(bmpHeader.offset_data - sizeof(BMPHeader));
    for (long unsigned int i = 0; i < bmpHeader.offset_data - sizeof(BMPHeader); i++) {
        bmpFile.read(reinterpret_cast<char *>(&extraHeaderInformation[i]), 1);
    }

    /* 2. Read the bitmap pixels and store them in a vector of pixels */
    // bmpFile.seekg(bmpHeader.offset_data);

    // Iterate over the rows of the bitmap
    Pixel pixel;
    bmpPixelsData.resize(bmpHeader.height, std::vector<Pixel>(bmpHeader.width));
    for (int i = 0; i < bmpHeader.height; i++) {
        // Fill the vector with the pixels of the row
        for(int j = 0; j < bmpHeader.width; j++) {
            bmpFile.read(reinterpret_cast<char*>(&pixel), sizeof(Pixel));
            bmpPixelsData[i][j] = pixel;
        }

        // Skip the padding bytes. Each row must be a multiple of 4 bytes.
        bmpFile.seekg(bmpHeader.width % 4, std::ios_base::cur);
    }

    /* 3. Close the file and return the vector of pixels */
    bmpFile.close();

    return std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::high_resolution_clock::now() - start).count();
}

int ImageAOS::WriteBitmapFile(std::string filename) {
    auto start = std::chrono::high_resolution_clock::now();

    // Create a file-writing object to write the bitmap file
    std::ofstream bmpFile(filename.c_str(), std::ios::out | std::ios::binary);

    /* 1. Write the bitmap file header and info header */
    bmpFile.write(reinterpret_cast<const char *>(&bmpHeader), sizeof(BMPHeader));

    for (long unsigned int i = 0; i < bmpHeader.offset_data - sizeof(BMPHeader); i++) {
        bmpFile.write(reinterpret_cast<const char *>(&extraHeaderInformation[i]), 1);
    }

    /* 2. Write the bitmap pixels */
    // bmpFile.seekp(bmpHeader.offset_data);

    char paddingValue = 0;
    int padding_length = bmpHeader.width % 4;
    // Iterate over the rows of the bitmap
    for (int i = 0; i < bmpHeader.height; i++) {
        // Write the pixels of the row
        for(int j = 0; j < bmpHeader.width; j++) {
            bmpFile.write(reinterpret_cast<const char *>(&bmpPixelsData[i][j]), sizeof(Pixel));
        }

        // Write the padding bytes. Each row must be a multiple of 4 bytes.
        for (int j = 0; j < padding_length; j++) {
            bmpFile.write(reinterpret_cast<const char *>(&paddingValue), 1);
        }
    }

    /* 3. Close the file */
    bmpFile.close();

    return std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::high_resolution_clock::now() - start).count();
}

std::vector<int> ImageAOS::CopyBitmapFile(string source, string destination) {
    int loadTime = ReadBitmapFile(source);
    int storeTime = WriteBitmapFile(destination);
    return {loadTime, storeTime};
}

BmpPixels ImageAOS::GetBitmapPixelsData() {
    return bmpPixelsData;
}