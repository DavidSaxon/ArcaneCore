#include "chaoscore/test/ChaosTest.hpp"

#include <iostream>

#include "chaoscore/io/file/FileExceptions.hpp"
#include "chaoscore/io/file/FileUtil.hpp"



namespace chaos
{
namespace test
{
namespace internal
{

//------------------------------------------------------------------------------
//                            PUBLIC STATIC ATTRIBUTES
//------------------------------------------------------------------------------

TestLogger                                    TestCore::logger;
std::map< chaos::str::UTF8String, UnitTest* > TestCore::test_map;
std::set< chaos::str::UTF8String >            TestCore::base_modules;
std::set< chaos::str::UTF8String >            TestCore::known_modules;
chaos::str::UTF8String                        TestCore::current_module;

//------------------------------------------------------------------------------
//                               TESTCORE FUNCTIONS
//------------------------------------------------------------------------------

void TestCore::declare_module(
        const chaos::str::UTF8String& path,
        const chaos::str::UTF8String& file,
              chaos::int32            line )
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
        TestCore::base_modules.insert( elements[ 0 ] );
        CHAOS_FOR_EACH( it, elements )
        {
            if ( !check_path.is_empty() )
            {
                check_path += ".";
            }
            check_path += *it;
            // add to the list of known modules
            TestCore::known_modules.insert( check_path );

            if ( TestCore::test_map.find( check_path ) !=
                 TestCore::test_map.end() )
            {
                chaos::str::UTF8String error_message;
                error_message << "Ambiguous test module path: \""
                             << check_path << "\". Unit test already "
                             << "defined with this exact path.";
                TestCore::throw_error( error_message, file, line );
            }
        }
    }

    TestCore::current_module = path;
}

void TestCore::declare_unit(
        const chaos::str::UTF8String& path,
              UnitTest*               unit_test,
        const chaos::str::UTF8String& file,
              chaos::int32            line )
{
    // ensure a module has been declared
    if ( TestCore::current_module.is_empty() )
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
    chaos::str::UTF8String full_path;
    full_path << TestCore::current_module << "." << path;
    // check that path is not already in the map
    if ( TestCore::test_map.find( full_path ) != TestCore::test_map.end() )
    {
        chaos::str::UTF8String error_message;
        error_message << "Test path: \"" << full_path << "\" has multiple "
                      << "definitions.";
        TestCore::throw_error( error_message, file, line );
    }
    // check that the full path doesn't match any known modules
    CHAOS_FOR_EACH( it, TestCore::known_modules )
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
    TestCore::test_map[ full_path ] = unit_test;
}

void TestCore::setup( RunInfo* run_info )
{
    // generate id?
    if ( run_info->id.is_empty() )
    {
        run_info->id << "chaoscore_tests_"
                     << chaos::time::get_current_time();
    }
    TestCore::logger.set_global_id( run_info->id );

    // mark parent logger?
    if ( !run_info->sub_proc )
    {
        TestCore::logger.set_as_parent( true );
    }

    // pass outputs to the logger
    if ( run_info->use_stdout )
    {
        TestCore::logger.add_stdout(
                run_info->stdout_info.verbosity,
                run_info->stdout_info.format );
    }
    CHAOS_FOR_EACH( f_it, run_info->files )
    {
        TestCore::logger.add_file_output(
                f_it->first,
                f_it->second->verbosity,
                f_it->second->format
        );
    }

    // open the logger
    TestCore::logger.open_log();
}

void TestCore::teardown( RunInfo* run_info )
{
    // close the logger
    TestCore::logger.close_log();

    // clean up run info
    CHAOS_FOR_EACH( r_t_it, run_info->files )
    {
        delete r_t_it->second;
    }
    // clean up unit test pointers
    CHAOS_FOR_EACH( t_it, test_map )
    {
        delete t_it->second;
    }
}

void TestCore::run( RunInfo* run_info )
{
    // have any paths been supplied?
    if ( run_info->paths.empty() )
    {
        // run this function again with each of the base modules
        CHAOS_FOR_EACH( it, TestCore::base_modules )
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
        CHAOS_FOR_EACH( mIt, TestCore::known_modules )
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
            CHAOS_FOR_EACH( u_p_it, TestCore::test_map )
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
        CHAOS_FOR_EACH( m_it, TestCore::test_map )
        {
            // is there an exact match?
            if ( m_it->first == *it )
            {
                path_group.test_paths.insert( m_it->first );
                continue;
            }
            // extract the path to the test
            chaos::str::UTF8String path = m_it->first;
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
                path_group.test_paths.insert( m_it->first );
            }
        }

        // find other modules that are directly under this path
        CHAOS_FOR_EACH( md_it, TestCore::known_modules )
        {
            // ignore exact match
            if ( *md_it == *it )
            {
                continue;
            }
            // extract the path to the module
            chaos::str::UTF8String path = *md_it;
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
                path_group.module_paths.insert( *md_it );
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
            TestCore::run_test(
                    TestCore::test_map[ *t_p_it ], *t_p_it, run_info );
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

void TestCore::run_test(
        UnitTest*                     unit_test,
        const chaos::str::UTF8String& full_path,
        RunInfo*                      run_info )
{
    // run the test dependent on the mode
    if ( run_info->single_proc )
    {
        if ( run_info->sub_proc )
        {
            TestCore::run_current_proc_no_open( unit_test, run_info );
        }
        else
        {
            TestCore::run_current_proc( unit_test, full_path, run_info );
        }
    }
    else
    {
        TestCore::run_new_proc( unit_test, full_path, run_info );
    }
}

void TestCore::run_current_proc(
        UnitTest*                     unit_test,
        const chaos::str::UTF8String& full_path,
        RunInfo*                      run_info )
{
    // generate an unique id for this test
    chaos::str::UTF8String id = generate_id( full_path );
    // open the test in logger
    TestCore::logger.open_test( full_path, id );
    // set up fixture
    unit_test->get_fixture()->setup();
    // execute
    unit_test->execute();
    // teardown
    unit_test->get_fixture()->teardown();
    // finialise report
    TestCore::logger.finialise_test_report();
    // close the test in logger
    TestCore::logger.close_test( id );
}

void TestCore::run_current_proc_no_open(
        UnitTest* unit_test,
        RunInfo*  run_info )
{
    // set up fixture
    unit_test->get_fixture()->setup();
    // execute
    unit_test->execute();
    // finialise report
    TestCore::logger.finialise_test_report();
    // teardown
    unit_test->get_fixture()->teardown();
}

void TestCore::run_new_proc(
        UnitTest*                     unit_test,
        const chaos::str::UTF8String& full_path,
        RunInfo*                      run_info )
{
    // The method spawning a new process is platform dependent
    #ifdef CHAOS_OS_UNIX

        // generate the unique id for this this test
        chaos::str::UTF8String id = TestCore::generate_id( full_path );
        // open the test in the logger
        TestCore::logger.open_test( full_path, id );

        // for to run the new process
        pid_t proc_id = fork();
        if ( proc_id == 0 )
        {
            // we are now on a new process so just use the single proc
            // function.
            TestCore::run_current_proc_no_open( unit_test, run_info );
            exit( 0 );
        }
        else
        {
            // wait for the child process to end
            int exit_status;
            waitpid( proc_id, &exit_status, 0 );

            // check that the process finished successfully
            if ( exit_status != 0 )
            {
                chaos::str::UTF8String message;
                // TODO: hex
                message << static_cast< chaos::int32 >( exit_status );
                TestCore::logger.report_crash( id, message );
            }

            // close the test in the logger
            TestCore::logger.close_test( id );
        }

    #elif defined( CHAOS_OS_WINDOWS )

        // generate the unique id for this this test
        chaos::str::UTF8String id = TestCore::generate_id( full_path );

        // rebuild the command line arguments
        chaos::str::UTF8String command_line_args;
        command_line_args << " --single_proc --sub_proc " << run_info->id
                          << " --silent_crash --test " << full_path;
        // std out
        if ( run_info->use_stdout )
        {
            command_line_args
                    << " --stdout "
                    << log_format_to_string( run_info->stdout_info.format )
                    << " " << run_info->stdout_info.verbosity;
        }
        // file outputs
        CHAOS_FOR_EACH( f_it, run_info->files )
        {
            // generate a mangled file path
            command_line_args
                    << " --fileout " << f_it->first << "." << id << " "
                    << log_format_to_string( f_it->second->format ) << " "
                    << f_it->second->verbosity;
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
        TestCore::logger.open_test( full_path, id );

        // start the child process
        BOOL create_success = CreateProcess(
                exe_path,
                const_cast< LPSTR >( command_line_args.to_cstring() ),
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

        // check that the process finished successfully
        DWORD exit_code;
        GetExitCodeProcess( proc_info.hProcess, &exit_code );
        if ( exit_code != 0 )
        {
            chaos::str::UTF8String message;
            // TODO: hex
            message << static_cast< chaos::uint32 >( exit_code );
            TestCore::logger.report_crash( id, message );
        }

        // close process and thread handles
        CloseHandle( proc_info.hProcess );
        CloseHandle( proc_info.hThread );

        // close the test in the logger
        TestCore::logger.close_test( id );

    #else

        throw chaos::test::ex::TestRuntimeError(
                "Running tests on new processes is not yet supported for "
                "non-UNIX, non-Windows platforms."
        );

    #endif
}

chaos::str::UTF8String TestCore::log_format_to_string(
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

void TestCore::throw_error(
        const chaos::str::UTF8String& message,
        const chaos::str::UTF8String& file,
              chaos::int32            line )
{
    //format the error message.
    chaos::str::UTF8String error_message;
    error_message << "\n\n\t" << message << "\n\n\tFILE: " << file
                  << "\n\tLINE: " << line << "\n";
    throw chaos::test::ex::TestDeclerationError( error_message );
}

} // namespace internal
} // namespace test
} // namespace chaos



// TODO: MOVE BELOW HERE TO A NEW FILE???

//------------------------------------------------------------------------------
//                             COMMAND LINE ARGUMENTS
//------------------------------------------------------------------------------

//----------------------------COMMAND LINE ARGUMENTS----------------------------

static chaos::str::UTF8String ARG_SINGLE_PROC   = "--single_proc";
static chaos::str::UTF8String ARG_SUB_PROC      = "--sub_proc";
static chaos::str::UTF8String ARG_SILENT_CRASH  = "--silent_crash";
static chaos::str::UTF8String ARG_TEST_PATH     = "--test";
static chaos::str::UTF8String ARG_STDOUT        = "--stdout";
static chaos::str::UTF8String ARG_FILEOUT       = "--fileout";

//-----------------------------COMMAND LINE OPTIONS-----------------------------

static chaos::str::UTF8String OPT_FORMAT_PLAIN  = "plain";
static chaos::str::UTF8String OPT_FORMAT_PRETTY = "pretty";
static chaos::str::UTF8String OPT_FORMAT_XML    = "xml";
static chaos::str::UTF8String OPT_FORMAT_HTML   = "html";

//------------------------------------------------------------------------------
//                                   PROTOTYPES
//------------------------------------------------------------------------------

/*!
 * \brief Attempts to convert a string to a TestLogger output format.
 *
 * \param str The string to parse to a format.
 * \param format Parameter that the format will be returned through.
 * \return Whether the input string was valid or not.
 */
bool string_to_format(
        const chaos::str::UTF8String&              str,
              chaos::test::TestLogger::OutFormat&  format );

// TODO: help

//------------------------------------------------------------------------------
//                                 MAIN FUNCTION
//------------------------------------------------------------------------------

int main( int argc, char* argv[] )
{
    // create run configuration information with default values
    chaos::test::internal::RunInfo run_info;

    // whether a standard output has been defined
    bool stdout_defined = false;

    // parse args
    for ( size_t i = 1; i < static_cast< size_t >( argc ); ++i )
    {
        // --single_proc
        if ( ARG_SINGLE_PROC == argv[ i ] )
        {
            run_info.single_proc = true;
        }
        // --sub_proc
        else if ( ARG_SUB_PROC == argv[ i ] )
        {
            // ensure there is another argument
            if ( argc - i <= 1 )
            {
                std::cerr << "\nERROR: Command line argument \'"
                          << ARG_SINGLE_PROC << "must be followed by the "
                          << "parent process's testing id.\n" << std::endl;
                return -1;
            }

            run_info.sub_proc = true;
            run_info.id = chaos::str::UTF8String( argv[ ++i ] );
        }
        // --silent_crash
        else if ( ARG_SILENT_CRASH == argv[ i ] )
        {
            #ifdef CHAOS_OS_WINDOWS

                // we don't want show a dialog box when this crashes
                SetErrorMode( SEM_FAILCRITICALERRORS | SEM_NOGPFAULTERRORBOX );
                _set_abort_behavior( 0, _WRITE_ABORT_MSG );

            #else

                chaos::str::UTF8String error_message( ARG_SILENT_CRASH );
                error_message << ARG_SILENT_CRASH
                              << " only supported on Windows systems.";
                throw chaos::test::ex::TestRuntimeError( error_message );

            #endif
        }
        // --test
        else if ( ARG_TEST_PATH == argv[ i ] )
        {
            // ensure there is another argument
            if ( argc - i <= 1 )
            {
                std::cerr << "\nERROR: Command line argument \'"
                          << ARG_TEST_PATH << "\' must be followed by a test "
                          << "path.\n" << std::endl;
                return -1;
            }

            // get the next argument
            run_info.paths.insert( chaos::str::UTF8String( argv[ ++i ] ) );
        }
        // --stdout
        else if ( ARG_STDOUT == argv[ i ] )
        {
            // ensure there is another two arguments
            if ( argc - i <= 2 )
            {
                std::cerr << "\nERROR: Command line argument \'"
                          << ARG_STDOUT << "\' must be followed by the format "
                          << "to use (plain, pretty, xml, or html) and the "
                          << "verbosity level (1-4).\n" << std::endl;
                return -1;
            }

            // ensure that stdout has not already been defined
            if ( stdout_defined )
            {
                std::cerr << "\nERROR: Multiple definitions for stdout format. "
                          << "Currently only one stdout stream is supported "
                          << "for test logging.\n" << std::endl;
                return -1;
            }

            // get the format to be use
            chaos::test::TestLogger::OutFormat out_format;
            chaos::str::UTF8String opt( argv[ ++i ] );
            if ( !string_to_format( opt, out_format ) )
            {
                std::cerr << "\nERROR: Unknown option: \'" << opt << "\' for "
                          << "command line argument: \'" << ARG_STDOUT << "\'. "
                          << "Available options are: plain, pretty, xml, and "
                          << "html.\n" << std::endl;
                return -1;
            }

            // get the verbosity level
            chaos::str::UTF8String verbosityString( argv[ ++i ] );
            if ( !verbosityString.is_uint() )
            {
                std::cerr << "\nERROR: Verbosity level: \'" << verbosityString
                          << "\' provided for the argument: \'" << ARG_STDOUT
                          << "\' is not a integer between 1 and 4.\n"
                          << std::endl;
                return -1;
            }
            // get as int and check range
            chaos::uint32 verbosity = verbosityString.to_uint32();
            if ( verbosity == 0 || verbosity > 4 )
            {
                std::cerr << "\nERROR: Verbosity level: \'" << verbosity
                          << "\' provided for the argument: \'" << ARG_STDOUT
                          << "\' is not a integer between 1 and 4.\n"
                          << std::endl;
                return -1;
            }

            // add to the run information
            run_info.use_stdout = true;
            run_info.stdout_info.verbosity =
                    static_cast< chaos::uint16 >( verbosity );
            run_info.stdout_info.format = out_format;
            // standard out has now been defined
            stdout_defined = true;
        }
        // --fileout
        else if ( ARG_FILEOUT == argv[ i ] )
        {
            // ensure there is another three arguments
            if ( argc - i <= 3 )
            {
                std::cerr << "\nERROR: Command line argument \'"
                          << ARG_FILEOUT << "\' must be followed by the file "
                          << "path to write to, the format to use (plain, "
                          << "pretty, xml, or html), and the verbosity level "
                          << "(1-4).\n" << std::endl;
                return -1;
            }

            // get the file to write to
            chaos::str::UTF8String file_path( argv[ ++i ] );

            // ensure the provided path is a file
            if ( file_path.get_symbol( file_path.get_length() - 1 ) == "/" ||
                 file_path.get_symbol( file_path.get_length() - 1 ) == "\\"   )
            {
                std::cerr << "\nERROR: Command line argument \'"
                          << ARG_FILEOUT << "\' has been provided with an "
                          << "invalid file path: \'" << file_path << "\' The "
                          << "provided path must not be a directory.\n"
                          << std::endl;
                return -1;
            }

            // attempt to validate the path
            try
            {
                chaos::io::file::validate_path( file_path );
            }
            catch( chaos::io::file::ex::FileSystemError e )
            {
                std::cerr << "\nERROR: validating the provided path \'"
                          << file_path << "\' has failed with the reason:\n"
                          << e.what() << "\n" << std::endl;
                return -1;
            }

            // get the format to be use
            chaos::test::TestLogger::OutFormat out_format;
            chaos::str::UTF8String opt( argv[ ++i ] );
            if ( !string_to_format( opt, out_format ) )
            {
                std::cerr << "\nERROR: Unknown option: \'" << opt << "\' for "
                          << "command line argument: \'" << ARG_FILEOUT
                          << "\'. Available options are: plain, pretty, xml, "
                          << "and html.\n" << std::endl;
                return -1;
            }

            // does the file output already exist?
            if ( run_info.files.find( file_path ) != run_info.files.end() )
            {
                std::cerr << "\nMultiple output definitions for the file: \'"
                          << file_path << "\'.\n" << std::endl;
                return -1;
            }

            // get the verbosity level
            chaos::str::UTF8String verbosityString( argv[ ++i ] );
            if ( !verbosityString.is_uint() )
            {
                std::cerr << "\nERROR: Verbosity level: \'" << verbosityString
                          << "\' provided for the argument: \'" << ARG_FILEOUT
                          << "\' is not a integer between 1 and 4.\n"
                          << std::endl;
                return -1;
            }
            // get as int and check range
            chaos::uint32 verbosity = verbosityString.to_uint32();
            if ( verbosity == 0 || verbosity > 4 )
            {
                std::cerr << "\nERROR: Verbosity level: \'" << verbosity
                          << "\' provided for the argument: \'" << ARG_FILEOUT
                          << "\' is not a integer between 1 and 4.\n"
                          << std::endl;
                return -1;
            }

            // add to run information
            run_info.files[ file_path ] =
                    new chaos::test::internal::OutInfo( verbosity, out_format );
            // if stdout hasn't be defined removed it
            if ( !stdout_defined )
            {
                run_info.use_stdout = false;
            }
        }
        // unknown argument
        else
        {
            std::cerr << "\nERROR: unknown command line argument: \'"
                      << argv[ i ] << "\'\n" << std::endl;
            return -1;
        }
    }

    chaos::test::internal::TestCore( "", NULL, "", 0, false, &run_info );
    return 0;
}

//------------------------------------------------------------------------------
//                                   FUNCTIONS
//------------------------------------------------------------------------------

bool string_to_format(
        const chaos::str::UTF8String&              str,
              chaos::test::TestLogger::OutFormat&  format )
{
    // check against know types
    if ( str == OPT_FORMAT_PLAIN )
    {
        format = chaos::test::TestLogger::OUT_PLAIN_TEXT;
        return true;
    }
    else if ( str == OPT_FORMAT_PRETTY )
    {
        format = chaos::test::TestLogger::OUT_PRETTY_TEXT;
        return true;
    }
    else if ( str == OPT_FORMAT_XML )
    {
        format = chaos::test::TestLogger::OUT_XML;
        return true;
    }
    else if ( str == OPT_FORMAT_HTML )
    {
        format = chaos::test::TestLogger::OUT_HTML;
        return true;
    }

    // not a valid string
    return false;
}
