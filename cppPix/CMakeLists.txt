cmake_minimum_required(VERSION 2.6)
project(cppPix)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

add_executable(cppPix
	Image.cpp
	Color.cpp
	ImageFile.cpp
	main.cpp
)

find_package(Boost 1.40 COMPONENTS filesystem REQUIRED)
include_directories(${Boost_INCLUDE_DIRS})

target_link_libraries(cppPix
    ${Boost_LIBRARIES}
)

#install(TARGETS cppPix RUNTIME DESTINATION bin)
