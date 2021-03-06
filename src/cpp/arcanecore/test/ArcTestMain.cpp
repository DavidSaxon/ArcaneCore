#include <iostream>

#include "arcanecore/io/sys/FileSystemOperations.hpp"
#include "arcanecore/test/ArcTest.hpp"
#include "arcanecore/test/TestExceptions.hpp"

#ifdef ARC_OS_WINDOWS

    #include <windows.h>

#endif

namespace arc
{
namespace test
{

//------------------------------------------------------------------------------
//                             COMMAND LINE ARGUMENTS
//------------------------------------------------------------------------------

//----------------------------COMMAND LINE ARGUMENTS----------------------------

static arc::str::UTF8String ARG_SINGLE_PROC   = "--single_proc";
static arc::str::UTF8String ARG_SUB_PROC      = "--sub_proc";
static arc::str::UTF8String ARG_SILENT_CRASH  = "--silent_crash";
static arc::str::UTF8String ARG_TEST_PATH     = "--test";
static arc::str::UTF8String ARG_STDOUT        = "--stdout";
static arc::str::UTF8String ARG_FILEOUT       = "--fileout";
static arc::str::UTF8String ARG_HELP          = "--help";

//-----------------------------COMMAND LINE OPTIONS-----------------------------

static arc::str::UTF8String OPT_FORMAT_PLAIN  = "plain";
static arc::str::UTF8String OPT_FORMAT_PRETTY = "pretty";
static arc::str::UTF8String OPT_FORMAT_XML    = "xml";
static arc::str::UTF8String OPT_FORMAT_HTML   = "html";

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
        const arc::str::UTF8String& str,
        arc::test::TestLogger::OutFormat& format);

/*!
 * \brief Prints usage information.
 */
void usage();

//------------------------------------------------------------------------------
//                                 MAIN FUNCTION
//------------------------------------------------------------------------------

int deferred_main(int argc, char* argv[])
{
    // create run configuration information with default values
    arc::test::internal::RunInfo run_info;

    // whether a standard output has been defined
    bool stdout_defined = false;

    // parse args
    for(std::size_t i = 1; i < static_cast<std::size_t>(argc); ++i)
    {
        // --single_proc
        if(ARG_SINGLE_PROC == argv[i])
        {
            run_info.single_proc = true;
        }
        // --sub_proc
        else if(ARG_SUB_PROC == argv[i])
        {
            // ensure there is another argument
            if(argc - i <= 1)
            {
                std::cerr << "\nERROR: Command line argument \'"
                          << ARG_SINGLE_PROC << "must be followed by the "
                          << "parent process's testing id.\n" << std::endl;
                return -1;
            }

            run_info.sub_proc = true;
            run_info.id = arc::str::UTF8String(argv[++i]);
        }
        // --silent_crash
        else if(ARG_SILENT_CRASH == argv[i])
        {
            #ifdef ARC_OS_WINDOWS

                // we don't want show a dialog box when this crashes
                SetErrorMode(SEM_FAILCRITICALERRORS | SEM_NOGPFAULTERRORBOX);
                _set_abort_behavior(0, _WRITE_ABORT_MSG);

            #else

                arc::str::UTF8String error_message(ARG_SILENT_CRASH);
                error_message << ARG_SILENT_CRASH
                              << " only supported on Windows systems.";
                throw arc::test::ex::TestRuntimeError(error_message);

            #endif
        }
        // --test
        else if(ARG_TEST_PATH == argv[i])
        {
            // ensure there is another argument
            if(argc - i <= 1)
            {
                std::cerr << "\nERROR: Command line argument \'"
                          << ARG_TEST_PATH << "\' must be followed by a test "
                          << "path.\n" << std::endl;
                return -1;
            }

            // get the next argument
            run_info.paths.insert(arc::str::UTF8String(argv[++i]));
        }
        // --stdout
        else if(ARG_STDOUT == argv[i])
        {
            // ensure there is another two arguments
            if(argc - i <= 2)
            {
                std::cerr << "\nERROR: Command line argument \'"
                          << ARG_STDOUT << "\' must be followed by the format "
                          << "to use (plain, pretty, xml, or html) and the "
                          << "verbosity level (1-4).\n" << std::endl;
                return -1;
            }

            // ensure that stdout has not already been defined
            if(stdout_defined)
            {
                std::cerr << "\nERROR: Multiple definitions for stdout format. "
                          << "Currently only one stdout stream is supported "
                          << "for test logging.\n" << std::endl;
                return -1;
            }

            // get the format to be use
            arc::test::TestLogger::OutFormat out_format;
            arc::str::UTF8String opt(argv[++i]);
            if(!string_to_format(opt, out_format))
            {
                std::cerr << "\nERROR: Unknown option: \'" << opt << "\' for "
                          << "command line argument: \'" << ARG_STDOUT << "\'. "
                          << "Available options are: plain, pretty, xml, and "
                          << "html.\n" << std::endl;
                return -1;
            }

            // get the verbosity level
            arc::str::UTF8String verbosityString(argv[++i]);
            if(!verbosityString.is_uint())
            {
                std::cerr << "\nERROR: Verbosity level: \'" << verbosityString
                          << "\' provided for the argument: \'" << ARG_STDOUT
                          << "\' is not a integer between 1 and 4.\n"
                          << std::endl;
                return -1;
            }
            // get as int and check range
            arc::uint32 verbosity = verbosityString.to_uint32();
            if(verbosity == 0 || verbosity > 4)
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
                    static_cast< arc::uint16 >(verbosity);
            run_info.stdout_info.format = out_format;
            // standard out has now been defined
            stdout_defined = true;
        }
        // --fileout
        else if(ARG_FILEOUT == argv[i])
        {
            // ensure there is another three arguments
            if(argc - i <= 3)
            {
                std::cerr << "\nERROR: Command line argument \'"
                          << ARG_FILEOUT << "\' must be followed by the file "
                          << "path to write to, the format to use (plain, "
                          << "pretty, xml, or html), and the verbosity level "
                          << "(1-4).\n" << std::endl;
                return -1;
            }

            // get provided path to write to
            arc::str::UTF8String path_arg(argv[++i]);
            // ensure the provided path is a file path
            if(path_arg.get_symbol(path_arg.get_length() - 1) == "/" ||
                 path_arg.get_symbol(path_arg.get_length() - 1) == "\\"  )
            {
                std::cerr << "\nERROR: Command line argument \'"
                          << ARG_FILEOUT << "\' has been provided with an "
                          << "invalid file path: \'" << path_arg << "\' The "
                          << "provided path must not be a directory.\n"
                          << std::endl;
                return -1;
            }

            // create as a path
            arc::io::sys::Path file_path(path_arg);
            // attempt to validate the path
            try
            {
                arc::io::sys::validate(file_path);
            }
            catch(const arc::ex::ArcException& e)
            {
                std::cerr << "\nERROR: validating the provided file output "
                          "path: \'" << file_path << "\' has failed with the "
                          << "reason:\n" << e.what() << "\n" << std::endl;
                return -1;
            }
            // does the path already exists but is not a regular file?
            if(arc::io::sys::exists(file_path) &&
               !arc::io::sys::is_file(file_path))
            {
                std::cerr << "\nERROR: The provided output file path: \'"
                          << file_path << "\' cannot be written to because it "
                          << "already exists but is not a fle." << std::endl;
                return -1;
            }

            // get the format to be use
            arc::test::TestLogger::OutFormat out_format;
            arc::str::UTF8String opt(argv[++i]);
            if(!string_to_format(opt, out_format))
            {
                std::cerr << "\nERROR: Unknown option: \'" << opt << "\' for "
                          << "command line argument: \'" << ARG_FILEOUT
                          << "\'. Available options are: plain, pretty, xml, "
                          << "and html.\n" << std::endl;
                return -1;
            }

            // does the file output already exist?
            if(run_info.files.find(file_path.to_native()) !=
                run_info.files.end())
            {
                std::cerr << "\nMultiple output definitions for the file: \'"
                          << file_path << "\'.\n" << std::endl;
                return -1;
            }

            // get the verbosity level
            arc::str::UTF8String verbosityString(argv[++i]);
            if(!verbosityString.is_uint())
            {
                std::cerr << "\nERROR: Verbosity level: \'" << verbosityString
                          << "\' provided for the argument: \'" << ARG_FILEOUT
                          << "\' is not a integer between 1 and 4.\n"
                          << std::endl;
                return -1;
            }
            // get as int and check range
            arc::uint32 verbosity = verbosityString.to_uint32();
            if(verbosity == 0 || verbosity > 4)
            {
                std::cerr << "\nERROR: Verbosity level: \'" << verbosity
                          << "\' provided for the argument: \'" << ARG_FILEOUT
                          << "\' is not a integer between 1 and 4.\n"
                          << std::endl;
                return -1;
            }

            // add to run information
            run_info.files[file_path.to_native()] =
                    new arc::test::internal::OutInfo(verbosity, out_format);
            // if stdout hasn't be defined removed it
            if(!stdout_defined)
            {
                run_info.use_stdout = false;
            }
        }
        // --help
        else if(ARG_HELP == argv[i])
        {
            usage();
            return 0;
        }
        // unknown argument
        else
        {
            std::cerr << "\nERROR: unknown command line argument: \'"
                      << argv[i] << "\'. Use \'" << ARG_HELP << "\' for "
                      << "usage information.\n" << std::endl;
            return -1;
        }
    }

    try
    {
        arc::test::internal::TestCore("", NULL, "", 0, false, &run_info);
    }
    catch (const arc::ex::IOError& e)
    {
        std::cerr << "\nERROR: Invalid test path supplied: \'"
                  << e.get_message() << "\'\n" << std::endl;
        return -1;
    }
    return 0;
}

//------------------------------------------------------------------------------
//                                   FUNCTIONS
//------------------------------------------------------------------------------

bool string_to_format(
        const arc::str::UTF8String&              str,
              arc::test::TestLogger::OutFormat&  format)
{
    // check against know types
    if(str == OPT_FORMAT_PLAIN)
    {
        format = arc::test::TestLogger::OUT_PLAIN_TEXT;
        return true;
    }
    else if(str == OPT_FORMAT_PRETTY)
    {
        format = arc::test::TestLogger::OUT_PRETTY_TEXT;
        return true;
    }
    else if(str == OPT_FORMAT_XML)
    {
        format = arc::test::TestLogger::OUT_XML;
        return true;
    }
    else if(str == OPT_FORMAT_HTML)
    {
        format = arc::test::TestLogger::OUT_HTML;
        return true;
    }

    // not a valid string
    return false;
}

void usage()
{
std::cout << "\n" <<
"ArcaneCore Testing Runtime Usage:"
<< "\n" << "\n" <<
"  --test [path]                             : Runs all unit test that are"
<< "\n" <<
"                                              submodules of this path or the"
<< "\n" <<
"                                              unit test that exactly matches"
<< "\n" <<
"                                              this path."
<< "\n" << "\n" <<
"  --single_proc                             : Runs all tests using a single"
<< "\n" <<
"                                              process. This means if a unit"
<< "\n" <<
"                                              encounters a critical crash, no"
<< "\n" <<
"                                              further unit tests will be run"
<< "\n" <<
"                                              and reports will be left"
<< "\n" <<
"                                              incomplete."
<< "\n" << "\n" <<
"  --stdout [format] [verbosity]             : Defines the std output "
<< "\n" <<
"                                              logging information. Available "
<< "\n" <<
"                                              formats: plain, pretty, xml,"
<< "\n" <<
"                                              or html. Verbosity: a number"
<< "\n" <<
"                                              between 1 and 4. Only one set of"
<< "\n" <<
"                                              std output logging information"
<< "\n" <<
"                                              may be defined. If neither"
<< "\n" <<
"                                              --stdout or --fileout arguments"
<< "\n" <<
"                                              are provided a default std"
<< "\n" <<
"                                              output logger is used with"
<< "\n" <<
"                                              format: pretty and verbosity: 3."
<< "\n" << "\n" <<
"  --fileout [filepath] [format] [verbosity] : Defines a set of file output"
<< "\n" <<
"                                              logging information. A valid"
<< "\n" <<
"                                              filepath must be provided to"
<< "\n" <<
"                                              write the logging data to."
<< "\n" <<
"                                              Available formats: plain,"
<< "\n" <<
"                                              pretty, xml, or html. Verbosity:"
<< "\n" <<
"                                              a number between 1 and 4."
<< "\n" << "\n" <<
"  --help                                    : Shows this information."
<< "\n" << std::endl;
}

} // namespace test
} // namespace arc
