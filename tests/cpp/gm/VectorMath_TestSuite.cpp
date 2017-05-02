#include "arcanecore/test/ArcTest.hpp"

ARC_TEST_MODULE(gm.VectorMath)

#include <arcanecore/gm/VectorMath.hpp>

namespace
{

ARC_TEST_UNIT(swizzle2)
{
    arc::gm::Vector4f v1(1.0F, 2.0F, 3.0F, 4.0F);
    ARC_CHECK_EQUAL(
        (arc::gm::swizzle2<3, 1>(v1)),
        arc::gm::Vector2f(4.0F, 2.0F)
    );
}

ARC_TEST_UNIT(swizzle3)
{
    arc::gm::Vector4f v1(1.0F, 2.0F, 3.0F, 4.0F);
    ARC_CHECK_EQUAL(
        (arc::gm::swizzle3<0, 3, 2>(v1)),
        arc::gm::Vector3f(1.0F, 4.0F, 3.0F)
    );

    //--------------------------------------------------------------------------
    ARC_TEST_MESSAGE("Testing Simd");
    arc::gm::SimdVector4f s1(1.0F, 2.0F, 3.0F, 4.0F);
    ARC_CHECK_EQUAL(
        (arc::gm::swizzle3<0, 3, 2>(s1)),
        arc::gm::SimdVector3f(1.0F, 4.0F, 3.0F)
    );
}

ARC_TEST_UNIT(abs)
{
    arc::gm::Vector4i v1(1, 2, -3, 4);
    arc::gm::Vector4i v2(6, 3, 20, -12);

    ARC_CHECK_EQUAL(arc::gm::abs(v1), arc::gm::Vector4i(1, 2, 3, 4));
    ARC_CHECK_EQUAL(arc::gm::abs(v2), arc::gm::Vector4i(6, 3, 20, 12));
}

ARC_TEST_UNIT(min)
{
    arc::gm::Vector4i v1(1, 6, -3, 4);
    arc::gm::Vector4i v2(6, 3, 20, -12);

    ARC_CHECK_EQUAL(arc::gm::min(v1, v2), arc::gm::Vector4i(1, 3, -3, -12));
}

ARC_TEST_UNIT(max)
{
    arc::gm::Vector4i v1(1, 6, -3, -30);
    arc::gm::Vector4i v2(6, 3, 20, -12);

    ARC_CHECK_EQUAL(arc::gm::max(v1, v2), arc::gm::Vector4i(6, 6, 20, -12));
}

ARC_TEST_UNIT(clamp_above_scalar)
{
    arc::gm::Vector4i v1(1, 6, -3, -30);

    ARC_CHECK_EQUAL(
        arc::gm::clamp_above(v1, 1),
        arc::gm::Vector4i(1, 6, 1, 1)
    );
}

ARC_TEST_UNIT(clamp_above_vector)
{
    arc::gm::Vector4i v1(1, 6, 4, -30);
    arc::gm::Vector4i v2(5, 6, -3, -40);

    ARC_CHECK_EQUAL(
        arc::gm::clamp_above(v1, v2),
        arc::gm::Vector4i(5, 6, 4, -30)
    );
}

ARC_TEST_UNIT(clamp_below_scalar)
{
    arc::gm::Vector4i v1(1, 6, -3, -30);

    ARC_CHECK_EQUAL(
        arc::gm::clamp_below(v1, 1),
        arc::gm::Vector4i(1, 1, -3, -30)
    );
}

ARC_TEST_UNIT(clamp_below_vector)
{
    arc::gm::Vector4i v1(1, 6, 4, -30);
    arc::gm::Vector4i v2(5, 6, -3, -40);

    ARC_CHECK_EQUAL(
        arc::gm::clamp_below(v1, v2),
        arc::gm::Vector4i(1, 6, -3, -40)
    );
}

ARC_TEST_UNIT(clamp_scalar)
{
    arc::gm::Vector4i v1(1, 6, -3, -30);

    ARC_CHECK_EQUAL(
        arc::gm::clamp(v1, -3, 1),
        arc::gm::Vector4i(1, 1, -3, -3)
    );
}

ARC_TEST_UNIT(clamp_vector)
{
    arc::gm::Vector4i v1( 1, 6,  4, -30);
    arc::gm::Vector4i v2(-2, 6,  5, -80);
    arc::gm::Vector4i v3( 5, 6, 10, -40);

    ARC_CHECK_EQUAL(
        arc::gm::clamp(v1, v2, v3),
        arc::gm::Vector4i(1, 6, 5, -40)
    );
}


} // namespace anonymous
