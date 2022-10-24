#include <iostream>
#include <fstream>
#include <string>

#include "aos.h"
#include "../common/common.h"

void ImageAOS::GenerateHistogram(std::string filename) {
    std::ofstream histogram(filename.c_str());
    std::vector<int> histogramValues(768, 0);

    for (long unsigned int i = 0; i < bmpPixelsData.size(); i++) {
        for (long unsigned int j = 0; j < bmpPixelsData[0].size(); j++) {
            histogramValues[bmpPixelsData[i][j].red]++;
            histogramValues[bmpPixelsData[i][j].green + 256]++;
            histogramValues[bmpPixelsData[i][j].blue + 512]++;
        }
    }
    
    for(int i = 1; i < 769; i++) {
        histogram << histogramValues[i-1] << " ";
        if(i % 256 == 0) histogram << std::endl;   
    }

    histogram.close();
}