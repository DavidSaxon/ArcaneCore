#include "arcanecore/base/os/OSOperations.hpp"

#ifdef ARC_OS_UNIX

    #include <cstring>
    #include <cerrno>

#elif defined(ARC_OS_WINDOWS)

    #include <windows.h>

#endif

#include "arcanecore/base/Exceptions.hpp"
#include "arcanecore/base/str/StringOperations.hpp"

namespace arc
{
namespace os
{

/*!
 * \brief Gets the last system error message.
 *
 * This should be used after platform specific call that has failed. The related
 * error message will attempt to be retrieved as an arc::str::UTF8String.
 */
arc::str::UTF8String get_last_system_error_message()
{
#ifdef ARC_OS_UNIX

    return arc::str::UTF8String(strerror(errno));

#elif defined(ARC_OS_WINDOWS)

    wchar_t error_message[512];
    FormatMessageW(
            FORMAT_MESSAGE_FROM_SYSTEM,
            NULL,
            GetLastError(),
            MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
            error_message,
            512,
            NULL
    );

    return arc::str::UTF8String(
            arc::str::utf16_to_utf8(
                    (const char*) error_message,
                    arc::str::npos
            )
    );

#else

    throw arc::ex::NotImplementedError(
            "get_last_system_error_message has not yet been implemented for "
            "this platform"
    );

#endif
}

} // namespace os
} // namespace arc
