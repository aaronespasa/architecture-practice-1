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
    std::ifstream bmpFile(filename.c_str(), std::ios::in | std::ios::binary);
    if (!bmpFile) throw std::runtime_error("File not found"); // Check if the file has been found

    bmpFile.read(reinterpret_cast<char*>(&bmpHeader), sizeof(BMPHeader)); // Read the header
    checkBMPHeader(bmpHeader);                                            // Check if the file is a bitmap file

    extraHeaderInformation.resize(bmpHeader.offset_data - sizeof(BMPHeader)); // extra information until the offset data
    for (long unsigned int i = 0; i < bmpHeader.offset_data - sizeof(BMPHeader); i++)
        bmpFile.read(reinterpret_cast<char *>(&extraHeaderInformation[i]), 1);
    
    Pixel pixel;
    bmpPixelsData.resize(bmpHeader.height, std::vector<Pixel>(bmpHeader.width));
    for (int i = 0; i < bmpHeader.height; i++) {
        for(int j = 0; j < bmpHeader.width; j++) {
            bmpFile.read(reinterpret_cast<char*>(&pixel), sizeof(Pixel));
            bmpPixelsData[i][j] = pixel;
        }
        // Skip the padding bytes. Each row must be a multiple of 4 bytes.
        bmpFile.seekg(bmpHeader.width % 4, std::ios_base::cur);
    }

    bmpFile.close(); // Close the file and return the vector of pixels
    return std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::high_resolution_clock::now() - start).count();
}

int ImageAOS::WriteBitmapFile(std::string filename) {
    auto start = std::chrono::high_resolution_clock::now();
    std::ofstream bmpFile(filename.c_str(), std::ios::out | std::ios::binary);

    /* 1. Write the bitmap file header and info header */
    bmpFile.write(reinterpret_cast<const char *>(&bmpHeader), sizeof(BMPHeader));
    for (long unsigned int i = 0; i < bmpHeader.offset_data - sizeof(BMPHeader); i++)
        bmpFile.write(reinterpret_cast<const char *>(&extraHeaderInformation[i]), 1);

    /* 2. Write the bitmap pixels */
    char paddingValue = 0; // padding is made of 0s
    int padding_length = bmpHeader.width % 4;
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