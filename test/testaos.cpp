#include <gtest/gtest.h>
#include <iostream>
#include <string>
#include <stdlib.h>
#include <vector>
#include <filesystem>
#include "../common/common.h"
#include "../aos/aos.h"

//   TEST(checkCopy,size) {
//      /*Test if the size of the bmp is equal before and after
//      applying Copy*/
//      ImageAOS imgaos;
//      imgaos.ReadBitmapFile("../images/balloon.bmp");
//      BmpPixels bmpPixelsData = imgaos.GetBitmapPixelsData();
//     //  long unsigned int size_before = bmpPixelsData.size();
//      BmpPixels bmpPixelsDataCopy 
//      imgaos.CopyBitmapFile(bmpPixelsData,bmpPixelsDataCopy );
//     //  long unsigned int size_after = bmpPixelsDataCopy.size();

//     //  EXPECT_EQ(size_before, size_after);
//      for (long unsigned int i = 0; i < bmpPixelsData.size(); i++) {
//             for (long unsigned int j = 0; j < bmpPixelsData[0].size(); j++) {
//                 EXPECT_EQ(bmpPixelsData[i][j].blue, bmpPixelsDataCopy[i][j].blue);
//                 EXPECT_EQ(bmpPixelsData[i][j].green, bmpPixelsDataCopy[i][j].green);
//                 EXPECT_EQ(bmpPixelsData[i][j].red, bmpPixelsDataCopy[i][j].red);
//             }
//         }

//  }
    
//  TEST(checkGaussianBlur,size) {
//      /*Test if the size of the bmp is equal before and after
//      applying Gaussian Blur*/
//      ImageAOS imgaos;
//      imgaos.ReadBitmapFile("../images");
    
//      BmpPixels bmpPixelsDataOriginal = imgaos.GetBitmapPixelsData();
//      imgaos.ApplyGaussianBlur();
//      BmpPixels bmpPixelsDataModified = imgaos.GetBitmapPixelsData();

//      EXPECT_EQ(bmpPixelsDataOriginal.size(), bmpPixelsDataModified.size());
//      EXPECT_EQ(bmpPixelsDataOriginal[0].size(), bmpPixelsDataModified[0].size());
//  }




// /* ----------------------------gray scale------------------------------------ */

TEST(check_gray_scale, all) {
   /* We are testing if the file porduced is the expected one by comparing 
      the bitmap of the image provided and the bitmap of the image produced  */
    std::string original_images_path = "../images";
    std::vector<std::string> original_images = getFiles(original_images_path);

    std::string transformed_images_path = "../images/images_test/gray_scale";
    std::string expected_images_path = "../images/images_test/gray_scale";
    std::string comparison_command;

    int output{-1};
    for(std::string file : original_images) {
        std::string filename = file + ".bmp";

        ImageAOS imgaos;
        imgaos.ReadBitmapFile(original_images_path + "/" + filename);
        imgaos.ToGrayScale();
        imgaos.WriteBitmapFile(transformed_images_path + "/" + filename);

        std::string transformed_image = transformed_images_path + "/" + filename;
        std::string expected_image = expected_images_path + "/" + filename;
        comparison_command = "cmp  " + transformed_image + " " + expected_image;
        output = system(comparison_command.c_str());
        EXPECT_EQ(output, 0);
    }
}

/* ----------------------------------------------------------------------- */ 