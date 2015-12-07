#include "chaoscore/base/math/MathOperations.hpp"

#include <cmath>

namespace chaos
{
namespace math
{

bool float_equals( float a, float b, float error_threshold )
{
    return std::fabs( a - b ) < error_threshold;
}

} // namespace math
} // namespace chaos
