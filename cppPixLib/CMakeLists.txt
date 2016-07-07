cmake_minimum_required(VERSION 2.6)

add_library(cppPixLib
	Image.cpp
	Color.cpp
	ImageFile.cpp
)

find_package(Boost 1.40 COMPONENTS filesystem REQUIRED)
include_directories(${Boost_INCLUDE_DIRS})

target_link_libraries(cppPixLib
    ${Boost_LIBRARIES}
)

#install(TARGETS cppPix RUNTIME DESTINATION bin)
