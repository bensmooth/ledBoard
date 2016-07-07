cmake_minimum_required(VERSION 2.6)
project (CppPix)

include_directories(${CMAKE_SOURCE_DIR}/cppPixLib)

add_subdirectory(cppPixLib)
add_subdirectory(loaderTest)

#install(TARGETS cppPix RUNTIME DESTINATION bin)
