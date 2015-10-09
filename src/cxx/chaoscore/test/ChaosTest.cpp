#include "chaoscore/test/ChaosTest.hpp"

#include <iostream>

//------------------------------------------------------------------------------
//                             COMMAND LINE ARGUMENTS
//------------------------------------------------------------------------------

//----------------------------COMMAND LINE ARGUMENTS----------------------------

static chaos::str::UTF8String ARG_SINGLE_PROC   = "--single_proc";
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
bool stringToFormat(
        const chaos::str::UTF8String&              str,
              chaos::test::TestLogger::OutFormat&  format );

// TODO: help

//------------------------------------------------------------------------------
//                                 MAIN FUNCTION
//------------------------------------------------------------------------------

int main( int argc, char* argv[] )
{
    // create run configuration information with default values
    chaos::test::internal::RunInfo runInfo;

    // whether a standard output has been defined
    bool stdoutDefined = false;

    // parse args
    for ( size_t i = 1; i < static_cast< size_t >( argc ); ++i )
    {
        // --single_proc
        if ( ARG_SINGLE_PROC == argv[ i ] )
        {
            runInfo.singleProc = true;
        }
        // --test
        else if ( ARG_TEST_PATH == argv[ i ] )
        {
            // ensure there is another argument
            if ( i == static_cast< size_t >( argc - 1 ) )
            {
                std::cerr << "\nERROR: Command line argument \'"
                          << ARG_TEST_PATH << "\' must be followed by a test "
                          << "path.\n" << std::endl;
                return -1;
            }

            // get the next argument
            runInfo.paths.insert( chaos::str::UTF8String( argv[ ++i ] ) );
        }
        // --stdout
        else if ( ARG_STDOUT == argv[ i ] )
        {
            // ensure there is another argument
            if ( i == static_cast< size_t >( argc - 1 ) )
            {
                std::cerr << "\nERROR: Command line argument \'"
                          << ARG_STDOUT << "\' must be followed by a format to "
                          << "use. Available formats are: plain, pretty, xml, "
                          << "and html.\n" << std::endl;
                return -1;
            }

            // ensure that stdout has not already been defined
            if ( stdoutDefined )
            {
                std::cerr << "\nERROR: Multiple definitions for stdout format. "
                          << "Currently only one stdout stream is supported "
                          << "for test logging.\n" << std::endl;
                return -1;
            }

            // get the format to be use
            chaos::test::TestLogger::OutFormat outFormat;
            chaos::str::UTF8String opt( argv[ ++i ] );
            if ( !stringToFormat( opt, outFormat ) )
            {
                std::cerr << "\nERROR: Unknown option: \'" << opt << "\' for "
                          << "command line argument: \'" << ARG_STDOUT << "\'. "
                          << "Available options are: plain, pretty, xml, and "
                          << "html.\n" << std::endl;
                return -1;
            }

            // add to the run information
            runInfo.useStdout = true;
            runInfo.stdoutFormat = outFormat;
            // standard out has now been defined
            stdoutDefined = true;
        }
        // --fileout
        else if ( ARG_FILEOUT == argv[ i ] )
        {
            // ensure there is another two arguments
            if ( i == static_cast< size_t >( argc - 1 ) )
            {
                std::cerr << "\nERROR: Command line argument \'"
                          << ARG_FILEOUT << "\' must be followed by a format to "
                          << "use. Available formats are: plain, pretty, xml, "
                          << "and html.\n" << std::endl;
                return -1;
            }

            // get the format to be use
            chaos::test::TestLogger::OutFormat outFormat;
            chaos::str::UTF8String opt( argv[ ++i ] );
            if ( !stringToFormat( opt, outFormat ) )
            {
                std::cerr << "\nERROR: Unknown option: \'" << opt << "\' for "
                          << "command line argument: \'" << ARG_FILEOUT
                          << "\'. Available options are: plain, pretty, xml, "
                          << "and html.\n" << std::endl;
                return -1;
            }

            // does the file output already exist?
            // if ( runInfo.files.find( ))

            // add to run information
            // runInfo->files[ ]
        }
        // unknown argument
        else
        {
            std::cerr << "\nERROR: unknown command line argument: \'"
                      << argv[ i ] << "\'\n" << std::endl;
            return -1;
        }
    }

    chaos::test::internal::TestCore( "", NULL, "", 0, false, &runInfo );
    return 0;
}

//------------------------------------------------------------------------------
//                                   FUNCTIONS
//------------------------------------------------------------------------------

bool stringToFormat(
        const chaos::str::UTF8String&              str,
              chaos::test::TestLogger::OutFormat&  format )
{
    // check against know types
    if ( str == OPT_FORMAT_PLAIN )
    {
        format = chaos::test::TestLogger::PLAIN_TEXT;
        return true;
    }
    else if ( str == OPT_FORMAT_PRETTY )
    {
        format = chaos::test::TestLogger::PRETTY_TEXT;
        return true;
    }
    else if ( str == OPT_FORMAT_XML )
    {
        format = chaos::test::TestLogger::XML;
        return true;
    }
    else if ( str == OPT_FORMAT_HTML )
    {
        format = chaos::test::TestLogger::HTML;
        return true;
    }

    // not a valid string
    return false;
}
