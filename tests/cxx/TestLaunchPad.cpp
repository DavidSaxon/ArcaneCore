#include "chaoscore/test/LaunchPad.hpp"

#include "test_suites/base/PreProc_TestSuite.hpp"

int main( int argc, char* argv[] )
{
    chaos::test::LaunchPad launchPad; // TODO: built in options

    // register test suites
    launchPad.registerTestSuite( new PreProc_TestSuite() );

    launchPad.init( argc, argv );
    return launchPad.execute();
}
