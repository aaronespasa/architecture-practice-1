#include <string>
#include <iostream>
#include <filesystem>

#include "common.h"

void printInputOutputDir(const std::string& inputDir, const std::string& outputDir) {
    std::cout << "Input path: " << inputDir << std::endl;
    std::cout << "Output path: " << outputDir << std::endl;
}

void printUsage() {
    std::cout << "  image in_path out_path oper" << std::endl;
    std::cout << "    operation: copy, histo, mono, gauss" << std::endl;
}

bool checkArgCount(int argc) {
    if (argc != 4) {
        std::cout << "Wrong format: " << std::endl;
        printUsage();
        return false;
    }
    return true;
}

int checkOperation(const std::string& operation) {
    if (operation == "copy") {
        return 0;
    } else if (operation == "histo") {
        return 1;
    } else if (operation == "mono") {
        return 2;
    } else if (operation == "gauss") {
        return 3;
    } else {
        std::cout << "Unexpected operation:" << operation << std::endl;
        printUsage();
        return -1;
    }
}

bool checkDirectories(const std::string& inputDir, const std::string& outputDir) {
    printInputOutputDir(inputDir, outputDir);
    if (!std::filesystem::exists(inputDir)) {
        std::cout << "Cannot open directory [" << inputDir << "]" << std::endl;
        printUsage();
        return false;
    }
    if (!std::filesystem::exists(outputDir)) {
        std::cout << "Output directory [" << outputDir << "] does not exist" << std::endl;
        printUsage();
        return false;
    }
    return true;
}

std::vector<std::string> getFiles(const std::string &inputDir) {
    std::vector<std::string> filenames;
    for (const std::filesystem::directory_entry & entry : std::filesystem::directory_iterator(inputDir)) {
        // only return those file names that end with .bmp
        if (entry.is_regular_file() && entry.path().extension() == ".bmp") {
            // push to filenames only the name of the entry without the path nor the extension
            filenames.push_back(entry.path().stem().string());
        }
    }
    return filenames;
}

Parser parseArgs(const std::string &inputDir, const std::string &outputDir, const std::string &operation) {
    Parser parser;

    // check that the operation is valid
    parser.operationNum = checkOperation(operation);
    if (parser.operationNum == -1) return parser;

    // check that the directories exist
    if (!checkDirectories(inputDir, outputDir)) {
        parser.operationNum = -1;
        return parser;
    } else {
        parser.inputDir = inputDir;
        parser.outputDir = outputDir;
    }

    // get the list of files in the input directory
    parser.filenames = getFiles(inputDir);

    return parser;
}

void printTime(const std::string &inputFilePath, const std::string& operation, int loadTime, int operationTime, int storeTime) {
    int totalTime = loadTime + operationTime + storeTime;
    std::cout << "File: \"" << inputFilePath << "\"(time: " << totalTime << ")" << std::endl;
    if (loadTime > 0) {
        std::cout << "  Load time: " << loadTime << std::endl;
    }
    if (operationTime > 0) {
        std::cout << "  " << operation << " time: " << operationTime << std::endl;
    }
    if (storeTime > 0) {
        std::cout << "  Store time: " << storeTime << std::endl;
    }
}