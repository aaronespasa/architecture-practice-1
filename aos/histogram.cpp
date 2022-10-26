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
            histogramValues[bmpPixelsData[i][j].red]++;
            histogramValues[bmpPixelsData[i][j].green + 256]++;
            histogramValues[bmpPixelsData[i][j].blue + 512]++;
        }
    }
    
    for(int i = 0; i < 768; i++) {
        histogram << histogramValues[i] << std::endl;
    }

    histogram.close();
    return std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::high_resolution_clock::now() - start).count();
}