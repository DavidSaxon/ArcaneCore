/*!
 * \file
 *
 * The ChaosCore testing module.
 *
 * \author David Saxon
 */
#ifndef CHAOSCORE_TEST_CHAOSTEST_HPP_
#define CHAOSCORE_TEST_CHAOSTEST_HPP_

#include <map>
#include <set>
#include <sstream>
#include <vector>

#include "chaoscore/base/BaseExceptions.hpp"
#include "chaoscore/base/Preproc.hpp"
#include "chaoscore/base/string/UTF8String.hpp"
#include "chaoscore/test/TestLogger.hpp"

// fork
#ifdef CHAOS_OS_UNIX
    #include <unistd.h>
    #include <sys/wait.h>
// create process
#elif defined( CHAOS_OS_WINDOWS )
    #include <windows.h>
#endif

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

    virtual Fixture* getFixture() = 0;

    virtual void execute() = 0;
};

//------------------------------------------------------------------------------
//                                    GLOBALS
//------------------------------------------------------------------------------

static TestLogger                                    logger;
static std::map< chaos::str::UTF8String, UnitTest* > testMap;
static std::set< chaos::str::UTF8String >            baseModules;
static std::set< chaos::str::UTF8String >            knownModules;
static chaos::str::UTF8String                        currentModule;

//------------------------------------------------------------------------------
//                                    CLASSES
//------------------------------------------------------------------------------

/*!
 * \internal
 *
 * \brief Structure containing information about the test run configuration,
 */
struct RunInfo
{
    // whether the tests should be run in a single process or not
    bool singleProc;
    // the paths to the tests to run
    std::set< chaos::str::UTF8String > paths;
    // whether the standard output stream is being used
    bool useStdout;
    // the format of the standard output stream
    TestLogger::OutFormat stdoutFormat;
    // mapping from file path to write to, to the format to use
    std::map< chaos::str::UTF8String, TestLogger::OutFormat > files;


    RunInfo()
        :
        singleProc  ( false ),
        useStdout   ( true ),
        stdoutFormat( TestLogger::OUT_PRETTY_TEXT )
    {
    }
};


/*!
 * \internal
 *
 * \brief Hacky object for performing test magic.
 *
 * For oddities relating to the static global variables used this object is
 * declared entirely inline.
 */
class TestCore
{
public:

    // TODO: can we move to inline cpp functions?

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
                  bool                    module  = false,
                  RunInfo*                runInfo = NULL )
    {
        // is this the run key?
        if ( runInfo )
        {
            // pass outputs to the logger
            if ( runInfo->useStdout )
            {
                logger.addStdOut( runInfo->stdoutFormat );
            }

            // run the tests
            TestCore::run( runInfo );
            // clean up unit test pointer pointers
            CHAOS_FOR_EACH( it, testMap )
            {
                delete it->second;
            }
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
                // add the first element to the base modules
                baseModules.insert( elements[ 0 ] );
                CHAOS_FOR_EACH( it, elements )
                {
                    if ( !checkPath.isEmpty() )
                    {
                        checkPath += ".";
                    }
                    checkPath += *it;
                    // add to the list of known modules
                    knownModules.insert( checkPath );

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
     * Runs tests defined by the run configuration information.
     */
    static void run( RunInfo* runInfo )
    {
        // have any paths been supplied?
        if ( runInfo->paths.empty() )
        {
            // run this function again with each of the base modules
            CHAOS_FOR_EACH( it, baseModules )
            {
                RunInfo baseRunInfo( *runInfo );
                baseRunInfo.paths.insert( *it );
                TestCore::run( &baseRunInfo );
            }
            return;
        }

        // sanitize the provided paths
        std::set< chaos::str::UTF8String > paths;
        CHAOS_FOR_EACH( pIt, runInfo->paths )
        {
            // check if the path is even valid
            bool match = false;
            // is the path a non-module
            CHAOS_FOR_EACH( mIt, knownModules )
            {
                if ( *pIt == *mIt )
                {
                    // this path is a known module
                    match = true;
                    break;
                }
            }
            // not a module, is it an exact path?
            if ( !match )
            {
                CHAOS_FOR_EACH( upIt, testMap )
                {
                    if ( *pIt == upIt->first )
                    {
                        // this path is an exact test
                        match = true;
                        break;
                    }
                }
            }
            // this isn't a valid test path
            if ( !match )
            {
                // TODO: write to log or output
                std::cout << "Invalid test path!" << std::endl;
                continue;
            }

            // check if this tests starts with any of the other paths
            bool isSubPath = false;
            CHAOS_FOR_EACH( pIt2, runInfo->paths )
            {
                // this is the same path
                if ( *pIt == *pIt2 )
                {
                    continue;
                }
                // is this a sub-path?
                if ( pIt->startsWith( *pIt2 ) )
                {
                    isSubPath = false;
                    break;
                }
            }
            // if this is not a sub-path then we shall use it
            if ( !isSubPath )
            {
                paths.insert( *pIt );
            }
        }

        // TODO: no valid paths?

        // structure for grouping tests by path
        struct PathGroup
        {
            chaos::str::UTF8String path;
            std::set< chaos::str::UTF8String > testPaths;
            std::set< chaos::str::UTF8String > modulePaths;
        };
        std::vector< PathGroup > pathGroups;

        // run logic for each supplied path
        CHAOS_FOR_EACH( it, paths )
        {
            // create a group for the path
            PathGroup pathGroup;
            pathGroup.path = *it;

            // find tests that are directly under this module or match this
            // exact module
            CHAOS_FOR_EACH( mIt, testMap )
            {
                // is there an exact match?
                if ( mIt->first == *it )
                {
                    pathGroup.testPaths.insert( mIt->first );
                    continue;
                }
                // extract the path to the test
                chaos::str::UTF8String path = mIt->first;
                // find the last period
                size_t lastIndex = path.findLast( "." );
                if ( lastIndex == chaos::str::UTF8String::npos )
                {
                    throw TestError( "Unexpected error 67" );
                }
                // get the base path
                path = path.substring( 0 , lastIndex );
                // does it match the current path
                if ( path == *it )
                {
                    pathGroup.testPaths.insert( mIt->first );
                }
            }

            // find other modules that are directly under this path
            CHAOS_FOR_EACH( mdIt, knownModules )
            {
                // ignore exact match
                if ( *mdIt == *it )
                {
                    continue;
                }
                // extract the path to the module
                chaos::str::UTF8String path = *mdIt;
                // find the last period
                size_t lastIndex = path.findLast( "." );
                if ( lastIndex == chaos::str::UTF8String::npos )
                {
                    continue;
                }
                // get the base path
                path = path.substring( 0 , lastIndex );
                // does it match the current path
                if ( path == *it )
                {
                    pathGroup.modulePaths.insert( *mdIt );
                }
            }

            // record the path group
            pathGroups.push_back( pathGroup );
        }

        // run each of the path groups
        CHAOS_FOR_EACH( pgIt, pathGroups )
        {
            // run any of single tests we have
            CHAOS_FOR_EACH( tpIt, pgIt->testPaths )
            {
                TestCore::runTest( testMap[ *tpIt ], runInfo );
            }
            // run any of the sub modules
            CHAOS_FOR_EACH( mpIt, pgIt->modulePaths )
            {
                // build new run info
                RunInfo moduleRunInfo( *runInfo );
                moduleRunInfo.paths.clear();
                moduleRunInfo.paths.insert( *mpIt );
                TestCore::run( &moduleRunInfo );
            }
        }
    }

    /*!
     * \internal
     *
     * \brief runs the single given unit test with the given run configuration.
     */
    static void runTest( UnitTest* unitTest, RunInfo* runInfo )
    {
        // run the test dependent on the mode
        if ( runInfo->singleProc )
        {
            runSingleProc( unitTest, runInfo );
        }
        else
        {
            runInNewProc( unitTest, runInfo );
        }
    }

    /*!
     * \internal
     *
     * \brief Runs the test on this current process.
     */
    static void runSingleProc( UnitTest* unitTest, RunInfo* runInfo )
    {
        // set up fixture
        unitTest->getFixture()->setup();
        // execute
        unitTest->execute();
        // teardown
        unitTest->getFixture()->teardown();
    }

    /*!
     * \internal
     *
     * \brief Runs the current test in a new process.
     */
    static void runInNewProc( UnitTest* unitTest, RunInfo* runInfo )
    {
        // The method spawning a new process is platform dependent
        #ifdef CHAOS_OS_UNIX

            // for to run the new process
            pid_t procId = fork();
            if ( procId == 0 )
            {
                // we are now on a new process so just use the single proc
                // function.
                TestCore::runSingleProc( unitTest, runInfo );
                exit( 0 );
            }
            else
            {
                // wait for the child process to end
                int procStatus;
                waitpid( procId, &procStatus, 0 );
                // TODO: check child status
            }

        #elif defined( CHAOS_OS_WINDOWS )

            // rebuild the command line arguments
            chaos::str::UTF8String commandLineArgs = " --single_proc";
            // get the test to run
            commandLineArgs += " --test ";
            commandLineArgs += *runInfo->paths.begin();
            // std out
            if ( runInfo->useStdout )
            {
                commandLineArgs += " --stdout ";
                commandLineArgs += logFormatToString( runInfo->stdoutFormat );
            }
            // file outputs
            CHAOS_FOR_EACH( fileIt, runInfo->files )
            {
                commandLineArgs += " --fileout ";
                commandLineArgs += fileIt->first + " ";
                commandLineArgs += logFormatToString( fileIt->second );
            }

            // spawn a new instance of this process but with arguments to point
            // to a single test case
            STARTUPINFO startupInfo;
            PROCESS_INFORMATION procInfo;
            ZeroMemory( &startupInfo, sizeof( startupInfo ) );
            startupInfo.cb = sizeof( startupInfo );
            ZeroMemory( &procInfo, sizeof( procInfo ) );

            // get the path to this executable
            TCHAR exePath[ MAX_PATH ];
            GetModuleFileName( NULL, exePath, MAX_PATH );

            // start the child process
            BOOL createSuccess = CreateProcess(
                    exePath,
                    const_cast< LPSTR >( commandLineArgs.getCString() ),
                    NULL,
                    NULL,
                    FALSE,
                    0,
                    NULL,
                    NULL,
                    &startupInfo,
                    &procInfo
            );

            // was there an error?
            if ( !createSuccess )
            {
                // TOOD: error check
                std::cout << "FAILED" << std::endl;
            }

            // wait until the child process has finished
            WaitForSingleObject( procInfo.hProcess, INFINITE );
            // close process and thread handles
            CloseHandle( procInfo.hProcess );
            CloseHandle( procInfo.hThread );

        #else

            // TODO: spawn new single_proc process
            // TODO: update error to know Windows and Unix
            throw TestError(
                    "Running tests on new processes is not yet supported for "
                    "non-UNIX non-Windows platforms."
            );

        #endif
    }

    /*!
     * \internal
     *
     * Converts a test logger output format to a UTF8String for the command
     * line.
     */
    static chaos::str::UTF8String logFormatToString(
            TestLogger::OutFormat format )
    {
        switch( format )
        {
            case TestLogger::OUT_PLAIN_TEXT:
            {
                return "plain";
            }
            case TestLogger::OUT_PRETTY_TEXT:
            {
                return "pretty";
            }
            case TestLogger::OUT_XML:
            {
                return "xml";
            }
            case TestLogger::OUT_HTML:
            {
                return "html";
            }
        }

        return "";
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
        // TODO: WRITE TO LOG OR OUTPUT
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
};

} // namespace internal

#endif
// IN_DOXYGEN


//------------------------------------------------------------------------------
//                                     MACROS
//------------------------------------------------------------------------------

// TODO: don't show macro value in docs..

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
        virtual chaos::test::Fixture* getFixture() { return fixture; }         \
        virtual void execute();                                                \
    };                                                                         \
    static chaos::test::internal::TestCore object_##path (                     \
            #path, new path(), __FILE__, __LINE__ );                           \
    void path::execute()


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
