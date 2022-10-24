#ifndef COMMON_H
#define COMMON_H

#include <stdint.h>

// using namespace std;

struct BMPHeader {
    uint16_t type{0x4D42};
    uint32_t file_size{0};
    uint32_t reserved{0};
    uint32_t offset_data{0};
    uint32_t header_size{14};
    int32_t width{0};
    int32_t height{0};
    uint16_t planes_count{1};
    uint16_t bits_per_pixel{24};
    uint32_t compression{0};
    uint32_t img_size{0};
    int32_t x_pixels_per_meter{0};
    int32_t y_pixels_per_meter{0};
    uint32_t colors_used{0};
    uint32_t colors_important{0};
} __attribute__((packed)); // to avoid padding

void checkBMPHeader(BMPHeader &header);

#endif