#include "chaoscore/test/ChaosTest.hpp"

#include <iostream>

//------------------------------------------------------------------------------
//                             COMMAND LINE ARGUMENTS
//------------------------------------------------------------------------------

static chaos::str::UTF8String ARG_SINGLE_PROC = "--single_proc";
static chaos::str::UTF8String ARG_TEST_PATH   = "--test";


// TODO: help

//------------------------------------------------------------------------------
//                                 MAIN FUNCTION
//------------------------------------------------------------------------------

int main( int argc, char* argv[] )
{
    // create run configuration information with default values
    chaos::test::internal::RunInfo runInfo;

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
    }

    // TODO: parse other args

    chaos::test::internal::TestCore( "", NULL, "", 0, false, &runInfo );
    return 0;
}
