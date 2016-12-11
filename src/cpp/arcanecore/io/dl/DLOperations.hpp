#ifndef ARCANECORE_IO_DL_DLLOPERATIONS_HPP_
#define ARCANECORE_IO_DL_DLLOPERATIONS_HPP_

#include <dlfcn.h>

#include <arcanecore/base/Exceptions.hpp>
#include <arcanecore/base/Preproc.hpp>
#include <arcanecore/base/introspect/IntrospectOperations.hpp>
#include <arcanecore/base/os/OSOperations.hpp>
#include <arcanecore/base/str/UTF8String.hpp>
#include <arcanecore/io/sys/Path.hpp>

//------------------------------------------------------------------------------
//                                     MACROS
//------------------------------------------------------------------------------

/*!
 * \brief Directive used to export a function in a dynamic library.
 */
#define ARC_IO_DL_EXPORT
#ifdef ARC_OS_WINDOWS
#   undef ARC_IO_DL_EXPORT
#   define ARC_IO_DL_EXPORT __declspec(dllexport)
// TODO: should be if GCC?
#elif defined(ARC_OS_LINUX)
#   undef ARC_IO_DL_EXPORT
#   define ARC_IO_DL_EXPORT __attribute__((visibility("default")))
#endif

namespace arc
{
namespace io
{
namespace dl
{

//------------------------------------------------------------------------------
//                                TYPE DEFINITIONS
//------------------------------------------------------------------------------

/*!
 * \brief A handle to a loaded dynamic library.
 */
typedef void* Handle;

/*!
 * \brief Opens the dynamic library at the given location.
 *
 * \param path The path to the library.
 * \return The handle for the loaded library.
 *
 * \throws arc::ex::IOError If the given path does not exist.
 * \throws arc::ex::DynamicLinkError If the file cannot be opened as a dynamic
 *                                   library.
 */
Handle open_library(const arc::io::sys::Path& path);

/*!
 * \brief Closes the library pointed to be the given handle.
 *
 * \param handle The handle to the library to close.
 *
 * \throws arc::ex::DynamicLinkError If the library failed to close.
 */
void close_library(Handle handle);

/*!
 * \brief Binds a symbol from the loaded dynamic library the handle is pointing
 *        to.
 *
 * \tparam SymbolType The type of the symbol to bind from the library.
 *
 * \param handle The handle to the loaded dynamic library to bind the symbol
 *               from.
 * \param name The name of the symbol bind from the dynamic library.
 */
template<typename SymbolType>
SymbolType* bind_symbol(Handle handle, const arc::str::UTF8String& name)
{
    void* symbol_handle = nullptr;

    #ifdef ARC_OS_WINDOWS

        // utf 16
        std::size_t length = 0;
        const char* utf16 = arc::str::utf8_to_utf16(
                name.get_raw(),
                length,
                arc::data::ENDIAN_LITTLE
        );
        // get the handle
        symbol_handle = GetProcAddressW(handle, utf16);

    #elif defined(ARC_OS_UNIX)

        // get the handle
        symbol_handle = dlsym(handle, name.get_raw());
        if(symbol_handle == nullptr)
        {
            throw arc::ex::DynamicLinkError(dlerror());
        }

    #else

        throw arc::test::ex::NotImplementedError(
                "bind_symbol has not been implemented for this platform.");

    #endif

    // check error
    if(symbol_handle == nullptr)
    {
        throw arc::ex::DynamicLinkError(
            arc::os::get_last_system_error_message());
    }

    // attempt to cast handle
    SymbolType* symbol = reinterpret_cast<SymbolType*>(
        reinterpret_cast<intptr_t>(symbol_handle)
    );
    if(symbol == nullptr)
    {
        arc::str::UTF8String error_message;
        error_message
            << "Cannot bind symbol: \"" << name << "\" as the requested "
            << "type: <" << arc::introspect::get_typename<SymbolType>() << ">.";
        throw arc::ex::DynamicLinkError(error_message);
    }

    // done
    return symbol;
}

} // namespace dl
} // namespace io
} // namespace arc

#endif
