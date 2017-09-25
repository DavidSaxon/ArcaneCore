#include "arcanecore/base/str/FnMatch.hpp"

#include "arcanecore/base/Exceptions.hpp"
#include "arcanecore/base/str/StringOperations.hpp"

#ifdef ARC_OS_UNIX

    #include <fnmatch.h>

#elif defined(ARC_OS_WINDOWS)

    #include <windows.h>
    #include <Shlwapi.h>
    #pragma comment(lib, "Shlwapi.lib")

#endif


namespace arc
{
namespace str
{

bool fnmatch(
        const arc::str::UTF8String& pattern,
        const arc::str::UTF8String& s)
{
    #ifdef ARC_OS_UNIX

        return ::fnmatch(pattern.get_raw(), s.get_raw(), 0) == 0;

    #elif defined(ARC_OS_WINDOWS)

        std::size_t p_length = 0;
        const char* p16 = arc::str::utf8_to_utf16(
                pattern,
                p_length,
                arc::data::ENDIAN_LITTLE
        );
        std::size_t s_length = 0;
        const char* s16 = arc::str::utf8_to_utf16(
                s,
                s_length,
                arc::data::ENDIAN_LITTLE
        );

        return PathMatchSpecW(
            (const wchar_t*) s16,
            (const wchar_t*) p16
        );

    #else

        throw arc::ex::NotImplementedError(
            "arc::str::fnmatch has not yet been implemented for this platform"
        );

    #endif
}

} // namespace str
} // namespace arc
