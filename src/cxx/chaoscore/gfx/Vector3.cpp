#include "chaoscore/gfx/Vector3.hpp"

#include "chaoscore/base/math/MathOperations.hpp"

namespace chaos
{
namespace gfx
{

//------------------------------------------------------------------------------
//                                  CONSTRUCTORS
//------------------------------------------------------------------------------

Vector3::Vector3()
    :
    x( 0.0F ),
    y( 0.0F ),
    z( 0.0F )
{
}

Vector3::Vector3( float i_x, float i_y, float i_z )
    :
    x( i_x ),
    y( i_y ),
    z( i_z )
{
}

Vector3::Vector3( float scalar )
    :
    x( scalar ),
    y( scalar ),
    z( scalar )
{
}

Vector3::Vector3( const Vector3& other )
    :
    x( other.x ),
    y( other.y ),
    z( other.z )
{
}

//------------------------------------------------------------------------------
//                                   OPERATORS
//------------------------------------------------------------------------------

Vector3& Vector3::operator=( const Vector3& other )
{
    x = other.x;
    y = other.y;
    z = other.z;

    return *this;
}

bool Vector3::operator==( const Vector3& other ) const
{
    return chaos::math::float_equals( x, other.x ) &&
           chaos::math::float_equals( y, other.y ) &&
           chaos::math::float_equals( z, other.z );
}

bool Vector3::operator!=( const Vector3& other ) const
{
    return !( ( *this ) == other );
}

Vector3 Vector3::operator-() const
{
    return Vector3( -x, -y, -z );
}

Vector3 Vector3::operator+( float scalar ) const
{
    Vector3 v( *this );
    return v += scalar;
}

Vector3& Vector3::operator+=( float scalar )
{
    x += scalar;
    y += scalar;
    z += scalar;

    return *this;
}

Vector3 Vector3::operator+( const Vector3& other ) const
{
    Vector3 v( *this );
    return v += other;
}

Vector3& Vector3::operator+=( const Vector3& other )
{
    x += other.x;
    y += other.y;
    z += other.z;

    return *this;
}

Vector3 Vector3::operator-( float scalar ) const
{
    Vector3 v( *this );
    return v -= scalar;
}

Vector3& Vector3::operator-=( float scalar )
{
    x -= scalar;
    y -= scalar;
    z -= scalar;

    return *this;
}

Vector3 Vector3::operator-( const Vector3& other ) const
{
    Vector3 v( *this );
    return v -= other;
}

Vector3& Vector3::operator-=( const Vector3& other )
{
    x -= other.x;
    y -= other.y;
    z -= other.z;

    return *this;
}

Vector3 Vector3::operator*( float scalar ) const
{
    Vector3 v( *this );
    return v *= scalar;
}

Vector3& Vector3::operator*=( float scalar )
{
    x *= scalar;
    y *= scalar;
    z *= scalar;

    return *this;
}

Vector3 Vector3::operator/( float scalar ) const
{
    Vector3 v( *this );
    return v /= scalar;
}

Vector3& Vector3::operator/=( float scalar )
{
    x /= scalar;
    y /= scalar;
    z /= scalar;

    return *this;
}

//------------------------------------------------------------------------------
//                               EXTERNAL OPERATORS
//------------------------------------------------------------------------------

chaos::uni::UTF8String& operator<<(
        chaos::uni::UTF8String& s,
        const Vector3& v )
{
    s << "(" << v.x << ", " << v.y << ", " << v.z << ")";
    return s;
}

std::ostream& operator<<( std::ostream& stream, const Vector3& v )
{
    stream << "(" << v.x << ", " << v.y << ", " << v.z << ")";
    return stream;
}

} // namespace gfx
} // namespace chaos
