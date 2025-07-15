cmake_minimum_required(VERSION 3.28.1) # is the current version were it is made.
project(color_detect)

find_package(OpenCV REQUIRED) # looks for the opencv package
include_directories( ${OpenCV_INCLUDE_DIRECTORIES})
add_executable(redblue src/red_and_blue_webcam.cpp)
target_link_libraries(redblue ${OpenCV_LIBS} )

