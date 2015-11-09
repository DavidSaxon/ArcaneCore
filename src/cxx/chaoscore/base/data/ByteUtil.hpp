/*!
 * \file
 * \brief functions for manipulating and reading byte data.
 * \author David Saxon
 */

#ifndef CHAOSCORE_BASE_DATA_BYTEUTIL_HPP_
#define CHAOSCORE_BASE_DATA_BYTEUTIL_HPP_

#include <stdlib.h>

#include "chaoscore/base/Types.hpp"
#include "chaoscore/base/data/BinaryUtil.hpp"

namespace chaos
{
namespace data
{

/*!
 * \brief TODO: DOC
 */
chaos::uint32 bytes_to_uint32(
        const void* bytes,
        size_t      length,
        Endianness  endianness = chaos::data::get_system_endianness() );

} // namespace data
} // namespace chaos

#endif
