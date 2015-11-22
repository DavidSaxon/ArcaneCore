#include "chaoscore/base/uni/UnicodeOperations.hpp"

namespace chaos
{
namespace uni
{

bool is_digit( chaos::uint32 code_point )
{
    return code_point >= 48 && code_point <= 57;
}

} // namespace uni
} // namespace chaos
