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

} // namespace gfx
} // namespace chaos
