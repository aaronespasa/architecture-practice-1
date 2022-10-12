#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "./common/common.h"

int main() {
    std::ifstream file;
    BMPFileHeader fileHeader;
    InformationHeader infoHeader;

    const char *path = "./amphora.bmp";
    file.open(path, std::ios::in | std::ios::binary);

    if (!file.is_open())
    {
        std::cout << "File could not be opened" << std::endl;
        return -1;
    }

    std::cout << "fileheader size: " << sizeof(fileHeader) << std::endl;

    file.read((char *)&fileHeader, sizeof(fileHeader));

    // Check if the file is a BMP file by checking the first two bytes
    if (fileHeader.file_type != 0x4D42)
    {
        std::cout << "File is not of type BMP" << std::endl;
        return -1;
    }

    file.read((char *)&infoHeader, sizeof(infoHeader));

    std::cout << "Number of planes: " << std::to_string(infoHeader.number_flat) << std::endl;

    // Check that the file has 1 plane
    if (infoHeader.number_flat != 1)
    {
        std::cout << "File should have only 1 plane" << std::endl;
        return -1;
    }

    std::cout << "Bits per pixel: " << std::to_string(infoHeader.bits_per_pixel) << std::endl;

    // Check if the file is a 24-bit BMP file
    if (infoHeader.bits_per_pixel != 24)
    {
        std::cout << "File has not 24 bits per pixel" << std::endl;
        return -1;
    }

    std::cout << "Compression: " << std::to_string(infoHeader.compression) << std::endl;

    // Check if the file is uncompressed
    if (infoHeader.compression != 0)
    {
        std::cout << "File is compressed" << std::endl; //  0 -> no comprimido, 1 -> RLE8, 2 -> RLE4
        return -1;
    }

    // Pixels are stored from the offset_data position in the file
    file.seekg(fileHeader.offset_data, std::ios::beg);

    // Create a vector of vectors of Pixels to store the pixels of the image
    std::vector<Pixel> pixels(infoHeader.height_pixel);

    Pixel pixel;
    // Read the pixels from the file and store them in the vector
    for (int pixel_vector_i = 0; pixel_vector_i < infoHeader.height_pixel; pixel_vector_i++)
    {
        file.read((char *)&pixel, sizeof(pixel));
        pixels[pixel_vector_i] = pixel;
    }

    for (int i = 0; i < 10; i++)
    {
        std::cout << "Pixel " << i << ": " << std::to_string(pixels[i].red) << " " << std::to_string(pixels[i].green) << " " << std::to_string(pixels[i].blue) << std::endl;
    }

    std::cout << "No problems were found" << std::endl;

    // Close the file
    file.close();

    return 0;
}