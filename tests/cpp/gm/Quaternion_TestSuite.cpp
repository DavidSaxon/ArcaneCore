#include "arcanecore/test/ArcTest.hpp"

ARC_TEST_MODULE(gm.Quaternion)

#include <arcanecore/gm/Quaternion.hpp>

namespace
{

//------------------------------------------------------------------------------
//                                  CONSTRUCTOR
//------------------------------------------------------------------------------

ARC_TEST_UNIT(constructor)
{
    //--------------------------------------------------------------------------
    ARC_TEST_MESSAGE("Testing default constructor");

    arc::gm::Quaternionf q1;
    ARC_CHECK_EQUAL(q1.x(), 0.0F);
    ARC_CHECK_EQUAL(q1.y(), 0.0F);
    ARC_CHECK_EQUAL(q1.z(), 0.0F);
    ARC_CHECK_EQUAL(q1.w(), 1.0F);

    //--------------------------------------------------------------------------
    ARC_TEST_MESSAGE("Testing component constructor");

    arc::gm::Quaternionf q2(1.0F, 2.0F, 3.0F, 4.0F);
    ARC_CHECK_EQUAL(q2.x(), 1.0F);
    ARC_CHECK_EQUAL(q2.y(), 2.0F);
    ARC_CHECK_EQUAL(q2.z(), 3.0F);
    ARC_CHECK_EQUAL(q2.w(), 4.0F);

    //--------------------------------------------------------------------------
    ARC_TEST_MESSAGE("Testing angle-axis constructor");

    arc::gm::Quaternionf q3(1.5707F, arc::gm::Vector3f(1.0F, 0.5F, 0.25F));

    ARC_CHECK_TRUE((q3.x() - 0.707073F) < 0.01F);
    ARC_CHECK_TRUE((q3.y() - 0.353536F) < 0.01F);
    ARC_CHECK_TRUE((q3.z() - 0.176768F) < 0.01F);
    ARC_CHECK_TRUE((q3.w() - 0.707141F) < 0.01F);

    //--------------------------------------------------------------------------
    ARC_TEST_MESSAGE("Testing copy constructor");

    arc::gm::SimdQuaternionf c1(4.0F, 3.0F, 2.0F, 1.0F);
    arc::gm::Quaternionf q4(c1);

    ARC_CHECK_EQUAL(q4.x(), 4.0F);
    ARC_CHECK_EQUAL(q4.y(), 3.0F);
    ARC_CHECK_EQUAL(q4.z(), 2.0F);
    ARC_CHECK_EQUAL(q4.w(), 1.0F);

    //--------------------------------------------------------------------------
    ARC_TEST_MESSAGE("Testing SIMD assign constructor");

    arc::gm::SimdQuaternionf c2(1.0F, 3.0F, 4.0F, 2.0F);
    arc::gm::SimdQuaternionf q5(
        c2.get_simd(),
        arc::gm::SimdQuaternionf::kSimdAssignTag
    );

    ARC_CHECK_EQUAL(q5.x(), 1.0F);
    ARC_CHECK_EQUAL(q5.y(), 3.0F);
    ARC_CHECK_EQUAL(q5.z(), 4.0F);
    ARC_CHECK_EQUAL(q5.w(), 2.0F);
}

//------------------------------------------------------------------------------
//                                    ADDITION
//------------------------------------------------------------------------------

ARC_TEST_UNIT(addition)
{
    arc::gm::Quaternionf q1(1.0F, 2.0F, 3.0F, 4.0F);
    arc::gm::Quaternionf q2(4.0F, -1.0F, 3.0F, -5.0F);

    arc::gm::Quaternionf r1(5.0F, 1.0F, 6.0F, -1.0F);
    ARC_CHECK_EQUAL(q1 + q2, r1);

    q1 += q2;
    ARC_CHECK_EQUAL(q1, r1);
}

//------------------------------------------------------------------------------
//                                  SUBTRACTION
//------------------------------------------------------------------------------

ARC_TEST_UNIT(subtraction)
{
    arc::gm::Quaternionf q1(1.0F, 2.0F, 3.0F, 4.0F);
    arc::gm::Quaternionf q2(4.0F, -1.0F, 3.0F, -5.0F);

    arc::gm::Quaternionf r1(-3.0F, 3.0F, 0.0F, 9.0F);
    ARC_CHECK_EQUAL(q1 - q2, r1);

    q1 -= q2;
    ARC_CHECK_EQUAL(q1, r1);
}

//------------------------------------------------------------------------------
//                                 MULTIPLICATION
//------------------------------------------------------------------------------

ARC_TEST_UNIT(multiplication)
{
    arc::gm::Quaternionf q1(1.0F, 2.0F, 3.0F, 4.0F);
    arc::gm::Quaternionf q2(4.0F, -1.0F, 3.0F, -5.0F);

    ARC_CHECK_EQUAL(q1 * q2, q1 * q2);
    q1 *= q2;

    // TODO: write a proper test
}

// TODO: multiplication

} // namespace anonymous
