set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_subdirectory(sorting)
add_subdirectory(search)
add_subdirectory(generator)

add_library(lab_1_sorting_wrapper INTERFACE)

target_include_directories(lab_1_sorting_wrapper INTERFACE sorting/ search/ generator/ )

target_link_directories(lab_1_sorting_wrapper INTERFACE sorting/ search/ generator/)

target_link_libraries(lab_1_sorting_wrapper INTERFACE sorting search generator)