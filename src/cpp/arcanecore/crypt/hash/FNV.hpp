/*!
 * \file
 * \brief Implementation of the FNV family of hashing functions.
 * \author David Saxon
 */
#ifndef ARCANECORE_CRYPT_HASH_FNV_HPP_
#define ARCANECORE_CRYPT_HASH_FNV_HPP_

#include <cstddef>

#include <arcanecore/base/Types.hpp>


namespace arc
{
namespace crypt
{
namespace hash
{

//------------------------------------------------------------------------------
//                                   FUNCTIONS
//------------------------------------------------------------------------------

/*!
 * \brief Computes a 32-bit FNV-1a hash of the given data.
 *
 * \param data The data to hash.
 * \param length The number of bytes in the data.
 *
 * \return The 32-bit result of the hash.
 */
arc::uint32 fnv1a_32(
        const void* data,
        std::size_t length,
        arc::uint32 initial = 0x811C9DC5);

/*!
 * \brief Computes a 64-bit FNV-1a hash of the given data.
 *
 * \param data The data to hash.
 * \param length The number of bytes in the data.
 *
 * \return The 64-bit result of the hash.
 */
arc::uint64 fnv1a_64(
        const void* data,
        std::size_t length,
        arc::uint64 initial = 0xCBF29CE484222325);

} // namespace hash
} // namespace crypt
} // namespace arc

#endif
