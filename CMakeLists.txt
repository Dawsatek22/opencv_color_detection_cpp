cmake_minimum_required(VERSION 3.28.1) # is the current version were it is made.
project(color_detect)

find_package(OpenCV REQUIRED) # looks for the opencv package
include_directories( ${OpenCV_INCLUDE_DIRECTORIES})
add_executable(blue_img src/blue_img.cpp)
add_executable(red_img src/red_img.cpp)
add_executable(red_cam src/red_cam.cpp)
add_executable(blue_cam src/blue_cam.cpp)
target_link_libraries(red_cam ${OpenCV_LIBS} )
target_link_libraries(blue_cam ${OpenCV_LIBS} )
target_link_libraries(red_img ${OpenCV_LIBS} )
target_link_libraries(blue_img ${OpenCV_LIBS} )

