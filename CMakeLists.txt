cmake_minimum_required(VERSION 3.23)
project(image LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS_OFF)
add_compile_options(-Wall -Wextra -Werror -pedantic -pedantic-errors)

set(CMAKE_CXX_FLAGS_RELEASE "-march=native")

add_library(common common/common.cpp common/progargs.cpp)
add_library(aos aos/imageaos.cpp aos/histogram.cpp aos/grayscale.cpp aos/gaussianblur.cpp)
add_library(soa soa/imagesoa.cpp soa/histogram.cpp soa/grayscale.cpp soa/gaussianblur.cpp)

include(FetchContent)
FetchContent_Declare(
    googletest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG release-1.12.1
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()

include(GoogleTest)

add_subdirectory(test)

# Create the AOS executable (imgaos) linking the libraries common & aos
add_executable(imgaos aos/imgaos.cpp)
target_link_libraries (imgaos aos common)

# Create the SOA executable (imgsoa) linking the libraries common & soa
add_executable(imgsoa soa/imgsoa.cpp)
target_link_libraries (imgsoa soa common)
