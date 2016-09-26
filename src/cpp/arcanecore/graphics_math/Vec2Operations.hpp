/*!
 * \file
 * \brief Functions and operators related to Vec2 objects.
 * \author David Saxon
 *
 * These functions and operations are separated into a different file than
 * Vec2.hpp to reduce compile time dependencies.
 */
#ifndef ARCANECORE_GM_VEC2OPERATIONS_HPP_
#define ARCANECORE_GM_VEC2OPERATIONS_HPP_

#include <cmath>

#include "arcanecore/base/str/UTF8String.hpp"
#include "arcanecore/graphics_math/Vec2.hpp"

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
 * Concatenates the given Vec2 onto the given stream.
 */
template <typename DataType>
std::ostream& operator<<(std::ostream& stream, const Vec2<DataType>& v)
{
    stream << "(" << v.x << ", " << v.y << ")";
    return stream;
}

/*!
 * \brief UTF8String stream operator.
 *
 * Concatenates the given Vec2 onto the given UTF8String.
 */
template <typename DataType>
arc::str::UTF8String& operator<<(
        arc::str::UTF8String& s,
        const Vec2<DataType>& v)
{
    s << "(" << v.x << ", " << v.y << ")";
    return s;
}

/*!
 * \brief Equality operator.
 *
 * \note This uses the ```==``` operator on the internal components.
 */
template <typename DataType>
bool operator==(const Vec2<DataType>& a, const Vec2<DataType>& b)
{
    return a.x == b.x && a.y == b.y;
}

/*!
 * \brief Inequality operator.
 *
 * \note This uses the ```==``` operator on the internal components.
 */
template <typename DataType>
bool operator!=(const Vec2<DataType>& a, const Vec2<DataType>& b)
{
    return !(a == b);
}

/*!
 * \brief Negation operator.
 *
 * Returns a negated copy of this Vec2.
 */
template <typename DataType>
Vec2<DataType> operator-(const Vec2<DataType>& v)
{
    return Vec2<DataType>(-v.x, -v.y);
}

/*!
 * \brief Addition operator.
 *
 * Adds the Vec2 ```b``` to the Vec2 ```a``` and returns the result as a new
 * Vec2.
 */
template <typename DataType>
Vec2<DataType> operator+(const Vec2<DataType>& a, const Vec2<DataType>& b)
{
    return Vec2<DataType>(a.x + b.x, a.y + b.y);
}

/*!
 * \brief Compound addition operator.
 *
 * Adds the Vec2 ```b``` to the Vec2 ```a``` and applies the result to ```a```.
 *
 * \returns A reference to ```a``` after the addition has been performed.
 */
template <typename DataType>
Vec2<DataType>& operator+=(Vec2<DataType>& a, const Vec2<DataType>& b)
{
    a.x += b.x;
    a.y += b.y;

    return a;
}

/*!
 * \brief Scalar addition operator.
 *
 * Adds the given scalar to each component of the Vec2 and returns the result as
 * a new Vec2.
 */
template <typename DataType>
Vec2<DataType> operator+(const Vec2<DataType>& v, const DataType& scalar)
{
    return Vec2<DataType>(v.x + scalar, v.y + scalar);
}

/*!
 * \brief Scalar compound addition operator.
 *
 * Adds the given scalar to each component of the Vec2 and applies the results
 * to the Vec2.
 *
 * \returns A reference to the Vec2 after the addition has been performed.
 */
template <typename DataType>
Vec2<DataType>& operator+=(Vec2<DataType>& v, const DataType& scalar)
{
    v.x += scalar;
    v.y += scalar;

    return v;
}

/*!
 * \brief Subtraction operator.
 *
 * Subtracts the Vec2 ```b``` from the Vec2 ```a``` and returns the result as a
 * new Vec2.
 */
template <typename DataType>
Vec2<DataType> operator-(const Vec2<DataType>& a, const Vec2<DataType>& b)
{
    return Vec2<DataType>(a.x - b.x, a.y - b.y);
}

/*!
 * \brief Compound subtraction operator operator.
 *
 * Subtracts the Vec2 ```b``` from the Vec2 ```a`` and applies the result to
 * ```a```.
 *
 * \returns A reference to ```a``` after the subtraction has been performed.
 */
template <typename DataType>
Vec2<DataType>& operator-=(Vec2<DataType>& a, const Vec2<DataType>& b)
{
    a.x -= b.x;
    a.y -= b.y;

    return a;
}

/*!
 * \brief Scalar subtraction operator.
 *
 * Subtracts the given scalar from each component of the Vec2 and returns the
 * results as a new Vec2.
 */
template <typename DataType>
Vec2<DataType> operator-(const Vec2<DataType>& v, const DataType& scalar)
{
    return Vec2<DataType>(v.x - scalar, v.y - scalar);
}

/*!
 * \brief Scalar compound subtraction operator.
 *
 * Subtracts the given scalar from each component of the Vec2 and applies the
 * results to the Vec2.
 *
 * \returns A reference to the Vec2 after the subtraction has been performed.
 */
template <typename DataType>
Vec2<DataType>& operator-=(Vec2<DataType>& v, const DataType& scalar)
{
    v.x -= scalar;
    v.y -= scalar;

    return v;
}

/*!
 * \brief Multiplication operator.
 *
 * Multiplies the Vec2 ```a``` by the Vec2 ```b``` and returns the result as a
 * new Vec2.
 */
template <typename DataType>
Vec2<DataType> operator*(const Vec2<DataType>& a, const Vec2<DataType>& b)
{
    return Vec2<DataType>(a.x * b.x, a.y * b.y);
}

/*!
 * \brief Compound multiplication operator operator.
 *
 * Multiplies the Vec2 ```a``` by the Vec2 ```b`` and applies the result to
 * ```a```.
 *
 * \returns A reference to ```a``` after the multiplication has been performed.
 */
template <typename DataType>
Vec2<DataType>& operator*=(Vec2<DataType>& a, const Vec2<DataType>& b)
{
    a.x *= b.x;
    a.y *= b.y;

    return a;
}

/*!
 * \brief Scalar multiplication operator.
 *
 * Multiplies the given scalar by each component of the Vec2 and returns the
 * results as a new Vec2.
 */
template <typename DataType>
Vec2<DataType> operator*(const Vec2<DataType>& v, const DataType& scalar)
{
    return Vec2<DataType>(v.x * scalar, v.y * scalar);
}

/*!
 * \brief Scalar compound multiplication operator.
 *
 * Multiplies the given scalar by each component of the Vec2 and applies the
 * results to the Vec2.
 *
 * \returns A reference to the Vec2 after the multiplication has been performed.
 */
template <typename DataType>
Vec2<DataType>& operator*=(Vec2<DataType>& v, const DataType& scalar)
{
    v.x *= scalar;
    v.y *= scalar;

    return v;
}

/*!
 * \brief Division operator.
 *
 * Divides the Vec2 ```a``` by the Vec2 ```b``` and returns the result as a
 * new Vec2.
 */
template <typename DataType>
Vec2<DataType> operator/(const Vec2<DataType>& a, const Vec2<DataType>& b)
{
    return Vec2<DataType>(a.x / b.x, a.y / b.y);
}

/*!
 * \brief Compound division operator operator.
 *
 * Divides the Vec2 ```a``` by the Vec2 ```b`` and applies the result to
 * ```a```.
 *
 * \returns A reference to ```a``` after the division has been performed.
 */
template <typename DataType>
Vec2<DataType>& operator/=(Vec2<DataType>& a, const Vec2<DataType>& b)
{
    a.x /= b.x;
    a.y /= b.y;

    return a;
}

/*!
 * \brief Scalar division operator.
 *
 * Divides the given scalar by each component of the Vec2 and returns the
 * results as a new Vec2.
 */
template <typename DataType>
Vec2<DataType> operator/(const Vec2<DataType>& v, const DataType& scalar)
{
    return Vec2<DataType>(v.x / scalar, v.y / scalar);
}

/*!
 * \brief Scalar compound division operator.
 *
 * Divides the given scalar by each component of the Vec2 and applies the
 * results to the Vec2.
 *
 * \returns A reference to the Vec2 after the division has been performed.
 */
template <typename DataType>
Vec2<DataType>& operator/=(Vec2<DataType>& v, const DataType& scalar)
{
    v.x /= scalar;
    v.y /= scalar;

    return v;
}

//------------------------------------------------------------------------------
//                                   FUNCTIONS
//------------------------------------------------------------------------------

/*!
 * \brief Calculates and returns the squared magnitude of the given Vec2.
 *
 * \note When this can be used (e.g. finding the difference between magnitudes)
 *       this is more efficient than magnitude() since it avoid have to
 *       calculate the squared root.
 */
template <typename DataType>
DataType magnitude2(const Vec2<DataType>& v)
{
    return (v.x * v.x) + (v.y * v.y);
}

/*!
 * \brief Calculates and returns the magnitude of the given Vec2.
 */
template <typename DataType>
DataType magnitude(const Vec2<DataType>& v)
{
    return static_cast<DataType>(std::sqrt(magnitude2(v)));
}

/*!
 * \brief Returns a normalised copy of the given Vec2.
 */
template <typename DataType>
Vec2<DataType> normalise(const Vec2<DataType>& v)
{
    // copy to return
    Vec2<DataType> ret(v);
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
 * \brief Computes and returns the dot product of the Vec2s.
 */
template <typename DataType>
DataType dot(const Vec2<DataType>& a, const Vec2<DataType>& b)
{
    return (a.x * b.x) + (a.y * b.y);
}

} // namespace gm
} // namespace arc

#endif
