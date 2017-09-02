/*!
 * \file
 * \brief Implementation of the FNV family of hashing functions
 * \author David Saxon
 */
#ifndef ARCANECORE_CRYPT_FNV_HPP_
#define ARCANECORE_CRYPT_FNV_HPP_

#include <arcanecore/base/Types.hpp>


namespace arc
{
namespace crypt
{

//------------------------------------------------------------------------------
//                                   FUNCTIONS
//------------------------------------------------------------------------------

/*!
 * \brief Computes a 32-bit FNV-1a hash of the given data.
 *
 * \param data The data to hash.
 * \param size The number of bytes in the data.
 *
 * \return The 32-bit result of the hash.
 */
arc::uint32 fnv1a_32(const void* data, std::size_t size);

/*!
 * \brief Computes a 64-bit FNV-1a hash of the given data.
 *
 * \param data The data to hash.
 * \param size The number of bytes in the data.
 *
 * \return The 64-bit result of the hash.
 */
arc::uint64 fnv1a_64(const void* data, std::size_t size);

} // namespace crypt
} // namespace arc

#endif
