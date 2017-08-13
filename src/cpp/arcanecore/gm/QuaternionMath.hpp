/*!
 * \file
 * \author David Saxon
 * \brief Math operations for vectors.
 */
#ifndef ARCANECORE_GM_QUATERNIONMATH_HPP_
#define ARCANECORE_GM_QUATERNIONMATH_HPP_

#include <arcanecore/base/math/MathOperations.hpp>

#include "arcanecore/gm/Quaternion.hpp"


namespace arc
{
namespace gm
{

/*!
 * \brief Casts the components of the given quaternion to a new quaternion with
 *        T_out_scalar as the type.
 */
template<
    typename T_out_scalar,
    typename T_in_scalar,
    bool T_use_simd
>
inline Quaternion<T_out_scalar, T_use_simd> cast(
        const Quaternion<T_in_scalar, T_use_simd>& q)
{
    return Quaternion<T_out_scalar, T_use_simd>(
        static_cast<T_out_scalar>(q.x()),
        static_cast<T_out_scalar>(q.y()),
        static_cast<T_out_scalar>(q.z()),
        static_cast<T_out_scalar>(q.w())
    );
}

/*!
 * \brief Calculates and returns the squared magnitude of the given quaternion.
 */
template<typename T_scalar, bool T_use_simd>
inline T_scalar magnitude2(const Quaternion<T_scalar, T_use_simd>& q)
{
    return
        (q.x() * q.x()) +
        (q.y() * q.y()) +
        (q.z() * q.z()) +
        (q.w() * q.w());
}

/*!
 * \brief Calculates and returns the magnitude of the given quaternion.
 */
template<typename T_scalar, bool T_use_simd>
inline T_scalar magnitude(const Quaternion<T_scalar, T_use_simd>& q)
{
    return static_cast<T_scalar>(std::sqrt(magnitude2(q)));
}

/*!
 * \brief Returns a normalised copy of the given quaternion.
 */
template<typename T_scalar, bool T_use_simd>
inline Quaternion<T_scalar, T_use_simd> normalise(
        const Quaternion<T_scalar, T_use_simd>& q)
{
    T_scalar recip_mag = arc::math::rsqrt(magnitude2(q));
    return Quaternion<T_scalar, T_use_simd>(
        q.x() * recip_mag,
        q.y() * recip_mag,
        q.z() * recip_mag,
        q.w() * recip_mag
    );
}

/*!
 * \brief Converts the given quaternion to an axis angle.
 *
 * \param q The quaternion to convert.
 * \param out_angle The resulting angle.
 * \param out_axis The resulting axis.
 */
template<typename T_scalar, bool T_use_simd, bool T_other_use_simd>
inline void to_axis_angle(
        const Quaternion<T_scalar, T_use_simd>& q,
        T_scalar& out_angle,
        Vector<T_scalar, 3, T_other_use_simd>& out_axis)
{
    out_angle = static_cast<T_scalar>(2) * std::acos(q.w());
    T_scalar recip =  arc::math::rsqrt(
        static_cast<T_scalar>(1) - (q.w() * q.w())
    );
    // check for division by zero
    if(std::isinf(recip))
    {
        // doesn't matter which axis we use here
        out_axis[0] = static_cast<T_scalar>(1);
        out_axis[1] = static_cast<T_scalar>(0);
        out_axis[2] = static_cast<T_scalar>(0);
        return;
    }

    out_axis[0] = q.x() * recip;
    out_axis[1] = q.y() * recip;
    out_axis[2] = q.z() * recip;
}

// TODO: to euler?

} // namespace gm
} // namespace arc

// TODO: simd specialisations

#endif

