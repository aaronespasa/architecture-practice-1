#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <stdint.h>
#include <chrono>

#include "aos.h"
#include "../common/common.h"

void ImageAOS::ReadBitmapHeader(BmpHeaderContainer header) {
    bmpHeader.type = header[1] * 256 + header[0];
    bmpHeader.file_size = ((header[5] * 256 + header[4]) * 256 + header[3]) * 256 + header[2];
    bmpHeader.reserved = ((header[9] * 256 + header[8]) * 256 + header[7]) * 256 + header[6];
    bmpHeader.offset_data = ((header[13] * 256 + header[12]) * 256 + header[11]) * 256 + header[10];
    bmpHeader.header_size = ((header[17] * 256 + header[16]) * 256 + header[15]) * 256 + header[14];
    bmpHeader.width = ((header[21] * 256 + header[20]) * 256 + header[19]) * 256 + header[18];
    bmpHeader.height = ((header[25] * 256 + header[24]) * 256 + header[23]) * 256 + header[22];
    bmpHeader.planes_count = header[27] * 256 + header[26];
    bmpHeader.bits_per_pixel = header[29] * 256 + header[28];
    bmpHeader.compression = ((header[33] * 256 + header[32]) * 256 + header[31]) * 256 + header[30];
    bmpHeader.img_size = ((header[37] * 256 + header[36]) * 256 + header[35]) * 256 + header[34];
    bmpHeader.x_pixels_per_meter = ((header[41] * 256 + header[40]) * 256 + header[39]) * 256 + header[38];
    bmpHeader.y_pixels_per_meter = ((header[45] * 256 + header[44]) * 256 + header[43]) * 256 + header[42];
    bmpHeader.colors_used = ((header[49] * 256 + header[48]) * 256 + header[47]) * 256 + header[46];
    bmpHeader.colors_important = ((header[53] * 256 + header[52]) * 256 + header[51]) * 256 + header[50];
}

void ImageAOS::WriteBitmapHeader(std::string filename) {
    std::ofstream bmpFile(filename.c_str(), std::ios::out | std::ios::binary);
    bmpFile.write(reinterpret_cast<const char *>(&bmpHeader.type), sizeof(bmpHeader.type));
    bmpFile.write(reinterpret_cast<const char *>(&bmpHeader.file_size), sizeof(bmpHeader.file_size));
    bmpFile.write(reinterpret_cast<const char *>(&bmpHeader.reserved), sizeof(bmpHeader.reserved));
    bmpFile.write(reinterpret_cast<const char *>(&bmpHeader.offset_data), sizeof(bmpHeader.offset_data));
    bmpFile.write(reinterpret_cast<const char *>(&bmpHeader.header_size), sizeof(bmpHeader.header_size));
    bmpFile.write(reinterpret_cast<const char *>(&bmpHeader.width), sizeof(bmpHeader.width));
    bmpFile.write(reinterpret_cast<const char *>(&bmpHeader.height), sizeof(bmpHeader.height));
    bmpFile.write(reinterpret_cast<const char *>(&bmpHeader.planes_count), sizeof(bmpHeader.planes_count));
    bmpFile.write(reinterpret_cast<const char *>(&bmpHeader.bits_per_pixel), sizeof(bmpHeader.bits_per_pixel));
    bmpFile.write(reinterpret_cast<const char *>(&bmpHeader.compression), sizeof(bmpHeader.compression));
    bmpFile.write(reinterpret_cast<const char *>(&bmpHeader.img_size), sizeof(bmpHeader.img_size));
    bmpFile.write(reinterpret_cast<const char *>(&bmpHeader.x_pixels_per_meter), sizeof(bmpHeader.x_pixels_per_meter));
    bmpFile.write(reinterpret_cast<const char *>(&bmpHeader.y_pixels_per_meter), sizeof(bmpHeader.y_pixels_per_meter));
    bmpFile.write(reinterpret_cast<const char *>(&bmpHeader.colors_used), sizeof(bmpHeader.colors_used));
    bmpFile.write(reinterpret_cast<const char *>(&bmpHeader.colors_important), sizeof(bmpHeader.colors_important));
    bmpFile.close();
}

int ImageAOS::ReadBitmapFile(std::string filename) {
    auto start = std::chrono::high_resolution_clock::now();
    std::ifstream bmpFile(filename.c_str(), std::ios::in | std::ios::binary);
    if (!bmpFile) throw std::runtime_error("File not found"); // Check if the file has been found
    
    BmpHeaderContainer header;
    bmpFile.read(reinterpret_cast<char*>(&header), sizeof(header)); // Read the header
    ReadBitmapHeader(header);             // Assign the information to a struct
    checkBMPHeader(bmpHeader);            // Check if the file is a bitmap file
    extraHeaderInformation.resize(bmpHeader.offset_data - sizeof(header)); // extra information until the offset data
    for (long unsigned int i = 0; i < bmpHeader.offset_data - sizeof(header); i++)
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
    WriteBitmapHeader(filename);
    std::ofstream bmpFile(filename.c_str(), std::ios::out | std::ios::binary | std::ios::app);
    if (!bmpFile) throw std::runtime_error("File not found");

    /* 1. Write the bitmap file header and info header */
    bmpFile.seekp(54, std::ios_base::beg);
    for (long unsigned int i = 0; i < bmpHeader.offset_data - 54; i++)
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