#include "arcanecore/test/ArcTest.hpp"

ARC_TEST_MODULE(gm.MatrixMath)

#include <arcanecore/gm/MatrixMath.hpp>

namespace
{

//------------------------------------------------------------------------------
//                             SCALAR MULTIPLICATION
//------------------------------------------------------------------------------


ARC_TEST_UNIT(scalar_multiplication)
{
    arc::gm::Matrix44f m(
        arc::gm::Vector4f(1.0F, 2.0F, 2.0F, 2.0F),
        arc::gm::Vector4f(2.0F, 1.0F, 2.0F, 2.0F),
        arc::gm::Vector4f(2.0F, 2.0F, 1.0F, 2.0F),
        arc::gm::Vector4f(2.0F, 2.0F, 2.0F, 1.0F)
    );
    arc::gm::Matrix44f r(
        arc::gm::Vector4f(4.4F, 8.8F, 8.8F, 8.8F),
        arc::gm::Vector4f(8.8F, 4.4F, 8.8F, 8.8F),
        arc::gm::Vector4f(8.8F, 8.8F, 4.4F, 8.8F),
        arc::gm::Vector4f(8.8F, 8.8F, 8.8F, 4.4F)
    );
    ARC_CHECK_EQUAL(m * 4.4F, r);

    m *= 8.8F;
    ARC_CHECK_EQUAL(m, r * 2.0F);
}

// TODO: test vector multiplication

} // namespace anonymous
