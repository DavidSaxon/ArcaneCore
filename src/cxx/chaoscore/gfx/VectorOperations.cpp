#include "chaoscore/gfx/VectorOperations.hpp"

#include <cmath>

namespace chaos
{
namespace gfx
{

float magnitude( const Vector2& v )
{
    return std::sqrt( ( v.x * v.x ) + ( v.y * v.y ) );
}

float magnitude( const Vector3& v )
{
    return std::sqrt( ( v.x * v.x ) + ( v.y * v.y ) + ( v.z * v.z ) );
}

float magnitude( const Vector4& v )
{
    return std::sqrt(
            ( v.x * v.x ) + ( v.y * v.y ) + ( v.z * v.z ) + ( v.w * v.w )
    );
}

float dot_product( const Vector2& v_1, const Vector2& v_2 )
{
    return ( v_1.x * v_2.x ) + ( v_1.y * v_2.y );
}

float dot_product( const Vector3& v_1, const Vector3& v_2 )
{
    return ( v_1.x * v_2.x ) + ( v_1.y * v_2.y ) + ( v_1.z * v_2.z );
}

float dot_product( const Vector4& v_1, const Vector4& v_2 )
{
    return ( v_1.x * v_2.x ) + ( v_1.y * v_2.y ) +
           ( v_1.z * v_2.z ) + ( v_1.w * v_2.w );
}

} // namespace gfx
} // namespace chaos
