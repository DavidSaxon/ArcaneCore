#include "arcanecore/gfx/Vector4.hpp"

#include "arcanecore/base/math/MathOperations.hpp"

namespace arc
{
namespace gfx
{

//------------------------------------------------------------------------------
//                                  CONSTRUCTORS
//------------------------------------------------------------------------------

Vector4::Vector4()
    :
    x(0.0F),
    y(0.0F),
    z(0.0F),
    w(0.0F),
    r(x),
    g(y),
    b(z),
    a(w)
{
}

Vector4::Vector4(float i_x, float i_y, float i_z, float i_w)
    :
    x(i_x),
    y(i_y),
    z(i_z),
    w(i_w),
    r(x),
    g(y),
    b(z),
    a(w)
{
}

Vector4::Vector4(float scalar)
    :
    x(scalar),
    y(scalar),
    z(scalar),
    w(scalar),
    r(x),
    g(y),
    b(z),
    a(w)
{
}

Vector4::Vector4(const Vector4& other)
    :
    x(other.x),
    y(other.y),
    z(other.z),
    w(other.w),
    r(x),
    g(y),
    b(z),
    a(w)
{
}

//------------------------------------------------------------------------------
//                                   OPERATORS
//------------------------------------------------------------------------------

Vector4& Vector4::operator=(const Vector4& other)
{
    x = other.x;
    y = other.y;
    z = other.z;
    w = other.w;

    return *this;
}

bool Vector4::operator==(const Vector4& other) const
{
    return arc::math::float_equals(x, other.x) &&
           arc::math::float_equals(y, other.y) &&
           arc::math::float_equals(z, other.z) &&
           arc::math::float_equals(w, other.w);
}

bool Vector4::operator!=(const Vector4& other) const
{
    return !((*this) == other);
}

Vector4 Vector4::operator-() const
{
    return Vector4(-x, -y, -z, -w);
}

Vector4 Vector4::operator+(float scalar) const
{
    Vector4 v(*this);
    return v += scalar;
}

Vector4& Vector4::operator+=(float scalar)
{
    x += scalar;
    y += scalar;
    z += scalar;
    w += scalar;

    return *this;
}

Vector4 Vector4::operator+(const Vector4& other) const
{
    Vector4 v(*this);
    return v += other;
}

Vector4& Vector4::operator+=(const Vector4& other)
{
    x += other.x;
    y += other.y;
    z += other.z;
    w += other.w;

    return *this;
}

Vector4 Vector4::operator-(float scalar) const
{
    Vector4 v(*this);
    return v -= scalar;
}

Vector4& Vector4::operator-=(float scalar)
{
    x -= scalar;
    y -= scalar;
    z -= scalar;
    w -= scalar;

    return *this;
}

Vector4 Vector4::operator-(const Vector4& other) const
{
    Vector4 v(*this);
    return v -= other;
}

Vector4& Vector4::operator-=(const Vector4& other)
{
    x -= other.x;
    y -= other.y;
    z -= other.z;
    w -= other.w;

    return *this;
}

Vector4 Vector4::operator*(float scalar) const
{
    Vector4 v(*this);
    return v *= scalar;
}

Vector4& Vector4::operator*=(float scalar)
{
    x *= scalar;
    y *= scalar;
    z *= scalar;
    w *= scalar;

    return *this;
}

Vector4 Vector4::operator*(const Vector4& other) const
{
    Vector4 v(*this);
    return v *= other;
}

Vector4& Vector4::operator*=(const Vector4& other)
{
    x *= other.x;
    y *= other.y;
    z *= other.z;
    w *= other.w;

    return *this;
}

Vector4 Vector4::operator/(float scalar) const
{
    Vector4 v(*this);
    return v /= scalar;
}

Vector4& Vector4::operator/=(float scalar)
{
    x /= scalar;
    y /= scalar;
    z /= scalar;
    w /= scalar;

    return *this;
}

Vector4 Vector4::operator/(const Vector4& other) const
{
    Vector4 v(*this);
    return v /= other;
}

Vector4& Vector4::operator/=(const Vector4& other)
{
    x /= other.x;
    y /= other.y;
    z /= other.z;
    w /= other.w;

    return *this;
}

//------------------------------------------------------------------------------
//                               EXTERNAL OPERATORS
//------------------------------------------------------------------------------

arc::str::UTF8String& operator<<(
        arc::str::UTF8String& s,
        const Vector4& v)
{
    s << "(" << v.x << ", " << v.y << ", " << v.z << ", " << v.w << ")";
    return s;
}

std::ostream& operator<<(std::ostream& stream, const Vector4& v)
{
    stream << "(" << v.x << ", " << v.y << ", " << v.z << ", " << v.w << ")";
    return stream;
}

} // namespace gfx
} // namespace arc
