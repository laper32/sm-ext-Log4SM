cmake_minimum_required(VERSION 3.20)

project(sm-ext-Log4SM)

include(${PROJECT_SOURCE_DIR}/configure.cmake)
include(${PROJECT_SOURCE_DIR}/cmake/All.cmake)

find_package(fmt REQUIRED)
find_package(spdlog REQUIRED)
find_package(Boost REQUIRED)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)

add_subdirectory(src)