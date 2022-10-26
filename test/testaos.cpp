#include "googletest/googletest/include/gtest/gtest.h"
#include <iostream>
#include "../common/common.h"
#include "../aos/aos.h"

/* #include "../aos/grayscale.cpp" */

  TEST(checkCopy,size) {
     /*Test if the size of the bmp is equal before and after
     applying Copy*/
     ImageAOS imgaos;
     imgaos.ReadBitmapFile("../images/balloon.bmp");
     BmpPixels bmpPixelsData = imgaos.GetBitmapPixelsData();
     long unsigned int size_before = bmpPixelsData.size();
     BmpPixels bmpPixelsDataCopy 
     imgaos.CopyBitmapFile(bmpPixelsData,bmpPixelsDataCopy );
     long unsigned int size_after = bmpPixelsDataCopy.size();

     EXPECT_EQ(size_before, size_after);
     for (long unsigned int i = 0; i < bmpPixelsData.size(); i++) {
            for (long unsigned int j = 0; j < bmpPixelsData[0].size(); j++) {
                EXPECT_EQ(bmpPixelsData[i][j].blue, bmpPixelsDataCopy[i][j].blue);
                EXPECT_EQ(bmpPixelsData[i][j].green, bmpPixelsDataCopy[i][j].green);
                EXPECT_EQ(bmpPixelsData[i][j].red, bmpPixelsDataCopy[i][j].red);
            }
        }

 }
    
 TEST(checkGaussianBlur,size) {
     /*Test if the size of the bmp is equal before and after
     applying Gaussian Blur*/
     ImageAOS imgaos;
     imgaos.ReadBitmapFile("../images/balloon.bmp");
     BmpPixels bmpPixelsData = imgaos.GetBitmapPixelsData();
     long unsigned int size_before = bmpPixelsData.size();
     imgaos.ApplyGaussianBlur();
     long unsigned int size_after = bmpPixelsData.size();

     EXPECT_EQ(size_before, size_after);
 }




/* ----------------------------gray scale------------------------------------ */

TEST(check_gray_scale, balloon) {
   /* We are testing if the file porduced is the expected one by comparing 
      the bitmap of the image provided and the bitmap of the image produced  */
    ImageAOS imgaos;
    /* Aqui debe ir la lectura de la imagen de prueba  */
    imgaos.ReadBitmapFile("../images/images_test/gray_scale/balloon.bmp");
    BmpPixels bmpPixelsData_test = imgaos.GetBitmapPixelsData();

    /* ----------------------------------------------- */

    imgaos.ReadBitmapFile("../images/balloon.bmp");
    BmpPixels bmpPixelsData = imgaos.GetBitmapPixelsData();
    long unsigned int size_before = bmpPixelsData.size();
    imgaos.ToGrayScale();
    long unsigned int size_after = bmpPixelsData.size();
    /* EXPECT_EQ(size_before, size_after); */
        for (long unsigned int i = 0; i < bmpPixelsData.size(); i++) {
            for (long unsigned int j = 0; j < bmpPixelsData[0].size(); j++) {
                EXPECT_EQ(bmpPixelsData[i][j].blue, bmpPixelsData_test[i][j].blue);
                EXPECT_EQ(bmpPixelsData[i][j].green, bmpPixelsData_test[i][j].green);
                EXPECT_EQ(bmpPixelsData[i][j].red, bmpPixelsData_test[i][j].red);
            }
        }
}

 TEST(check_gray_scale, amphora) {
    /* We are testing if the file porduced is the expected one by comparing 
       the bitmap of the image provided and the bitmap of the image produced  */
     ImageAOS imgaos;
     /* Aqui debe ir la lectura de la imagen de prueba  */
     imgaos.ReadBitmapFile("../images/images_test/gray_scale/amphora.bmp");
     BmpPixels bmpPixelsData_test = imgaos.GetBitmapPixelsData();

     /* ----------------------------------------------- */

     imgaos.ReadBitmapFile("../images/amphora.bmp");
     BmpPixels bmpPixelsData = imgaos.GetBitmapPixelsData();
     long unsigned int size_before = bmpPixelsData.size();
     imgaos.ToGrayScale();
     long unsigned int size_after = bmpPixelsData.size();

     for (long unsigned int i = 0; i < bmpPixelsData.size(); i++) {
            for (long unsigned int j = 0; j < bmpPixelsData[0].size(); j++) {
                EXPECT_EQ(bmpPixelsData[i][j].blue, bmpPixelsData_test[i][j].blue);
                EXPECT_EQ(bmpPixelsData[i][j].green, bmpPixelsData_test[i][j].green);
                EXPECT_EQ(bmpPixelsData[i][j].red, bmpPixelsData_test[i][j].red);
            }
        }
 }

 TEST(check_gray_scale, car) {
    /* We are testing if the file porduced is the expected one by comparing 
       the bitmap of the image provided and the bitmap of the image produced  */
     ImageAOS imgaos;
     /* Aqui debe ir la lectura de la imagen de prueba  */
     imgaos.ReadBitmapFile("../images/images_test/gray_scale/car.bmp");
     BmpPixels bmpPixelsData_test = imgaos.GetBitmapPixelsData();

     /* ----------------------------------------------- */

     imgaos.ReadBitmapFile("../images/car.bmp");
     BmpPixels bmpPixelsData = imgaos.GetBitmapPixelsData();
     long unsigned int size_before = bmpPixelsData.size();
     imgaos.ToGrayScale();
     long unsigned int size_after = bmpPixelsData.size();

     for (long unsigned int i = 0; i < bmpPixelsData.size(); i++) {
            for (long unsigned int j = 0; j < bmpPixelsData[0].size(); j++) {
                EXPECT_EQ(bmpPixelsData[i][j].blue, bmpPixelsData_test[i][j].blue);
                EXPECT_EQ(bmpPixelsData[i][j].green, bmpPixelsData_test[i][j].green);
                EXPECT_EQ(bmpPixelsData[i][j].red, bmpPixelsData_test[i][j].red);
            }
        }
 }

 TEST(check_gray_scale, elephant) {
    /* We are testing if the file porduced is the expected one by comparing 
       the bitmap of the image provided and the bitmap of the image produced  */
     ImageAOS imgaos;
     /* Aqui debe ir la lectura de la imagen de prueba  */
     imgaos.ReadBitmapFile("../images/images_test/gray_scale/elephant.bmp");
     BmpPixels bmpPixelsData_test = imgaos.GetBitmapPixelsData();

     /* ----------------------------------------------- */

     imgaos.ReadBitmapFile("../images/elephant.bmp");
     BmpPixels bmpPixelsData = imgaos.GetBitmapPixelsData();
     long unsigned int size_before = bmpPixelsData.size();
     imgaos.ToGrayScale();
     long unsigned int size_after = bmpPixelsData.size();

     for (long unsigned int i = 0; i < bmpPixelsData.size(); i++) {
            for (long unsigned int j = 0; j < bmpPixelsData[0].size(); j++) {
                EXPECT_EQ(bmpPixelsData[i][j].blue, bmpPixelsData_test[i][j].blue);
                EXPECT_EQ(bmpPixelsData[i][j].green, bmpPixelsData_test[i][j].green);
                EXPECT_EQ(bmpPixelsData[i][j].red, bmpPixelsData_test[i][j].red);
            }
        }
 }

 TEST(check_gray_scale, landscape) {
    /* We are testing if the file porduced is the expected one by comparing 
       the bitmap of the image provided and the bitmap of the image produced  */
     ImageAOS imgaos;
     /* Aqui debe ir la lectura de la imagen de prueba  */
     imgaos.ReadBitmapFile("../images/images_test/gray_scale/landscape.bmp");
     BmpPixels bmpPixelsData_test = imgaos.GetBitmapPixelsData();

     /* ----------------------------------------------- */

     imgaos.ReadBitmapFile("../images/landscape.bmp");
     BmpPixels bmpPixelsData = imgaos.GetBitmapPixelsData();
     long unsigned int size_before = bmpPixelsData.size();
     imgaos.ToGrayScale();
     long unsigned int size_after = bmpPixelsData.size();

     for (long unsigned int i = 0; i < bmpPixelsData.size(); i++) {
            for (long unsigned int j = 0; j < bmpPixelsData[0].size(); j++) {
                EXPECT_EQ(bmpPixelsData[i][j].blue, bmpPixelsData_test[i][j].blue);
                EXPECT_EQ(bmpPixelsData[i][j].green, bmpPixelsData_test[i][j].green);
                EXPECT_EQ(bmpPixelsData[i][j].red, bmpPixelsData_test[i][j].red);
            }
        }
 }

 TEST(check_gray_scale, plane) {
    /* We are testing if the file porduced is the expected one by comparing 
       the bitmap of the image provided and the bitmap of the image produced  */
     ImageAOS imgaos;
     /* Aqui debe ir la lectura de la imagen de prueba  */
     imgaos.ReadBitmapFile("../images/images_test/gray_scale/plane.bmp");
     BmpPixels bmpPixelsData_test = imgaos.GetBitmapPixelsData();

     /* ----------------------------------------------- */

     imgaos.ReadBitmapFile("../images/planes.bmp");
     BmpPixels bmpPixelsData = imgaos.GetBitmapPixelsData();
     long unsigned int size_before = bmpPixelsData.size();
     imgaos.ToGrayScale();
     long unsigned int size_after = bmpPixelsData.size();

     for (long unsigned int i = 0; i < bmpPixelsData.size(); i++) {
            for (long unsigned int j = 0; j < bmpPixelsData[0].size(); j++) {
                EXPECT_EQ(bmpPixelsData[i][j].blue, bmpPixelsData_test[i][j].blue);
                EXPECT_EQ(bmpPixelsData[i][j].green, bmpPixelsData_test[i][j].green);
                EXPECT_EQ(bmpPixelsData[i][j].red, bmpPixelsData_test[i][j].red);
            }
        }
 }

 TEST(check_gray_scale, pyramid) {
    /* We are testing if the file porduced is the expected one by comparing 
       the bitmap of the image provided and the bitmap of the image produced  */
     ImageAOS imgaos;
     /* Aqui debe ir la lectura de la imagen de prueba  */
     imgaos.ReadBitmapFile("../images/images_test/gray_scale/pyramid.bmp");
     BmpPixels bmpPixelsData_test = imgaos.GetBitmapPixelsData();

     /* ----------------------------------------------- */
     imgaos.ReadBitmapFile("../images/pyramid.bmp");
     BmpPixels bmpPixelsData = imgaos.GetBitmapPixelsData();
     long unsigned int size_before = bmpPixelsData.size();
     imgaos.ToGrayScale();
     long unsigned int size_after = bmpPixelsData.size();

     for (long unsigned int i = 0; i < bmpPixelsData.size(); i++) {
            for (long unsigned int j = 0; j < bmpPixelsData[0].size(); j++) {
                EXPECT_EQ(bmpPixelsData[i][j].blue, bmpPixelsData_test[i][j].blue);
                EXPECT_EQ(bmpPixelsData[i][j].green, bmpPixelsData_test[i][j].green);
                EXPECT_EQ(bmpPixelsData[i][j].red, bmpPixelsData_test[i][j].red);
            }
        }
 }

 TEST(check_gray_scale, snake) {
    /* We are testing if the file porduced is the expected one by comparing 
       the bitmap of the image provided and the bitmap of the image produced  */
     ImageAOS imgaos;
     /* Aqui debe ir la lectura de la imagen de prueba  */
     imgaos.ReadBitmapFile("../images/images_test/gray_scale/snake.bmp");
     BmpPixels bmpPixelsData_test = imgaos.GetBitmapPixelsData();

     /* ----------------------------------------------- */

     imgaos.ReadBitmapFile("../images/snake.bmp");
     BmpPixels bmpPixelsData = imgaos.GetBitmapPixelsData();
     long unsigned int size_before = bmpPixelsData.size();
     imgaos.ToGrayScale();
     long unsigned int size_after = bmpPixelsData.size();

     for (long unsigned int i = 0; i < bmpPixelsData.size(); i++) {
            for (long unsigned int j = 0; j < bmpPixelsData[0].size(); j++) {
                EXPECT_EQ(bmpPixelsData[i][j].blue, bmpPixelsData_test[i][j].blue);
                EXPECT_EQ(bmpPixelsData[i][j].green, bmpPixelsData_test[i][j].green);
                EXPECT_EQ(bmpPixelsData[i][j].red, bmpPixelsData_test[i][j].red);
            }
        }
 }

/* ----------------------------gray scale------------------------------------ */ 