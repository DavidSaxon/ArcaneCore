/*!
 * \file
 * \author David Saxon
 */
#ifndef ARCANECORE_TEST_EXCEPTIONS_HPP_
#define ARCANECORE_TEST_EXCEPTIONS_HPP_

#include "arcanecore/base/Exceptions.hpp"

namespace arc
{
namespace test
{
/*!
 * \brief Exceptions relating to ArcaneCore's testing module.
 */
namespace ex
{

/*!
 * \brief Abstract base exception that warns of an unexpected error during
 *        testing procedures.
 */
class TestError : public arc::ex::ArcException
{
protected:

    template<typename T_derived_type>
    TestError(
            const arc::str::UTF8String& message,
            const T_derived_type* derived)
        : ArcException(message, derived)
    {
    }
};

/*!
 * \brief Warns that an error has occurred during test deceleration time.
 */
class TestDeclerationError : public TestError
{
public:

    TestDeclerationError(const arc::str::UTF8String& message)
        : TestError(message, this)
    {
    }
};

/*!
 * \brief Warns that an error has occurred during test runtime.
 */
class TestRuntimeError : public TestError
{
public:

    TestRuntimeError(const arc::str::UTF8String& message)
        : TestError(message, this)
    {
    }
};

} // namespace ex
} // namespace test
} // namespace arc

#endif
