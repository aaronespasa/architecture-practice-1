#include <iostream>
#include <fstream>
#include <string>

#include "soa.h"
#include "../common/common.h"

void ImageSOA::GenerateHistogram(std::string filename) {
    std::ofstream histogram(filename.c_str());
    std::vector<int> histogramValues(768, 0);

    for (long unsigned int i = 0; i < bmpPixelsData.blue.size(); i++) {
        for (long unsigned int j = 0; j < bmpPixelsData.blue[0].size(); j++) {
            histogramValues[bmpPixelsData.red[i][j]]++;
            histogramValues[bmpPixelsData.green[i][j] + 256]++;
            histogramValues[bmpPixelsData.blue[i][j] + 512]++;
        }
    }
    
    for(int i = 1; i < 769; i++) {
        histogram << histogramValues[i-1] << " ";
        if(i % 256 == 0) histogram << std::endl;   
    }

    histogram.close();
}