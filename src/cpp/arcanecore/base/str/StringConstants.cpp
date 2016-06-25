#include "arcanecore/base/str/StringConstants.hpp"

#include <limits>

namespace arc
{
namespace str
{

const std::size_t npos = std::numeric_limits<std::size_t>::max();

const std::size_t UTF8_BOM_SIZE = 3;
const char UTF8_BOM[UTF8_BOM_SIZE] = {'\xEF', '\xBB', '\xBF'};

const std::size_t UTF16_BOM_SIZE = 2;
const char UTF16LE_BOM[UTF16_BOM_SIZE] = {'\xFF', '\xFE'};
const char UTF16BE_BOM[UTF16_BOM_SIZE] = {'\xFE', '\xFF'};

const arc::uint32 UTF16_MAX_2BYTE = 0xFFFF;
const arc::uint32 UTF16_4BYTE_OFFSET = 0x10000;
const arc::uint32 UTF16_HIGH_SURROGATE_MIN = 0xD800;
const arc::uint32 UTF16_HIGH_SURROGATE_MAX = 0xDBFF;
const arc::uint32 UTF16_LOW_SURROGATE_MIN = 0xDC00;

} // namespace str
} // namespace arc
