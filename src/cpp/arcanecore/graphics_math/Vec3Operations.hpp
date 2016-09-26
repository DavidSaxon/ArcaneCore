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

#include <cmath>

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

/*!
 * \brief Subtraction operator.
 *
 * Subtracts the Vec3 ```b``` from the Vec3 ```a``` and returns the result as a
 * new Vec3.
 */
template <typename DataType>
Vec3<DataType> operator-(const Vec3<DataType>& a, const Vec3<DataType>& b)
{
    return Vec3<DataType>(a.x - b.x, a.y - b.y, a.z - b.z);
}

/*!
 * \brief Compound subtraction operator operator.
 *
 * Subtracts the Vec3 ```b``` from the Vec3 ```a`` and applies the result to
 * ```a```.
 *
 * \returns A reference to ```a``` after the subtraction has been performed.
 */
template <typename DataType>
Vec3<DataType>& operator-=(Vec3<DataType>& a, const Vec3<DataType>& b)
{
    a.x -= b.x;
    a.y -= b.y;
    a.z -= b.z;

    return a;
}

/*!
 * \brief Scalar subtraction operator.
 *
 * Subtracts the given scalar from each component of the Vec3 and returns the
 * results as a new Vec3.
 */
template <typename DataType>
Vec3<DataType> operator-(const Vec3<DataType>& v, const DataType& scalar)
{
    return Vec3<DataType>(v.x - scalar, v.y - scalar, v.z - scalar);
}

/*!
 * \brief Scalar compound subtraction operator.
 *
 * Subtracts the given scalar from each component of the Vec3 and applies the
 * results to the Vec3.
 *
 * \returns A reference to the Vec3 after the subtraction has been performed.
 */
template <typename DataType>
Vec3<DataType>& operator-=(Vec3<DataType>& v, const DataType& scalar)
{
    v.x -= scalar;
    v.y -= scalar;
    v.z -= scalar;

    return v;
}

/*!
 * \brief Multiplication operator.
 *
 * Multiplies the Vec3 ```a``` by the Vec3 ```b``` and returns the result as a
 * new Vec3.
 */
template <typename DataType>
Vec3<DataType> operator*(const Vec3<DataType>& a, const Vec3<DataType>& b)
{
    return Vec3<DataType>(a.x * b.x, a.y * b.y, a.z * b.z);
}

/*!
 * \brief Compound multiplication operator operator.
 *
 * Multiplies the Vec3 ```a``` by the Vec3 ```b`` and applies the result to
 * ```a```.
 *
 * \returns A reference to ```a``` after the multiplication has been performed.
 */
template <typename DataType>
Vec3<DataType>& operator*=(Vec3<DataType>& a, const Vec3<DataType>& b)
{
    a.x *= b.x;
    a.y *= b.y;
    a.z *= b.z;

    return a;
}

/*!
 * \brief Scalar multiplication operator.
 *
 * Multiplies the given scalar by each component of the Vec3 and returns the
 * results as a new Vec3.
 */
template <typename DataType>
Vec3<DataType> operator*(const Vec3<DataType>& v, const DataType& scalar)
{
    return Vec3<DataType>(v.x * scalar, v.y * scalar, v.z  * scalar);
}

/*!
 * \brief Scalar compound multiplication operator.
 *
 * Multiplies the given scalar by each component of the Vec3 and applies the
 * results to the Vec3.
 *
 * \returns A reference to the Vec3 after the multiplication has been performed.
 */
template <typename DataType>
Vec3<DataType>& operator*=(Vec3<DataType>& v, const DataType& scalar)
{
    v.x *= scalar;
    v.y *= scalar;
    v.z *= scalar;

    return v;
}

/*!
 * \brief Division operator.
 *
 * Divides the Vec3 ```a``` by the Vec3 ```b``` and returns the result as a
 * new Vec3.
 */
template <typename DataType>
Vec3<DataType> operator/(const Vec3<DataType>& a, const Vec3<DataType>& b)
{
    return Vec3<DataType>(a.x / b.x, a.y / b.y, a.z / b.z);
}

/*!
 * \brief Compound division operator operator.
 *
 * Divides the Vec3 ```a``` by the Vec3 ```b`` and applies the result to
 * ```a```.
 *
 * \returns A reference to ```a``` after the division has been performed.
 */
template <typename DataType>
Vec3<DataType>& operator/=(Vec3<DataType>& a, const Vec3<DataType>& b)
{
    a.x /= b.x;
    a.y /= b.y;
    a.z /= b.z;

    return a;
}

/*!
 * \brief Scalar division operator.
 *
 * Divides the given scalar by each component of the Vec3 and returns the
 * results as a new Vec3.
 */
template <typename DataType>
Vec3<DataType> operator/(const Vec3<DataType>& v, const DataType& scalar)
{
    return Vec3<DataType>(v.x / scalar, v.y / scalar, v.z / scalar);
}

/*!
 * \brief Scalar compound division operator.
 *
 * Divides the given scalar by each component of the Vec3 and applies the
 * results to the Vec3.
 *
 * \returns A reference to the Vec3 after the division has been performed.
 */
template <typename DataType>
Vec3<DataType>& operator/=(Vec3<DataType>& v, const DataType& scalar)
{
    v.x /= scalar;
    v.y /= scalar;
    v.z /= scalar;

    return v;
}

//------------------------------------------------------------------------------
//                                   FUNCTIONS
//------------------------------------------------------------------------------

/*!
 * \brief Calculates and returns the squared magnitude of the given Vec3.
 *
 * \note When this can be used (e.g. finding the difference between magnitudes)
 *       this is more efficient than magnitude() since it avoid have to
 *       calculate the squared root.
 */
template <typename DataType>
DataType magnitude2(const Vec3<DataType>& v)
{
    return (v.x * v.x) + (v.y * v.y) + (v.z * v.z);
}

/*!
 * \brief Calculates and returns the magnitude of the given Vec3.
 */
template <typename DataType>
DataType magnitude(const Vec3<DataType>& v)
{
    return static_cast<DataType>(std::sqrt(magnitude2(v)));
}

/*!
 * \brief Returns a normalised copy of the given Vec3.
 */
template <typename DataType>
Vec3<DataType> normalise(const Vec3<DataType>& v)
{
    // copy to return
    Vec3<DataType> ret(v);
    // use squared magnitude here, since we may not need to the squared value
    DataType mag = magnitude2(v);
    if(mag > 0)
    {
        DataType inverse =
            static_cast<DataType>(1) / static_cast<DataType>(std::sqrt(mag));
        ret *= inverse;
    }
    return ret;
}

/*!
 * \brief Computes and returns the dot product of the Vec3s.
 */
template <typename DataType>
DataType dot(const Vec3<DataType>& a, const Vec3<DataType>& b)
{
    return (a.x * b.x) + (a.y * b.y) + (a.z * b.z);
}

} // namespace gm
} // namespace arc

#endif
