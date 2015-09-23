#include "chaoscore/test/LaunchPad.hpp"

#include "chaoscore/test/TestSuite.hpp"
#include "chaoscore/test/__TestServices.hpp"

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
//                                   DESTRUCTOR
//------------------------------------------------------------------------------

LaunchPad::~LaunchPad()
{
    // delete the registered suites
    CHAOS_FOREACH( suiteIt, m_registeredSuites )
    {
        delete suiteIt->second;
    }
    m_registeredSuites.clear();
}

//------------------------------------------------------------------------------
//                            PUBLIC MEMBER FUNCTIONS
//------------------------------------------------------------------------------

void LaunchPad::registerTestSuite( TestSuite* suite )
{
    // get the name of the suite
    chaos::str::UTF8String suiteName( suite->getName() );
    const chaos::int8* raw = suiteName.getRawData();
    raw = new chaos::int8[ 78 ];
    // validate the suite
    service::validateInputTest( suiteName, m_registeredSuites );
    // // register the suite
    // suite->registerTestUnits();
    // // store it
    // m_registeredSuites[ suiteName ] = suite;
}

void LaunchPad::init( int argc, char* argv[] )
{
}

int LaunchPad::execute()
{
}

} // namespace test
} // namespace chaos
