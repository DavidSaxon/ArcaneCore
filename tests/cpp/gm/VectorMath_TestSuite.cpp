#include "arcanecore/test/ArcTest.hpp"

ARC_TEST_MODULE(gm.VectorMath)

#include <arcanecore/gm/VectorMath.hpp>

namespace
{

//------------------------------------------------------------------------------
//                                      CAST
//------------------------------------------------------------------------------

ARC_TEST_UNIT(cast)
{
    arc::gm::Vector4f v1(1.0F, 2.0F, -3.0F, 4.0F);
    ARC_CHECK_EQUAL(arc::gm::cast<int32_t>(v1), arc::gm::Vector4i(1, 2, -3, 4));

    arc::gm::Vector2u v2(4, 17);
    ARC_CHECK_EQUAL(arc::gm::cast<float>(v2), arc::gm::Vector2f(4.0F, 17.0F));
}

//------------------------------------------------------------------------------
//                                      ABS
//------------------------------------------------------------------------------

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

//------------------------------------------------------------------------------
//                                      MIN
//------------------------------------------------------------------------------

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

//------------------------------------------------------------------------------
//                                      MAX
//------------------------------------------------------------------------------

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

//------------------------------------------------------------------------------
//                                  CLAMP SCALAR
//------------------------------------------------------------------------------

ARC_TEST_UNIT(clamp_scalar)
{
    arc::gm::Vector4i v1(1, 6, -3, -30);

    ARC_CHECK_EQUAL(
        arc::gm::clamp(v1, -3, 1),
        arc::gm::Vector4i(1, 1, -3, -3)
    );
}

//------------------------------------------------------------------------------
//                                  CLAMP VECTOR
//------------------------------------------------------------------------------

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

//------------------------------------------------------------------------------
//                                     FLOOR
//------------------------------------------------------------------------------

ARC_TEST_UNIT(floor)
{
    arc::gm::Vector3f v1(1.0F, 2.9F, -3.3F);

    ARC_CHECK_EQUAL(
        arc::gm::floor(v1),
        arc::gm::Vector3f(1.0F, 2.0F, -4.0F)
    );

    //--------------------------------------------------------------------------
    ARC_TEST_MESSAGE("Testing Simd");

    arc::gm::SimdVector3f s1(1.0F, 2.9F, -3.3F);

    ARC_CHECK_EQUAL(
        arc::gm::floor(s1),
        arc::gm::SimdVector3f(1.0F, 2.0F, -4.0F)
    );

    arc::gm::SimdVector4f s2(1.0F, 2.9F, -3.3F, 88607.0F);

    ARC_CHECK_EQUAL(
        arc::gm::floor(s2),
        arc::gm::SimdVector4f(1.0F, 2.0F, -4.0F, 88607.0F)
    );
}

//------------------------------------------------------------------------------
//                                      CEIL
//------------------------------------------------------------------------------

ARC_TEST_UNIT(ceil)
{
    arc::gm::Vector3f v1(1.0F, 2.9F, -3.3F);

    ARC_CHECK_EQUAL(
        arc::gm::ceil(v1),
        arc::gm::Vector3f(1.0F, 3.0F, -3.0F)
    );

    //--------------------------------------------------------------------------
    ARC_TEST_MESSAGE("Testing Simd");

    arc::gm::SimdVector3f s1(1.0F, 2.9F, -3.3F);

    ARC_CHECK_EQUAL(
        arc::gm::ceil(s1),
        arc::gm::SimdVector3f(1.0F, 3.0F, -3.0F)
    );

    arc::gm::SimdVector4f s2(1.0F, 2.9F, -3.3F, 88607.0F);

    ARC_CHECK_EQUAL(
        arc::gm::ceil(s2),
        arc::gm::SimdVector4f(1.0F, 3.0F, -3.0F, 88607.0F)
    );
}

//------------------------------------------------------------------------------
//                                     ROUND
//------------------------------------------------------------------------------

ARC_TEST_UNIT(round)
{
    arc::gm::Vector3f v1(1.0F, 2.5F, -3.3F);

    ARC_CHECK_EQUAL(
        arc::gm::round(v1),
        arc::gm::Vector3f(1.0F, 3.0F, -3.0F)
    );

    //--------------------------------------------------------------------------
    ARC_TEST_MESSAGE("Testing Simd");

    arc::gm::SimdVector3f s1(1.0F, 2.5F, -3.3F);

    ARC_CHECK_EQUAL(
        arc::gm::round(s1),
        arc::gm::SimdVector3f(1.0F, 3.0F, -3.0F)
    );

    arc::gm::SimdVector4f s2(1.0F, 2.5F, -3.3F, 88607.0F);

    ARC_CHECK_EQUAL(
        arc::gm::round(s2),
        arc::gm::SimdVector4f(1.0F, 3.0F, -3.0F, 88607.0F)
    );
}

//------------------------------------------------------------------------------
//                                   NORMALISE
//------------------------------------------------------------------------------

ARC_TEST_UNIT(normalise)
{
    arc::gm::Vector3f v1(1.0F, 2.0F, 3.0F);
    arc::gm::Vector3f n1 = arc::gm::normalise(v1);

    ARC_CHECK_TRUE(arc::math::abs(n1.x() - 0.2672612419124244F) < 0.01F);
    ARC_CHECK_TRUE(arc::math::abs(n1.y() - 0.5345224838248488F) < 0.01F);
    ARC_CHECK_TRUE(arc::math::abs(n1.z() - 0.8017837257372732F) < 0.01F);
}

//------------------------------------------------------------------------------
//                                      DOT
//------------------------------------------------------------------------------

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

//------------------------------------------------------------------------------
//                                     CROSS
//------------------------------------------------------------------------------

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

//------------------------------------------------------------------------------
//                                   MAGNITUDE2
//------------------------------------------------------------------------------

ARC_TEST_UNIT(magnitude2)
{
    arc::gm::SimdVector3f v1(1.0F, 2.0F, 3.0F);
    ARC_CHECK_FLOAT_EQUAL(arc::gm::magnitude2(v1), 14.0F);
}

//------------------------------------------------------------------------------
//                                   MAGNITUDE
//------------------------------------------------------------------------------

ARC_TEST_UNIT(magnitude)
{
    arc::gm::SimdVector4f v1(2.0F);
    ARC_CHECK_FLOAT_EQUAL(arc::gm::magnitude(v1), 4.0F);
}

//------------------------------------------------------------------------------
//                                    DISTANCE
//------------------------------------------------------------------------------

ARC_TEST_UNIT(distance)
{
    arc::gm::Vector3f v1(1.0F, 2.0F, 3.0F);
    arc::gm::Vector3f v2(4.0F, 5.0F, 6.0F);

    ARC_CHECK_FLOAT_EQUAL(arc::gm::distance(v1, v2), 5.19615F);
}

//------------------------------------------------------------------------------
//                                   DIRECTION
//------------------------------------------------------------------------------

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

//------------------------------------------------------------------------------
//                                     ANGLE2
//------------------------------------------------------------------------------

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

//------------------------------------------------------------------------------
//                                      LOG
//------------------------------------------------------------------------------

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

//------------------------------------------------------------------------------
//                                      LOG2
//------------------------------------------------------------------------------

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

//------------------------------------------------------------------------------
//                                      EXP
//------------------------------------------------------------------------------

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

//------------------------------------------------------------------------------
//                                   POW VECTOR
//------------------------------------------------------------------------------

ARC_TEST_UNIT(pow_vector)
{
    arc::gm::Vector3f v1(5.0F, 2.0F, -23.3F);
    arc::gm::Vector3f v2(0.0F, 5.5F, 3.0F);
    arc::gm::Vector3f r1(arc::gm::pow(v1, v2));

    ARC_CHECK_TRUE(arc::math::abs(r1.x() - 1.0F) < 0.01F);
    ARC_CHECK_TRUE(arc::math::abs(r1.y() - 45.2548339959390415F) < 0.01F);
    ARC_CHECK_TRUE(arc::math::abs(r1.z() - -12649.337F) < 0.01F);

    //--------------------------------------------------------------------------
    ARC_TEST_MESSAGE("Testing Simd");

    arc::gm::SimdVector3f s1(5.0F, 2.0F, -23.3F);
    arc::gm::SimdVector3f s2(0.0F, 5.5F, 3.0F);
    arc::gm::SimdVector3f rs1(arc::gm::pow(s1, s2));

    ARC_CHECK_TRUE(arc::math::abs(rs1.x() - 1.0F) < 0.01F);
    ARC_CHECK_TRUE(arc::math::abs(rs1.y() - 45.2548339959390415F) < 0.01F);
    ARC_CHECK_TRUE(arc::math::abs(rs1.z() - -12649.337F) < 0.01F);

    arc::gm::SimdVector4f s3(5.0F, 2.0F, -23.3F, 3.0F);
    arc::gm::SimdVector4f s4(0.0F, 5.5F, 3.0F, -3.7F);
    arc::gm::SimdVector4f rs2(arc::gm::pow(s3, s4));

    ARC_CHECK_TRUE(arc::math::abs(rs2.x() - 1.0F) < 0.01F);
    ARC_CHECK_TRUE(arc::math::abs(rs2.y() - 45.2548339959390415F) < 0.01F);
    ARC_CHECK_TRUE(arc::math::abs(rs2.z() - -12649.337F) < 0.01F);
    ARC_CHECK_TRUE(arc::math::abs(rs2.w() - 0.017165298398961843F) < 0.0001F);
}

//------------------------------------------------------------------------------
//                                   POW SCALAR
//------------------------------------------------------------------------------

ARC_TEST_UNIT(pow_scalar)
{
    arc::gm::Vector3f v1(5.0F, 2.0F, -23.3F);
    arc::gm::Vector3f r1(arc::gm::pow(v1, 3.0F));

    ARC_CHECK_TRUE(arc::math::abs(r1.x() - 125.0F) < 0.01F);
    ARC_CHECK_TRUE(arc::math::abs(r1.y() - 8.0F) < 0.01F);
    ARC_CHECK_TRUE(arc::math::abs(r1.z() - -12649.337F) < 0.01F);

    //--------------------------------------------------------------------------
    ARC_TEST_MESSAGE("Testing Simd");

    arc::gm::SimdVector3f s1(5.0F, 2.0F, -23.3F);
    arc::gm::SimdVector3f rs1(arc::gm::pow(s1, 3.0F));

    ARC_CHECK_TRUE(arc::math::abs(rs1.x() - 125.0F) < 0.01F);
    ARC_CHECK_TRUE(arc::math::abs(rs1.y() - 8.0F) < 0.01F);
    ARC_CHECK_TRUE(arc::math::abs(rs1.z() - -12649.337F) < 0.01F);

    arc::gm::SimdVector4f s2(5.0F, 2.0F, -23.3F, 0.5F);
    arc::gm::SimdVector4f rs2(arc::gm::pow(s2, 3.0F));

    ARC_CHECK_TRUE(arc::math::abs(rs2.x() - 125.0F) < 0.01F);
    ARC_CHECK_TRUE(arc::math::abs(rs2.y() - 8.0F) < 0.01F);
    ARC_CHECK_TRUE(arc::math::abs(rs2.z() - -12649.337F) < 0.01F);
    ARC_CHECK_TRUE(arc::math::abs(rs2.w() - 0.125F) < 0.0001F);
}

//------------------------------------------------------------------------------
//                                POW FAST VECTOR
//------------------------------------------------------------------------------

ARC_TEST_UNIT(pow_fast_vector)
{
    arc::gm::Vector3f v1(5.0F, 2.0F, 23.3F);
    arc::gm::Vector3f v2(0.0F, 5.5F, 3.0F);
    arc::gm::Vector3f r1(arc::gm::pow_fast(v1, v2));

    ARC_CHECK_TRUE(arc::math::abs(r1.x() - 1.0F) < 0.01F);
    ARC_CHECK_TRUE(arc::math::abs(r1.y() - 45.2548339959390415F) < 0.01F);
    ARC_CHECK_TRUE(arc::math::abs(r1.z() - 12649.337F) < 0.01F);

    //--------------------------------------------------------------------------
    ARC_TEST_MESSAGE("Testing Simd");

    arc::gm::SimdVector3f s1(5.0F, 2.0F, 23.3F);
    arc::gm::SimdVector3f s2(0.0F, 5.5F, 3.0F);
    arc::gm::SimdVector3f rs1(arc::gm::pow_fast(s1, s2));

    ARC_CHECK_TRUE(arc::math::abs(rs1.x() - 1.0F) < 0.01F);
    ARC_CHECK_TRUE(arc::math::abs(rs1.y() - 45.2548339959390415F) < 0.01F);
    ARC_CHECK_TRUE(arc::math::abs(rs1.z() - 12649.337F) < 0.01F);

    arc::gm::SimdVector4f s3(5.0F, 2.0F, 23.3F, 3.0F);
    arc::gm::SimdVector4f s4(0.0F, 5.5F, 3.0F, -3.7F);
    arc::gm::SimdVector4f rs2(arc::gm::pow_fast(s3, s4));

    ARC_CHECK_TRUE(arc::math::abs(rs2.x() - 1.0F) < 0.01F);
    ARC_CHECK_TRUE(arc::math::abs(rs2.y() - 45.2548339959390415F) < 0.01F);
    ARC_CHECK_TRUE(arc::math::abs(rs2.z() - 12649.337F) < 0.01F);
    ARC_CHECK_TRUE(arc::math::abs(rs2.w() - 0.017165298398961843F) < 0.0001F);
}

//------------------------------------------------------------------------------
//                                POW FAST SCALAR
//------------------------------------------------------------------------------

ARC_TEST_UNIT(pow_fast_scalar)
{
    arc::gm::Vector3f v1(5.0F, 2.0F, 23.3F);
    arc::gm::Vector3f r1(arc::gm::pow_fast(v1, 3.0F));

    ARC_CHECK_TRUE(arc::math::abs(r1.x() - 125.0F) < 0.01F);
    ARC_CHECK_TRUE(arc::math::abs(r1.y() - 8.0F) < 0.01F);
    ARC_CHECK_TRUE(arc::math::abs(r1.z() - 12649.337F) < 0.01F);

    //--------------------------------------------------------------------------
    ARC_TEST_MESSAGE("Testing Simd");

    arc::gm::SimdVector3f s1(5.0F, 2.0F, 23.3F);
    arc::gm::SimdVector3f rs1(arc::gm::pow_fast(s1, 3.0F));

    ARC_CHECK_TRUE(arc::math::abs(rs1.x() - 125.0F) < 0.01F);
    ARC_CHECK_TRUE(arc::math::abs(rs1.y() - 8.0F) < 0.01F);
    ARC_CHECK_TRUE(arc::math::abs(rs1.z() - 12649.337F) < 0.01F);

    arc::gm::SimdVector4f s2(5.0F, 2.0F, 23.3F, 0.5F);
    arc::gm::SimdVector4f rs2(arc::gm::pow_fast(s2, 3.0F));

    ARC_CHECK_TRUE(arc::math::abs(rs2.x() - 125.0F) < 0.01F);
    ARC_CHECK_TRUE(arc::math::abs(rs2.y() - 8.0F) < 0.01F);
    ARC_CHECK_TRUE(arc::math::abs(rs2.z() - 12649.337F) < 0.01F);
    ARC_CHECK_TRUE(arc::math::abs(rs2.w() - 0.125F) < 0.0001F);
}

//------------------------------------------------------------------------------
//                                      SQRT
//------------------------------------------------------------------------------

ARC_TEST_UNIT(sqrt)
{
    arc::gm::Vector3f v1(16.0F, 16777216.0F, 7.7F);
    arc::gm::Vector3f r1(arc::gm::sqrt(v1));

    ARC_CHECK_TRUE(arc::math::abs(r1.x() - 4.0F) < 0.01F);
    ARC_CHECK_TRUE(arc::math::abs(r1.y() - 4096.0F) < 0.01F);
    ARC_CHECK_TRUE(arc::math::abs(r1.z() - 2.7748873851023215F) < 0.01F);

    //--------------------------------------------------------------------------
    ARC_TEST_MESSAGE("Testing Simd");

    arc::gm::SimdVector3f s1(16.0F, 16777216.0F, 7.7F);
    arc::gm::SimdVector3f rs1(arc::gm::sqrt(s1));

    ARC_CHECK_TRUE(arc::math::abs(rs1.x() - 4.0F) < 0.01F);
    ARC_CHECK_TRUE(arc::math::abs(rs1.y() - 4096.0F) < 0.01F);
    ARC_CHECK_TRUE(arc::math::abs(rs1.z() - 2.7748873851023215F) < 0.01F);

    arc::gm::SimdVector4f s2(16.0F, 16777216.0F, 7.7F, 16777216.0F);
    arc::gm::SimdVector4f rs2(arc::gm::sqrt(s2));

    ARC_CHECK_TRUE(arc::math::abs(rs2.x() - 4.0F) < 0.01F);
    ARC_CHECK_TRUE(arc::math::abs(rs2.y() - 4096.0F) < 0.01F);
    ARC_CHECK_TRUE(arc::math::abs(rs2.z() - 2.7748873851023215F) < 0.01F);
    ARC_CHECK_TRUE(arc::math::abs(rs2.w() - 4096.0F) < 0.01F);
}

//------------------------------------------------------------------------------
//                                     RSQRT
//------------------------------------------------------------------------------

ARC_TEST_UNIT(rsqrt)
{
    arc::gm::Vector3f v1(16.0F, 16777216.0F, 7.7F);
    arc::gm::Vector3f r1(arc::gm::rsqrt(v1));

    ARC_CHECK_TRUE(arc::math::abs(r1.x() - 0.25F) < 0.01F);
    ARC_CHECK_TRUE(arc::math::abs(r1.y() - 0.000244140625F) < 0.000001F);
    ARC_CHECK_TRUE(arc::math::abs(r1.z() - 0.360375F) < 0.01F);

    //--------------------------------------------------------------------------
    ARC_TEST_MESSAGE("Testing Simd");

    arc::gm::SimdVector3f s1(16.0F, 16777216.0F, 7.7F);
    arc::gm::SimdVector3f rs1(arc::gm::rsqrt(s1));

    ARC_CHECK_TRUE(arc::math::abs(rs1.x() - 0.25F) < 0.01F);
    ARC_CHECK_TRUE(arc::math::abs(rs1.y() - 0.000244140625F) < 0.000001F);
    ARC_CHECK_TRUE(arc::math::abs(rs1.z() - 0.360375F) < 0.01F);

    arc::gm::SimdVector4f s2(16.0F, 16777216.0F, 7.7F, 16777216.0F);
    arc::gm::SimdVector4f rs2(arc::gm::rsqrt(s2));

    ARC_CHECK_TRUE(arc::math::abs(rs1.x() - 0.25F) < 0.01F);
    ARC_CHECK_TRUE(arc::math::abs(rs1.y() - 0.000244140625F) < 0.000001F);
    ARC_CHECK_TRUE(arc::math::abs(rs1.z() - 0.360375F) < 0.01F);
    ARC_CHECK_TRUE(arc::math::abs(rs2.w() - 0.000244140625F) < 0.000001F);
}

//------------------------------------------------------------------------------
//                                      SIN
//------------------------------------------------------------------------------

ARC_TEST_UNIT(sin)
{
    arc::gm::Vector3f v1(1.0F, -0.39F, 745.7F);
    arc::gm::Vector3f r1(arc::gm::sin(v1));

    ARC_CHECK_TRUE(arc::math::abs(r1.x() -  0.841470984807F) < 0.01F);
    ARC_CHECK_TRUE(arc::math::abs(r1.y() - -0.380188415123F) < 0.000001F);
    ARC_CHECK_TRUE(arc::math::abs(r1.z() - -0.909691710435F) < 0.01F);

    //--------------------------------------------------------------------------
    ARC_TEST_MESSAGE("Testing Simd");

    arc::gm::SimdVector3f s1(1.0F, -0.39F, 745.7F);
    arc::gm::SimdVector3f rs1(arc::gm::sin(s1));

    ARC_CHECK_TRUE(arc::math::abs(rs1.x() -  0.841470984807F) < 0.01F);
    ARC_CHECK_TRUE(arc::math::abs(rs1.y() - -0.380188415123F) < 0.000001F);
    ARC_CHECK_TRUE(arc::math::abs(rs1.z() - -0.909691710435F) < 0.01F);

    arc::gm::SimdVector4f s2(1.0F, -0.39F, 745.7F, -0.39F);
    arc::gm::SimdVector4f rs2(arc::gm::sin(s2));

    ARC_CHECK_TRUE(arc::math::abs(rs2.x() -  0.841470984807F) < 0.01F);
    ARC_CHECK_TRUE(arc::math::abs(rs2.y() - -0.380188415123F) < 0.000001F);
    ARC_CHECK_TRUE(arc::math::abs(rs2.z() - -0.909691710435F) < 0.01F);
    ARC_CHECK_TRUE(arc::math::abs(rs2.w() - -0.380188415123F) < 0.000001F);
}

//------------------------------------------------------------------------------
//                                      COS
//------------------------------------------------------------------------------

ARC_TEST_UNIT(cos)
{
    arc::gm::Vector3f v1(1.0F, 0.89F, -3491.08F);
    arc::gm::Vector3f r1(arc::gm::cos(v1));

    ARC_CHECK_TRUE(arc::math::abs(r1.x() -  0.540302305868F) < 0.01F);
    ARC_CHECK_TRUE(arc::math::abs(r1.y() -  0.629412026573F) < 0.000001F);
    ARC_CHECK_TRUE(arc::math::abs(r1.z() - -0.717519424557F) < 0.01F);

    //--------------------------------------------------------------------------
    ARC_TEST_MESSAGE("Testing Simd");

    arc::gm::SimdVector3f s1(1.0F, 0.89F, -3491.08F);
    arc::gm::SimdVector3f rs1(arc::gm::cos(s1));

    ARC_CHECK_TRUE(arc::math::abs(rs1.x() -  0.540302305868F) < 0.01F);
    ARC_CHECK_TRUE(arc::math::abs(rs1.y() -  0.629412026573F) < 0.000001F);
    ARC_CHECK_TRUE(arc::math::abs(rs1.z() - -0.717519424557F) < 0.01F);

    arc::gm::SimdVector4f s2(1.0F, 0.89F, -3491.08F, 0.89F);
    arc::gm::SimdVector4f rs2(arc::gm::cos(s2));

    ARC_CHECK_TRUE(arc::math::abs(rs2.x() -  0.540302305868F) < 0.01F);
    ARC_CHECK_TRUE(arc::math::abs(rs2.y() -  0.629412026573F) < 0.000001F);
    ARC_CHECK_TRUE(arc::math::abs(rs2.z() - -0.717519424557F) < 0.01F);
    ARC_CHECK_TRUE(arc::math::abs(rs2.w() -  0.629412026573F) < 0.000001F);
}

//------------------------------------------------------------------------------
//                                     SINCOS
//------------------------------------------------------------------------------

ARC_TEST_UNIT(sincos)
{
    arc::gm::Vector3f v1(1.0F, -0.39F, 745.7F);
    arc::gm::Vector3f r1_sin;
    arc::gm::Vector3f r1_cos;
    arc::gm::sincos(v1, r1_sin, r1_cos);

    ARC_CHECK_TRUE(arc::math::abs(r1_sin.x() -  0.841470984807F) < 0.01F);
    ARC_CHECK_TRUE(arc::math::abs(r1_sin.y() - -0.380188415123F) < 0.000001F);
    ARC_CHECK_TRUE(arc::math::abs(r1_sin.z() - -0.909691710435F) < 0.01F);

    ARC_CHECK_TRUE(arc::math::abs(r1_cos.x() -  0.540302305868F) < 0.01F);
    ARC_CHECK_TRUE(arc::math::abs(r1_cos.y() -  0.924909059857F) < 0.000001F);
    ARC_CHECK_TRUE(arc::math::abs(r1_cos.z() - -0.415284230334F) < 0.01F);

    //--------------------------------------------------------------------------
    ARC_TEST_MESSAGE("Testing Simd");

    arc::gm::SimdVector3f s1(1.0F, -0.39F, 745.7F);
    arc::gm::SimdVector3f s1_sin;
    arc::gm::SimdVector3f s1_cos;
    arc::gm::sincos(s1, s1_sin, s1_cos);

    ARC_CHECK_TRUE(arc::math::abs(s1_sin.x() -  0.841470984807F) < 0.01F);
    ARC_CHECK_TRUE(arc::math::abs(s1_sin.y() - -0.380188415123F) < 0.000001F);
    ARC_CHECK_TRUE(arc::math::abs(s1_sin.z() - -0.909691710435F) < 0.01F);

    ARC_CHECK_TRUE(arc::math::abs(s1_cos.x() -  0.540302305868F) < 0.01F);
    ARC_CHECK_TRUE(arc::math::abs(s1_cos.y() -  0.924909059857F) < 0.000001F);
    ARC_CHECK_TRUE(arc::math::abs(s1_cos.z() - -0.415284230334F) < 0.01F);

    arc::gm::SimdVector4f s2(1.0F, -0.39F, 745.7F, -0.39F);
    arc::gm::SimdVector4f s2_sin;
    arc::gm::SimdVector4f s2_cos;
    arc::gm::sincos(s2, s2_sin, s2_cos);

    ARC_CHECK_TRUE(arc::math::abs(s2_sin.x() -  0.841470984807F) < 0.01F);
    ARC_CHECK_TRUE(arc::math::abs(s2_sin.y() - -0.380188415123F) < 0.000001F);
    ARC_CHECK_TRUE(arc::math::abs(s2_sin.z() - -0.909691710435F) < 0.01F);
    ARC_CHECK_TRUE(arc::math::abs(s2_sin.w() - -0.380188415123F) < 0.000001F);

    ARC_CHECK_TRUE(arc::math::abs(s2_cos.x() -  0.540302305868F) < 0.01F);
    ARC_CHECK_TRUE(arc::math::abs(s2_cos.y() -  0.924909059857F) < 0.000001F);
    ARC_CHECK_TRUE(arc::math::abs(s2_cos.z() - -0.415284230334F) < 0.01F);
    ARC_CHECK_TRUE(arc::math::abs(s2_cos.w() -  0.924909059857F) < 0.000001F);
}

} // namespace anonymous
