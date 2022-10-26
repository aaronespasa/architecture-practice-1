cmake_minimum_required(VERSION 3.23)
project(image LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS_OFF)
add_compile_options(-Wall -Wextra -Werror -pedantic -pedantic-errors)

set(CMAKE_CXX_FLAGS_RELEASE "-march=native")

add_subdirectory(test/googletest)

add_library(common common/common.cpp common/progargs.cpp)
add_library(aos aos/imageaos.cpp aos/histogram.cpp aos/grayscale.cpp aos/gaussianblur.cpp)
add_library(soa soa/imagesoa.cpp soa/histogram.cpp soa/grayscale.cpp soa/gaussianblur.cpp)

# Create the AOS executable (imgaos) linking the libraries common & aos
add_executable(imgaos aos/imgaos.cpp)
target_link_libraries (imgaos aos common)

# Create the Test executable (test) linking the libraries common & aos
add_executable(testaos test/testaos.cpp)
target_link_libraries (testaos aos common gtest_main)

# Create the SOA executable (imgsoa) linking the libraries common & soa
add_executable(imgsoa soa/imgsoa.cpp)
target_link_libraries (imgsoa soa common)

# Create the Test executable (test) linking the libraries common & soa
add_executable(testsoa test/testsoa.cpp)
target_link_libraries(testsoa soa common gtest_main)