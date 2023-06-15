set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if (NOT TARGET pseudo_random)
    add_subdirectory(../pseudo_random pseudo_random)
endif() 

add_library(model STATIC model.cpp model.hpp)

if(Boost_FOUND)
    target_include_directories(model PUBLIC ${Boost_INCLUDE_DIRS} ../pseudo_random)
	target_link_directories(model PUBLIC ${Boost_INCLUDE_DIRS} ../pseudo_random)
	target_link_libraries(model ${Boost_LIBRARIES} pseudo_random)
else()
	message(FATAL_ERROR "Boost is not found, please install it and recompile the project.")
endif()