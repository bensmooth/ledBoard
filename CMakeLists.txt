cmake_minimum_required(VERSION 3.4)
project (CppPix)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

include_directories(${CMAKE_SOURCE_DIR}/cppPixLib)

add_subdirectory(cppPixLib)
add_subdirectory(loaderTest)
add_subdirectory(visualizations)
add_subdirectory(life)
add_subdirectory(hockeyScores)
add_subdirectory(marquee)

#install(TARGETS cppPix RUNTIME DESTINATION bin)
