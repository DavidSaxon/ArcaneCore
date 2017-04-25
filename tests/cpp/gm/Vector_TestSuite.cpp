#include "arcanecore/test/ArcTest.hpp"

ARC_TEST_MODULE(gm.Vector)

#include <arcanecore/gm/Vector.hpp>

namespace
{

ARC_TEST_UNIT(proto)
{
    arc::gm::SimdVector3f* v = new arc::gm::SimdVector3f(1.0, 2.0, 3.0);
    arc::gm::Vector2f v2(*v);
    arc::gm::Vector3f v3(6.03F, 3.0F, -124.4F);
    v2 = v3;
    v3 += (*v);
    std::cout << "v: " << v3 << std::endl;
    std::cout << "dim: " << v2.get_dimensions() << std::endl;
    std::cout << "eq: " << (v3 != v3) << std::endl;
}

} // namespace anonymous
