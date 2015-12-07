/*!
 * \file
 * \brief Operations relating to math.
 * \author David Saxon
 */
#ifndef CHAOSCORE_BASE_MATHOPERATIONS_HPP_
#define CHAOSCORE_BASE_MATHOPERATIONS_HPP_

#include "chaoscore/base/math/MathConstants.hpp"

namespace chaos
{
namespace math
{

/*!
 * \brief Checks whether two floating point values are considered equal or not.
 *
 * This check is done by using the `error_threshold` parameter. If the
 * difference between the two values is less than `error_threshold` then the
 * values are considered to be equal.
 */
bool float_equals(
        float a,
        float b,
        float error_threshold = chaos::math::EPSILON );

} // namespace math
} // namespace chaos

#endif
