#include "arcanecore/crypt/FNV.hpp"

namespace arc
{
namespace crypt
{

//------------------------------------------------------------------------------
//                                   FUNCTIONS
//------------------------------------------------------------------------------

arc::uint32 fnv1a_32(const void* data, std::size_t size)
{
    const arc::uint8* bytes = static_cast<const arc::uint8*>(data);
    arc::uint32 hash = 0x811C9DC5;
    for(std::size_t i = 0; i < size; ++i)
    {
        hash = hash ^ bytes[i];
        hash = hash * 0x1000193;
    }
    return hash;
}

arc::uint64 fnv1a_64(const void* data, std::size_t size)
{
    const arc::uint8* bytes = static_cast<const arc::uint8*>(data);
    arc::uint64 hash = 0xCBF29CE484222325;
    for(std::size_t i = 0; i < size; ++i)
    {
        hash = hash ^ bytes[i];
        hash = hash * 0x100000001B3;
    }
    return hash;
}

} // namespace crypt
} // namespace arc
