#include "chaoscore/test/TestUnit.hpp"

namespace chaos
{
namespace test
{

//------------------------------------------------------------------------------
//                                  CONSTRUCTOR
//------------------------------------------------------------------------------

TestUnit::TestUnit( const std::string& name )
    :
    m_name( name )
{
}

//------------------------------------------------------------------------------
//                            PUBLIC MEMBER FUNCTIONS
//------------------------------------------------------------------------------

//------------------------------VIRTUAL FUNCTIONS-------------------------------

void TestUnit::setup()
{
    // to be overridden
}

void TestUnit::teardown()
{
    // to be overridden
}

//------------------------------------------------------------------------------

const std::string& TestUnit::getName() const
{
    return m_name;
}

} // namespace test
} // namespace chaos
