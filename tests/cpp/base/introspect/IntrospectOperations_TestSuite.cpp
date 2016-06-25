#include "arcanecore/test/ArcTest.hpp"

ARC_TEST_MODULE(base.introspect.IntrospectOperations)

#include "arcanecore/base/introspect/IntrospectOperations.hpp"

namespace
{

ARC_TEST_UNIT(intro_test)
{
    // not really a proper test, since this is compiler specific and should only
    // be used for reporting
    ARC_CHECK_EQUAL(arc::introspect::get_typename<int>(), "int");
}

} // namespace anonymous
