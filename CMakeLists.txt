cmake_minimum_required(VERSION 3.2)
project(ArcaneCore)

set(BASE_SRC
    src/cpp/arcanecore/base/clock/ClockOperations.cpp
    src/cpp/arcanecore/base/data/BinaryOperations.cpp
    src/cpp/arcanecore/base/data/BitwiseFloat.cpp
    src/cpp/arcanecore/base/data/ByteOperations.cpp
    src/cpp/arcanecore/base/math/MathConstants.cpp
    src/cpp/arcanecore/base/math/MathOperations.cpp
    src/cpp/arcanecore/base/os/OSOperations.cpp
    src/cpp/arcanecore/base/str/StringConstants.cpp
    src/cpp/arcanecore/base/str/StringOperations.cpp
    src/cpp/arcanecore/base/str/UTF8String.cpp
)

set(IO_SRC
    src/cpp/arcanecore/io/format/ANSI.cpp
    src/cpp/arcanecore/io/format/FormatOperations.cpp
    src/cpp/arcanecore/io/sys/FileHandle.cpp
    src/cpp/arcanecore/io/sys/FileReader.cpp
    src/cpp/arcanecore/io/sys/FileSystemOperations.cpp
    src/cpp/arcanecore/io/sys/FileWriter.cpp
    src/cpp/arcanecore/io/sys/Path.cpp
)

set(GFX_SRC
    src/cpp/arcanecore/gfx/Vector2.cpp
    src/cpp/arcanecore/gfx/Vector3.cpp
    src/cpp/arcanecore/gfx/Vector4.cpp
    src/cpp/arcanecore/gfx/VectorOperations.cpp
)

set(TEST_SRC
    src/cpp/arcanecore/test/ArcTest.cpp
    src/cpp/arcanecore/test/ArcTestMain.cpp
    src/cpp/arcanecore/test/TestLogger.cpp
    src/cpp/arcanecore/test/log_formatter/AbstractTestLogFormatter.cpp
    src/cpp/arcanecore/test/log_formatter/HTMLTestLogFormatter.cpp
    src/cpp/arcanecore/test/log_formatter/PlainTestLogFormatter.cpp
    src/cpp/arcanecore/test/log_formatter/PrettyTestLogFormatter.cpp
    src/cpp/arcanecore/test/log_formatter/XMLTestLogFormatter.cpp
)

set(TESTS_SUITES
    tests/cpp/TestsMain.cpp

#    tests/cpp/base/Preproc_TestSuite.cpp
#    tests/cpp/base/Types_TestSuite.cpp
    tests/cpp/base/data/BitwiseFloat_TestSuite.cpp
#    tests/cpp/base/data/ByteOperations_TestSuite.cpp
#    tests/cpp/base/introspect/IntrospectOperations_TestSuite.cpp
#    tests/cpp/base/math/MathOperations_TestSuite.cpp
#    tests/cpp/base/str/UTF8String_TestSuite.cpp
#    tests/cpp/base/str/StringOperations_TestSuite.cpp
#
#    tests/cpp/io/format/FormatOperations_TestSuite.cpp
#    tests/cpp/io/sys/FileHandle_TestSuite.cpp
#    tests/cpp/io/sys/FileReader_TestSuite.cpp
#    tests/cpp/io/sys/FileSystemOperations_TestSuite.cpp
#    tests/cpp/io/sys/Path_TestSuite.cpp
#
#    tests/cpp/gfx/Vector2_TestSuite.cpp
#    tests/cpp/gfx/Vector3_TestSuite.cpp
#    tests/cpp/gfx/Vector4_TestSuite.cpp
#    tests/cpp/gfx/VectorOperations_TestSuite.cpp
)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/build/linux_x86)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/build/linux_x86)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/build/linux_x86)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -std=c++0x -Wall -Wno-varargs -fPIC")

include_directories(
    ${INCLUDE_DIRECTORIES}
    /usr/include/python3.4
    src/cpp
    tests/cpp
)

link_directories(
    ${LINK_DIRECTORIES}
    /usr/lib/python3.4/
    ${CMAKE_BINARY_DIR}/build/linux_x86
)

add_library(arcanecore_base STATIC ${BASE_SRC})
add_library(arcanecore_io STATIC ${IO_SRC})
add_library(arcanecore_gfx STATIC ${GFX_SRC})
add_library(arcanecore_test STATIC ${TEST_SRC})

add_executable(tests ${TESTS_SUITES})

target_link_libraries(tests
    arcanecore_test
    arcanecore_io
    arcanecore_base
    arcanecore_gfx
    python3.4m
)
