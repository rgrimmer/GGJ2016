cmake_minimum_required(VERSION 3.2.1)

project(GGJ2016)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/Modules/")

set_property(GLOBAL PROPERTY USE_FOLDERS ON)

# Enable C++11
set(CMAKE_CXX_STANDARD 11)

# Set Warning levels
if (MSVC)
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -D_CRT_SECURE_NO_WARNINGS /wd4800")
else (MSVC)
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra")
endif (MSVC)

# Enable Address Sanitizer
if (UNIX)
	option(ENABLE_ASAN "Enable address sanitizer" ON)
	
	if (ENABLE_ASAN)
		set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=address")
	endif (ENABLE_ASAN)
endif(UNIX)

# Find the Shine Engine SDK
set(SH_INCLUDE_DIR "../Shine/include" CACHE PATH "Shine include directory")
set(SH_LIB_DIR "../Shine/lib" CACHE PATH "Shine libraries directory")
find_package(ShSDK)

# recurse into subdirectory
add_subdirectory(src)
