#include "chaoscore/test/TestSuite.hpp"

namespace chaos
{
namespace test
{

//------------------------------------------------------------------------------
//                                  CONSTRUCTOR
//------------------------------------------------------------------------------

TestSuite::TestSuite()
{
}

//------------------------------------------------------------------------------
//                            PUBLIC MEMBER FUNCTIONS
//------------------------------------------------------------------------------

void TestSuite::setup()
{
    // to be overridden
}

void TestSuite::teardown()
{
    // to be override
}

} // namespace test
} // namespace chaos
