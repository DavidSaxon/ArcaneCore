cmake_minimum_required(VERSION 2.6)
project(ChaosCore)

set( CORE_SRC

    src/cxx/chaoscore/base/file/FileSystem.cpp
    src/cxx/chaoscore/base/string/UTF8String.cpp


    src/cxx/chaoscore/test/ChaosTest.cpp
    src/cxx/chaoscore/test/TestLogger.cpp
    src/cxx/chaoscore/test/log_formatter/HTMLTestLogFormatter.cpp
    src/cxx/chaoscore/test/log_formatter/PlainTestLogFormatter.cpp
    src/cxx/chaoscore/test/log_formatter/PrettyTestLogFormatter.cpp
    src/cxx/chaoscore/test/log_formatter/XMLTestLogFormatter.cpp
)

set( TEST_SRC

    tests/cxx/base/PreProc_TestSuite.cpp
    tests/cxx/base/str/UTF8String_TestSuite.cpp
)

set( DEV_SRC

    src/cxx/__dev/Main.cpp
)

find_package(Boost)

set(BASEPATH "${CMAKE_SOURCE_DIR}")

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/build/linux_x86)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -std=c++0x -Wall -Wno-varargs")

add_definitions(-DBOOST_TEST_DYN_LINK)

include_directories("${BASEPATH}" ${INCLUDE_DIRECTORIES} ${Boost_INCLUDE_DIRS} src/cxx/ tests/cxx/)

link_directories(${LINK_DIRECTORIES} ${Boost_LIBRARY_DIRS})

#add_executable( dev_binary ${DEV_SRC} ${CORE_SRC})
#target_link_libraries( dev_binary )

add_executable(tests ${TEST_SRC} ${CORE_SRC})

target_link_libraries( tests

        ${Boost_LIBRARIES}
        -lboost_system
        -lboost_filesystem
)
