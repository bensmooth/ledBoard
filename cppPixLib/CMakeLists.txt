cmake_minimum_required(VERSION 3.4)

file(GLOB SRC_FILES *.cpp)
add_library(cppPixLib ${SRC_FILES})

if ( CMAKE_COMPILER_IS_GNUCC )
    set_property( TARGET cppPixLib APPEND_STRING PROPERTY COMPILE_FLAGS "-Wall -pedantic -Werror" )
endif ( CMAKE_COMPILER_IS_GNUCC )

find_package(Boost 1.40 COMPONENTS filesystem REQUIRED)
include_directories(${Boost_INCLUDE_DIRS})

target_link_libraries(cppPixLib
    ${Boost_LIBRARIES}
)

#install(TARGETS cppPix RUNTIME DESTINATION bin)
