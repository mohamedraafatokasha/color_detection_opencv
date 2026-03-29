cmake_minimum_required(VERSION 3.11)

project(opencv_project)

find_package(OpenCV REQUIRED)
find_package(spdlog REQUIRED)

add_executable(app main.cpp)

target_link_libraries(app
    PRIVATE
        ${OpenCV_LIBS}
        spdlog::spdlog
)