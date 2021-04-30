cmake_minimum_required(VERSION 3.19)
project(Reynolds_Group_Integrator)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS "-Wall -Wextra")
set(CMAKE_CXX_FLAGS_RELEASE "-O3")
set(CMAKE_CXX_FLAGS_DEBUG "-g")
set(OUTPUT_NAME "rtIntegrator")

include_directories(.)

add_executable(Reynolds_Group_Integrator
        main.cpp
        valarray_updates.cpp
        )
