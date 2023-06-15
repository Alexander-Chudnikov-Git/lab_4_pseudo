set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if (NOT TARGET model)
    add_subdirectory(../model model)
endif() 

add_library(generator STATIC generator.cpp generator.hpp)

target_include_directories(generator PUBLIC ../model/)

target_link_directories(generator PUBLIC ../model/)

target_link_libraries(generator model)