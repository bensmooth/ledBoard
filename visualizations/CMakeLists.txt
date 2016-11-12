cmake_minimum_required(VERSION 3.4)

add_executable(psycho psycho.cpp)
target_link_libraries(psycho cppPixLib)

add_executable(perlin perlin.cpp)
target_link_libraries(perlin cppPixLib)
