#include "chaoscore/gfx/Vector4.hpp"

#include "chaoscore/base/math/MathOperations.hpp"

namespace chaos
{
namespace gfx
{

//------------------------------------------------------------------------------
//                                  CONSTRUCTORS
//------------------------------------------------------------------------------

Vector4::Vector4()
    :
    x( 0.0F ),
    y( 0.0F ),
    z( 0.0F ),
    w( 0.0F )
{
}

Vector4::Vector4( float i_x, float i_y, float i_z, float i_w )
    :
    x( i_x ),
    y( i_y ),
    z( i_z ),
    w( i_w )
{
}

Vector4::Vector4( float scalar )
    :
    x( scalar ),
    y( scalar ),
    z( scalar ),
    w( scalar )
{
}

Vector4::Vector4( const Vector4& other )
    :
    x( other.x ),
    y( other.y ),
    z( other.z ),
    w( other.w )
{
}

//------------------------------------------------------------------------------
//                                   OPERATORS
//------------------------------------------------------------------------------

Vector4& Vector4::operator=( const Vector4& other )
{
    x = other.x;
    y = other.y;
    z = other.z;
    w = other.w;

    return *this;
}

bool Vector4::operator==( const Vector4& other ) const
{
    return chaos::math::float_equals( x, other.x ) &&
           chaos::math::float_equals( y, other.y ) &&
           chaos::math::float_equals( z, other.z ) &&
           chaos::math::float_equals( w, other.w );
}

bool Vector4::operator!=( const Vector4& other ) const
{
    return !( ( *this ) == other );
}

Vector4 Vector4::operator+( float scalar ) const
{
    Vector4 v( *this );
    return v += scalar;
}

Vector4& Vector4::operator+=( float scalar )
{
    x += scalar;
    y += scalar;
    z += scalar;
    w += scalar;

    return *this;
}

Vector4 Vector4::operator+( const Vector4& other ) const
{
    Vector4 v( *this );
    return v += other;
}

Vector4& Vector4::operator+=( const Vector4& other )
{
    x += other.x;
    y += other.y;
    z += other.z;
    w += other.w;

    return *this;
}

Vector4 Vector4::operator-( float scalar ) const
{
    Vector4 v( *this );
    return v -= scalar;
}

Vector4& Vector4::operator-=( float scalar )
{
    x -= scalar;
    y -= scalar;
    z -= scalar;
    w -= scalar;

    return *this;
}

Vector4 Vector4::operator-( const Vector4& other ) const
{
    Vector4 v( *this );
    return v -= other;
}

Vector4& Vector4::operator-=( const Vector4& other )
{
    x -= other.x;
    y -= other.y;
    z -= other.z;
    w -= other.w;

    return *this;
}

Vector4 Vector4::operator*( float scalar ) const
{
    Vector4 v( *this );
    return v *= scalar;
}

Vector4& Vector4::operator*=( float scalar )
{
    x *= scalar;
    y *= scalar;
    z *= scalar;
    w *= scalar;

    return *this;
}

Vector4 Vector4::operator/( float scalar ) const
{
    Vector4 v( *this );
    return v /= scalar;
}

Vector4& Vector4::operator/=( float scalar )
{
    x /= scalar;
    y /= scalar;
    z /= scalar;
    w /= scalar;

    return *this;
}

//------------------------------------------------------------------------------
//                               EXTERNAL OPERATORS
//------------------------------------------------------------------------------

chaos::uni::UTF8String& operator<<(
        chaos::uni::UTF8String& s,
        const Vector4& v )
{
    s << "(" << v.x << ", " << v.y << ", " << v.z << ", " << v.w << ")";
    return s;
}

std::ostream& operator<<( std::ostream& stream, const Vector4& v )
{
    stream << "(" << v.x << ", " << v.y << ", " << v.z << ", " << v.w << ")";
    return stream;
}

} // namespace gfx
} // namespace chaos
