#include "arcanecore/test/ArcTest.hpp"

ARC_TEST_MODULE(gm.MatrixMath)

#include <arcanecore/gm/MatrixMath.hpp>

namespace
{

//------------------------------------------------------------------------------
//                                   TRANSPOSE
//------------------------------------------------------------------------------

ARC_TEST_UNIT(transpose)
{
    arc::gm::Matrix33f m1(
        arc::gm::Vector3f(1.0F, 2.0F, 3.0F),
        arc::gm::Vector3f(4.0F, 5.0F, 6.0F),
        arc::gm::Vector3f(7.0F, 8.0F, 9.0F)
    );
    arc::gm::Matrix33f r1(
        arc::gm::Vector3f(1.0F, 4.0F, 7.0F),
        arc::gm::Vector3f(2.0F, 5.0F, 8.0F),
        arc::gm::Vector3f(3.0F, 6.0F, 9.0F)
    );
    ARC_CHECK_EQUAL(arc::gm::transpose(m1), r1);

    arc::gm::Matrix34f m2(
        arc::gm::Vector4f(1.0F,  2.0F,  3.0F,  4.0F),
        arc::gm::Vector4f(5.0F,  6.0F,  7.0F,  8.0F),
        arc::gm::Vector4f(9.0F, 10.0F, 11.0F, 12.0F)
    );
    arc::gm::Matrix<float, 4, 3> r2(
        arc::gm::Vector3f(1.0F,  5.0,   9.0F),
        arc::gm::Vector3f(2.0F,  6.0,  10.0F),
        arc::gm::Vector3f(3.0F,  7.0,  11.0F),
        arc::gm::Vector3f(4.0F,  8.0,  12.0F)
    );
    ARC_CHECK_EQUAL(arc::gm::transpose(m2), r2);

    arc::gm::Matrix44f m3(
        arc::gm::Vector4f( 1.0F,  2.0F,  3.0F,  4.0F),
        arc::gm::Vector4f( 5.0F,  6.0F,  7.0F,  8.0F),
        arc::gm::Vector4f( 9.0F, 10.0F, 11.0F, 12.0F),
        arc::gm::Vector4f(13.0F, 14.0F, 15.0F, 16.0F)
    );
    arc::gm::Matrix44f r3(
        arc::gm::Vector4f(1.0F, 5.0F, 9.0F,  13.0F),
        arc::gm::Vector4f(2.0F, 6.0F, 10.0F, 14.0F),
        arc::gm::Vector4f(3.0F, 7.0F, 11.0F, 15.0F),
        arc::gm::Vector4f(4.0F, 8.0F, 12.0F, 16.0F)
    );
    ARC_CHECK_EQUAL(arc::gm::transpose(m3), r3);
}

} // namespace anonymous
