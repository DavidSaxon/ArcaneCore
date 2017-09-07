/*!
 * \file
 * \brief Implementation of the Spooky family of hashing functions.
 * \author David Saxon
 */
#ifndef ARCANECORE_CRYPT_HASH_SPOOKY_HPP_
#define ARCANECORE_CRYPT_HASH_SPOOKY_HPP_

#include <cstddef>

#include <arcanecore/base/Types.hpp>


namespace arc
{
namespace crypt
{
namespace hash
{

//------------------------------------------------------------------------------
//                                   VARIABLES
//------------------------------------------------------------------------------

/*!
 * \brief If set to ```true``` the Spooky hash function will ensure that the
 *        input data is aligned before reading from it.
 *
 * Defaults to ```false```.
 *
 * \warn In most cases this will induce a copy of the data to be made.
 */
extern bool spooky_force_aligned_reads;

//------------------------------------------------------------------------------
//                                   FUNCTIONS
//------------------------------------------------------------------------------

/*!
 * \brief Computes a 128-bit Spooky hash of the given data.
 *
 * \param data The data to hash.
 * \param length The number of bytes in the data.
 * \param out_hash1 Returns the first 64-bits of the hash.
 * \param out_hash2 Returns the second 64-bits of the hash.
 * \param initial1 The first 640-bit initial value to begin the hash with.
 * \param initial2 The second 640-bit initial value to begin the hash with.
 */
void spooky_128(
        const void* data,
        std::size_t length,
        arc::uint64& out_hash1,
        arc::uint64& out_hash2,
        arc::uint64 initial1 = 0,
        arc::uint64 initial2 = 0);

/*!
 * \brief Computes a 64-bit Spooky hash of the given data.
 *
 * \param data The data to hash.
 * \param length The number of bytes in the data.
 * \param initial The initial value to begin the hash with.
 *
 * \return The 64-bit result of the hash.
 */
arc::uint64 spooky_64(
        const void* data,
        std::size_t length,
        arc::uint64 initial = 0);

/*!
 * \brief Computes a 32-bit Spooky hash of the given data.
 *
 * \param data The data to hash.
 * \param length The number of bytes in the data.
 * \param initial The initial value to begin the hash with.
 *
 * \return The 32-bit result of the hash.
 */
arc::uint32 spooky_32(
        const void* data,
        std::size_t length,
        arc::uint32 initial = 0);

} // namespace hash
} // namespace crypt
} // namespace arc

#endif
