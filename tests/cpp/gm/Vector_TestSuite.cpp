#include "arcanecore/test/ArcTest.hpp"

ARC_TEST_MODULE(gm.Vector)

#include <arcanecore/gm/Vector.hpp>

namespace
{

ARC_TEST_UNIT(scalar_addition)
{
    arc::gm::Vector3f v1(1.0F, 2.0F, 3.0F);
    arc::gm::Vector3f r1(2.0F, 4.0F, 6.0F);
    ARC_CHECK_EQUAL(v1 + v1, r1);
    arc::gm::Vector4f v2(1.0F, 2.0F, 3.0F, -4.0F);
    arc::gm::Vector4f r2(2.0F, 4.0F, 6.0F, -8.0F);
    ARC_CHECK_EQUAL(v2 + v2, r2);

    v1 += v1;
    ARC_CHECK_EQUAL(v1, r1);
    v2 += v2;
    ARC_CHECK_EQUAL(v2, r2);

    //--------------------------------------------------------------------------
    ARC_TEST_MESSAGE("Testing SIMD");

    arc::gm::SimdVector3f s1(1.0F, 2.0F, 3.0F);
    arc::gm::SimdVector3f sr1(2.0F, 4.0F, 6.0F);
    ARC_CHECK_EQUAL(s1 + s1, sr1);

    arc::gm::Vector4f s2(1.0F, 2.0F, 3.0F, -4.0F);
    arc::gm::SimdVector4f sr2(2.0F, 4.0F, 6.0F, -8.0F);
    ARC_CHECK_EQUAL(s2 + s2, sr2);

    s1 += s1;
    ARC_CHECK_EQUAL(s1, sr1);
    s2 += s2;
    ARC_CHECK_EQUAL(s2, sr2);
}

} // namespace anonymous
