set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if (NOT TARGET model)
    add_subdirectory(../model model)
endif() 

add_library(search STATIC search.cpp search.hpp)

target_include_directories(search PUBLIC ../model/)

target_link_directories(search PUBLIC ../model/)

target_link_libraries(search model)