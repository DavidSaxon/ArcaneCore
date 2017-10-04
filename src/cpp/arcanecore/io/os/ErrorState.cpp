#include "arcanecore/io/os/ErrorState.hpp"

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
namespace io
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

    LPWSTR error_message = nullptr;
    std::size_t message_size = FormatMessageW(
            FORMAT_MESSAGE_ALLOCATE_BUFFER |
            FORMAT_MESSAGE_FROM_SYSTEM     |
            FORMAT_MESSAGE_IGNORE_INSERTS,
            NULL,
            GetLastError(),
            MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
            (LPWSTR) &error_message,
            0,
            NULL
    );

    // copy to UTF8String
    arc::str::UTF8String r_string(
        arc::str::utf16_to_utf8(
                (const char*) error_message,
                message_size * sizeof(wchar_t)
        )
    );
    // destroy the system string
    LocalFree(error_message);

    // remove a newline from the end of the message if it exists
    if(r_string.ends_with("\n"))
    {
        r_string = r_string.substring(0, r_string.get_length() - 1);
    }
    // remove a carriage return from the end of the message if it exists
    if(r_string.ends_with("\r"))
    {
        r_string = r_string.substring(0, r_string.get_length() - 1);
    }

    return r_string;

#else

    throw arc::ex::NotImplementedError(
            "get_last_system_error_message has not yet been implemented for "
            "this platform"
    );

#endif
}

} // namespace os
} // namespace io
} // namespace arc
