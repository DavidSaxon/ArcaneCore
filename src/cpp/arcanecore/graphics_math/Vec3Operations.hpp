/*!
 * \file
 * \brief Functions and operators related to Vec3 objects.
 * \author David Saxon
 *
 * These functions and operations are separated into a different file than
 * Vec3.hpp to reduce compile time dependencies.
 */
#ifndef ARCANECORE_GM_VEC3OPERATIONS_HPP_
#define ARCANECORE_GM_VEC3OPERATIONS_HPP_

#include "arcanecore/base/str/UTF8String.hpp"
#include "arcanecore/graphics_math/Vec3.hpp"

namespace arc
{
namespace gm
{

//------------------------------------------------------------------------------
//                                   OPERATORS
//------------------------------------------------------------------------------

/*!
 * \brief Stream operator.
 *
 * Concatenates the given Vec3 onto the given stream.
 */
template <typename DataType>
std::ostream& operator<<(std::ostream& stream, const Vec3<DataType>& v)
{
    stream << "(" << v.x << ", " << v.y << ", " << v.z << ")";
    return stream;
}

/*!
 * \brief UTF8String stream operator.
 *
 * Concatenates the given Vec3 onto the given UTF8String.
 */
template <typename DataType>
arc::str::UTF8String& operator<<(
        arc::str::UTF8String& s,
        const Vec3<DataType>& v)
{
    s << "(" << v.x << ", " << v.y << ", " << v.z << ")";
    return s;
}

/*!
 * \brief Equality operator.
 *
 * \note This uses the ```==``` operator on the internal components.
 */
template <typename DataType>
bool operator==(const Vec3<DataType>& a, const Vec3<DataType>& b)
{
    return a.x == b.x && a.y == b.y && a.z == b.z;
}

/*!
 * \brief Inequality operator.
 *
 * \note This uses the ```==``` operator on the internal components.
 */
template <typename DataType>
bool operator!=(const Vec3<DataType>& a, const Vec3<DataType>& b)
{
    return !(a == b);
}

/*!
 * \brief Negation operator.
 *
 * Returns a negated copy of this Vec3.
 */
template <typename DataType>
Vec3<DataType> operator-(const Vec3<DataType>& v)
{
    return Vec3<DataType>(-v.x, -v.y, -v.z);
}

/*!
 * \brief Addition operator.
 *
 * Adds the two Vec3 objects together and returns the result in a new Vec3.
 */
template <typename DataType>
Vec3<DataType> operator+(const Vec3<DataType>& a, const Vec3<DataType>& b)
{
    return Vec3<DataType>(a.x + b.x, a.y + b.y, a.z + b.z);
}

/*!
 * \brief Compound addition operator.
 *
 * Adds the two Vec3 objects together and applies the results to ```a```.
 *
 * \returns A reference to ```a``` after the addition has been performed.
 */
template <typename DataType>
Vec3<DataType>& operator+=(Vec3<DataType>& a, const Vec3<DataType>& b)
{
    a.x += b.x;
    a.y += b.y;
    a.z += b.z;

    return a;
}

/*!
 * \brief Scalar addition operator.
 *
 * Adds the given scalar to each component of the Vec3 and returns the result as
 * a new Vec3.
 */
template <typename DataType>
Vec3<DataType> operator+(const Vec3<DataType>& v, const DataType& scalar)
{
    return Vec3<DataType>(v.x + scalar, v.y + scalar, v.z + scalar);
}

/*!
 * \brief Scalar compound addition operator.
 *
 * Adds the given scalar to each component of the Vec3 and applies the results
 * to the Vec3.
 *
 * \returns A reference to the Vec3 after the addition has been performed.
 */
template <typename DataType>
Vec3<DataType>& operator+=(Vec3<DataType>& v, const DataType& scalar)
{
    v.x += scalar;
    v.y += scalar;
    v.z += scalar;

    return v;
}

} // namespace gm
} // namespace arc

#endif
