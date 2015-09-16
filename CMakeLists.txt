cmake_minimum_required(VERSION 2.6)
project(ChaosCore)

set(SRCS

    src/cxx/__dev/Main.cpp


    src/cxx/base/string/UString.cpp
)

set(BASEPATH "${CMAKE_SOURCE_DIR}")

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/build/linux_x86)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -std=c++0x")

include_directories("${BASEPATH}" ${INCLUDE_DIRECTORIES} src/cxx/)

link_directories(${LINK_DIRECTORIES})

add_executable(ChaosCore ${SRCS})

target_link_libraries( ChaosCore )
