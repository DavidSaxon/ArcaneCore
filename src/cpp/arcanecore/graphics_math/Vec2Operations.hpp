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
 * Adds the two Vec2 objects together and returns the result in a new Vec2.
 */
template <typename DataType>
Vec2<DataType> operator+(const Vec2<DataType>& a, const Vec2<DataType>& b)
{
    return Vec2<DataType>(a.x + b.x, a.y + b.y);
}

/*!
 * \brief Compound addition operator.
 *
 * Adds the two Vec2 objects together and applies the results to ```a```.
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

} // namespace gm
} // namespace arc

#endif
