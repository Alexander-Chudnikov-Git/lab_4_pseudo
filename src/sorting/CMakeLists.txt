set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if (NOT TARGET model)
    add_subdirectory(../model model)
endif() 

add_library(sorting STATIC sorting.cpp sorting.hpp)

target_include_directories(sorting PUBLIC ../model/)

target_link_directories(sorting PUBLIC ../model/)

target_link_libraries(sorting model)