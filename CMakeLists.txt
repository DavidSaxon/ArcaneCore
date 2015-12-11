cmake_minimum_required(VERSION 2.6)
project(ChaosCore)

set( HEADERS
)

set( BASE_SRC
    src/cxx/chaoscore/base/clock/ClockOperations.cpp
    src/cxx/chaoscore/base/data/BinaryOperations.cpp
    src/cxx/chaoscore/base/data/BitwiseFloat.cpp
    src/cxx/chaoscore/base/data/ByteOperations.cpp
    src/cxx/chaoscore/base/math/MathConstants.cpp
    src/cxx/chaoscore/base/math/MathOperations.cpp
    src/cxx/chaoscore/base/os/OSOperations.cpp
    src/cxx/chaoscore/base/uni/UnicodeConstants.cpp
    src/cxx/chaoscore/base/uni/UnicodeOperations.cpp
    src/cxx/chaoscore/base/uni/UTF8String.cpp
)

set( IO_SRC
    src/cxx/chaoscore/io/format/ANSI.cpp
    src/cxx/chaoscore/io/format/FormatOperations.cpp
    src/cxx/chaoscore/io/sys/FileHandle.cpp
    src/cxx/chaoscore/io/sys/FileSystemOperations.cpp
    src/cxx/chaoscore/io/sys/FileWriter.cpp
    src/cxx/chaoscore/io/sys/Path.cpp
)

set( GFX_SRC
    src/cxx/chaoscore/gfx/Vector2.cpp
)

set( TEST_SRC
    src/cxx/chaoscore/test/ChaosTest.cpp
    src/cxx/chaoscore/test/ChaosTestMain.cpp
    src/cxx/chaoscore/test/TestLogger.cpp
    src/cxx/chaoscore/test/log_formatter/AbstractTestLogFormatter.cpp
    src/cxx/chaoscore/test/log_formatter/HTMLTestLogFormatter.cpp
    src/cxx/chaoscore/test/log_formatter/PlainTestLogFormatter.cpp
    src/cxx/chaoscore/test/log_formatter/PrettyTestLogFormatter.cpp
    src/cxx/chaoscore/test/log_formatter/XMLTestLogFormatter.cpp
)


set( TESTS_SUITES

    tests/cxx/base/PreProc_TestSuite.cpp
    tests/cxx/base/Types_TestSuite.cpp
    tests/cxx/base/data/BitwiseFloat_TestSuite.cpp
    tests/cxx/base/data/ByteOperations_TestSuite.cpp
    tests/cxx/base/math/MathOperations_TestSuite.cpp
    tests/cxx/base/uni/UTF8String_TestSuite.cpp
    tests/cxx/base/uni/UnicodeOperations_TestSuite.cpp

    tests/cxx/io/format/FormatOperations_TestSuite.cpp
    tests/cxx/io/sys/FileSystemOperations_TestSuite.cpp
    tests/cxx/io/sys/Path_TestSuite.cpp

    tests/cxx/gfx/Vector2_TestSuite.cpp
)

set(BASEPATH "${CMAKE_SOURCE_DIR}")

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/build/linux_x86/)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/build/linux_x86)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -std=c++0x -Wall -Wno-varargs")

include_directories("${BASEPATH}" ${INCLUDE_DIRECTORIES} src/cxx/ tests/cxx/)

link_directories(${LINK_DIRECTORIES})

add_executable( tests
    ${BASE_SRC}
    ${IO_SRC}
    ${GFX_SRC}
    ${TEST_SRC}
    ${TESTS_SUITES}
)

add_library(chaoscore_base SHARED ${BASE_SRC})
add_library(chaoscore_io SHARED ${IO_SRC})
add_library(chaoscore_gfx SHARED ${GFX_SRC})
add_library(chaoscore_test SHARED ${TEST_SRC})

target_link_libraries( tests
)
