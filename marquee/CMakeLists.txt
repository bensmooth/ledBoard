cmake_minimum_required(VERSION 3.4)

file(GLOB SRC_FILES *.cpp)
add_executable(marquee ${SRC_FILES})
target_link_libraries(marquee cppPixLib)
