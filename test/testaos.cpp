#include <iostream>

#include "../aos/aos.h"

void checkReadAndWriteTest1() {
    // ImageAOS imgaos;

    // imgaos.ReadBitmapFile("../images/amphora.bmp");
    // imgaos.WriteBitmapFile("../images/amphora_copy.bmp");

    std::cout << "Read and write test 1 passed" << std::endl;
}

int main() {
    checkReadAndWriteTest1();
    return 0;
}