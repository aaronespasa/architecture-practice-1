#include <iostream>
#include <fstream>
#include <string>

#include "aos.h"
#include "../common/common.h"

void ImageAOS::GenerateHistogram() {
    std::string filename = "./histogram.txt";
    std::ofstream histogram(filename.c_str());
    // if(!histogram.is_open()) {
    //     throw std::runtime_error("Error opening histogram file");
    // }

    std::cout << "Generating histogram..." << std::endl;
    histogram << "Histogram for " << filename << std::endl;

    int red[256] = {0};
    int green[256] = {0};
    int blue[256] = {0};

    for (long unsigned int i = 0; i < bmpPixelsData.size(); i++) {
        for (long unsigned int j = 0; j < bmpPixelsData[0].size(); j++) {
            red[bmpPixelsData[i][j].red]++;
            green[bmpPixelsData[i][j].green]++;
            blue[bmpPixelsData[i][j].blue]++;
        }
    }
    
    // write in the histogram the values from red, green and blue. first, the
    // red values, then the green values and finally the blue values
    for (int i = 0; i < 256; i++) {
        histogram << red[i] << std::endl;
    }
    for (int i = 0; i < 256; i++) {
        histogram << green[i] << std::endl;
    }
    for (int i = 0; i < 256; i++) {
        histogram << blue[i] << std::endl;
    }

    histogram.close();
}