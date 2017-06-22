/*!
 * \file
 * \brief Operations relating to math.
 * \author David Saxon
 */
#ifndef ARCANECORE_BASE_MATHOPERATIONS_HPP_
#define ARCANECORE_BASE_MATHOPERATIONS_HPP_

#include <cfloat>
#include <cmath>
#include <limits>
#include <cstring>

#include "arcanecore/base/math/MathConstants.hpp"

// TODO: REMOVE ME
#include <iostream>

namespace arc
{
namespace math
{

/*!
 * \brief Returns absolute form value of the given value.
 */
template<typename T_data>
inline T_data abs(T_data v)
{
    // branches should be optimised out
    if(std::numeric_limits<T_data>::is_signed)
    {
        return static_cast<T_data>(::abs(static_cast<int>(v)));
    }
    return v;
}

//---------------T E M P L A T E -- S P E C I A L I S A T I O N S---------------

template<>
inline float abs<float>(float v)
{
    return fabsf(v);
}

template<>
inline double abs<double>(double v)
{
    return fabs(v);
}

template<>
inline long double abs<long double>(long double v)
{
    return fabsl(v);
}

template<>
inline arc::int64 abs<arc::int64>(arc::int64 v)
{
     return static_cast<arc::int64>(llabs(v));
}

//------------------------------------------------------------------------------

/*!
 * \brief Clamps the given value so that it is greater than or equal to the
 *        threshold.
 */
template<typename T_data>
inline T_data clamp_above(T_data v, T_data threshold)
{
    if(v <= threshold)
    {
        return threshold;
    }
    return v;
}

/*!
 * \brief Clamps the given value so that it is less than or equal to the
 *        threshold.
 */
template<typename T_data>
inline T_data clamp_below(T_data v, T_data threshold)
{
    if(v >= threshold)
    {
        return threshold;
    }
    return v;
}

/*!
 * \brief Clamps the given value so that it is greater than or equal to the
 *        lower threshold and less than or equal to the upper threshold.
 *
 * \warning If upper_threshold is less than lower_threshold the result of this
 *          function is undefined.
 */
template<typename T_data>
inline T_data clamp(T_data v, T_data lower_threshold, T_data upper_threshold)
{
    if(v <= lower_threshold)
    {
        return lower_threshold;
    }
    if(v >= upper_threshold)
    {
        return upper_threshold;
    }

    return v;
}

/*!
 * \brief Calculates the exponent a raised to the power of b.
 *
 * \warning This is a performance orientated version of power that does not
 *          support negative exponents.
 */
template<typename T_data>
T_data pow_fast(T_data a, T_data b)
{
    return std::exp(b * std::log(a));
}

/*!
 * \brief Computes the reciprocal (or multiplicative inverse) of the square
 *        root for the given value.
 *
 * \note If T_data is float this will use the Fast Inverse Square Root to
 *       perform the calculation.
 */
template<typename T_data>
inline T_data rsqrt(T_data v)
{
    return static_cast<T_data>(1) / static_cast<T_data>(std::sqrt(v));
}

//---------------T E M P L A T E -- S P E C I A L I S A T I O N S---------------

template<>
inline float rsqrt(float v)
{
    // straight from Quake III Arena
    static const float threehalfs = 1.5F;

    float x2 = v * 0.5F;
    float y  = v;
    // evil floating point bit level hacking
    arc::uint32 i;
    std::memcpy(&i, &y, sizeof(float));
    // what the fuck?
    i  = 0x5f3759DF - (i >> 1);
    std::memcpy(&y, &i, sizeof(float));
    // y  = *((float*) &i);
    // 1st iteration
    y  = y * (threehalfs - (x2 * y * y));
    // 2nd iteration, this can be removed
    return y;
}

//------------------------------------------------------------------------------

/*!
 * \brief Checks whether two floating point values are equal or almost equal.
 *
 * This performs a two stage check:
 *
 * - First the values are subtracted from one another and if the absolute result
 *   is less than or equal to ```delta_threshold``` then this operation resolves
 *   true.
 *
 * - Second the integer representations of the values are subtracted from one
 *   another and if the absolute result is less than or equal to
 *   ```ulps_threshold``` then this function resolves true.
 *
 * The first check is performed for the purpose of values near 0 where ULPs
 * style comparisons break down, e.g. ```0.0F == -0.0F```.
 *
 * The second comparison is a comparison of the difference of units in last
 * place (ULPs) between the two floats. This effectively compares the number
 * of possible float representations between the two values. Larger numbers with
 * less precision will have a bigger numerical difference than two smaller
 * values with more precision for the same ULPs difference.
 *
 * \param a The first float to compare.
 * \param b The second float to compare.
 * \param delta_threshold If ```a``` and ```b``` have a difference less than
 *                        or equal to this, they are considered equal.
 * \param ulps_threshold If ```a``` and ```b``` have units in last place
 *                       difference less than or equal to this, they are
 *                       considered equal.
 */
bool float_equals(
        float a,
        float b,
        float delta_threshold = FLT_EPSILON,
        arc::uint32 ulps_threshold = 8);

} // namespace math
} // namespace arc

#endif
