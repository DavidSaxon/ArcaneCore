/*!
 * \file
 * \author David Saxon
 * \brief Math operations for vectors.
 */
#ifndef ARCANECORE_GM_VECTORMATH_HPP_
#define ARCANECORE_GM_VECTORMATH_HPP_

#include <algorithm>

#include <arcanecore/base/math/MathOperations.hpp>

#include "arcanecore/gm/Vector.hpp"

namespace arc
{
namespace gm
{

/*!
 * \brief Returns a copy of the given vector with all components made absolute.
 */
template<typename T_scalar, std::size_t T_dimensions, bool T_use_simd>
inline Vector<T_scalar, T_dimensions, T_use_simd> abs(
        const Vector<T_scalar, T_dimensions, T_use_simd>& v)
{
    Vector<T_scalar, T_dimensions, T_use_simd> r;
    for(std::size_t i = 0; i < T_dimensions; ++i)
    {
        r[i] = arc::math::abs<T_scalar>(v[i]);
    }
    return r;
}

/*!
 * \brief Returns a new vector which has the smallest of each of of the
 *        components of the vectors a and b.
 */
template<typename T_scalar, std::size_t T_dimensions, bool T_use_simd>
inline Vector<T_scalar, T_dimensions, T_use_simd> min(
        const Vector<T_scalar, T_dimensions, T_use_simd>& a,
        const Vector<T_scalar, T_dimensions, T_use_simd>& b)
{
    Vector<T_scalar, T_dimensions, T_use_simd> r;
    for(std::size_t i = 0; i < T_dimensions; ++i)
    {
        r[i] = std::min<T_scalar>(a[i], b[i]);
    }
    return r;
}

/*!
 * \brief Returns a new vector which has the largest of each of of the
 *        components of the vectors a and b.
 */
template<typename T_scalar, std::size_t T_dimensions, bool T_use_simd>
inline Vector<T_scalar, T_dimensions, T_use_simd> max(
        const Vector<T_scalar, T_dimensions, T_use_simd>& a,
        const Vector<T_scalar, T_dimensions, T_use_simd>& b)
{
    Vector<T_scalar, T_dimensions, T_use_simd> r;
    for(std::size_t i = 0; i < T_dimensions; ++i)
    {
        r[i] = std::max<T_scalar>(a[i], b[i]);
    }
    return r;
}

/*!
 * \brief Clamps the each component in the given vector so that it is greater
 *        than or equal to the scalar and returns the result as a new vector.
 */
template<typename T_scalar, std::size_t T_dimensions, bool T_use_simd>
inline Vector<T_scalar, T_dimensions, T_use_simd> clamp_above(
        const Vector<T_scalar, T_dimensions, T_use_simd>& v,
        T_scalar threshold)
{
    Vector<T_scalar, T_dimensions, T_use_simd> r;
    for(std::size_t i = 0; i < T_dimensions; ++i)
    {
        r[i] = arc::math::clamp_above<T_scalar>(v[i], threshold);
    }
    return r;
}

/*!
 * \brief Clamps the each component in the given vector so that it is greater
 *        than or equal to the respective component in the threshold vector and
 *        returns the result as a new vector.
 */
template<typename T_scalar, std::size_t T_dimensions, bool T_use_simd>
inline Vector<T_scalar, T_dimensions, T_use_simd> clamp_above(
        const Vector<T_scalar, T_dimensions, T_use_simd>& v,
        const Vector<T_scalar, T_dimensions, T_use_simd>& threshold)
{
    Vector<T_scalar, T_dimensions, T_use_simd> r;
    for(std::size_t i = 0; i < T_dimensions; ++i)
    {
        r[i] = arc::math::clamp_above<T_scalar>(v[i], threshold[i]);
    }
    return r;
}

/*!
 * \brief Clamps the each component in the given vector so that it is less
 *        than or equal to the scalar and returns the result as a new vector.
 */
template<typename T_scalar, std::size_t T_dimensions, bool T_use_simd>
inline Vector<T_scalar, T_dimensions, T_use_simd> clamp_below(
        const Vector<T_scalar, T_dimensions, T_use_simd>& v,
        T_scalar threshold)
{
    Vector<T_scalar, T_dimensions, T_use_simd> r;
    for(std::size_t i = 0; i < T_dimensions; ++i)
    {
        r[i] = arc::math::clamp_below<T_scalar>(v[i], threshold);
    }
    return r;
}

/*!
 * \brief Clamps the each component in the given vector so that it is less
 *        than or equal to the respective component in the threshold vector and
 *        returns the result as a new vector.
 */
template<typename T_scalar, std::size_t T_dimensions, bool T_use_simd>
inline Vector<T_scalar, T_dimensions, T_use_simd> clamp_below(
        const Vector<T_scalar, T_dimensions, T_use_simd>& v,
        const Vector<T_scalar, T_dimensions, T_use_simd>& threshold)
{
    Vector<T_scalar, T_dimensions, T_use_simd> r;
    for(std::size_t i = 0; i < T_dimensions; ++i)
    {
        r[i] = arc::math::clamp_below<T_scalar>(v[i], threshold[i]);
    }
    return r;
}

/*!
 * \brief Clamps the each component in the given vector so that it is greater
 *        than or equal to the lower threshold scalar and less than or equal to
 *        the upper threshold scalar.
 *
 * \warning If upper_threshold is less than lower_threshold the result of this
 *          function is undefined.
 *
 * \return The result as a new vector.
 */
template<typename T_scalar, std::size_t T_dimensions, bool T_use_simd>
inline Vector<T_scalar, T_dimensions, T_use_simd> clamp(
        const Vector<T_scalar, T_dimensions, T_use_simd>& v,
        T_scalar lower_threshold,
        T_scalar upper_threshold)
{
    Vector<T_scalar, T_dimensions, T_use_simd> r;
    for(std::size_t i = 0; i < T_dimensions; ++i)
    {
        r[i] = arc::math::clamp<T_scalar>(
            v[i],
            lower_threshold,
            upper_threshold
        );
    }
    return r;
}

/*!
 * \brief Clamps the each component in the given vector so that it is greater
 *        than or equal to the respective component in the lower threshold
 *        vector and is less than or equal to each respective in the upper
 *        threshold vector.
 *
 * \warning If a component in upper_threshold vector is less than a respective
 *          component n the lower_threshold vector the result of this function
 *          is undefined.
 *
 * \return The result as a new vector.
 */
template<typename T_scalar, std::size_t T_dimensions, bool T_use_simd>
inline Vector<T_scalar, T_dimensions, T_use_simd> clamp(
        const Vector<T_scalar, T_dimensions, T_use_simd>& v,
        const Vector<T_scalar, T_dimensions, T_use_simd>& lower_threshold,
        const Vector<T_scalar, T_dimensions, T_use_simd>& upper_threshold)
{
    Vector<T_scalar, T_dimensions, T_use_simd> r;
    for(std::size_t i = 0; i < T_dimensions; ++i)
    {
        r[i] = arc::math::clamp<T_scalar>(
            v[i],
            lower_threshold[i],
            upper_threshold[i]
        );
    }
    return r;
}

} // namespace gm
} // namespace arc

#endif
