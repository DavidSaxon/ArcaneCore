/*!
 * \file
 * \author David Saxon
 * \brief Math operations for vectors.
 */
#ifndef ARCANECORE_GM_VECTORMATH_HPP_
#define ARCANECORE_GM_VECTORMATH_HPP_

#include <algorithm>
#include <cmath>

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

/*!
 * \brief Returns a normalised copy of the given vector.
 */
template<typename T_scalar, std::size_t T_dimensions, bool T_use_simd>
Vector<T_scalar, T_dimensions, T_use_simd> normalise(
        const Vector<T_scalar, T_dimensions, T_use_simd>& v)
{
    return v * arc::math::rsqrt(dot(v, v));
}

/*!
 * \brief Computes the dot product of vectors a and b.
 */
template<
    typename T_scalar,
    std::size_t T_dimensions,
    bool T_use_simd,
    bool T_other_use_simd
>
T_scalar dot(
    const Vector<T_scalar, T_dimensions, T_use_simd>& a,
    const Vector<T_scalar, T_dimensions, T_other_use_simd>& b)
{
    T_scalar r = 0;
    for(std::size_t i = 0; i < T_dimensions; ++i)
    {
        r += a[i] * b[i];
    }
    return r;
}

/*!
 * \brief Computes the cross product of vectors a and b.
 */
template<
    typename T_scalar,
    std::size_t T_dimensions,
    bool T_use_simd,
    bool T_other_use_simd
>
Vector<T_scalar, T_dimensions, T_use_simd> cross(
    const Vector<T_scalar, T_dimensions, T_use_simd>& a,
    const Vector<T_scalar, T_dimensions, T_other_use_simd>& b)
{
    // check dimensionality
    static_assert(
        T_dimensions == 3,
        "Cross product is only valid for vectors with a dimensionality of 3"
    );

    return Vector<T_scalar, T_dimensions, T_use_simd>(
        (a[1] * b[2]) - (b[1] * a[2]),
        (a[2] * b[0]) - (b[2] * a[0]),
        (a[0] * b[1]) - (b[0] * a[1])
    );
}

/*!
 * \brief Calculates and returns the squared magnitude of the given vector.
 *
 * \note When this can be used (e.g. finding the difference between magnitudes)
 *       this is more efficient than magnitude() since it avoid have to
 *       calculate the squared root.
 */
template<typename T_scalar, std::size_t T_dimensions, bool T_use_simd>
T_scalar magnitude2(const Vector<T_scalar, T_dimensions, T_use_simd>& v)
{
    return dot(v, v);
}

/*!
 * \brief Calculates and returns the magnitude of the given vector.
 */
template<typename T_scalar, std::size_t T_dimensions, bool T_use_simd>
T_scalar magnitude(const Vector<T_scalar, T_dimensions, T_use_simd>& v)
{
    return static_cast<T_scalar>(std::sqrt(magnitude2(v)));
}

/*!
 * \brief Calculates the distance between the vectors a and b.
 */
template<typename T_scalar, std::size_t T_dimensions, bool T_use_simd>
T_scalar distance(
        const Vector<T_scalar, T_dimensions, T_use_simd>& a,
        const Vector<T_scalar, T_dimensions, T_use_simd>& b)
{
    return magnitude(b - a);
}

/*!
 * \brief Returns the direction vector between the two points a and b.
 */
template<
    typename T_scalar,
    std::size_t T_dimensions,
    bool T_use_simd,
    bool T_other_use_simd
>
Vector<T_scalar, T_dimensions, T_use_simd> direction(
        const Vector<T_scalar, T_dimensions, T_use_simd>& a,
        const Vector<T_scalar, T_dimensions, T_other_use_simd>& b)
{
    Vector<T_scalar, T_dimensions, T_use_simd> diff(b - a);
    return Vector<T_scalar, T_dimensions, T_use_simd>(diff / magnitude(diff));
}

/*!
 * \brief Returns the single value directional angle of the difference between
 *        the x and y components of the vectors a and b.
 *
 * \note The directional vector between a and b is (1.0, 0.0), then the angle
 * would be 0.0, likewise if it were (-1.0, 0.0) the angle would be pi,
 * (0.0, 1.0) would have angle of pi/2, and (0.0, -1.0) would have angle of
 * -pi/2.
 */
template<
    typename T_scalar,
    std::size_t T_dimensions,
    bool T_use_simd,
    bool T_other_use_simd
>
T_scalar angle2(
        const Vector<T_scalar, T_dimensions, T_use_simd>& a,
        const Vector<T_scalar, T_dimensions, T_other_use_simd>& b)
{
    // check dimensionality
    static_assert(
        T_dimensions >= 2,
        "angle2 is only valid for vectors with a dimensionality of 2 or more"
    );

    Vector<T_scalar, T_dimensions, T_use_simd> d(direction(a, b));
    return std::atan2(d[1], d[0]);
}

// TODO: cast (takes template type and move to the top)

// TODO: floor?

// TODO: ceil?

// TODO: IsFinite

// TODO: pow?

// TODO: Sqrt

// TODO: Rsqrt

// TODO: Recip

// TODO: log?

// TODO: log2?

// TODO: Exp?

// TODO: Exp2?


} // namespace gm
} // namespace arc

//----------------------I N L I N E -- E X T E N S I O N S----------------------
#ifndef ARC_GM_DISABLE_SSE
    #include "arcanecore/gm/VectorMathSimd3f.inl"
    #include "arcanecore/gm/VectorMathSimd4f.inl"
#endif

#endif
