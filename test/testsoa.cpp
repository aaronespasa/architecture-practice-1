#include "googletest/googletest/include/gtest/gtest.h"
#include <iostream>
#include "../common/common.h"
#include "../soa/soa.h"

/* #include "../aos/grayscale.cpp" */

  TEST(checkCopy,size) {
     /*Test if the size of the bmp is equal before and after
     applying Copy*/
     ImageAOS imgsoa;
     imgsoa.ReadBitmapFile("../images/balloon.bmp");
     BmpPixels bmpPixelsData = imgsoa.GetBitmapPixelsData();
     long unsigned int size_before = bmpPixelsData.size();
     BmpPixels bmpPixelsDataCopy 
     imgsoa.CopyBitmapFile(bmpPixelsData,bmpPixelsDataCopy );
     long unsigned int size_after = bmpPixelsDataCopy.size();

     EXPECT_EQ(size_before, size_after);
     for (long unsigned int i = 0; i < bmpPixelsData.blue.size(); i++) {
        for (long unsigned int j = 0; j < bmpPixelsData.blue[0].size(); j++) {
                EXPECT_EQ(bmpPixelsData.blue[i][j], bmpPixelsDataCopy.blue[i][j]);
                EXPECT_EQ(bmpPixelsData.green[i][j], bmpPixelsDataCopy.green[i][j]);
                EXPECT_EQ(bmpPixelsData.red[i][j], bmpPixelsDataCopy.red[i][j]);
            }
        }

 }
    
 TEST(checkGaussianBlur,size) {
     /*Test if the size of the bmp is equal before and after
     applying Gaussian Blur*/
     ImageAOS imgsoa;
     imgsoa.ReadBitmapFile("../images/balloon.bmp");
     BmpPixels bmpPixelsData = imgsoa.GetBitmapPixelsData();
     long unsigned int size_before = bmpPixelsData.blue.size();
     imgsoa.ApplyGaussianBlur();
     long unsigned int size_after = bmpPixelsData.blue.size();

/* Esta eso bien? */

     EXPECT_EQ(size_before, size_after);
 }




/* ----------------------------gray scale------------------------------------ */

TEST(check_gray_scale, balloon) {
   /* We are testing if the file porduced is the expected one by comparing 
      the bitmap of the image provided and the bitmap of the image produced  */
    ImageAOS imgsoa;
    /* Aqui debe ir la lectura de la imagen de prueba  */
    imgsoa.ReadBitmapFile("../images/images_test/gray_scale/balloon.bmp");
    BmpPixels bmpPixelsData_test = imgsoa.GetBitmapPixelsData();

    /* ----------------------------------------------- */

    imgsoa.ReadBitmapFile("../images/balloon.bmp");
    BmpPixels bmpPixelsData = imgsoa.GetBitmapPixelsData();
    long unsigned int size_before = bmpPixelsData.size();
    imgsoa.ToGrayScale();
    long unsigned int size_after = bmpPixelsData.size();
    /* EXPECT_EQ(size_before, size_after); */
        for (long unsigned int i = 0; i < bmpPixelsData.blue.size(); i++) {
            for (long unsigned int j = 0; j < bmpPixelsData.blue[0].size(); j++) {
                EXPECT_EQ(bmpPixelsData.blue[i][j], bmpPixelsDataCopy.blue[i][j]);
                EXPECT_EQ(bmpPixelsData.green[i][j], bmpPixelsDataCopy.green[i][j]);
                EXPECT_EQ(bmpPixelsData.red[i][j], bmpPixelsDataCopy.red[i][j]);
            }
        }
}

 TEST(check_gray_scale, amphora) {
    /* We are testing if the file porduced is the expected one by comparing 
       the bitmap of the image provided and the bitmap of the image produced  */
     ImageAOS imgsoa;
     /* Aqui debe ir la lectura de la imagen de prueba  */
     imgsoa.ReadBitmapFile("../images/images_test/gray_scale/amphora.bmp");
     BmpPixels bmpPixelsData_test = imgsoa.GetBitmapPixelsData();

     /* ----------------------------------------------- */

     imgsoa.ReadBitmapFile("../images/amphora.bmp");
     BmpPixels bmpPixelsData = imgsoa.GetBitmapPixelsData();
     long unsigned int size_before = bmpPixelsData.size();
     imgsoa.ToGrayScale();
     long unsigned int size_after = bmpPixelsData.size();

     for (long unsigned int i = 0; i < bmpPixelsData.blue.size(); i++) {
            for (long unsigned int j = 0; j < bmpPixelsData.blue[0].size(); j++) {
                EXPECT_EQ(bmpPixelsData.blue[i][j], bmpPixelsDataCopy.blue[i][j]);
                EXPECT_EQ(bmpPixelsData.green[i][j], bmpPixelsDataCopy.green[i][j]);
                EXPECT_EQ(bmpPixelsData.red[i][j], bmpPixelsDataCopy.red[i][j]);
            }
        }
 }

 TEST(check_gray_scale, car) {
    /* We are testing if the file porduced is the expected one by comparing 
       the bitmap of the image provided and the bitmap of the image produced  */
     ImageAOS imgsoa;
     /* Aqui debe ir la lectura de la imagen de prueba  */
     imgsoa.ReadBitmapFile("../images/images_test/gray_scale/car.bmp");
     BmpPixels bmpPixelsData_test = imgsoa.GetBitmapPixelsData();

     /* ----------------------------------------------- */

     imgsoa.ReadBitmapFile("../images/car.bmp");
     BmpPixels bmpPixelsData = imgsoa.GetBitmapPixelsData();
     long unsigned int size_before = bmpPixelsData.size();
     imgsoa.ToGrayScale();
     long unsigned int size_after = bmpPixelsData.size();

     for (long unsigned int i = 0; i < bmpPixelsData.blue.size(); i++) {
            for (long unsigned int j = 0; j < bmpPixelsData.blue[0].size(); j++) {
                EXPECT_EQ(bmpPixelsData.blue[i][j], bmpPixelsDataCopy.blue[i][j]);
                EXPECT_EQ(bmpPixelsData.green[i][j], bmpPixelsDataCopy.green[i][j]);
                EXPECT_EQ(bmpPixelsData.red[i][j], bmpPixelsDataCopy.red[i][j]);
            }
        }
 }

 TEST(check_gray_scale, elephant) {
    /* We are testing if the file porduced is the expected one by comparing 
       the bitmap of the image provided and the bitmap of the image produced  */
     ImageAOS imgsoa;
     /* Aqui debe ir la lectura de la imagen de prueba  */
     imgsoa.ReadBitmapFile("../images/images_test/gray_scale/elephant.bmp");
     BmpPixels bmpPixelsData_test = imgsoa.GetBitmapPixelsData();

     /* ----------------------------------------------- */

     imgsoa.ReadBitmapFile("../images/elephant.bmp");
     BmpPixels bmpPixelsData = imgsoa.GetBitmapPixelsData();
     long unsigned int size_before = bmpPixelsData.size();
     imgsoa.ToGrayScale();
     long unsigned int size_after = bmpPixelsData.size();

     for (long unsigned int i = 0; i < bmpPixelsData.blue.size(); i++) {
            for (long unsigned int j = 0; j < bmpPixelsData.blue[0].size(); j++) {
                EXPECT_EQ(bmpPixelsData.blue[i][j], bmpPixelsDataCopy.blue[i][j]);
                EXPECT_EQ(bmpPixelsData.green[i][j], bmpPixelsDataCopy.green[i][j]);
                EXPECT_EQ(bmpPixelsData.red[i][j], bmpPixelsDataCopy.red[i][j]);
            }
        }
 }

 TEST(check_gray_scale, landscape) {
    /* We are testing if the file porduced is the expected one by comparing 
       the bitmap of the image provided and the bitmap of the image produced  */
     ImageAOS imgsoa;
     /* Aqui debe ir la lectura de la imagen de prueba  */
     imgsoa.ReadBitmapFile("../images/images_test/gray_scale/landscape.bmp");
     BmpPixels bmpPixelsData_test = imgsoa.GetBitmapPixelsData();

     /* ----------------------------------------------- */

     imgsoa.ReadBitmapFile("../images/landscape.bmp");
     BmpPixels bmpPixelsData = imgsoa.GetBitmapPixelsData();
     long unsigned int size_before = bmpPixelsData.size();
     imgsoa.ToGrayScale();
     long unsigned int size_after = bmpPixelsData.size();

     for (long unsigned int i = 0; i < bmpPixelsData.blue.size(); i++) {
            for (long unsigned int j = 0; j < bmpPixelsData.blue[0].size(); j++) {
                EXPECT_EQ(bmpPixelsData.blue[i][j], bmpPixelsDataCopy.blue[i][j]);
                EXPECT_EQ(bmpPixelsData.green[i][j], bmpPixelsDataCopy.green[i][j]);
                EXPECT_EQ(bmpPixelsData.red[i][j], bmpPixelsDataCopy.red[i][j]);
            }
        }
 }

 TEST(check_gray_scale, plane) {
    /* We are testing if the file porduced is the expected one by comparing 
       the bitmap of the image provided and the bitmap of the image produced  */
     ImageAOS imgsoa;
     /* Aqui debe ir la lectura de la imagen de prueba  */
     imgsoa.ReadBitmapFile("../images/images_test/gray_scale/plane.bmp");
     BmpPixels bmpPixelsData_test = imgsoa.GetBitmapPixelsData();

     /* ----------------------------------------------- */

     imgsoa.ReadBitmapFile("../images/planes.bmp");
     BmpPixels bmpPixelsData = imgsoa.GetBitmapPixelsData();
     long unsigned int size_before = bmpPixelsData.size();
     imgsoa.ToGrayScale();
     long unsigned int size_after = bmpPixelsData.size();

     for (long unsigned int i = 0; i < bmpPixelsData.blue.size(); i++) {
            for (long unsigned int j = 0; j < bmpPixelsData.blue[0].size(); j++) {
                EXPECT_EQ(bmpPixelsData.blue[i][j], bmpPixelsDataCopy.blue[i][j]);
                EXPECT_EQ(bmpPixelsData.green[i][j], bmpPixelsDataCopy.green[i][j]);
                EXPECT_EQ(bmpPixelsData.red[i][j], bmpPixelsDataCopy.red[i][j]);
            }
        }
 }

 TEST(check_gray_scale, pyramid) {
    /* We are testing if the file porduced is the expected one by comparing 
       the bitmap of the image provided and the bitmap of the image produced  */
     ImageAOS imgsoa;
     /* Aqui debe ir la lectura de la imagen de prueba  */
     imgsoa.ReadBitmapFile("../images/images_test/gray_scale/pyramid.bmp");
     BmpPixels bmpPixelsData_test = imgsoa.GetBitmapPixelsData();

     /* ----------------------------------------------- */
     imgsoa.ReadBitmapFile("../images/pyramid.bmp");
     BmpPixels bmpPixelsData = imgsoa.GetBitmapPixelsData();
     long unsigned int size_before = bmpPixelsData.size();
     imgsoa.ToGrayScale();
     long unsigned int size_after = bmpPixelsData.size();

     for (long unsigned int i = 0; i < bmpPixelsData.blue.size(); i++) {
            for (long unsigned int j = 0; j < bmpPixelsData.blue[0].size(); j++) {
                EXPECT_EQ(bmpPixelsData.blue[i][j], bmpPixelsDataCopy.blue[i][j]);
                EXPECT_EQ(bmpPixelsData.green[i][j], bmpPixelsDataCopy.green[i][j]);
                EXPECT_EQ(bmpPixelsData.red[i][j], bmpPixelsDataCopy.red[i][j]);
            }
        }
 }

 TEST(check_gray_scale, snake) {
    /* We are testing if the file porduced is the expected one by comparing 
       the bitmap of the image provided and the bitmap of the image produced  */
     ImageAOS imgsoa;
     /* Aqui debe ir la lectura de la imagen de prueba  */
     imgsoa.ReadBitmapFile("../images/images_test/gray_scale/snake.bmp");
     BmpPixels bmpPixelsData_test = imgsoa.GetBitmapPixelsData();

     /* ----------------------------------------------- */

     imgsoa.ReadBitmapFile("../images/snake.bmp");
     BmpPixels bmpPixelsData = imgsoa.GetBitmapPixelsData();
     long unsigned int size_before = bmpPixelsData.size();
     imgsoa.ToGrayScale();
     long unsigned int size_after = bmpPixelsData.size();

     for (long unsigned int i = 0; i < bmpPixelsData.blue.size(); i++) {
            for (long unsigned int j = 0; j < bmpPixelsData.blue[0].size(); j++) {
                EXPECT_EQ(bmpPixelsData.blue[i][j], bmpPixelsDataCopy.blue[i][j]);
                EXPECT_EQ(bmpPixelsData.green[i][j], bmpPixelsDataCopy.green[i][j]);
                EXPECT_EQ(bmpPixelsData.red[i][j], bmpPixelsDataCopy.red[i][j]);
            }
        }
 }

/* ----------------------------gray scale------------------------------------ */ 