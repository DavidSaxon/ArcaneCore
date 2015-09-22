#include "chaoscore/test/TestSuite.hpp"

#include "chaoscore/test/TestUnit.hpp"

namespace chaos
{
namespace test
{

//------------------------------------------------------------------------------
//                                  CONSTRUCTOR
//------------------------------------------------------------------------------

TestSuite::TestSuite( const chaos::str::UTF8String& name )
    :
    m_name( name )
{
}

//------------------------------------------------------------------------------
//                            PUBLIC MEMBER FUNCTIONS
//------------------------------------------------------------------------------

//------------------------------VIRTUAL FUNCTIONS-------------------------------

void TestSuite::setup()
{
    // to be overridden
}

void TestSuite::teardown()
{
    // to be overridden
}

//------------------------------------------------------------------------------

const chaos::str::UTF8String& TestSuite::getName() const
{
    return m_name;
}

//------------------------------------------------------------------------------
//                           PROTECTED MEMBER FUNCTIONS
//------------------------------------------------------------------------------

void TestSuite::registerTestUnit( TestUnit* unit )
{
    // TODO: replace with map
    // store the test
    m_units.push_back( unit );
}

} // namespace test
} // namespace chaos
