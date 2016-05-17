#include "chaoscore/base/str/StringConstants.hpp"

#include <limits>

namespace chaos
{
namespace str
{

const std::size_t npos = std::numeric_limits< std::size_t >::max();

const chaos::uint32 UTF16_MAX_2BYTE = 0xFFFF;
const chaos::uint32 UTF16_4BYTE_OFFSET = 0x10000;
const chaos::uint32 UTF16_HIGH_SURROGATE_MIN = 0xD800;
const chaos::uint32 UTF16_HIGH_SURROGATE_MAX = 0xDBFF;
const chaos::uint32 UTF16_LOW_SURROGATE_MIN = 0xDC00;

} // namespace str
} // namespace chaos
