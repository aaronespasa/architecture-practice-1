#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <stdint.h>
#include <chrono>

#include "soa.h"
#include "../common/common.h"

int ImageSOA::ReadBitmapFile(std::string filename) {
    auto start = std::chrono::high_resolution_clock::now();
    std::ifstream bmpFile(filename.c_str(), std::ios::in | std::ios::binary);
    if (!bmpFile) throw std::runtime_error("File not found"); // // Check if the file has been found

    bmpFile.read(reinterpret_cast<char*>(&bmpHeader), sizeof(BMPHeader));
    checkBMPHeader(bmpHeader);

    extraHeaderInformation.resize(bmpHeader.offset_data - sizeof(BMPHeader));
    for (long unsigned int i = 0; i < bmpHeader.offset_data - sizeof(BMPHeader); i++)
        bmpFile.read(reinterpret_cast<char *>(&extraHeaderInformation[i]), 1);

    uint8_t blue = 0, green = 0, red = 0;
    bmpPixelsData.blue.resize(bmpHeader.height, std::vector<uint8_t>(bmpHeader.width));
    bmpPixelsData.green.resize(bmpHeader.height, std::vector<uint8_t>(bmpHeader.width));
    bmpPixelsData.red.resize(bmpHeader.height, std::vector<uint8_t>(bmpHeader.width));
    for (int i = 0; i < bmpHeader.height; i++) {
        for(int j = 0; j < bmpHeader.width; j++) {
            bmpFile.read(reinterpret_cast<char*>(&blue), sizeof(blue));
            bmpFile.read(reinterpret_cast<char*>(&green), sizeof(green));
            bmpFile.read(reinterpret_cast<char*>(&red), sizeof(red));
            bmpPixelsData.blue[i][j] = blue; bmpPixelsData.green[i][j] = green; bmpPixelsData.red[i][j] = red;
        }
        bmpFile.seekg(bmpHeader.width % 4, std::ios_base::cur); // Skip the padding bytes
    }
    bmpFile.close();
    return std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::high_resolution_clock::now() - start).count();
}

int ImageSOA::WriteBitmapFile(std::string filename) {
    auto start = std::chrono::high_resolution_clock::now();
    std::ofstream bmpFile(filename.c_str(), std::ios::out | std::ios::binary);

    /* 1. Write the bitmap file header and info header */
    bmpFile.write(reinterpret_cast<const char*>(&bmpHeader), sizeof(BMPHeader));
    for (long unsigned int i = 0; i < bmpHeader.offset_data - sizeof(BMPHeader); i++)
        bmpFile.write(reinterpret_cast<const char *>(&extraHeaderInformation[i]), 1);

    /* 2. Write the bitmap pixels */
    char paddingValue = 0; // padding is made of 0s
    int padding_length = bmpHeader.width % 4;
    for (int i = 0; i < bmpHeader.height; i++) {
        for(int j = 0; j < bmpHeader.width; j++) {
            bmpFile.write(reinterpret_cast<const char*>(&bmpPixelsData.blue[i][j]), sizeof(uint8_t));
            bmpFile.write(reinterpret_cast<const char*>(&bmpPixelsData.green[i][j]), sizeof(uint8_t));
            bmpFile.write(reinterpret_cast<const char*>(&bmpPixelsData.red[i][j]), sizeof(uint8_t));
        }

        // Write the padding bytes. Each row must be a multiple of 4 bytes.
        for (int j = 0; j < padding_length; j++) {
            bmpFile.write(reinterpret_cast<const char *>(&paddingValue), 1);
        }
    }
    bmpFile.close();
    return std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::high_resolution_clock::now() - start).count();
}

std::vector<int> ImageSOA::CopyBitmapFile(string source, string destination) {
    int loadTime = ReadBitmapFile(source);
    int storeTime = WriteBitmapFile(destination);
    return {loadTime, storeTime};
}

BmpPixels ImageSOA::GetBitmapPixelsData() {
    return bmpPixelsData;
}