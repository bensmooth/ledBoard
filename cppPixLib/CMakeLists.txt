cmake_minimum_required(VERSION 3.4)

file(GLOB SRC_FILES *.cpp)
add_library(cppPixLib ${SRC_FILES})

if ( CMAKE_COMPILER_IS_GNUCC )
    set_property( TARGET cppPixLib APPEND_STRING PROPERTY COMPILE_FLAGS "-Wall -pedantic -Werror" )
endif ( CMAKE_COMPILER_IS_GNUCC )

find_package(Boost 1.40 COMPONENTS filesystem REQUIRED)

SET(SDL2PP_WITH_IMAGE ON) # if you need SDL_image support
SET(SDL2PP_WITH_MIXER ON) # if you need SDL_mixer support
SET(SDL2PP_WITH_TTF ON) # if you need SDL_ttf support
add_subdirectory(libSDL2pp)
include_directories(
	${SDL2PP_INCLUDE_DIRS}
	${Boost_INCLUDE_DIRS}
)

target_link_libraries(cppPixLib
    ${Boost_LIBRARIES}
    ${SDL2PP_LIBRARIES}
)
