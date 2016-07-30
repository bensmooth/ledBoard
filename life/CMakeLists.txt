cmake_minimum_required(VERSION 3.4)

file(GLOB SRC_FILES *.cpp)
add_executable(life ${SRC_FILES})
target_link_libraries(life cppPixLib)
