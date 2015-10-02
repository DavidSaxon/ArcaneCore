cmake_minimum_required(VERSION 2.6)
project(ChaosCore)

set( CORE_SRC

    src/cxx/chaoscore/base/string/UTF8String.cpp
    src/cxx/chaoscore/test/ChaosTest.cpp
)

set( TEST_SRC

    tests/cxx/test_suites/base/PreProc_TestSuite.cpp
    tests/cxx/test_suites/base/str/UTF8String_TestSuite.cpp
)

set( DEV_SRC

    src/cxx/__dev/Main.cpp
)

set(BASEPATH "${CMAKE_SOURCE_DIR}")

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/build/linux_x86)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -std=c++0x -Wall -Wno-varargs")

include_directories("${BASEPATH}" ${INCLUDE_DIRECTORIES} src/cxx/ tests/cxx/ )

link_directories(${LINK_DIRECTORIES})

#add_executable( dev_binary ${DEV_SRC} ${CORE_SRC})
#target_link_libraries( dev_binary )

add_executable( tests ${TEST_SRC} ${CORE_SRC})
target_link_libraries( tests )
