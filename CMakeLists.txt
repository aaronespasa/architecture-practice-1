cmake_minimum_required(VERSION 3.23)
project(image LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS_OFF)
add_compile_options(-Wall -Wextra -Werror -pedantic -pedantic-errors)

set(CMAKE_CXX_FLAGS_RELEASE "-march=native")

add_library(common common/progargs.cpp)
add_library(aos aos/imageaos.cpp aos/imgaos.cpp)
add_library(soa soa/imagesoa.cpp soa/imgsoa.cpp)

# Create the AOS executable (imgaos) linking the libraries common & aos
add_executable(imgaos aos/imgaos.cpp)
target_link_libraries (imgaos common aos)

# Create the SOA executable (imgsoa) linking the libraries common & soa
add_executable(imgsoa soa/imgsoa.cpp)
target_link_libraries (imgsoa common soa)