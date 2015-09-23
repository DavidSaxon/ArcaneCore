#ifndef CHAOSCORE_TEST_TESTSERVICES_HPP_
#define CHAOSCORE_TEST_TESTSERVICES_HPP_

#include <map>

#include "chaoscore/base/string/UTF8String.hpp"

// TODO: REMOVE ME
#include <iostream>

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
    // TODO:
    // check the name is not empty
    if ( name.isEmpty() )
    {
        std::cout << "blank name" << std::endl;
    }
    // TODO:
    // check the name is already in the map
    // TODO:
    // check the name doesn't contain periods
}

} // namespace service
} // namespace test
} // namespace chaos

#endif
