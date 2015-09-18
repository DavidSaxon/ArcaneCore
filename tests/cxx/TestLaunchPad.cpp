#include "test/LaunchPad.hpp"

int main( int argc, char* argv )
{
    chaos::test::LaunchPad launchPad(); // TODO: built in options
    launchPad.init( argc, argv );

    return launchPad.launch();
}
