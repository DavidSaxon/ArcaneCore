#include "arcanecore/test/ArcTest.hpp"

ARC_TEST_MODULE(gm.Vector)

#include <arcanecore/gm/Vector.hpp>

namespace
{

//------------------------------------------------------------------------------
//                                  CONSTRUCTOR
//------------------------------------------------------------------------------

ARC_TEST_UNIT(constructor)
{
    //--------------------------------------------------------------------------
    ARC_TEST_MESSAGE("Testing Zero constructor");

    arc::gm::Vector3f v1;
    ARC_CHECK_EQUAL(v1.x(), 0.0F);
    ARC_CHECK_EQUAL(v1.y(), 0.0F);
    ARC_CHECK_EQUAL(v1.z(), 0.0F);

    arc::gm::SimdVector3f s1;
    ARC_CHECK_EQUAL(s1.x(), 0.0F);
    ARC_CHECK_EQUAL(s1.y(), 0.0F);
    ARC_CHECK_EQUAL(s1.z(), 0.0F);

    //--------------------------------------------------------------------------
    ARC_TEST_MESSAGE("Testing scalar constructor");

    arc::gm::Vector3f v2(2.0F);
    ARC_CHECK_EQUAL(v2.x(), 2.0F);
    ARC_CHECK_EQUAL(v2.y(), 2.0F);
    ARC_CHECK_EQUAL(v2.z(), 2.0F);

    arc::gm::SimdVector3f s2(3.0F);
    ARC_CHECK_EQUAL(s2.x(), 3.0F);
    ARC_CHECK_EQUAL(s2.y(), 3.0F);
    ARC_CHECK_EQUAL(s2.z(), 3.0F);

    //--------------------------------------------------------------------------
    ARC_TEST_MESSAGE("Testing copy constructor");

    arc::gm::Vector3f c1(1.0F, 2.0F, 3.0F);
    arc::gm::Vector3f v3(c1);
    ARC_CHECK_EQUAL(v3.x(), 1.0F);
    ARC_CHECK_EQUAL(v3.y(), 2.0F);
    ARC_CHECK_EQUAL(v3.z(), 3.0F);

    arc::gm::SimdVector3f sc1(1.0F, 2.0F, 3.0F);
    arc::gm::SimdVector3f s3(sc1);
    ARC_CHECK_EQUAL(s3.x(), 1.0F);
    ARC_CHECK_EQUAL(s3.y(), 2.0F);
    ARC_CHECK_EQUAL(s3.z(), 3.0F);
}

//------------------------------------------------------------------------------
//                                   ASSIGNMENT
//------------------------------------------------------------------------------

ARC_TEST_UNIT(assignment)
{
    //--------------------------------------------------------------------------
    ARC_TEST_MESSAGE("Testing scalar assignment");

    arc::gm::Vector4f v1;
    v1 = 11.0F;
    ARC_CHECK_EQUAL(v1, arc::gm::Vector4f(11.0F, 11.0F, 11.0F, 11.0F));

    arc::gm::SimdVector4f s1;
    s1 = 11.0F;
    ARC_CHECK_EQUAL(s1, arc::gm::SimdVector4f(11.0F, 11.0F, 11.0F, 11.0F));

    //--------------------------------------------------------------------------
    ARC_TEST_MESSAGE("Testing vector assignment");

    arc::gm::Vector4f v2(-12.0F);
    arc::gm::Vector4f v3(12.0F, 13.0F, -12.0F, 48.0F);
    v2 = v3;
    ARC_CHECK_EQUAL(v2, v3);

    arc::gm::Vector4f s2(-12.0F);
    arc::gm::Vector4f s3(12.0F, 13.0F, -12.0F, 48.0F);
    s2 = s3;
    ARC_CHECK_EQUAL(s2, s3);
}

//------------------------------------------------------------------------------
//                                    NEGATION
//------------------------------------------------------------------------------

ARC_TEST_UNIT(negation)
{
    arc::gm::Vector3f v1(1.0F, -2.0F, 3.0F);
    ARC_CHECK_EQUAL((-v1), arc::gm::Vector3f(-1.0F, 2.0F, -3.0F));

    arc::gm::Vector4f v2(1.0F, 2.0F, 3.0F, -4.0F);
    ARC_CHECK_EQUAL((-v2), arc::gm::Vector4f(-1.0F, -2.0F, -3.0F, 4.0F));

    //--------------------------------------------------------------------------
    ARC_TEST_MESSAGE("Testing SIMD");

    arc::gm::SimdVector3f s1(1.0F, -2.0F, 3.0F);
    ARC_CHECK_EQUAL((-s1), arc::gm::SimdVector3f(-1.0F, 2.0F, -3.0F));

    arc::gm::SimdVector4f s2(1.0F, 2.0F, 3.0F, -4.0F);
    ARC_CHECK_EQUAL((-s2), arc::gm::SimdVector4f(-1.0F, -2.0F, -3.0F, 4.0F));
}

//------------------------------------------------------------------------------
//                                SCALAR ADDITION
//------------------------------------------------------------------------------

ARC_TEST_UNIT(scalar_addition)
{
    arc::gm::Vector3f v1(1.0F, 2.0F, 3.0F);
    arc::gm::Vector3f r1(5.0F, 6.0F, 7.0F);
    ARC_CHECK_EQUAL(v1 + 4.0F, r1);

    v1 += 4.0F;
    ARC_CHECK_EQUAL(v1, r1);

    //--------------------------------------------------------------------------
    ARC_TEST_MESSAGE("Testing SIMD");

    arc::gm::SimdVector3f s1(1.0F, 2.0F, 3.0F);
    arc::gm::SimdVector3f sr1(5.0F, 6.0F, 7.0F);
    ARC_CHECK_EQUAL(s1 + 4.0F, sr1);

    s1 += 4.0F;
    ARC_CHECK_EQUAL(s1, sr1);
}

//------------------------------------------------------------------------------
//                                VECTOR ADDITION
//------------------------------------------------------------------------------

ARC_TEST_UNIT(vector_addition)
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

    arc::gm::SimdVector4f s2(1.0F, 2.0F, 3.0F, -4.0F);
    arc::gm::SimdVector4f sr2(2.0F, 4.0F, 6.0F, -8.0F);
    ARC_CHECK_EQUAL(s2 + s2, sr2);

    s1 += s1;
    ARC_CHECK_EQUAL(s1, sr1);
    s2 += s2;
    ARC_CHECK_EQUAL(s2, sr2);
}

//------------------------------------------------------------------------------
//                               SCALAR SUBTRACTION
//------------------------------------------------------------------------------

ARC_TEST_UNIT(scalar_subtraction)
{
    arc::gm::Vector3f v1(1.0F, 2.0F, 3.0F);
    arc::gm::Vector3f r1(-3.0F, -2.0F, -1.0F);
    ARC_CHECK_EQUAL(v1 - 4.0F, r1);

    v1 -= 4.0F;
    ARC_CHECK_EQUAL(v1, r1);

    //--------------------------------------------------------------------------
    ARC_TEST_MESSAGE("Testing SIMD");

    arc::gm::SimdVector3f s1(1.0F, 2.0F, 3.0F);
    arc::gm::SimdVector3f sr1(-3.0F, -2.0F, -1.0F);
    ARC_CHECK_EQUAL(s1 - 4.0F, sr1);

    s1 -= 4.0F;
    ARC_CHECK_EQUAL(s1, sr1);
}

//------------------------------------------------------------------------------
//                               VECTOR SUBTRACTION
//------------------------------------------------------------------------------

ARC_TEST_UNIT(vector_subtraction)
{
    arc::gm::Vector3f v1(1.0F, 2.0F, 3.0F);
    arc::gm::Vector3f v1_(1.0F, -1.0F, 4.0F);
    arc::gm::Vector3f r1(0.0F, 3.0F, -1.0F);
    ARC_CHECK_EQUAL(v1 - v1_, r1);

    v1 -= v1_;
    ARC_CHECK_EQUAL(v1, r1);

    //--------------------------------------------------------------------------
    ARC_TEST_MESSAGE("Testing SIMD");

    arc::gm::SimdVector3f s1(1.0F, 2.0F, 3.0F);
    arc::gm::SimdVector3f s1_(1.0F, -1.0F, 4.0F);
    arc::gm::SimdVector3f sr1(0.0F, 3.0F, -1.0F);
    ARC_CHECK_EQUAL(s1 - s1_, sr1);

    s1 -= s1_;
    ARC_CHECK_EQUAL(s1, sr1);
}

} // namespace anonymous
