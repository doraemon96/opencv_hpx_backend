# Require a recent version of cmake
cmake_minimum_required(VERSION 3.5.1 FATAL_ERROR)

# This project is C++ based.
project(hpx_mandelbrot CXX)

# Instruct cmake to find the HPX settings
find_package(HPX REQUIRED)
find_package(OpenCV REQUIRED)

# Build your application using HPX
add_hpx_executable(hpx_mandelbrot
        ESSENTIAL
        SOURCES hpx_mandelbrot.cpp system_characteristics.hpp
        DEPENDENCIES ${OpenCV_LIBS}
        COMPONENT_DEPENDENCIES iostreams)

target_include_directories(hpx_mandelbrot_exe PRIVATE ${OpenCV_INCLUDE_DIRS})

if(MSVC)
    add_definitions(-D_USE_MATH_DEFINES)
endif()
