/*!
 * \file
 * \brief Functions and operators related to Vec4 objects.
 * \author David Saxon
 *
 * These functions and operations are separated into a different file than
 * Vec4.hpp to reduce compile time dependencies.
 */
#ifndef ARCANECORE_GM_VEC4OPERATIONS_HPP_
#define ARCANECORE_GM_VEC4OPERATIONS_HPP_

#include "arcanecore/base/str/UTF8String.hpp"
#include "arcanecore/graphics_math/Vec4.hpp"

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
 * Concatenates the given Vec4 onto the given stream.
 */
template <typename DataType>
std::ostream& operator<<(std::ostream& stream, const Vec4<DataType>& v)
{
    stream << "(" << v.x << ", " << v.y << ", " << v.z << ", " << v.w << ")";
    return stream;
}

/*!
 * \brief UTF8String stream operator.
 *
 * Concatenates the given Vec4 onto the given UTF8String.
 */
template <typename DataType>
arc::str::UTF8String& operator<<(
        arc::str::UTF8String& s,
        const Vec4<DataType>& v)
{
    s << "(" << v.x << ", " << v.y << ", " << v.z << ", " << v.w << ")";
    return s;
}

/*!
 * \brief Equality operator.
 *
 * \note This uses the ```==``` operator on the internal components.
 */
template <typename DataType>
bool operator==(const Vec4<DataType>& a, const Vec4<DataType>& b)
{
    return a.x == b.x && a.y == b.y && a.z == b.z && a.w == b.w;
}

/*!
 * \brief Inequality operator.
 *
 * \note This uses the ```==``` operator on the internal components.
 */
template <typename DataType>
bool operator!=(const Vec4<DataType>& a, const Vec4<DataType>& b)
{
    return !(a == b);
}

/*!
 * \brief Negation operator.
 *
 * Returns a negated copy of this Vec4.
 */
template <typename DataType>
Vec4<DataType> operator-(const Vec4<DataType>& v)
{
    return Vec4<DataType>(-v.x, -v.y, -v.z, -v.w);
}

/*!
 * \brief Addition operator.
 *
 * Adds the two Vec4 objects together and returns the result in a new Vec4.
 */
template <typename DataType>
Vec4<DataType> operator+(const Vec4<DataType>& a, const Vec4<DataType>& b)
{
    return Vec4<DataType>(
        a.x + b.x,
        a.y + b.y,
        a.z + b.z,
        a.w + b.w
    );
}

/*!
 * \brief Compound addition operator.
 *
 * Adds the two Vec4 objects together and applies the results to ```a```.
 *
 * \returns A reference to ```a``` after the addition has been performed.
 */
template <typename DataType>
Vec4<DataType>& operator+=(Vec4<DataType>& a, const Vec4<DataType>& b)
{
    a.x += b.x;
    a.y += b.y;
    a.z += b.z;
    a.w += b.w;

    return a;
}

/*!
 * \brief Scalar addition operator.
 *
 * Adds the given scalar to each component of the Vec4 and returns the result as
 * a new Vec4.
 */
template <typename DataType>
Vec4<DataType> operator+(const Vec4<DataType>& v, const DataType& scalar)
{
    return Vec4<DataType>(
        v.x + scalar,
        v.y + scalar,
        v.z + scalar,
        v.w + scalar
    );
}

/*!
 * \brief Scalar compound addition operator.
 *
 * Adds the given scalar to each component of the Vec4 and applies the results
 * to the Vec4.
 *
 * \returns A reference to the Vec4 after the addition has been performed.
 */
template <typename DataType>
Vec4<DataType>& operator+=(Vec4<DataType>& v, const DataType& scalar)
{
    v.x += scalar;
    v.y += scalar;
    v.z += scalar;
    v.w += scalar;

    return v;
}

/*!
 * \brief Subtraction operator.
 *
 * Subtracts the Vec4 ```b``` from the Vec4 ```a``` and returns the result as a
 * new Vec4.
 */
template <typename DataType>
Vec4<DataType> operator-(const Vec4<DataType>& a, const Vec4<DataType>& b)
{
    return Vec4<DataType>(
        a.x - b.x,
        a.y - b.y,
        a.z - b.z,
        a.w - b.w
    );
}

/*!
 * \brief Compound subtraction operator operator.
 *
 * Subtracts the Vec4 ```b``` from the Vec4 ```a`` and applies the result to
 * ```a```.
 *
 * \returns A reference to ```a``` after the subtraction has been performed.
 */
template <typename DataType>
Vec4<DataType>& operator-=(Vec4<DataType>& a, const Vec4<DataType>& b)
{
    a.x -= b.x;
    a.y -= b.y;
    a.z -= b.z;
    a.w -= b.w;

    return a;
}

/*!
 * \brief Scalar subtraction operator.
 *
 * Subtracts the given scalar from each component of the Vec4 and returns the
 * results as a new Vec4.
 */
template <typename DataType>
Vec4<DataType> operator-(const Vec4<DataType>& v, const DataType& scalar)
{
    return Vec4<DataType>(
        v.x - scalar,
        v.y - scalar,
        v.z - scalar,
        v.w - scalar
    );
}

/*!
 * \brief Scalar compound subtraction operator.
 *
 * Subtracts the given scalar from each component of the Vec4 and applies the
 * results to the Vec4.
 *
 * \returns A reference to the Vec4 after the subtraction has been performed.
 */
template <typename DataType>
Vec4<DataType>& operator-=(Vec4<DataType>& v, const DataType& scalar)
{
    v.x -= scalar;
    v.y -= scalar;
    v.z -= scalar;
    v.w -= scalar;

    return v;
}

/*!
 * \brief Multiplication operator.
 *
 * Multiplies the Vec4 ```a``` by the Vec4 ```b``` and returns the result as a
 * new Vec4.
 */
template <typename DataType>
Vec4<DataType> operator*(const Vec4<DataType>& a, const Vec4<DataType>& b)
{
    return Vec4<DataType>(a.x * b.x, a.y * b.y, a.z * b.z, a.w * b.w);
}

/*!
 * \brief Compound multiplication operator operator.
 *
 * Multiplies the Vec4 ```a``` by the Vec4 ```b`` and applies the result to
 * ```a```.
 *
 * \returns A reference to ```a``` after the multiplication has been performed.
 */
template <typename DataType>
Vec4<DataType>& operator*=(Vec4<DataType>& a, const Vec4<DataType>& b)
{
    a.x *= b.x;
    a.y *= b.y;
    a.z *= b.z;
    a.w *= b.w;

    return a;
}

/*!
 * \brief Scalar multiplication operator.
 *
 * Multiplies the given scalar by each component of the Vec4 and returns the
 * results as a new Vec4.
 */
template <typename DataType>
Vec4<DataType> operator*(const Vec4<DataType>& v, const DataType& scalar)
{
    return Vec4<DataType>(
        v.x * scalar,
        v.y * scalar,
        v.z * scalar,
        v.w * scalar
    );
}

/*!
 * \brief Scalar compound multiplication operator.
 *
 * Multiplies the given scalar by each component of the Vec4 and applies the
 * results to the Vec4.
 *
 * \returns A reference to the Vec4 after the multiplication has been performed.
 */
template <typename DataType>
Vec4<DataType>& operator*=(Vec4<DataType>& v, const DataType& scalar)
{
    v.x *= scalar;
    v.y *= scalar;
    v.z *= scalar;
    v.w *= scalar;

    return v;
}

/*!
 * \brief Division operator.
 *
 * Divides the Vec4 ```a``` by the Vec4 ```b``` and returns the result as a
 * new Vec4.
 */
template <typename DataType>
Vec4<DataType> operator/(const Vec4<DataType>& a, const Vec4<DataType>& b)
{
    return Vec4<DataType>(a.x / b.x, a.y / b.y, a.z / b.z, a.w / b.w);
}

/*!
 * \brief Compound division operator operator.
 *
 * Divides the Vec4 ```a``` by the Vec4 ```b`` and applies the result to
 * ```a```.
 *
 * \returns A reference to ```a``` after the division has been performed.
 */
template <typename DataType>
Vec4<DataType>& operator/=(Vec4<DataType>& a, const Vec4<DataType>& b)
{
    a.x /= b.x;
    a.y /= b.y;
    a.z /= b.z;
    a.w /= b.w;

    return a;
}

/*!
 * \brief Scalar division operator.
 *
 * Divides the given scalar by each component of the Vec4 and returns the
 * results as a new Vec4.
 */
template <typename DataType>
Vec4<DataType> operator/(const Vec4<DataType>& v, const DataType& scalar)
{
    return Vec4<DataType>(
        v.x / scalar,
        v.y / scalar,
        v.z / scalar,
        v.w / scalar
    );
}

/*!
 * \brief Scalar compound division operator.
 *
 * Divides the given scalar by each component of the Vec4 and applies the
 * results to the Vec4.
 *
 * \returns A reference to the Vec4 after the division has been performed.
 */
template <typename DataType>
Vec4<DataType>& operator/=(Vec4<DataType>& v, const DataType& scalar)
{
    v.x /= scalar;
    v.y /= scalar;
    v.z /= scalar;
    v.w /= scalar;

    return v;
}

} // namespace gm
} // namespace arc

#endif
