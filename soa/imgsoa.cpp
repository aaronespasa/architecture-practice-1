#include <iostream>
#include <string>
#include <vector>

#include "../common/common.h"
#include "soa.h"

void PrintCopyInformation(std::string outputDir, std::string inputFilePath, std::string filename, Times timesStruct) {
    ImageSOA imgsoa;
    std::string outputFilePath = outputDir + "/" + filename + ".bmp";
    std::vector<int>times = imgsoa.CopyBitmapFile(inputFilePath, outputFilePath);
    timesStruct.loadTime = times[0], timesStruct.storeTime = times[1];
    printTime(inputFilePath, "Copy", timesStruct);
}

void PrintHistoInformation(std::string outputDir, std::string inputFilePath, std::string filename, Times timesStruct) {
    ImageSOA imgsoa;
    std::string outputFilePath = outputDir + "/" + filename + ".hst";
    timesStruct.loadTime = imgsoa.ReadBitmapFile(inputFilePath);
    timesStruct.operationTime = imgsoa.GenerateHistogram(outputFilePath);
    printTime(inputFilePath, "Histo", timesStruct);
}

void PrintGrayscaleInformation(std::string outputDir, std::string inputFilePath, std::string filename, Times timesStruct) {
    ImageSOA imgsoa;
    std::string outputFilePath = outputDir + "/" + filename + ".bmp";
    timesStruct.loadTime = imgsoa.ReadBitmapFile(inputFilePath);
    timesStruct.operationTime = imgsoa.ToGrayScale();
    timesStruct.storeTime = imgsoa.WriteBitmapFile(outputFilePath);
    printTime(inputFilePath, "Mono", timesStruct);
}

void PrintGaussInformation(std::string outputDir, std::string inputFilePath, std::string filename, Times timesStruct) {
    ImageSOA imgsoa;
    std::string outputFilePath = outputDir + "/" + filename + ".bmp";
    timesStruct.loadTime = imgsoa.ReadBitmapFile(inputFilePath);
    timesStruct.operationTime = imgsoa.ApplyGaussianBlur();
    timesStruct.storeTime = imgsoa.WriteBitmapFile(outputFilePath);
    printTime(inputFilePath, "Gauss", timesStruct);
}



int main (int argc, char *argv[]) {
    if(!checkArgCount(argc)) return -1;
    Parser parser = parseArgs(argv[1], argv[2], argv[3]);
    if(parser.operationNum == -1) return -1;

    Times timesStruct;
    for (std::string file : parser.filenames) {
        std::string inputFilePath = parser.inputDir + "/" + file + ".bmp";
        switch (parser.operationNum) {
            case 0:
                PrintCopyInformation(parser.outputDir, inputFilePath, file, timesStruct);
                break;
            case 1:
                PrintHistoInformation(parser.outputDir, inputFilePath, file, timesStruct);
                break;
            case 2:
                PrintGrayscaleInformation(parser.outputDir, inputFilePath, file, timesStruct);
                break;
            case 3:
                PrintGaussInformation(parser.outputDir, inputFilePath, file, timesStruct);
                break;
        }
    }

    return 0;
}