#include "chaoscore/base/string/UnicodeUtil.hpp"

namespace chaos
{
namespace str
{

bool utf8_is_digit( chaos::uint32 code_point )
{
    return code_point >= 48 && code_point <= 57;
}

} // namespace str
} // namespace chaos
