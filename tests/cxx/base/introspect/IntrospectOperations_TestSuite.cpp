#include "chaoscore/test/ChaosTest.hpp"

CHAOS_TEST_MODULE(base.introspect.IntrospectOperations)

#include "chaoscore/base/introspect/IntrospectOperations.hpp"

namespace
{

CHAOS_TEST_UNIT(intro_test)
{
    // not really a proper test, since this is compiler specific and should only
    // be used for reporting
    CHAOS_CHECK_EQUAL(chaos::introspect::get_typename<int>(), "int");
}

} // namespace anonymous
