#include <gtest/gtest.h>
#include <iostream>
#include <string>
#include <stdlib.h>
#include <vector>
#include <filesystem>
#include "../common/common.h"
#include "../aos/aos.h"
    
/* ----------------------------copy------------------------------------ */

TEST(check_copy_task, all) {
    /* Check all images are copied correctly by comparing them
         with the expected ones (those included in the ../images/test/copy folder)*/
    std::string original_images_path = "../images";
    std::vector<std::string> original_images = getFiles(original_images_path);
    std::string transformed_images_path = "../images/test/copy";
    std::string expected_images_path = "../images/test/copy";
    std::string comparison_command;

    int output{-1};
    for(std::string file : original_images) {
        std::string filename = file + ".bmp";
        std::string transformed_filename = file + "_copy.bmp";
        std::string original_image_path = original_images_path + "/" + filename;
        std::string transformed_image = transformed_images_path + "/" + transformed_filename;
        std::string expected_image = expected_images_path + "/" + filename;

        ImageAOS imgaos;
        imgaos.CopyBitmapFile(original_image_path, transformed_image);

        comparison_command = "cmp  " + transformed_image + " " + expected_image;
        output = system(comparison_command.c_str());
        EXPECT_EQ(output, 0);
    }
}

/* ----------------------------------------------------------------------- */ 

/* ----------------------------histo------------------------------------ */

TEST(check_histogram_task, all) {
    /* Check all histograms are generated correctly by comparing them
         with the expected ones (those included in the ../histograms/test folder)*/
    std::string original_images_path = "../images";
    std::vector<std::string> original_images = getFiles(original_images_path);
    std::string transformed_images_path = "../histograms";
    std::string expected_images_path = "../histograms/test";
    std::string comparison_command;

    int output{-1};
    for(std::string file : original_images) {
        std::string original_image_path = original_images_path + "/" + file + ".bmp";
        std::string histogram = transformed_images_path + "/" + file + ".hst";
        std::string expected_histogram = expected_images_path + "/" + file + ".hst";

        ImageAOS imgaos;
        imgaos.ReadBitmapFile(original_image_path);
        imgaos.GenerateHistogram(histogram);

        comparison_command = "diff  " + histogram + " " + expected_histogram;
        output = system(comparison_command.c_str());
        EXPECT_EQ(output, 0);
    }
}

/* ----------------------------------------------------------------------- */ 

/* ----------------------------grayscale------------------------------------ */

TEST(check_grayscale_task, all) {
    /* Check all grayscale images are generated correctly by comparing them
        with the expected ones (those included in the ../images/test/mono folder)*/
    std::string original_images_path = "../images";
    std::vector<std::string> original_images = getFiles(original_images_path);
    std::string transformed_images_path = "../images/test/mono";
    std::string expected_images_path = "../images/test/mono";
    std::string comparison_command;

    int output{-1};
    for(std::string file : original_images) {
        std::string filename = file + ".bmp";
        std::string transformed_filename = file + "_mono.bmp";
        std::string original_image_path = original_images_path + "/" + filename;
        std::string transformed_image = transformed_images_path + "/" + transformed_filename;
        std::string expected_image = expected_images_path + "/" + filename;

        ImageAOS imgaos;
        imgaos.ReadBitmapFile(original_image_path);
        imgaos.ToGrayScale();
        imgaos.WriteBitmapFile(transformed_image);

        comparison_command = "cmp  " + transformed_image + " " + expected_image;
        output = system(comparison_command.c_str());
        EXPECT_EQ(output, 0);
    }
}

/* ----------------------------------------------------------------------- */ 

/* ----------------------------gaussian blur------------------------------------ */

 TEST(checkGaussianBlur,size) {
     /* Check if the size of the bitmaps (height & width) is the same
     before and after applying the gaussian convolution */
     ImageAOS imgaos;
     imgaos.ReadBitmapFile("../images/balloon.bmp");
     BmpPixels bmpPixelsDataOriginal = imgaos.GetBitmapPixelsData();
     imgaos.ApplyGaussianBlur();
     BmpPixels bmpPixelsDataModified = imgaos.GetBitmapPixelsData();

     EXPECT_EQ(bmpPixelsDataOriginal.size(), bmpPixelsDataModified.size());
     EXPECT_EQ(bmpPixelsDataOriginal[0].size(), bmpPixelsDataModified[0].size());
 }

 /* --------------------------------------------------------------------------- */