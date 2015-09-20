#include "chaoscore/test/LaunchPad.hpp"

#include "chaoscore/test/TestSuite.hpp"

namespace chaos
{
namespace test
{

//------------------------------------------------------------------------------
//                                  CONSTRUCTOR
//------------------------------------------------------------------------------

LaunchPad::LaunchPad( chaos::uint64 options )
{
}

//------------------------------------------------------------------------------
//                            PUBLIC MEMBER FUNCTIONS
//------------------------------------------------------------------------------

void LaunchPad::registerTestSuite( TestSuite* suites )
{
    m_registeredSuites.push_back( suites );
}

void LaunchPad::init( int argc, char* argv[] )
{
}

int LaunchPad::execute()
{
}

} // namespace test
} // namespace chaos
