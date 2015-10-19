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
#include "chaoscore/base/time/TimeUtil.hpp"
#include "chaoscore/test/TestExceptions.hpp"
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

    UnitTest( const chaos::str::UTF8String& name ) : m_name( name )
    {
    }

    virtual ~UnitTest()
    {
    }

    const chaos::str::UTF8String& get_name()
    {
        return m_name;
    }

    virtual Fixture* get_fixture() = 0;

    virtual void execute() = 0;

private:

    chaos::str::UTF8String m_name;
};

//------------------------------------------------------------------------------
//                                    GLOBALS
//------------------------------------------------------------------------------

static TestLogger                                    logger;
static std::map< chaos::str::UTF8String, UnitTest* > test_map;
static std::set< chaos::str::UTF8String >            base_modules;
static std::set< chaos::str::UTF8String >            known_modules;
static chaos::str::UTF8String                        current_module;

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
    bool single_proc;
    // whether the test is being run as a sub-process of a parent testing
    // process
    bool sub_proc;
    // the paths to the tests to run
    std::set< chaos::str::UTF8String > paths;
    // whether the standard output stream is being used
    bool use_stdout;
    // the format of the standard output stream
    TestLogger::OutFormat stdout_format;
    // mapping from file path to write to, to the format to use
    std::map< chaos::str::UTF8String, TestLogger::OutFormat > files;


    RunInfo()
        :
        single_proc  ( false ),
        sub_proc     ( false ),
        use_stdout   ( true ),
        stdout_format( TestLogger::OUT_PRETTY_TEXT )
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
                  UnitTest*               unit_test,
            const chaos::str::UTF8String& file,
                  chaos::int32            line,
                  bool                    module  = false,
                  RunInfo*                run_info = NULL )
    {
        // is this the run key?
        if ( run_info )
        {
            // mark parent logger?
            if ( !run_info->sub_proc )
            {
                logger.set_as_parent( true );
            }

            // pass outputs to the logger
            if ( run_info->use_stdout )
            {
                logger.add_stdout( run_info->stdout_format );
            }
            CHAOS_FOR_EACH( fIt, run_info->files )
            {
                logger.add_file_output( fIt->first, fIt->second );
            }

            // open the logger
            logger.open_log();

            // run the tests
            TestCore::run( run_info );

            // close the logger
            logger.close_log();

            // clean up unit test pointer pointers
            CHAOS_FOR_EACH( it, test_map )
            {
                delete it->second;
            }
            return;
        }

        // is this a module deceleration?
        if ( module )
        {
            // does the path need checking?
            if ( path.get_length() > 1 )
            {
                // check that first or last symbols are not a periods
                if ( path.get_symbol( 0 )                    == "." ||
                     path.get_symbol( path.get_length() - 1 ) == "."    )
                {
                    chaos::str::UTF8String error_message;
                    error_message << "Invalid test module path: \"" << path
                                  << "\". Test paths cannot start or end with "
                                  << "\'.\'";
                    TestCore::throw_error( error_message, file, line );
                }
                // check that there are not two consecutive periods
                for ( size_t i = 0; i < path.get_length() - 1; ++i )
                {
                    if ( path.get_symbol( i )     == "." &&
                         path.get_symbol( i + 1 ) == "."    )
                    {
                        chaos::str::UTF8String error_message;
                        error_message << "Invalid test module path: \"" << path
                                      << "\". Test paths cannot contain two or "
                                      << "more consecutive \'.\'";
                        TestCore::throw_error( error_message, file, line );
                    }
                }
                // check any variation of the path exists in the map
                std::vector< chaos::str::UTF8String > elements =
                        path.split( "." );
                chaos::str::UTF8String check_path;
                // add the first element to the base modules
                base_modules.insert( elements[ 0 ] );
                CHAOS_FOR_EACH( it, elements )
                {
                    if ( !check_path.is_empty() )
                    {
                        check_path += ".";
                    }
                    check_path += *it;
                    // add to the list of known modules
                    known_modules.insert( check_path );

                    if ( test_map.find( check_path ) != test_map.end() )
                    {
                        chaos::str::UTF8String error_message;
                        error_message << "Ambiguous test module path: \""
                                     << check_path << "\". Unit test already "
                                     << "defined with this exact path.";
                        TestCore::throw_error( error_message, file, line );
                    }
                }
            }

            current_module = path;
            return;
        }

        // validate
        // ensure a module has been declared
        if ( current_module.is_empty() )
        {
            TestCore::throw_error(
                    "CHAOS_TEST_MODULE( <module_name> ) must be declared in "
                    "file before any test decelerations.",
                    file,
                    line
            );
        }
        // ensure the path is not empty
        if ( path.is_empty() )
        {
            TestCore::throw_error(
                    "Unit test declared with no path.",
                    file,
                    line
            );
        }
        // build the full path
        chaos::str::UTF8String full_path( current_module );
        full_path += ".";
        full_path += path;
        // check that path is not already in the map
        if ( test_map.find( full_path ) != test_map.end() )
        {
            chaos::str::UTF8String error_message;
            error_message << "Test path: \"" << full_path << "\" has multiple "
                          << "definitions.";
            TestCore::throw_error( error_message, file, line );
        }
        // check that the full path doesn't match any known modules
        CHAOS_FOR_EACH( it, known_modules )
        {
            if ( full_path == *it )
            {
                chaos::str::UTF8String error_message;
                error_message << "Ambiguous test path: \"" << full_path
                              << "\". Test module already defined with this "
                              << "exact path.";
                TestCore::throw_error( error_message, file, line );
            }
        }
        // pass the test unit into the global mapping
        test_map[ full_path ] = unit_test;
    }

    /*!
     * \internal
     *
     * Runs tests defined by the run configuration information.
     */
    static void run( RunInfo* run_info )
    {
        // have any paths been supplied?
        if ( run_info->paths.empty() )
        {
            // run this function again with each of the base modules
            CHAOS_FOR_EACH( it, base_modules )
            {
                RunInfo base_run_info( *run_info );
                base_run_info.paths.insert( *it );
                TestCore::run( &base_run_info );
            }
            return;
        }

        // sanitize the provided paths
        std::set< chaos::str::UTF8String > paths;
        CHAOS_FOR_EACH( p_it, run_info->paths )
        {
            // check if the path is even valid
            bool match = false;
            // is the path a non-module
            CHAOS_FOR_EACH( mIt, known_modules )
            {
                if ( *p_it == *mIt )
                {
                    // this path is a known module
                    match = true;
                    break;
                }
            }
            // not a module, is it an exact path?
            if ( !match )
            {
                CHAOS_FOR_EACH( u_p_it, test_map )
                {
                    if ( *p_it == u_p_it->first )
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
                // TODO: throw exception? or...
                // TODO: write to log or output
                std::cout << "Invalid test path!" << std::endl;
                continue;
            }

            // check if this tests starts with any of the other paths
            bool is_sub_path = false;
            CHAOS_FOR_EACH( p_it2, run_info->paths )
            {
                // this is the same path
                if ( *p_it == *p_it2 )
                {
                    continue;
                }
                // is this a sub-path?
                if ( p_it->starts_with( *p_it2 ) )
                {
                    is_sub_path = false;
                    break;
                }
            }
            // if this is not a sub-path then we shall use it
            if ( !is_sub_path )
            {
                paths.insert( *p_it );
            }
        }

        // TODO: no valid paths?

        // structure for grouping tests by path
        struct PathGroup
        {
            chaos::str::UTF8String path;
            std::set< chaos::str::UTF8String > test_paths;
            std::set< chaos::str::UTF8String > module_paths;
        };
        std::vector< PathGroup > path_groups;

        // run logic for each supplied path
        CHAOS_FOR_EACH( it, paths )
        {
            // create a group for the path
            PathGroup path_group;
            path_group.path = *it;

            // find tests that are directly under this module or match this
            // exact module
            CHAOS_FOR_EACH( mIt, test_map )
            {
                // is there an exact match?
                if ( mIt->first == *it )
                {
                    path_group.test_paths.insert( mIt->first );
                    continue;
                }
                // extract the path to the test
                chaos::str::UTF8String path = mIt->first;
                // find the last period
                size_t lastIndex = path.find_last( "." );
                if ( lastIndex == chaos::str::UTF8String::npos )
                {
                    throw chaos::test::ex::TestRuntimeError(
                            "Unexpected error 67" );
                }
                // get the base path
                path = path.substring( 0 , lastIndex );
                // does it match the current path
                if ( path == *it )
                {
                    path_group.test_paths.insert( mIt->first );
                }
            }

            // find other modules that are directly under this path
            CHAOS_FOR_EACH( mdIt, known_modules )
            {
                // ignore exact match
                if ( *mdIt == *it )
                {
                    continue;
                }
                // extract the path to the module
                chaos::str::UTF8String path = *mdIt;
                // find the last period
                size_t lastIndex = path.find_last( "." );
                if ( lastIndex == chaos::str::UTF8String::npos )
                {
                    continue;
                }
                // get the base path
                path = path.substring( 0 , lastIndex );
                // does it match the current path
                if ( path == *it )
                {
                    path_group.module_paths.insert( *mdIt );
                }
            }

            // record the path group
            path_groups.push_back( path_group );
        }

        // run each of the path groups
        CHAOS_FOR_EACH( p_g_it, path_groups )
        {
            // run any of single tests we have
            CHAOS_FOR_EACH( t_p_it, p_g_it->test_paths )
            {
                TestCore::run_test( test_map[ *t_p_it ], run_info );
            }
            // run any of the sub modules
            CHAOS_FOR_EACH( m_p_it, p_g_it->module_paths )
            {
                // build new run info
                RunInfo module_run_info( *run_info );
                module_run_info.paths.clear();
                module_run_info.paths.insert( *m_p_it );
                TestCore::run( &module_run_info );
            }
        }
    }

    /*!
     * \internal
     *
     * \brief runs the single given unit test with the given run configuration.
     */
    static void run_test( UnitTest* unit_test, RunInfo* run_info )
    {
        // run the test dependent on the mode
        if ( run_info->single_proc )
        {
            if ( run_info->sub_proc )
            {
                run_current_proc_no_open( unit_test );
            }
            else
            {
                run_current_proc( unit_test, run_info );
            }
        }
        else
        {
            run_new_proc( unit_test, run_info );
        }
    }

    /*!
     * \internal
     *
     * \brief Runs the test on this current process.
     */
    static void run_current_proc( UnitTest* unit_test, RunInfo* run_info )
    {
        // the path to this test
        chaos::str::UTF8String test_path( *run_info->paths.begin() );
        // generate an unique id for this test
        chaos::str::UTF8String id = generate_id( test_path );
        // open the test in logger
        logger.open_test( test_path, id );
        // set up fixture
        unit_test->get_fixture()->setup();
        // execute
        unit_test->execute();
        // teardown
        unit_test->get_fixture()->teardown();
        // close the test in logger
        logger.close_test( id );
    }

    /*!
     * \internal
     *
     * \brief Runs the test on this current process with no log open and close.
     */
    static void run_current_proc_no_open( UnitTest* unit_test )
    {
        // set up fixture
        unit_test->get_fixture()->setup();
        // execute
        unit_test->execute();
        // teardown
        unit_test->get_fixture()->teardown();
    }

    /*!
     * \internal
     *
     * \brief Runs the current test in a new process.
     */
    static void run_new_proc( UnitTest* unit_test, RunInfo* run_info )
    {
        // The method spawning a new process is platform dependent
        #ifdef CHAOS_OS_UNIX

            // the path to this test
            chaos::str::UTF8String test_path( *run_info->paths.begin() );
            // generate the unique id for this this test
            chaos::str::UTF8String id = generate_id( test_path );
            // open the test in the logger
            logger.open_test( test_path, id );

            // for to run the new process
            pid_t proc_id = fork();
            if ( proc_id == 0 )
            {
                // we are now on a new process so just use the single proc
                // function.
                TestCore::run_current_proc_no_open( unit_test );
                exit( 0 );
            }
            else
            {
                // wait for the child process to end
                int proc_status;
                waitpid( proc_id, &proc_status, 0 );
                // TODO: check child status and log error message

                // close the test in the logger
                logger.close_test( id );
            }

        #elif defined( CHAOS_OS_WINDOWS )

            // the path to this test
            chaos::str::UTF8String test_path( *run_info->paths.begin() );
            // generate the unique id for this this test
            chaos::str::UTF8String id = generate_id( test_path );

            // rebuild the command line arguments
            chaos::str::UTF8String command_line_args;
            command_line_args << " --single_proc --sub_proc --silent_crash "
                              << " --test " << test_path;
            // std out
            if ( run_info->use_stdout )
            {
                command_line_args << " --stdout " << log_format_to_string(
                        run_info->stdout_format );
            }
            // file outputs
            CHAOS_FOR_EACH( fileIt, run_info->files )
            {
                // generate a mangled file path
                command_line_args << " --fileout " << fileIt->first << "."
                                  << id << " "
                                  << log_format_to_string( fileIt->second );
            }

            // spawn a new instance of this process but with arguments to point
            // to a single test case
            STARTUPINFO startup_info;
            PROCESS_INFORMATION proc_info;
            ZeroMemory( &startup_info, sizeof( startup_info ) );
            startup_info.cb = sizeof( startup_info );
            startup_info.hStdError = FALSE;
            ZeroMemory( &proc_info, sizeof( proc_info ) );

            // get the path to this executable
            TCHAR exe_path[ MAX_PATH ];
            GetModuleFileName( NULL, exe_path, MAX_PATH );

            // open the test in the logger
            logger.open_test( test_path, id );

            // start the child process
            BOOL create_success = CreateProcess(
                    exe_path,
                    const_cast< LPSTR >( command_line_args.get_cstring() ),
                    NULL,
                    NULL,
                    FALSE,
                    0,
                    NULL,
                    NULL,
                    &startup_info,
                    &proc_info
            );

            // was there an error?
            if ( !create_success )
            {
                // get the error code
                DWORD last_error = GetLastError();
                TCHAR win_error_message[ 512 ];
                FormatMessage(
                        FORMAT_MESSAGE_FROM_SYSTEM,
                        NULL,
                        last_error,
                        MAKELANGID( LANG_NEUTRAL, SUBLANG_DEFAULT ),
                        win_error_message,
                        511,
                        NULL
                );
                chaos::str::UTF8String error_message;
                error_message << "Spawning separate test process using "
                              << "CreateProcess (Windows) has failed with the "
                              << "error message: " << win_error_message;
                throw chaos::test::ex::TestRuntimeError( error_message );
            }

            // wait until the child process has finished
            WaitForSingleObject( proc_info.hProcess, INFINITE );
            // close process and thread handles
            CloseHandle( proc_info.hProcess );
            CloseHandle( proc_info.hThread );

            // TODO: check child process and log error message

            // close the test in the logger
            logger.close_test( id );

        #else

            // TODO: spawn new single_proc process
            // TODO: update error to know Windows and Unix
            throw chaos::test::ex::TestRuntimeError(
                    "Running tests on new processes is not yet supported for "
                    "non-UNIX non-Windows platforms."
            );

        #endif
    }

    /*!
     * \brief Generates a new unique id for the given unit test name.
     */
    static chaos::str::UTF8String generate_id(
            const chaos::str::UTF8String& name )
    {
        chaos::str::UTF8String id = name;
        id << "_" << chaos::time::get_current_time();
        return id;
    }

    /*!
     * \internal
     *
     * Converts a test logger output format to a UTF8String for the command
     * line.
     */
    static chaos::str::UTF8String log_format_to_string(
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
    static void register_failure(
            const chaos::str::UTF8String& file,
                  int                     line,
            const chaos::str::UTF8String& message )
    {
        // create the key
        std::stringstream key_stream;
        key_stream << file << ":" << line;

        std::cout << "FAILURE AT: " << key_stream.str() << ": "
                  << message << std::endl;
        // TODO: WRITE TO LOG OR OUTPUT
    }

    /*!
     * \internal
     *
     * Formats and throws a TestDeclerationError.
     */
    static void throw_error(
            const chaos::str::UTF8String& message,
            const chaos::str::UTF8String& file,
                  chaos::int32            line )
    {
        // convert line to string
        std::stringstream lineStr;
        // TODO: need operator to do this with UTF8String
        lineStr << line;

        //format the error message.
        chaos::str::UTF8String error_message;
        error_message << "\n\n\t" << message << "\n\n\tFILE: " << file
                      << "\n\tLINE: " << line << "\n";
        throw chaos::test::ex::TestDeclerationError( error_message );
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
#define CHAOS_TEST_UNIT_FIXTURE( path, fixture_type )                          \
    struct path : public chaos::test::internal::UnitTest                       \
    {                                                                          \
        fixture_type* fixture;                                                 \
        path() : UnitTest( #path ), fixture( new fixture_type() ){}            \
        virtual ~path(){ delete fixture; }                                     \
        virtual chaos::test::Fixture* get_fixture() { return fixture; }        \
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
            chaos::test::internal::TestCore::register_failure(                 \
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
