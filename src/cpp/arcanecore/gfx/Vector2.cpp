#include "arcanecore/gfx/Vector2.hpp"

#include "arcanecore/base/math/MathOperations.hpp"

namespace arc
{
namespace gfx
{

//------------------------------------------------------------------------------
//                                  CONSTRUCTORS
//------------------------------------------------------------------------------


Vector2::Vector2()
    :
    x(0.0F),
    y(0.0F),
    r(x),
    g(y)
{
}

Vector2::Vector2(float i_x, float i_y)
    :
    x(i_x),
    y(i_y),
    r(x),
    g(y)
{
}

Vector2::Vector2(float scalar)
    :
    x(scalar),
    y(scalar),
    r(x),
    g(y)
{
}

Vector2::Vector2(const Vector2& other)
    :
    x(other.x),
    y(other.y),
    r(x),
    g(y)
{
}

//------------------------------------------------------------------------------
//                                   OPERATORS
//------------------------------------------------------------------------------

Vector2& Vector2::operator=(const Vector2& other)
{
    x = other.x;
    y = other.y;

    return *this;
}

bool Vector2::operator==(const Vector2& other) const
{
    // TODO: this should be a raw equals
    return arc::math::float_equals(x, other.x) &&
           arc::math::float_equals(y, other.y);
}

bool Vector2::operator!=(const Vector2& other) const
{
    return !((*this) == other);
}

Vector2 Vector2::operator-() const
{
    return Vector2(-x, -y);
}

Vector2 Vector2::operator+(float scalar) const
{
    Vector2 v(*this);
    return v += scalar;
}

Vector2& Vector2::operator+=(float scalar)
{
    x += scalar;
    y += scalar;

    return *this;
}

Vector2 Vector2::operator+(const Vector2& other) const
{
    Vector2 v(*this);
    return v += other;
}

Vector2& Vector2::operator+=(const Vector2& other)
{
    x += other.x;
    y += other.y;

    return *this;
}

Vector2 Vector2::operator-(float scalar) const
{
    Vector2 v(*this);
    return v -= scalar;
}

Vector2& Vector2::operator-=(float scalar)
{
    x -= scalar;
    y -= scalar;

    return *this;
}

Vector2 Vector2::operator-(const Vector2& other) const
{
    Vector2 v(*this);
    return v -= other;
}

Vector2& Vector2::operator-=(const Vector2& other)
{
    x -= other.x;
    y -= other.y;

    return *this;
}

Vector2 Vector2::operator*(float scalar) const
{
    Vector2 v(*this);
    return v *= scalar;
}

Vector2& Vector2::operator*=(float scalar)
{
    x *= scalar;
    y *= scalar;

    return *this;
}

Vector2 Vector2::operator*(const Vector2& other) const
{
    Vector2 v(*this);
    return v *= other;
}

Vector2& Vector2::operator*=(const Vector2& other)
{
    x *= other.x;
    y *= other.y;

    return *this;
}

Vector2 Vector2::operator/(float scalar) const
{
    Vector2 v(*this);
    return v /= scalar;
}

Vector2& Vector2::operator/=(float scalar)
{
    x /= scalar;
    y /= scalar;

    return *this;
}

Vector2 Vector2::operator/(const Vector2& other) const
{
    Vector2 v(*this);
    return v /= other;
}

Vector2& Vector2::operator/=(const Vector2& other)
{
    x /= other.x;
    y /= other.y;

    return *this;
}

//------------------------------------------------------------------------------
//                               EXTERNAL OPERATORS
//------------------------------------------------------------------------------

arc::str::UTF8String& operator<<(
        arc::str::UTF8String& s,
        const Vector2& v)
{
    s << "(" << v.x << ", " << v.y << ")";
    return s;
}

std::ostream& operator<<(std::ostream& stream, const Vector2& v)
{
    stream << "(" << v.x << ", " << v.y << ")";
    return stream;
}

} // namespace gfx
} // namespace arc
