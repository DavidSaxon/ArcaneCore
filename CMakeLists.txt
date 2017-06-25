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
    src/cpp/arcanecore/io/dl/DLOperations.cpp
    src/cpp/arcanecore/io/format/ANSI.cpp
    src/cpp/arcanecore/io/format/FormatOperations.cpp
    src/cpp/arcanecore/io/sys/FileHandle.cpp
    src/cpp/arcanecore/io/sys/FileReader.cpp
    src/cpp/arcanecore/io/sys/FileSystemOperations.cpp
    src/cpp/arcanecore/io/sys/FileWriter.cpp
    src/cpp/arcanecore/io/sys/Path.cpp
)

set(LOG_SRC
    src/cpp/arcanecore/log/AbstractOutput.cpp
    src/cpp/arcanecore/log/Input.cpp
    src/cpp/arcanecore/log/LogHandler.cpp
    src/cpp/arcanecore/log/Stream.cpp
    src/cpp/arcanecore/log/outputs/FileOutput.cpp
    src/cpp/arcanecore/log/outputs/StdOutput.cpp
)

set(LOG_SHARED_SRC
    src/cpp/arcanecore/log/Shared.cpp
)

set(JSON_SRC
    src/cpp/json/jsoncpp.cpp
)

set(CONFIG_SRC
    src/cpp/arcanecore/config/Document.cpp
    src/cpp/arcanecore/config/Variant.cpp
    src/cpp/arcanecore/config/visitors/Path.cpp
    src/cpp/arcanecore/config/visitors/Primitive.cpp
    src/cpp/arcanecore/config/visitors/String.cpp
)

set(COLLATE_SRC
    src/cpp/arcanecore/col/Accessor.cpp
    src/cpp/arcanecore/col/Collator.cpp
    src/cpp/arcanecore/col/Reader.cpp
    src/cpp/arcanecore/col/TableOfContents.cpp
)

set(COLLATE_CMD_SRC
    src/cpp/arcanecore/col/__cmd/CommandLineTool.cpp
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

    tests/cpp/base/Preproc_TestSuite.cpp
    tests/cpp/base/Types_TestSuite.cpp
    tests/cpp/base/data/BitwiseFloat_TestSuite.cpp
    tests/cpp/base/data/ByteOperations_TestSuite.cpp
    tests/cpp/base/introspect/IntrospectOperations_TestSuite.cpp
    tests/cpp/base/math/MathOperations_TestSuite.cpp
    tests/cpp/base/str/UTF8String_TestSuite.cpp
    tests/cpp/base/str/StringOperations_TestSuite.cpp

    tests/cpp/gm/Matrix_TestSuite.cpp
    tests/cpp/gm/MatrixMath_TestSuite.cpp
    tests/cpp/gm/Vector_TestSuite.cpp
    tests/cpp/gm/VectorMath_TestSuite.cpp

    tests/cpp/io/format/FormatOperations_TestSuite.cpp
    tests/cpp/io/sys/FileHandle_TestSuite.cpp
    tests/cpp/io/sys/FileReader_TestSuite.cpp
    tests/cpp/io/sys/FileSystemOperations_TestSuite.cpp
    tests/cpp/io/sys/Path_TestSuite.cpp

    tests/cpp/log/Log_TestSuite.cpp

    tests/cpp/config/Document_TestSuite.cpp
    tests/cpp/config/Variant_TestSuite.cpp
    tests/cpp/config/visitors/PathVisitor_TestSuite.cpp
    tests/cpp/config/visitors/PrimitiveVisitor_TestSuite.cpp
    tests/cpp/config/visitors/StringVisitor_TestSuite.cpp

    tests/cpp/col/Read_TestSuite.cpp
    tests/cpp/col/Write_TestSuite.cpp
)


set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/build/linux_x86)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/build/linux_x86)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/build/linux_x86)

set(CMAKE_CXX_FLAGS
    "${CMAKE_CXX_FLAGS} -g -std=c++0x -Wall -Wno-varargs -fPIC -msse3"
)

include_directories(
    ${INCLUDE_DIRECTORIES}
    /usr/include/python3.5
    src/cpp
    tests/cpp
)

link_directories(
    ${LINK_DIRECTORIES}
    /usr/lib/python3.5/
    ${CMAKE_BINARY_DIR}/build/linux_x86
)

add_library(arcanecore_base STATIC ${BASE_SRC})
add_library(arcanecore_io STATIC ${IO_SRC})
add_library(arcanecore_log STATIC ${LOG_SRC})
add_library(arcanecore_json STATIC ${JSON_SRC})
add_library(arcanecore_config STATIC ${CONFIG_SRC})
add_library(arcanecore_collate STATIC ${COLLATE_SRC})
add_library(arcanecore_test STATIC ${TEST_SRC})

add_library(arcanecore_log_shared SHARED ${LOG_SHARED_SRC})

target_link_libraries(arcanecore_log_shared
    arcanecore_log
    arcanecore_io
    arcanecore_base
)

add_executable(arc_collate_tool ${COLLATE_CMD_SRC})

target_link_libraries(arc_collate_tool
    arcanecore_collate
    arcanecore_log_shared
    arcanecore_log
    arcanecore_io
    arcanecore_base
)

add_executable(tests ${TESTS_SUITES})

target_link_libraries(tests
    arcanecore_test
    arcanecore_collate
    arcanecore_config
    arcanecore_json
    arcanecore_log
    arcanecore_io
    arcanecore_base
    python3.5m
    dl
)
