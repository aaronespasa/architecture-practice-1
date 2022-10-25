#include <iostream>
#include <string>
#include <vector>

#include "../common/common.h"
#include "aos.h"

int main (int argc, char *argv[]) {
    if(!checkArgCount(argc)) return -1;
    Parser parser = parseArgs(argv[1], argv[2], argv[3]);
    if(parser.operationNum == -1) return -1;

    int loadTime = 0, operationTime = 0, storeTime = 0;
    std::vector<int> times;
    for (std::string file : parser.filenames) {
        ImageAOS imgaos;
        std::string inputFilePath = parser.inputDir + "/" + file + ".bmp";
        std::string outputFilePath;

        switch (parser.operationNum) {
            case 0:
                outputFilePath = parser.outputDir + "/" + file + ".bmp";
                times = imgaos.CopyBitmapFile(inputFilePath, outputFilePath);
                loadTime = times[0], storeTime = times[1];
                printTime(inputFilePath, "Copy", loadTime, operationTime, storeTime);
                break;
            case 1:
                outputFilePath = parser.outputDir + "/" + file + ".hst";
                loadTime = imgaos.ReadBitmapFile(inputFilePath);
                operationTime = imgaos.GenerateHistogram(outputFilePath);
                printTime(inputFilePath, "Histo", loadTime, operationTime, storeTime);
                break;
            case 2:
                outputFilePath = parser.outputDir + "/" + file + ".bmp";
                loadTime = imgaos.ReadBitmapFile(inputFilePath);
                operationTime = imgaos.ToGrayScale();
                storeTime = imgaos.WriteBitmapFile(outputFilePath);
                printTime(inputFilePath, "Mono", loadTime, operationTime, storeTime);
                break;
            case 3:
                outputFilePath = parser.outputDir + "/" + file + ".bmp";
                loadTime = imgaos.ReadBitmapFile(inputFilePath);
                operationTime = imgaos.ApplyGaussianBlur();
                storeTime = imgaos.WriteBitmapFile(outputFilePath);
                printTime(inputFilePath, "Gauss", loadTime, operationTime, storeTime);
                break;
        }
    }

    return 0;
}