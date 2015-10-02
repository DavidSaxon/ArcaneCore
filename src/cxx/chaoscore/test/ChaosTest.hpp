/*!
 * \file
 *
 * The ChaosCore testing module.
 *
 * \author David Saxon
 */
#ifndef CHAOSCORE_TEST_CHAOSTEST_HPP_
#define CHAOSCORE_TEST_CHAOSTEST_HPP_

#include "chaoscore/base/Preproc.hpp"

#include <map>
#include <vector>

#ifdef CHAOS_OS_UNIX
    #include <unistd.h>
    #include <sys/wait.h>
#endif

#include "chaoscore/base/BaseExceptions.hpp"
#include "chaoscore/base/string/UTF8String.hpp"

// TODO: currently used because format is not supported for UTF8Strings
#include <sstream>

// TODO: REMOVE ME
#include <iostream>

namespace chaos
{
/*!
 * \brief ChaosCore's testing module.
 */
namespace test
{

//------------------------------------------------------------------------------
//                                    CLASSES
//------------------------------------------------------------------------------

/*!
 * \brief TODO: DOC
 *
 * TODO: DOC
 */
class Fixture
{
public:

    virtual ~Fixture()
    {
    }

    virtual void setup()
    {
    }

    virtual void teardown()
    {
    }
};

/*!
 * \brief Warns of an unexpected error during testing procedures.
 */
class TestError : public chaos::ex::ChaosException
{
public:

    TestError( const chaos::str::UTF8String& message )
        :
        ChaosException( message )
    {
    }
};

// hide from doxygen
#ifndef IN_DOXYGEN
/*!
 * \internal
 */
namespace internal
{

//------------------------------------------------------------------------------
//                                    STRUCTS
//------------------------------------------------------------------------------

/*!
 * \internal
 *
 * Structure used to wrap up a unit test. UnitTests will override this class and
 * implement the execute member function.
 */
class UnitTest
{
public:

    virtual ~UnitTest()
    {
    }

    virtual void execute() = 0;

};

//------------------------------------------------------------------------------
//                                TYPE DEFINITIONS
//------------------------------------------------------------------------------

// the map type from test paths to the UnitTest pointer
typedef std::map< chaos::str::UTF8String, UnitTest* > TestMap;

//------------------------------------------------------------------------------
//                                    CLASSES
//------------------------------------------------------------------------------

/*!
 * \internal
 *
 * Templated object which means a static TestMap can be defined from purely
 * within a header.
 */
// template < typename T >
// struct StaticHeaderDefine
// {
//     static T testMap;
// };
// template < typename T >
// T StaticHeaderDefine< T >::testMap;

static TestMap testMap;

/*!
 * \internal
 */
// class TestCore : private StaticHeaderDefine< TestMap >
class TestCore
{
public:

    /*!
     * \internal
     *
     * This constructor should be used like a function to declare a unit test.
     *
     * \param path Unique string path used to identify the test.
     * \param unitTest UnitTest object that is wrapping up the test function.
     */
    TestCore(
            const chaos::str::UTF8String& path,
                  UnitTest*               unitTest,
                  bool                    runTests = false )
    {
        // is this the run key?
        if ( runTests )
        {
            TestCore::runAll();
            return;
        }


        // validate
        // ensure the path is not empty
        if ( path.isEmpty() )
        {
            throw TestError( "Unit test declared with no path." );
        }
        // check that first or last symbols are not a periods
        if ( path.getSymbol( 0 )                    == "." ||
             path.getSymbol( path.getLength() - 1 ) == "."    )
        {
            // TODO: use format, but needs support for UTF8String
            // TODO: add backwards + operator?
            chaos::str::UTF8String errorMessage( "Invalid test path: \"" );
            errorMessage += path;
            errorMessage += "\". Test paths cannot start or end with \'.\'";
            throw TestError( errorMessage );
        }
        // check that there are not two consecutive periods
        for ( size_t i = 0; i < path.getLength() - 1; ++i )
        {
            if ( path.getSymbol( i )     == "." &&
                 path.getSymbol( i + 1 ) == "."    )
            {
                chaos::str::UTF8String errorMessage( "Invalid test path: \"" );
                errorMessage += path;
                errorMessage += "\". Test paths cannot contain two or more "
                                "consecutive \'.\'";
                throw TestError( errorMessage );
            }
        }
        // check that path is not already in the map
        if ( testMap.find( path ) != testMap.end() )
        {
            chaos::str::UTF8String errorMessage( "Test path: \"" );
            errorMessage += path;
            errorMessage +=  "\" has multiple definitions";
            throw TestError( errorMessage );
        }
        // pass the test unit into the global mapping
        testMap[ path ] = unitTest;
    }

    /*!
     * \internal
     *
     * Runs all unit tests that have been declared.
     */
    static void runAll()
    {
        // TODO: support args and parsing

        std::cout << "RUN ALL: " << testMap.size() << std::endl;

        CHAOS_FOR_EACH( unitTestIt, testMap )
        {
            std::cout << "TEST!" << std::endl;

            unitTestIt->second->execute();

            // TODO: support for running in a single process

            // we don't have a platform independent way to support spawning a
            // new process, so we need to branch here. Fork is preferred since
            // it means we can skip the setup process of registering tests.
            // However on Windows we need to use CreateProcess to run another
            // instance of this binary with the specific args for that test

            // TODO: this should be a thread for windows support
            // run the test in a fork
            // pid_t procId = fork();
            // if ( procId == 0 )
            // {
            //     // TODO: REMOVE ME
            //     std::cout << "CHILD PROC" << std::endl;
            //     // TODO: fixture
            //     unitTestIt->second->execute();
            //     // char* seg = new char[ 2 ];
            //     // seg[ 56 ] = 12;
            //     // delete[] seg;
            //     // delete[] seg;
            //     // delete[] seg;
            //     // test complete
            //     exit( 0 );
            // }
            // else
            // {
            //     // TODO: REMOVE ME
            //     std::cout << "PARENT PROC" << std::endl;

            //     // wait for the test containing the fork to time out
            //     int procStatus;
            //     waitpid( procId, &procStatus, 0 );
            //     std::cout << "CHILD STATUS: " << procStatus << std::endl;
            // }

        }
    }

    /*!
     * \internal
     *
     * Registers a failure at the given location.
     *
     * \param file Name of the file the failure occurred in.
     * \param line Line number where the failure occurred.
     * \param message Explanation of the failure.
     */
    static void registerFailure(
            const chaos::str::UTF8String& file,
                  int                     line,
            const chaos::str::UTF8String& message )
    {
        // create the key
        std::stringstream keyStream;
        keyStream << file << ":" << line;

        std::cout << "FAILURE AT: " << keyStream.str() << ": "
                  << message << std::endl;
    }

};

} // namespace internal

#endif
// IN_DOXYGEN


//------------------------------------------------------------------------------
//                                     MACROS
//------------------------------------------------------------------------------

/*!
 * \todo leave un-doc-ed?
 */
#define CHAOS_TEST_MAIN                                                        \
    int main( int argc, char* argv[] )                                         \
    {                                                                          \
        chaos::test::internal::TestCore testCore;                              \
        testCore.runAll();                                                     \
        return 0;                                                              \
    }

/*!
 * \brief TODO: DOC
 *
 * TODO: DOC
 */
#define CHAOS_TEST_UNIT( path ) \
        CHAOS_TEST_UNIT_FIXTURE( path, chaos::test::Fixture )

/*!
 * \brief TODO: DOC
 *
 * TODO: DOC
 */
#define CHAOS_TEST_UNIT_FIXTURE( path, fixtureType )                           \
    struct path : public chaos::test::internal::UnitTest                       \
    {                                                                          \
        fixtureType* fixture;                                                  \
        path() : fixture( new fixtureType() ){}                                \
        virtual ~path(){ delete fixture; }                                     \
        virtual void execute();                                                \
    };                                                                         \
    chaos::test::internal::TestCore object_##path ( #path, new path() );       \
    void path::execute()

/*!
 * \brief TODO: DOC
 *
 * TODO: DOC
 */
#define CHAOS_TEST_RUN_ALL() chaos::test::internal::TestCore::runAll()

// TODO: TEST ARGS

 #define CHAOS_TEST_EQUAL( a, b )                                              \
        if ( a == b )                                                          \
        {                                                                      \
        }                                                                      \
        else                                                                   \
        {                                                                      \
            chaos::test::internal::TestCore::registerFailure(                  \
                    __FILE__,                                                  \
                    __LINE__,                                                  \
                    "CHAOS_TEST_EQUAL"                                         \
            );                                                                 \
        }

} // namespace test
} // namespace chaos

#endif
