#include "arcanecore/base/math/MathOperations.hpp"

#include <cstdlib>

#include "arcanecore/base/data/BitwiseFloat.hpp"

namespace arc
{
namespace math
{

bool float_equals(
        float a,
        float b,
        float delta_threshold,
        arc::uint32 ulps_threshold)
{
    // first perform the delta threshold check, this is needed for values near 0
    if(std::fabs(a - b) <= delta_threshold)
    {
        return true;
    }

    // TODO: could optimise here

    // create bitwise representations of the floats
    arc::data::BitwiseFloat b_a(a);
    arc::data::BitwiseFloat b_b(b);

    // ulps comparisons only work on values of the same sign
    if(b_a.get_sign_bit() != b_b.get_sign_bit())
    {
        return false;
    }

    // find the difference in ulps
    arc::int64 ulps = std::labs(
            static_cast<arc::int64>(b_a.int_rep) -
            static_cast<arc::int64>(b_b.int_rep)
    );

    if(ulps <= static_cast< arc::int64>(ulps_threshold))
    {
        return true;
    }

    return false;
}

} // namespace math
} // namespace arc
