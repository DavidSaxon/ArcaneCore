#include "arcanecore/test/ArcTest.hpp"

ARC_TEST_MODULE(gm.VectorMath)

#include <arcanecore/gm/VectorMath.hpp>

namespace
{

ARC_TEST_UNIT(cast)
{
    arc::gm::Vector4f v1(1.0F, 2.0F, -3.0F, 4.0F);
    ARC_CHECK_EQUAL(arc::gm::cast<int32_t>(v1), arc::gm::Vector4i(1, 2, -3, 4));

    arc::gm::Vector2u v2(4, 17);
    ARC_CHECK_EQUAL(arc::gm::cast<float>(v2), arc::gm::Vector2f(4.0F, 17.0F));
}

ARC_TEST_UNIT(abs)
{
    arc::gm::Vector4i v1(1, 2, -3, 4);
    arc::gm::Vector4i v2(6, 3, 20, -12);

    ARC_CHECK_EQUAL(arc::gm::abs(v1), arc::gm::Vector4i(1, 2, 3, 4));
    ARC_CHECK_EQUAL(arc::gm::abs(v2), arc::gm::Vector4i(6, 3, 20, 12));

    //--------------------------------------------------------------------------
    ARC_TEST_MESSAGE("Testing Simd");

    arc::gm::SimdVector4f s1(1, 2, -3, 4);
    arc::gm::SimdVector4f s2(6, 3, 20, -12);

    ARC_CHECK_EQUAL(arc::gm::abs(s1), arc::gm::SimdVector4f(1, 2, 3, 4));
    ARC_CHECK_EQUAL(arc::gm::abs(s2), arc::gm::SimdVector4f(6, 3, 20, 12));
}

ARC_TEST_UNIT(min)
{
    arc::gm::Vector4i v1(1, 6, -3, 4);
    arc::gm::Vector4i v2(6, 3, 20, -12);

    ARC_CHECK_EQUAL(arc::gm::min(v1, v2), arc::gm::Vector4i(1, 3, -3, -12));

    //--------------------------------------------------------------------------
    ARC_TEST_MESSAGE("Testing Simd");

    arc::gm::SimdVector3f s1(1.0F, 6.0F, -3.0F);
    arc::gm::SimdVector3f s2(6.0F, 3.0F, 20.0F);

    ARC_CHECK_EQUAL(
        arc::gm::min(s1, s2),
        arc::gm::SimdVector3f(1.0F, 3.0F, -3.0F)
    );
}

ARC_TEST_UNIT(max)
{
    arc::gm::Vector4i v1(1, 6, -3, -30);
    arc::gm::Vector4i v2(6, 3, 20, -12);

    ARC_CHECK_EQUAL(arc::gm::max(v1, v2), arc::gm::Vector4i(6, 6, 20, -12));

    //--------------------------------------------------------------------------
    ARC_TEST_MESSAGE("Testing Simd");

    arc::gm::SimdVector3f s1(1.0F, -3.0F, -30.0F);
    arc::gm::SimdVector3f s2(6.0F, 20.0F, -12.0F);

    ARC_CHECK_EQUAL(
        arc::gm::max(s1, s2),
        arc::gm::SimdVector3f(6.0F, 20, -12.0F)
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

    //--------------------------------------------------------------------------
    ARC_TEST_MESSAGE("Testing Simd");

    arc::gm::Vector4f s1( 1.0F, 6.0F,  4.0F, -30.0F);
    arc::gm::Vector4f s2(-2.0F, 6.0F,  5.0F, -80.0F);
    arc::gm::Vector4f s3( 5.0F, 6.0F, 10.0F, -40.0F);

    ARC_CHECK_EQUAL(
        arc::gm::clamp(s1, s2, s3),
        arc::gm::Vector4f(1.0F, 6.0F, 5.0F, -40.0F)
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

ARC_TEST_UNIT(log)
{
    arc::gm::Vector3f v1(1.0F, 2.0F, 3.0F);
    arc::gm::Vector3f r1(arc::gm::log(v1));

    ARC_CHECK_TRUE(arc::math::abs(r1.x() - 0.0F) < 0.01F);
    ARC_CHECK_TRUE(arc::math::abs(r1.y() - 0.6931471805599453F) < 0.01F);
    ARC_CHECK_TRUE(arc::math::abs(r1.z() - 1.0986122886681096F) < 0.01F);

    //--------------------------------------------------------------------------
    ARC_TEST_MESSAGE("Testing Simd");

    arc::gm::SimdVector3f s1(1.0F, 2.0F, 3.0F);
    arc::gm::SimdVector3f rs1(arc::gm::log(s1));

    ARC_CHECK_TRUE(arc::math::abs(rs1.x() - 0.0F) < 0.01F);
    ARC_CHECK_TRUE(arc::math::abs(rs1.y() - 0.6931471805599453F) < 0.01F);
    ARC_CHECK_TRUE(arc::math::abs(rs1.z() - 1.0986122886681096F) < 0.01F);

    arc::gm::SimdVector4f s2(1.0F, 2.0F, 3.0F, 2.0F);
    arc::gm::SimdVector4f rs2(arc::gm::log(s2));

    ARC_CHECK_TRUE(arc::math::abs(rs2.x() - 0.0F) < 0.01F);
    ARC_CHECK_TRUE(arc::math::abs(rs2.y() - 0.6931471805599453F) < 0.01F);
    ARC_CHECK_TRUE(arc::math::abs(rs2.z() - 1.0986122886681096F) < 0.01F);
    ARC_CHECK_TRUE(arc::math::abs(rs2.w() - 0.6931471805599453F) < 0.01F);
}

ARC_TEST_UNIT(log2)
{
    arc::gm::Vector3f v1(1.0F, 2.0F, 3.0F);
    arc::gm::Vector3f r1(arc::gm::log2(v1));

    ARC_CHECK_TRUE(arc::math::abs(r1.x() - 0.0F) < 0.01F);
    ARC_CHECK_TRUE(arc::math::abs(r1.y() - 1.0F) < 0.01F);
    ARC_CHECK_TRUE(arc::math::abs(r1.z() - 1.5849625007211561F) < 0.01F);


    //--------------------------------------------------------------------------
    ARC_TEST_MESSAGE("Testing Simd");

    arc::gm::SimdVector3f s1(1.0F, 2.0F, 3.0F);
    arc::gm::SimdVector3f rs1(arc::gm::log2(s1));

    ARC_CHECK_TRUE(arc::math::abs(rs1.x() - 0.0F) < 0.01F);
    ARC_CHECK_TRUE(arc::math::abs(rs1.y() - 1.0F) < 0.01F);
    ARC_CHECK_TRUE(arc::math::abs(rs1.z() - 1.5849625007211561F) < 0.01F);

    arc::gm::SimdVector4f s2(1.0F, 2.0F, 3.0F, 2.0F);
    arc::gm::SimdVector4f rs2(arc::gm::log2(s2));

    ARC_CHECK_TRUE(arc::math::abs(rs2.x() - 0.0F) < 0.01F);
    ARC_CHECK_TRUE(arc::math::abs(rs2.y() - 1.0F) < 0.01F);
    ARC_CHECK_TRUE(arc::math::abs(rs2.z() - 1.5849625007211561F) < 0.01F);
    ARC_CHECK_TRUE(arc::math::abs(rs2.w() - 1.0F) < 0.01F);
}

ARC_TEST_UNIT(exp)
{
    arc::gm::Vector3f v1(1.0F, 2.0F, 3.0F);
    arc::gm::Vector3f r1(arc::gm::exp(v1));

    ARC_CHECK_TRUE(arc::math::abs(r1.x() - 2.7182818284590452F) < 0.01F);
    ARC_CHECK_TRUE(arc::math::abs(r1.y() - 7.3890560989306502F) < 0.01F);
    ARC_CHECK_TRUE(arc::math::abs(r1.z() - 20.0855369231876677F) < 0.01F);

    //--------------------------------------------------------------------------
    ARC_TEST_MESSAGE("Testing Simd");

    arc::gm::SimdVector3f s1(1.0F, 2.0F, 3.0F);
    arc::gm::SimdVector3f rs1(arc::gm::exp(s1));

    ARC_CHECK_TRUE(arc::math::abs(rs1.x() - 2.7182818284590452F) < 0.01F);
    ARC_CHECK_TRUE(arc::math::abs(rs1.y() - 7.3890560989306502F) < 0.01F);
    ARC_CHECK_TRUE(arc::math::abs(rs1.z() - 20.0855369231876677F) < 0.01F);

    arc::gm::SimdVector4f s2(1.0F, 2.0F, 3.0F, 2.0F);
    arc::gm::SimdVector4f rs2(arc::gm::exp(s2));


    ARC_CHECK_TRUE(arc::math::abs(rs2.x() - 2.7182818284590452F) < 0.01F);
    ARC_CHECK_TRUE(arc::math::abs(rs2.y() - 7.3890560989306502F) < 0.01F);
    ARC_CHECK_TRUE(arc::math::abs(rs2.z() - 20.0855369231876677F) < 0.01F);
    ARC_CHECK_TRUE(arc::math::abs(rs2.w() - 7.3890560989306502F) < 0.01F);
}

} // namespace anonymous
