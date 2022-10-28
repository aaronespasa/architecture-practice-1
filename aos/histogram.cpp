#include <iostream>
#include <fstream>
#include <string>
#include <chrono>

#include "aos.h"
#include "../common/common.h"

int ImageAOS::GenerateHistogram(std::string filename) {
    auto start = std::chrono::high_resolution_clock::now();
    std::ofstream histogram(filename.c_str());
    std::vector<int> histogramValues(768, 0);

    for (long unsigned int i = 0; i < bmpPixelsData.size(); i++) {
        for (long unsigned int j = 0; j < bmpPixelsData[0].size(); j++) {
            histogramValues[bmpPixelsData[i][j].red]++; // first 256 values will be red
            histogramValues[bmpPixelsData[i][j].green + 256]++; // next 256 values will be green
            histogramValues[bmpPixelsData[i][j].blue + 512]++; // last 256 values will be blue
        }
    }
    
    // as the values are in order, we just need one for loop
    for(int i = 0; i < 768; i++) {
        histogram << histogramValues[i] << std::endl;
    }

    histogram.close();
    return std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::high_resolution_clock::now() - start).count();
}