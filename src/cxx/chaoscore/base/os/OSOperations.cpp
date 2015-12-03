#include "chaoscore/base/os/OSOperations.hpp"

#ifdef CHAOS_OS_UNIX

    #include <cstring>
    #include <cerrno>

#elif defined( CHAOS_OS_WINDOWS )

    #include <windows.h>

#endif

#include "chaoscore/base/BaseExceptions.hpp"
#include "chaoscore/base/uni/UnicodeOperations.hpp"

namespace chaos
{
namespace os
{

/*!
 * \brief Gets the last system error message.
 *
 * This should be used after platform specific call that has failed. The related
 * error message will attempt to be retrieved as an chaos::uni::UTF8String.
 */
chaos::uni::UTF8String get_last_system_error_message()
{
#ifdef CHAOS_OS_UNIX

    return chaos::uni::UTF8String( strerror( errno ) );

#elif defined( CHAOS_OS_WINDOWS )

    wchar_t error_message[ 512 ];
    FormatMessageW(
            FORMAT_MESSAGE_FROM_SYSTEM,
            NULL,
            GetLastError(),
            MAKELANGID( LANG_NEUTRAL, SUBLANG_DEFAULT ),
            error_message,
            512,
            NULL
    );

    return chaos::uni::UTF8String(
            chaos::uni::utf16_to_utf8(
                    ( const char* ) error_message,
                    chaos::uni::npos
            )
    );

#else

    throw chaos::ex::NotImplementedError(
            "get_last_system_error_message has not yet been implemented for "
            "this platform"
    );

#endif
}

} // namespace os
} // namespace chaos
