#ifndef ARCANECORE_IO_DL_DLLOPERATIONS_HPP_
#define ARCANECORE_IO_DL_DLLOPERATIONS_HPP_

#include <arcanecore/base/Exceptions.hpp>
#include <arcanecore/base/Preproc.hpp>
#include <arcanecore/base/introspect/IntrospectOperations.hpp>
#include <arcanecore/io/os/ErrorState.hpp>
#include <arcanecore/base/str/StringOperations.hpp>
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
#   include <windows.h>
#   undef ARC_IO_DL_EXPORT
#   define ARC_IO_DL_EXPORT __declspec(dllexport)
// TODO: should be if GCC?
#elif defined(ARC_OS_LINUX)
#   include <dlfcn.h>
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
//                                  ENUMERATORS
//------------------------------------------------------------------------------

/*!
 * \brief The various flags that can be used when opening libraries (Unix only).
 */
enum OpenFlag
{
    /// Performs lazy binding. Only resolve symbols as the code references them
    /// is execute. If the symbol is never reference, then it is never resolved.
    /// (Lazy binding is only performed for function references; references to
    /// variables are always immediately bound when the library is loaded.)
    kOpenLazy     = 1UL,
    /// If this value is specified, all undefined symbols in the library are
    /// resolved before open_library returns. If it cannot be done, an error is
    /// returned.
    kOpenNow      = 1UL << 1,
    /// The symbols defined by this library will be made available for symbol
    /// resolution of subsequently loaded libraries.
    kOpenGlobal   = 1UL << 2,
    /// This is the converse of kOpenGlobal, and the default if neither flag is
    /// specified. Symbols defined in this library are not made available to
    /// resolve references in subsequently loaded libraries.
    kOpenLocal    = 1UL << 3,
    /// Do not unload the library during close_library(). Consequently, the
    /// library's static variables are not reinitialized if the library is
    /// reloaded with open_library() at a later time.
    kOpenNoDelete = 1UL << 4,
    /// Place the lookup scope of the symbols in this library ahead of the
    /// global scope. This means that a self-contained library will use its own
    /// symbols in preference to global symbols with the same name contained in
    /// libraries that have already been loaded.
    kOpenDeepBind = 1UL << 6
};

//------------------------------------------------------------------------------
//                                TYPE DEFINITIONS
//------------------------------------------------------------------------------

/*!
 * \brief A handle to a loaded dynamic library.
 */
typedef void* Handle;

//------------------------------------------------------------------------------
//                                   FUNCTIONS
//------------------------------------------------------------------------------

/*!
 * \brief Opens the dynamic library at the given location.
 *
 * \param path The path to the library.
 * \param flags The flags that will be used to open the library (Unix only).
 * \return The handle for the loaded library.
 *
 * \throws arc::ex::IOError If the given path does not exist.
 * \throws arc::ex::DynamicLinkError If the file cannot be opened as a dynamic
 *                                   library.
 */
Handle open_library(
        const arc::io::sys::Path& path,
        int flags = kOpenLazy);

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

        // note - this doesn't support Unicode function names
        // get the handle
        symbol_handle = GetProcAddress((HMODULE) handle, name.get_raw());

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
            arc::io::os::get_last_system_error_message()
        );
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
