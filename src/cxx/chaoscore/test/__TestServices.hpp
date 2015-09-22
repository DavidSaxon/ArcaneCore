#ifndef CHAOSCORE_TEST_TESTSERVICES_HPP_
#define CHAOSCORE_TEST_TESTSERVICES_HPP_

#include <map>

#include "chaoscore/base/string/UTF8String.hpp"

namespace chaos
{
namespace test
{
namespace service
{

template <typename T>
inline void validateInputTest(
        const chaos::str::UTF8String& name,
        const std::map< chaos::str::UTF8String, T>& registeredMap )
{
}

} // namespace service
} // namespace test
} // namespace chaos

#endif
