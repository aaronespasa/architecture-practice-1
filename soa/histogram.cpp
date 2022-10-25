#include <iostream>
#include <fstream>
#include <string>
#include <chrono>

#include "soa.h"
#include "../common/common.h"

int ImageSOA::GenerateHistogram(std::string filename) {
    auto start = std::chrono::high_resolution_clock::now();
    std::ofstream histogram(filename.c_str());
    std::vector<int> histogramValues(768, 0);

    for (long unsigned int i = 0; i < bmpPixelsData.blue.size(); i++) {
        for (long unsigned int j = 0; j < bmpPixelsData.blue[0].size(); j++) {
            histogramValues[bmpPixelsData.red[i][j]]++;
            histogramValues[bmpPixelsData.green[i][j] + 256]++;
            histogramValues[bmpPixelsData.blue[i][j] + 512]++;
        }
    }
    
    for(int i = 0; i < 768; i++) {
        histogram << histogramValues[i-1] << std::endl;
    }

    histogram.close();

    return std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::high_resolution_clock::now() - start).count();
}