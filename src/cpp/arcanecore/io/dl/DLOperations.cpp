#include "arcanecore/io/dl/DLOperations.hpp"

#include "arcanecore/io/sys/FileSystemOperations.hpp"

namespace arc
{
namespace io
{
namespace dl
{

Handle open_library(const arc::io::sys::Path& path)
{
    if(!arc::io::sys::exists(path))
    {
        arc::str::UTF8String error_message;
        error_message
            << "Path to library does not exist: \"" << path << "\".";
        throw arc::ex::IOError(error_message);
    }

    Handle handle = nullptr;

    #ifdef ARC_OS_WINDOWS

        // utf 16
        std::size_t length = 0;
        const char* utf16 = arc::str::utf8_to_utf16(
                path.to_native() .get_raw(),
                length,
                arc::data::ENDIAN_LITTLE
        );
        // get the handle
        handle = LoadLibraryW((const wchar_t*) utf16);

    #elif defined(ARC_OS_UNIX)

        // get the handle
        handle = dlopen(path.to_native().get_raw(), RTLD_LAZY);
        if(handle == nullptr)
        {
            throw arc::ex::DynamicLinkError(dlerror());
        }

    #else

        throw arc::test::ex::NotImplementedError(
                "open_library has not been implemented for this platform.");

    #endif

    // check error
    if(handle == nullptr)
    {
        throw arc::ex::DynamicLinkError(
            arc::io::os::get_last_system_error_message());
    }

    return handle;
}

void close_library(Handle handle)
{
    bool error = false;

    #ifdef ARC_OS_WINDOWS

        error = !FreeLibrary((HMODULE) handle);

    #elif defined(ARC_OS_UNIX)

        if(dlclose(handle) != 0)
        {
            throw arc::ex::DynamicLinkError(dlerror());
        }

    #else

        throw arc::test::ex::NotImplementedError(
                "close_library has not been implemented for this platform.");

    #endif

    // check error
    if(error)
    {
        throw arc::ex::DynamicLinkError(
            arc::io::os::get_last_system_error_message());
    }
}

} // namespace dl
} // namespace io
} // namespace arc
