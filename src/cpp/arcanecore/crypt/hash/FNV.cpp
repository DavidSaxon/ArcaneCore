#include "arcanecore/crypt/hash/FNV.hpp"


namespace arc
{
namespace crypt
{
namespace hash
{

//------------------------------------------------------------------------------
//                                   FUNCTIONS
//------------------------------------------------------------------------------

arc::uint32 fnv1a_32(const void* data, std::size_t length, arc::uint32 initial)
{
    const arc::uint8* bytes = static_cast<const arc::uint8*>(data);
    arc::uint32 hash = initial;
    for(std::size_t i = 0; i < length; ++i)
    {
        hash = hash ^ bytes[i];
        hash = hash * 0x1000193;
    }
    return hash;
}

arc::uint64 fnv1a_64(const void* data, std::size_t length, arc::uint64 initial)
{
    const arc::uint8* bytes = static_cast<const arc::uint8*>(data);
    arc::uint64 hash = initial;
    for(std::size_t i = 0; i < length; ++i)
    {
        hash = hash ^ bytes[i];
        hash = hash * 0x100000001B3;
    }
    return hash;
}

} // namespace hash
} // namespace crypt
} // namespace arc
