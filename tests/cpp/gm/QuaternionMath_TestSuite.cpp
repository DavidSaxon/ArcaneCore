#include "arcanecore/test/ArcTest.hpp"

ARC_TEST_MODULE(gm.QuaternionMath)

#include <arcanecore/gm/QuaternionMath.hpp>

namespace
{

//------------------------------------------------------------------------------
//                                      CAST
//------------------------------------------------------------------------------

ARC_TEST_UNIT(cast)
{
    arc::gm::Quaternionf q1(1.0F, 2.0F, -3.0F, 4.0F);
    arc::gm::Quaterniond q2(1.0, 2.0, -3.0, 4.0);

    ARC_CHECK_EQUAL(arc::gm::cast<double>(q1), q2);
    ARC_CHECK_EQUAL(arc::gm::cast<float>(q2), q1);
}

//------------------------------------------------------------------------------
//                                   MAGNITUDE2
//------------------------------------------------------------------------------

ARC_TEST_UNIT(magnitude2)
{
    arc::gm::Quaternionf q1(1.0F, 2.0F, 3.0F, 4.0F);
    ARC_CHECK_FLOAT_EQUAL(arc::gm::magnitude2(q1), 30.0F);
}

//------------------------------------------------------------------------------
//                                   MAGNITUDE
//------------------------------------------------------------------------------

ARC_TEST_UNIT(magnitude)
{
    arc::gm::Quaternionf q1(2.0F, 2.0F, 2.0F, 2.0F);
    ARC_CHECK_FLOAT_EQUAL(arc::gm::magnitude(q1), 4.0F);
}

//------------------------------------------------------------------------------
//                                   NORMALISE
//------------------------------------------------------------------------------

ARC_TEST_UNIT(normalise)
{
    arc::gm::Quaternionf q1(1.0F, 2.0F, 3.0F, 4.0F);
    arc::gm::Quaternionf n1 = arc::gm::normalise(q1);
    ARC_CHECK_EQUAL(n1, n1);

    // TODO: proper test
}

//------------------------------------------------------------------------------
//                                 TO AXIS ANGLE
//------------------------------------------------------------------------------

ARC_TEST_UNIT(to_axis_angle)
{
    arc::gm::Quaternionf q1(0.7071F, 0.0F, 0.0F, 0.7071F);

    float angle = 0.0F;
    arc::gm::Vector3f axis;
    arc::gm::to_axis_angle(q1, angle, axis);

    ARC_CHECK_TRUE((angle - 1.57082F) < 0.01F);
    ARC_CHECK_TRUE((axis[0] - 1.0F) < 0.01F);
    ARC_CHECK_EQUAL(axis[1], 0.0F);
    ARC_CHECK_EQUAL(axis[2], 0.0F);

    // TODO: more tests
}

} // namespace anonymous
