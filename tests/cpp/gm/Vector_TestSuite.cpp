#include "arcanecore/test/ArcTest.hpp"

ARC_TEST_MODULE(gm.Vector)

#include <arcanecore/gm/Vector.hpp>

namespace
{

ARC_TEST_UNIT(proto)
{
    // typedef arc::gm::Vector<float, 3, 16> vType;
    std::cout << "align of float: " << alignof(float) << std::endl;
    arc::gm::SimdVector3f* v = new arc::gm::SimdVector3f(1.0, 2.0, 3.0);
}

} // namespace anonymous
