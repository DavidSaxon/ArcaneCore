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
#include <sstream>
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

static TestMap                               testMap;
static std::vector< chaos::str::UTF8String > knownModules;
static chaos::str::UTF8String                currentModule;

/*!
 * \internal
 */
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
            const chaos::str::UTF8String& file,
                  int                     line,
                  bool                    module   = false,
                  bool                    runTests = false )
    {
        // is this the run key?
        if ( runTests )
        {
            TestCore::runAll();
            return;
        }

        // is this a module deceleration?
        if ( module )
        {
            // does the path need checking?
            if ( path.getLength() > 1 )
            {
                // check that first or last symbols are not a periods
                if ( path.getSymbol( 0 )                    == "." ||
                     path.getSymbol( path.getLength() - 1 ) == "."    )
                {
                    chaos::str::UTF8String errorMessage( "Invalid test " );
                    errorMessage += "module path: \"";
                    errorMessage += path;
                    errorMessage += "\". Test paths cannot start or end with";
                    errorMessage += " \'.\'";
                    TestCore::throwError( errorMessage, file, line );
                }
                // check that there are not two consecutive periods
                for ( size_t i = 0; i < path.getLength() - 1; ++i )
                {
                    if ( path.getSymbol( i )     == "." &&
                         path.getSymbol( i + 1 ) == "."    )
                    {
                        chaos::str::UTF8String errorMessage( "Invalid test " );
                        errorMessage += "moudle path: \"";
                        errorMessage += path;
                        errorMessage += "\". Test paths cannot contain two or ";
                        errorMessage += "more consecutive \'.\'";
                        TestCore::throwError( errorMessage, file, line );
                    }
                }
                // check any variation of the path exists in the map
                std::vector< chaos::str::UTF8String > elements =
                        path.split( "." );
                chaos::str::UTF8String checkPath;
                CHAOS_FOR_EACH( it, elements )
                {
                    if ( !checkPath.isEmpty() )
                    {
                        checkPath += ".";
                    }
                    checkPath += *it;
                    // add to the list of known modules
                    knownModules.push_back( checkPath );

                    if ( testMap.find( checkPath ) != testMap.end() )
                    {
                        chaos::str::UTF8String errorMessage( "Ambiguous " );
                        errorMessage += "test module path: \"";
                        errorMessage += checkPath;
                        errorMessage +=  "\". Unit test already defined with ";
                        errorMessage += "this exact path.";
                        TestCore::throwError( errorMessage, file, line );
                    }
                }
            }

            currentModule = path;
            return;
        }

        // validate
        // ensure a module has been declared
        if ( currentModule.isEmpty() )
        {
            TestCore::throwError(
                    "CHAOS_TEST_MODULE( <module_name> ) must be declared in "
                    "file before any test decelerations.",
                    file,
                    line
            );
        }
        // ensure the path is not empty
        if ( path.isEmpty() )
        {
            TestCore::throwError(
                    "Unit test declared with no path.",
                    file,
                    line
            );
        }
        // build the full path
        chaos::str::UTF8String fullPath( currentModule );
        fullPath += ".";
        fullPath += path;
        // check that path is not already in the map
        if ( testMap.find( fullPath ) != testMap.end() )
        {
            chaos::str::UTF8String errorMessage( "Test path: \"" );
            errorMessage += fullPath;
            errorMessage +=  "\" has multiple definitions";
            TestCore::throwError( errorMessage, file, line );
        }
        // check that the full path doesn't match any known modules
        CHAOS_FOR_EACH( it, knownModules )
        {
            if ( fullPath == *it )
            {
                chaos::str::UTF8String errorMessage( "Ambiguous test " );
                errorMessage += "path: \"";
                errorMessage += fullPath;
                errorMessage +=  "\". Test module already defined with ";
                errorMessage += "this exact path.";
                TestCore::throwError( errorMessage, file, line );
            }
        }
        // pass the test unit into the global mapping
        testMap[ fullPath ] = unitTest;
    }

    /*!
     * \internal
     *
     * Runs all unit tests that have been declared.
     */
    static void runAll()
    {
        // TODO: support args and parsing

        CHAOS_FOR_EACH( unitTestIt, testMap )
        {
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
     * Formats and throws a TestError.
     */
    static void throwError(
            const chaos::str::UTF8String& message,
            const chaos::str::UTF8String& file,
                  int                     line )
    {
        // convert line to string
        std::stringstream lineStr;
        lineStr << line;

        //format the error message.
        chaos::str::UTF8String errorMessage( "\n\n\t" );
        errorMessage += message;
        errorMessage += "\n\n\tFILE: ";
        errorMessage += file;
        errorMessage += "\n\tLINE: ";
        errorMessage += lineStr.str().c_str();
        errorMessage += "\n";
        throw TestError( errorMessage );
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
 * \brief TODO: DOC
 *
 * TODO: DOC
 */
#define CHAOS_TEST_MODULE( path )                                              \
        namespace                                                              \
        {                                                                      \
        chaos::test::internal::TestCore t( #path, NULL, "", 0, true );         \
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
    static chaos::test::internal::TestCore object_##path (                     \
            #path, new path(), __FILE__, __LINE__ );                           \
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

// reset the current module
namespace chaos_test_include
{
static chaos::test::internal::TestCore reset( "", NULL, "", 0, true );
}
