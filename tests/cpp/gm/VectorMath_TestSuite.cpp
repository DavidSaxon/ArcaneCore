#include "arcanecore/test/ArcTest.hpp"

ARC_TEST_MODULE(gm.VectorMath)

#include <arcanecore/gm/VectorMath.hpp>

namespace
{

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

ARC_TEST_UNIT(normalise)
{
    arc::gm::Vector3f v1(1.0F, 2.0F, 3.0F);
    arc::gm::Vector3f n1 = arc::gm::normalise(v1);

    ARC_CHECK_TRUE(arc::math::abs(n1.x() - 0.2672612419124244F) < 0.01F);
    ARC_CHECK_TRUE(arc::math::abs(n1.y() - 0.5345224838248488F) < 0.01F);
    ARC_CHECK_TRUE(arc::math::abs(n1.z() - 0.8017837257372732F) < 0.01F);
}

ARC_TEST_UNIT(dot)
{
    arc::gm::Vector3f v1(1.0F, 2.0F, 3.0F);
    arc::gm::Vector3f v2(5.0F, 6.0F, 7.0F);
    ARC_CHECK_FLOAT_EQUAL(
        arc::gm::dot(v1, v2),
        38.0F
    );

    arc::gm::Vector4f v3(1.0F, 2.0F, -3.0F, 8.0F);
    arc::gm::Vector4f v4(5.0F, -6.0F, 7.0F, 8.0F);
    ARC_CHECK_FLOAT_EQUAL(
        arc::gm::dot(v3, v4),
        36.0F
    );

    //--------------------------------------------------------------------------
    ARC_TEST_MESSAGE("Testing Simd");

    arc::gm::SimdVector3f s1(1.0F, 2.0F, 3.0F);
    arc::gm::SimdVector3f s2(5.0F, 6.0F, 7.0F);

    ARC_CHECK_FLOAT_EQUAL(
        arc::gm::dot(s1, s2),
        38.0F
    );

    arc::gm::SimdVector4f s3(1.0F, 2.0F, -3.0F, 8.0F);
    arc::gm::SimdVector4f s4(5.0F, -6.0F, 7.0F, 8.0F);
    ARC_CHECK_FLOAT_EQUAL(
        arc::gm::dot(s3, s4),
        36.0F
    );
}

ARC_TEST_UNIT(cross)
{
    arc::gm::Vector3f v1(5.0F, 1.0F, 3.0F);
    arc::gm::Vector3f v2(4.0F, 0.0F, 11.0F);

    ARC_CHECK_EQUAL(
        arc::gm::cross(v1, v2),
        arc::gm::Vector3f(11.0F, -43.0F, -4.0F)
    );

    //--------------------------------------------------------------------------
    ARC_TEST_MESSAGE("Testing Simd");

    arc::gm::SimdVector3f s1(5.0F, 1.0F, 3.0F);
    arc::gm::SimdVector3f s2(4.0F, 0.0F, 11.0F);

    ARC_CHECK_EQUAL(
        arc::gm::cross(s1, s2),
        arc::gm::SimdVector3f(11.0F, -43.0F, -4.0F)
    );
}

ARC_TEST_UNIT(magnitude2)
{
    arc::gm::SimdVector3f v1(1.0F, 2.0F, 3.0F);
    ARC_CHECK_FLOAT_EQUAL(arc::gm::magnitude2(v1), 14.0F);
}

ARC_TEST_UNIT(magnitude)
{
    arc::gm::SimdVector4f v1(2.0F);
    ARC_CHECK_FLOAT_EQUAL(arc::gm::magnitude(v1), 4.0F);
}

ARC_TEST_UNIT(distance)
{
    arc::gm::Vector3f v1(1.0F, 2.0F, 3.0F);
    arc::gm::Vector3f v2(4.0F, 5.0F, 6.0F);

    ARC_CHECK_FLOAT_EQUAL(arc::gm::distance(v1, v2), 5.19615F);
}

ARC_TEST_UNIT(direction)
{
    arc::gm::Vector3f v1(0.0F, 0.0F, 0.0F);
    arc::gm::Vector3f v2(1.0F, 0.0F, 0.0F);

    ARC_CHECK_EQUAL(
        arc::gm::direction(v1, v2),
        arc::gm::Vector3f(1.0F, 0.0F, 0.0F)
    );

    ARC_CHECK_EQUAL(
        arc::gm::direction(v2, v1),
        arc::gm::Vector3f(-1.0F, 0.0F, 0.0F)
    );
}

ARC_TEST_UNIT(angle2)
{
    arc::gm::Vector3f v1(0.0F, 0.0F, 0.0F);
    arc::gm::Vector3f v2(1.0F, 0.0F, 0.0F);
    arc::gm::Vector3f v3(0.0F, 1.0F, 0.0F);
    arc::gm::Vector3f v4(0.0F, -1.0F, 0.0F);

    ARC_CHECK_FLOAT_EQUAL(arc::gm::angle2(v1, v2), 0.0F);
    ARC_CHECK_FLOAT_EQUAL(arc::gm::angle2(v2, v1), 3.14159265359F);
    ARC_CHECK_FLOAT_EQUAL(arc::gm::angle2(v1, v3), 1.57079632679F);
    ARC_CHECK_FLOAT_EQUAL(arc::gm::angle2(v1, v4), -1.57079632679F);
}

} // namespace anonymous
