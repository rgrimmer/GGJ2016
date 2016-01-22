cmake_minimum_required(VERSION 3.2.1)

project(GGJ2016)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/Modules/")

set_property(GLOBAL PROPERTY USE_FOLDERS ON)

set(SH_INCLUDE_DIR "../Shine/include" CACHE PATH "Shine include directory")
set(SH_LIB_DIR "../Shine/lib" CACHE PATH "Shine libraries directory")

find_package(ShSDK)

add_subdirectory(src)
