#include "chaoscore/base/string/UnicodeOperations.hpp"

namespace chaos
{
namespace str
{

bool is_digit( chaos::uint32 code_point )
{
    return code_point >= 48 && code_point <= 57;
}

} // namespace str
} // namespace chaos
