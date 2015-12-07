#include "chaoscore/gfx/Vector2.hpp"

namespace chaos
{
namespace gfx
{

//------------------------------------------------------------------------------
//                                  CONSTRUCTORS
//------------------------------------------------------------------------------


Vector2::Vector2()
    :
    x( 0.0F ),
    y( 0.0F )
{
}

Vector2::Vector2( float i_x, float i_y )
    :
    x( i_x ),
    y( i_y )
{
}

//------------------------------------------------------------------------------
//                               EXTERNAL OPERATORS
//------------------------------------------------------------------------------

chaos::uni::UTF8String& operator<<(
        chaos::uni::UTF8String& s,
        const Vector2& v )
{
    s << "(" << v.x << ", " << v.y << ")";
    return s;
}

std::ostream& operator<<( std::ostream& stream, const Vector2& v )
{
    stream << "(" << v.x << ", " << v.y << ")";
    return stream;
}

} // namespace gfx
} // namespace chaos
