#include "arcanecore/test/ArcTest.hpp"

ARC_TEST_MODULE(gm.Matrix)

#include <arcanecore/gm/Matrix.hpp>

namespace
{

//------------------------------------------------------------------------------
//                                  CONSTRUCTOR
//------------------------------------------------------------------------------

ARC_TEST_UNIT(constructor)
{
    //--------------------------------------------------------------------------
    ARC_TEST_MESSAGE("Testing Zero constructor");

    arc::gm::Matrix44f m1;
    ARC_CHECK_EQUAL(m1[0][0], 0.0F);
    ARC_CHECK_EQUAL(m1[0][1], 0.0F);
    ARC_CHECK_EQUAL(m1[0][2], 0.0F);
    ARC_CHECK_EQUAL(m1[0][3], 0.0F);
    ARC_CHECK_EQUAL(m1[1][0], 0.0F);
    ARC_CHECK_EQUAL(m1[1][1], 0.0F);
    ARC_CHECK_EQUAL(m1[1][2], 0.0F);
    ARC_CHECK_EQUAL(m1[1][3], 0.0F);
    ARC_CHECK_EQUAL(m1[2][0], 0.0F);
    ARC_CHECK_EQUAL(m1[2][1], 0.0F);
    ARC_CHECK_EQUAL(m1[2][2], 0.0F);
    ARC_CHECK_EQUAL(m1[2][3], 0.0F);
    ARC_CHECK_EQUAL(m1[3][0], 0.0F);
    ARC_CHECK_EQUAL(m1[3][1], 0.0F);
    ARC_CHECK_EQUAL(m1[3][2], 0.0F);
    ARC_CHECK_EQUAL(m1[3][3], 0.0F);

    //--------------------------------------------------------------------------
    ARC_TEST_MESSAGE("Testing Identity constructor");
    arc::gm::Matrix44f m2(1.0F);
    ARC_CHECK_EQUAL(m2[0][0], 1.0F);
    ARC_CHECK_EQUAL(m2[0][1], 0.0F);
    ARC_CHECK_EQUAL(m2[0][2], 0.0F);
    ARC_CHECK_EQUAL(m2[0][3], 0.0F);
    ARC_CHECK_EQUAL(m2[1][0], 0.0F);
    ARC_CHECK_EQUAL(m2[1][1], 1.0F);
    ARC_CHECK_EQUAL(m2[1][2], 0.0F);
    ARC_CHECK_EQUAL(m2[1][3], 0.0F);
    ARC_CHECK_EQUAL(m2[2][0], 0.0F);
    ARC_CHECK_EQUAL(m2[2][1], 0.0F);
    ARC_CHECK_EQUAL(m2[2][2], 1.0F);
    ARC_CHECK_EQUAL(m2[2][3], 0.0F);
    ARC_CHECK_EQUAL(m2[3][0], 0.0F);
    ARC_CHECK_EQUAL(m2[3][1], 0.0F);
    ARC_CHECK_EQUAL(m2[3][2], 0.0F);
    ARC_CHECK_EQUAL(m2[3][3], 1.0F);

    //--------------------------------------------------------------------------
    ARC_TEST_MESSAGE("Testing data constructor");
    float m3_data[12] = {
        0.0F, 1.0F,  2.0F,  3.0F,
        4.0F, 5.0F,  6.0F,  7.0F,
        8.0F, 9.0F, 10.0F, 11.0F
    };
    arc::gm::Matrix34f m3(m3_data);
    ARC_CHECK_EQUAL(m3[0][0], 0.0F);
    ARC_CHECK_EQUAL(m3[0][1], 1.0F);
    ARC_CHECK_EQUAL(m3[0][2], 2.0F);
    ARC_CHECK_EQUAL(m3[0][3], 3.0F);
    ARC_CHECK_EQUAL(m3[1][0], 4.0F);
    ARC_CHECK_EQUAL(m3[1][1], 5.0F);
    ARC_CHECK_EQUAL(m3[1][2], 6.0F);
    ARC_CHECK_EQUAL(m3[1][3], 7.0F);
    ARC_CHECK_EQUAL(m3[2][0], 8.0F);
    ARC_CHECK_EQUAL(m3[2][1], 9.0F);
    ARC_CHECK_EQUAL(m3[2][2], 10.0F);
    ARC_CHECK_EQUAL(m3[2][3], 11.0F);

    //--------------------------------------------------------------------------
    ARC_TEST_MESSAGE("Testing single vector constructor");
    arc::gm::Matrix33f m4(arc::gm::Vector3f(1.0F, 2.0F, 3.0F));
    ARC_CHECK_EQUAL(m4[0][0], 1.0F);
    ARC_CHECK_EQUAL(m4[0][1], 2.0F);
    ARC_CHECK_EQUAL(m4[0][2], 3.0F);
    ARC_CHECK_EQUAL(m4[1][0], 1.0F);
    ARC_CHECK_EQUAL(m4[1][1], 2.0F);
    ARC_CHECK_EQUAL(m4[1][2], 3.0F);
    ARC_CHECK_EQUAL(m4[2][0], 1.0F);
    ARC_CHECK_EQUAL(m4[2][1], 2.0F);
    ARC_CHECK_EQUAL(m4[2][2], 3.0F);

    //--------------------------------------------------------------------------
    ARC_TEST_MESSAGE("Testing 3 vector constructor");
    arc::gm::Matrix34f m5(
        arc::gm::Vector4f(0.0F, 1.0F,  2.0F,  3.0F),
        arc::gm::Vector4f(4.0F, 5.0F,  6.0F,  7.0F),
        arc::gm::Vector4f(8.0F, 9.0F, 10.0F, 11.0F)
    );
    ARC_CHECK_EQUAL(m5[0][0], 0.0F);
    ARC_CHECK_EQUAL(m5[0][1], 1.0F);
    ARC_CHECK_EQUAL(m5[0][2], 2.0F);
    ARC_CHECK_EQUAL(m5[0][3], 3.0F);
    ARC_CHECK_EQUAL(m5[1][0], 4.0F);
    ARC_CHECK_EQUAL(m5[1][1], 5.0F);
    ARC_CHECK_EQUAL(m5[1][2], 6.0F);
    ARC_CHECK_EQUAL(m5[1][3], 7.0F);
    ARC_CHECK_EQUAL(m5[2][0], 8.0F);
    ARC_CHECK_EQUAL(m5[2][1], 9.0F);
    ARC_CHECK_EQUAL(m5[2][2], 10.0F);
    ARC_CHECK_EQUAL(m5[2][3], 11.0F);

    //--------------------------------------------------------------------------
    ARC_TEST_MESSAGE("Testing 4 vector constructor");
    arc::gm::Matrix44f m6(
        arc::gm::Vector4f( 0.0F,  1.0F,  2.0F,  3.0F),
        arc::gm::Vector4f( 4.0F,  5.0F,  6.0F,  7.0F),
        arc::gm::Vector4f( 8.0F,  9.0F, 10.0F, 11.0F),
        arc::gm::Vector4f(12.0F, 13.0F, 14.0F, 15.0F)
    );
    ARC_CHECK_EQUAL(m6[0][0], 0.0F);
    ARC_CHECK_EQUAL(m6[0][1], 1.0F);
    ARC_CHECK_EQUAL(m6[0][2], 2.0F);
    ARC_CHECK_EQUAL(m6[0][3], 3.0F);
    ARC_CHECK_EQUAL(m6[1][0], 4.0F);
    ARC_CHECK_EQUAL(m6[1][1], 5.0F);
    ARC_CHECK_EQUAL(m6[1][2], 6.0F);
    ARC_CHECK_EQUAL(m6[1][3], 7.0F);
    ARC_CHECK_EQUAL(m6[2][0], 8.0F);
    ARC_CHECK_EQUAL(m6[2][1], 9.0F);
    ARC_CHECK_EQUAL(m6[2][2], 10.0F);
    ARC_CHECK_EQUAL(m6[2][3], 11.0F);
    ARC_CHECK_EQUAL(m6[3][0], 12.0F);
    ARC_CHECK_EQUAL(m6[3][1], 13.0F);
    ARC_CHECK_EQUAL(m6[3][2], 14.0F);
    ARC_CHECK_EQUAL(m6[3][3], 15.0F);

    //--------------------------------------------------------------------------
    ARC_TEST_MESSAGE("Same dimensionality copy constructor");
    arc::gm::Matrix34f m7(0.5F);
    arc::gm::Matrix34f m8(m7);
    ARC_CHECK_EQUAL(m8[0][0], 0.5F);
    ARC_CHECK_EQUAL(m8[0][1], 0.0F);
    ARC_CHECK_EQUAL(m8[0][2], 0.0F);
    ARC_CHECK_EQUAL(m8[0][3], 0.0F);
    ARC_CHECK_EQUAL(m8[1][0], 0.0F);
    ARC_CHECK_EQUAL(m8[1][1], 0.5F);
    ARC_CHECK_EQUAL(m8[1][2], 0.0F);
    ARC_CHECK_EQUAL(m8[1][3], 0.0F);
    ARC_CHECK_EQUAL(m8[2][0], 0.0F);
    ARC_CHECK_EQUAL(m8[2][1], 0.0F);
    ARC_CHECK_EQUAL(m8[2][2], 0.5F);
    ARC_CHECK_EQUAL(m8[2][3], 0.0F);

    //--------------------------------------------------------------------------
    ARC_TEST_MESSAGE("Different dimensionality copy constructor");
    arc::gm::Matrix33f m9(2.0F);
    arc::gm::Matrix44f m10(m9);
    ARC_CHECK_EQUAL(m10[0][0], 2.0F);
    ARC_CHECK_EQUAL(m10[0][1], 0.0F);
    ARC_CHECK_EQUAL(m10[0][2], 0.0F);
    ARC_CHECK_EQUAL(m10[0][3], 0.0F);
    ARC_CHECK_EQUAL(m10[1][0], 0.0F);
    ARC_CHECK_EQUAL(m10[1][1], 2.0F);
    ARC_CHECK_EQUAL(m10[1][2], 0.0F);
    ARC_CHECK_EQUAL(m10[1][3], 0.0F);
    ARC_CHECK_EQUAL(m10[2][0], 0.0F);
    ARC_CHECK_EQUAL(m10[2][1], 0.0F);
    ARC_CHECK_EQUAL(m10[2][2], 2.0F);
    ARC_CHECK_EQUAL(m10[2][3], 0.0F);
    ARC_CHECK_EQUAL(m10[3][0], 0.0F);
    ARC_CHECK_EQUAL(m10[3][1], 0.0F);
    ARC_CHECK_EQUAL(m10[3][2], 0.0F);
    ARC_CHECK_EQUAL(m10[3][3], 0.0F);

    arc::gm::Matrix44f m11(0.1F);
    arc::gm::Matrix34f m12(m11);
    ARC_CHECK_EQUAL(m12[0][0], 0.1F);
    ARC_CHECK_EQUAL(m12[0][1], 0.0F);
    ARC_CHECK_EQUAL(m12[0][2], 0.0F);
    ARC_CHECK_EQUAL(m12[0][3], 0.0F);
    ARC_CHECK_EQUAL(m12[1][0], 0.0F);
    ARC_CHECK_EQUAL(m12[1][1], 0.1F);
    ARC_CHECK_EQUAL(m12[1][2], 0.0F);
    ARC_CHECK_EQUAL(m12[1][3], 0.0F);
    ARC_CHECK_EQUAL(m12[2][0], 0.0F);
    ARC_CHECK_EQUAL(m12[2][1], 0.0F);
    ARC_CHECK_EQUAL(m12[2][2], 0.1F);
    ARC_CHECK_EQUAL(m12[2][3], 0.0F);
}

//------------------------------------------------------------------------------
//                                   ASSIGNMENT
//------------------------------------------------------------------------------

ARC_TEST_UNIT(assignment)
{
    //--------------------------------------------------------------------------
    ARC_TEST_MESSAGE("Testing scalar assignment");
    arc::gm::Matrix44f m1(
        arc::gm::Vector4f( 0.0F,  1.0F,  2.0F,  3.0F),
        arc::gm::Vector4f( 4.0F,  5.0F,  6.0F,  7.0F),
        arc::gm::Vector4f( 8.0F,  9.0F, 10.0F, 11.0F),
        arc::gm::Vector4f(12.0F, 13.0F, 14.0F, 15.0F)
    );
    m1 = 5.0F;
    ARC_CHECK_EQUAL(m1[0][0], 5.0F);
    ARC_CHECK_EQUAL(m1[0][1], 0.0F);
    ARC_CHECK_EQUAL(m1[0][2], 0.0F);
    ARC_CHECK_EQUAL(m1[0][3], 0.0F);
    ARC_CHECK_EQUAL(m1[1][0], 0.0F);
    ARC_CHECK_EQUAL(m1[1][1], 5.0F);
    ARC_CHECK_EQUAL(m1[1][2], 0.0F);
    ARC_CHECK_EQUAL(m1[1][3], 0.0F);
    ARC_CHECK_EQUAL(m1[2][0], 0.0F);
    ARC_CHECK_EQUAL(m1[2][1], 0.0F);
    ARC_CHECK_EQUAL(m1[2][2], 5.0F);
    ARC_CHECK_EQUAL(m1[2][3], 0.0F);
    ARC_CHECK_EQUAL(m1[3][0], 0.0F);
    ARC_CHECK_EQUAL(m1[3][1], 0.0F);
    ARC_CHECK_EQUAL(m1[3][2], 0.0F);
    ARC_CHECK_EQUAL(m1[3][3], 5.0F);

    //--------------------------------------------------------------------------
    ARC_TEST_MESSAGE("Testing vector assignment");
    arc::gm::Matrix33f m2(
        arc::gm::Vector3f(0.0F, 1.0F, 2.0F),
        arc::gm::Vector3f(3.0F, 4.0F, 5.0F),
        arc::gm::Vector3f(6.0F, 7.0F, 8.0F)
    );
    m2 = arc::gm::Vector3f(-3.0F, -2.0F, -1.0F);
    ARC_CHECK_EQUAL(m2[0][0], -3.0F);
    ARC_CHECK_EQUAL(m2[0][1], -2.0F);
    ARC_CHECK_EQUAL(m2[0][2], -1.0F);
    ARC_CHECK_EQUAL(m2[1][0], -3.0F);
    ARC_CHECK_EQUAL(m2[1][1], -2.0F);
    ARC_CHECK_EQUAL(m2[1][2], -1.0F);
    ARC_CHECK_EQUAL(m2[2][0], -3.0F);
    ARC_CHECK_EQUAL(m2[2][1], -2.0F);
    ARC_CHECK_EQUAL(m2[2][2], -1.0F);

    //--------------------------------------------------------------------------
    ARC_TEST_MESSAGE("Same dimensionality matrix assignment");
    arc::gm::Matrix34f m3(0.5F);
    arc::gm::Matrix34f m4(arc::gm::Vector4f(1.0F, 2.0F, 3.0F, 4.0F));
    m4 = m3;
    ARC_CHECK_EQUAL(m4[0][0], 0.5F);
    ARC_CHECK_EQUAL(m4[0][1], 0.0F);
    ARC_CHECK_EQUAL(m4[0][2], 0.0F);
    ARC_CHECK_EQUAL(m4[0][3], 0.0F);
    ARC_CHECK_EQUAL(m4[1][0], 0.0F);
    ARC_CHECK_EQUAL(m4[1][1], 0.5F);
    ARC_CHECK_EQUAL(m4[1][2], 0.0F);
    ARC_CHECK_EQUAL(m4[1][3], 0.0F);
    ARC_CHECK_EQUAL(m4[2][0], 0.0F);
    ARC_CHECK_EQUAL(m4[2][1], 0.0F);
    ARC_CHECK_EQUAL(m4[2][2], 0.5F);
    ARC_CHECK_EQUAL(m4[2][3], 0.0F);

    //--------------------------------------------------------------------------
    ARC_TEST_MESSAGE("Different dimensionality matrix assignment");
    arc::gm::Matrix33f m5(2.0F);
    arc::gm::Matrix44f m6(arc::gm::Vector4f(-1.0F, -2.0F, -3.0F, -4.0F));
    m6 = m5;
    ARC_CHECK_EQUAL(m6[0][0], 2.0F);
    ARC_CHECK_EQUAL(m6[0][1], 0.0F);
    ARC_CHECK_EQUAL(m6[0][2], 0.0F);
    ARC_CHECK_EQUAL(m6[0][3], 0.0F);
    ARC_CHECK_EQUAL(m6[1][0], 0.0F);
    ARC_CHECK_EQUAL(m6[1][1], 2.0F);
    ARC_CHECK_EQUAL(m6[1][2], 0.0F);
    ARC_CHECK_EQUAL(m6[1][3], 0.0F);
    ARC_CHECK_EQUAL(m6[2][0], 0.0F);
    ARC_CHECK_EQUAL(m6[2][1], 0.0F);
    ARC_CHECK_EQUAL(m6[2][2], 2.0F);
    ARC_CHECK_EQUAL(m6[2][3], 0.0F);
    ARC_CHECK_EQUAL(m6[3][0], 0.0F);
    ARC_CHECK_EQUAL(m6[3][1], 0.0F);
    ARC_CHECK_EQUAL(m6[3][2], 0.0F);
    ARC_CHECK_EQUAL(m6[3][3], 0.0F);

    arc::gm::Matrix44f m7(
        arc::gm::Vector4f( 0.0F,  1.0F,  2.0F,  3.0F),
        arc::gm::Vector4f( 4.0F,  5.0F,  6.0F,  7.0F),
        arc::gm::Vector4f( 8.0F,  9.0F, 10.0F, 11.0F),
        arc::gm::Vector4f(12.0F, 13.0F, 14.0F, 15.0F)
    );
    arc::gm::Matrix34f m8(0.1F);
    m8 = m7;
    ARC_CHECK_EQUAL(m8[0][0],  0.0F);
    ARC_CHECK_EQUAL(m8[0][1],  1.0F);
    ARC_CHECK_EQUAL(m8[0][2],  2.0F);
    ARC_CHECK_EQUAL(m8[0][3],  3.0F);
    ARC_CHECK_EQUAL(m8[1][0],  4.0F);
    ARC_CHECK_EQUAL(m8[1][1],  5.0F);
    ARC_CHECK_EQUAL(m8[1][2],  6.0F);
    ARC_CHECK_EQUAL(m8[1][3],  7.0F);
    ARC_CHECK_EQUAL(m8[2][0],  8.0F);
    ARC_CHECK_EQUAL(m8[2][1],  9.0F);
    ARC_CHECK_EQUAL(m8[2][2], 10.0F);
    ARC_CHECK_EQUAL(m8[2][3], 11.0F);
}

//------------------------------------------------------------------------------
//                                SCALAR ADDITION
//------------------------------------------------------------------------------

ARC_TEST_UNIT(scalar_addition)
{
    arc::gm::Matrix44f m(1.0F);
    arc::gm::Matrix44f r(
        arc::gm::Vector4f(21.2F, 20.2F, 20.2F, 20.2F),
        arc::gm::Vector4f(20.2F, 21.2F, 20.2F, 20.2F),
        arc::gm::Vector4f(20.2F, 20.2F, 21.2F, 20.2F),
        arc::gm::Vector4f(20.2F, 20.2F, 20.2F, 21.2F)
    );
    ARC_CHECK_EQUAL(m + 20.2F, r);

    m += 25.7F;
    ARC_CHECK_EQUAL(m, r + 5.5F);
}

//------------------------------------------------------------------------------
//                                VECTOR ADDITION
//------------------------------------------------------------------------------

ARC_TEST_UNIT(vector_addition)
{
    arc::gm::Matrix34f m(0.5F);

    arc::gm::Matrix34f r(
        arc::gm::Vector4f(3.5F, 1.0F, 4.0F, 2.0F),
        arc::gm::Vector4f(3.0F, 1.5F, 4.0F, 2.0F),
        arc::gm::Vector4f(3.0F, 1.0F, 4.5F, 2.0F)
    );
    ARC_CHECK_EQUAL(m + arc::gm::Vector4f(3.0F, 1.0F, 4.0F, 2.0F), r);

    m += arc::gm::Vector4f(5.0F, 0.0F, 5.0F, 20.0F);
    ARC_CHECK_EQUAL(m, r + arc::gm::Vector4f(2.0F, -1.0F, 1.0F, 18.0F));
}

//------------------------------------------------------------------------------
//                                MATRIX ADDITION
//------------------------------------------------------------------------------

ARC_TEST_UNIT(matrix_addition)
{
    arc::gm::Matrix33f m1(
        arc::gm::Vector3f(0.0F, 1.0F, 2.0F),
        arc::gm::Vector3f(3.0F, 4.0F, 5.0F),
        arc::gm::Vector3f(6.0F, 7.0F, 8.0F)
    );
    arc::gm::Matrix33f m2(
        arc::gm::Vector3f(8.0F, 7.0F, 6.0F),
        arc::gm::Vector3f(5.0F, 4.0F, 3.0F),
        arc::gm::Vector3f(2.0F, 1.0F, 0.0F)
    );
    arc::gm::Matrix33f r(
        arc::gm::Vector3f(8.0F, 8.0F, 8.0F),
        arc::gm::Vector3f(8.0F, 8.0F, 8.0F),
        arc::gm::Vector3f(8.0F, 8.0F, 8.0F)
    );

    ARC_CHECK_EQUAL(m1 + m2, r);

    m2 += m1;
    ARC_CHECK_EQUAL(m2, r);
}

//------------------------------------------------------------------------------
//                               SCALAR SUBTRACTION
//------------------------------------------------------------------------------

ARC_TEST_UNIT(scalar_subtraction)
{
    arc::gm::Matrix34f m(5.0F);
    arc::gm::Matrix34f r(
        arc::gm::Vector4f( 2.3F, -2.7F, -2.7F, -2.7F),
        arc::gm::Vector4f(-2.7F,  2.3F, -2.7F, -2.7F),
        arc::gm::Vector4f(-2.7F, -2.7F,  2.3F, -2.7F)
    );
    ARC_CHECK_EQUAL(m - 2.7F, r);

    m -= 2.7F;
    ARC_CHECK_EQUAL(m, r);
}

//------------------------------------------------------------------------------
//                               VECTOR SUBTRACTION
//------------------------------------------------------------------------------

ARC_TEST_UNIT(vector_subtraction)
{
    arc::gm::Matrix33f m(0.5F);

    arc::gm::Matrix33f r(
        arc::gm::Vector3f(-2.5F, -1.0F, -4.0F),
        arc::gm::Vector3f(-3.0F, -0.5F, -4.0F),
        arc::gm::Vector3f(-3.0F, -1.0F, -3.5F)
    );
    ARC_CHECK_EQUAL(m - arc::gm::Vector3f(3.0F, 1.0F, 4.0F), r);

    m -= arc::gm::Vector3f(3.0F, 1.0F, 4.0F);
    ARC_CHECK_EQUAL(m, r);
}

//------------------------------------------------------------------------------
//                               MATRIX SUBTRACTION
//------------------------------------------------------------------------------

ARC_TEST_UNIT(matrix_subtraction)
{
    arc::gm::Matrix33f m1(
        arc::gm::Vector3f(0.0F, 1.0F, 2.0F),
        arc::gm::Vector3f(3.0F, 4.0F, 5.0F),
        arc::gm::Vector3f(6.0F, 7.0F, 8.0F)
    );
    arc::gm::Matrix33f m2(
        arc::gm::Vector3f(8.0F, 7.0F, 6.0F),
        arc::gm::Vector3f(5.0F, 4.0F, 3.0F),
        arc::gm::Vector3f(2.0F, 1.0F, 0.0F)
    );
    arc::gm::Matrix33f r(
        arc::gm::Vector3f(-8.0F, -6.0F, -4.0F),
        arc::gm::Vector3f(-2.0F,  0.0F,  2.0F),
        arc::gm::Vector3f( 4.0F,  6.0F,  8.0F)
    );

    ARC_CHECK_EQUAL(m1 - m2, r);

    m1 -= m2;
    ARC_CHECK_EQUAL(m1, r);
}

} // namespace anonymous
