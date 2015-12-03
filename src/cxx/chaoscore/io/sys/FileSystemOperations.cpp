#include "chaoscore/io/sys/FileSystemOperations.hpp"

#include <algorithm>
#include <sys/stat.h>
#include <sys/types.h>

#ifdef CHAOS_OS_UNIX

    #include <dirent.h>
    #include <unistd.h>

#elif defined( CHAOS_OS_WINDOWS )

    #include <windows.h>

#endif

#include "chaoscore/base/os/OSOperations.hpp"
#include "chaoscore/base/uni/UnicodeOperations.hpp"

// TODO: REMOVE ME
#include <iostream>

namespace chaos
{
namespace io
{
namespace sys
{

bool exists( const chaos::io::sys::Path& path, bool resolve_links )
{
#ifdef CHAOS_OS_UNIX

    struct stat s;

    // stat or lstat the file depending on whether we want to resolve links or
    // not
    int stat_ret = false;
    if ( resolve_links )
    {
        stat_ret = stat( path.to_unix().get_raw(), &s );
    }
    else
    {
        stat_ret = lstat( path.to_unix().get_raw(), &s );
    }

    // return based on the stat return code
    if (  stat_ret == 0 )
    {
        return true;
    }
    return false;

#elif defined( CHAOS_OS_WINDOWS )

    // utf-16
    std::size_t length = 0;
    const char* p = chaos::uni::utf8_to_utf16(
            path.to_windows().get_raw(),
            length,
            chaos::data::ENDIAN_LITTLE
    );

    struct _stat64i32 s;
    int result =  _wstat64i32( ( const wchar_t* ) p, &s );
    delete[] p;

    if ( result == 0 )
    {
        return true;
    }
    return false;

#else

    throw chaos::ex::NotImplementedError(
            "chaos::io::sys::exists has not yet been implemented for this "
            "platform"
    );

#endif

    return true;
}

bool is_file( const chaos::io::sys::Path& path, bool resolve_links )
{
#ifdef CHAOS_OS_UNIX

    struct stat s;

    // stat or lstat the file depending on whether we want to resolve links or
    // not
    int stat_ret = false;
    if ( resolve_links )
    {
        stat_ret = stat( path.to_unix().get_raw(), &s );
    }
    else
    {
        stat_ret = lstat( path.to_unix().get_raw(), &s );
    }

    if ( stat_ret == 0 )
    {
        if ( S_ISREG( s.st_mode ) )
        {
            return true;
        }
    }
    return false;

#elif defined( CHAOS_OS_WINDOWS )

    // utf-16
    std::size_t length = 0;
    const char* p = chaos::uni::utf8_to_utf16(
            path.to_windows().get_raw(),
            length,
            chaos::data::ENDIAN_LITTLE
    );

    struct _stat64i32 s;
    int result = _wstat64i32( ( const wchar_t* ) p, &s );
    delete[] p;

    if ( result == 0 )
    {
        if ( s.st_mode & S_IFREG )
        {
            return true;
        }
    }
    return false;

#else

    throw chaos::ex::NotImplementedError(
            "chaos::io::sys::is_file has not yet been implemented for this "
            "platform"
    );

#endif
}

bool is_directory(
        const chaos::io::sys::Path& path,
        bool  resolve_links )
{
#ifdef CHAOS_OS_UNIX

    struct stat s;

    // stat or lstat the file depending on whether we want to resolve links or
    // not
    int stat_ret = false;
    if ( resolve_links )
    {
        stat_ret = stat( path.to_unix().get_raw(), &s );
    }
    else
    {
        stat_ret = lstat( path.to_unix().get_raw(), &s );
    }

    if ( stat_ret == 0 )
    {
        if ( S_ISDIR( s.st_mode ) )
        {
            return true;
        }
    }
    return false;

#elif defined( CHAOS_OS_WINDOWS )

    // utf-16
    std::size_t length = 0;
    const char* p = chaos::uni::utf8_to_utf16(
            path.to_windows().get_raw(),
            length,
            chaos::data::ENDIAN_LITTLE
    );

    struct _stat64i32 s;
    int result =_wstat64i32( ( const wchar_t* ) p, &s );
    delete[] p;

    if ( result == 0 )
    {
        if ( s.st_mode & S_IFDIR )
        {
            return true;
        }
    }
    return false;

#else

    throw chaos::ex::NotImplementedError(
            "chaos::io::sys::is_directory has not yet been implemented for "
            "this platform"
    );

#endif
}

bool is_symbolic_link( const chaos::io::sys::Path& path )
{
#ifdef CHAOS_OS_UNIX

    struct stat s;
    if ( lstat( path.to_unix().get_raw(), &s ) == 0 )
    {
        if ( S_ISLNK( s.st_mode ) )
        {
            return true;
        }
    }
    return false;

#elif defined( CHAOS_OS_WINDOWS )

    // no symbolic links on Windows
    return false;

#else

    throw chaos::ex::NotImplementedError(
            "chaos::io::sys::is_directory has not yet been implemented for "
            "this platform"
    );

#endif
}

std::vector< chaos::io::sys::Path > list( const chaos::io::sys::Path& path )
{
    // vector to be returned
    std::vector< chaos::io::sys::Path > ret;

    // is the given path a directory?
    if ( !is_directory( path, false ) )
    {
        // not a directory so there are no sub-children
        return ret;
    }

#ifdef CHAOS_OS_UNIX

    // open the directory
    DIR* dir;
    if ( ( dir = opendir( path.to_unix().get_raw() ) ) == NULL )
    {
        // TODO: should this throw an error?
        // failed to open the directory
        return ret;
    }

    struct dirent *dir_entry;
    while( ( dir_entry = readdir( dir ) ) != NULL )
    {
        chaos::io::sys::Path p( path );
        p << dir_entry->d_name;
        ret.push_back( p );
    }

#else

    // construct the directory path
    chaos::uni::UTF8String u( path.to_windows() );
    // TODO: ends with
    if ( !u.ends_with( "\\" ) )
    {
        u += "\\";
    }
    u += "*";

    // utf-16
    std::size_t length = 0;
    const char* p = chaos::uni::utf8_to_utf16(
            u,
            length,
            chaos::data::ENDIAN_LITTLE
    );

    WIN32_FIND_DATAW find_data;
    HANDLE find_handle = FindFirstFileW( ( const wchar_t* ) p, &find_data );
    delete[] p;

    if ( find_handle == INVALID_HANDLE_VALUE )
    {
        // failed to open the directory
        // TODO: should this throw an error?
        return ret;
    }

    // iterate over sub paths
    do
    {
        chaos::io::sys::Path sub_path( path );

        sub_path << chaos::uni::utf16_to_utf8(
                ( const char* ) find_data.cFileName,
                chaos::uni::npos
        );

        ret.push_back( sub_path );
    }
    while ( FindNextFileW( find_handle, &find_data ) != 0 );

#endif

    // order alphabetically
    std::sort( ret.begin(), ret.end() );
    return ret;
}

std::vector< chaos::io::sys::Path > list_rec( const chaos::io::sys::Path& path )
{
    std::vector< chaos::io::sys::Path > ret;

    std::vector< chaos::io::sys::Path > ls( list( path ) );
    CHAOS_FOR_EACH( it, ls )
    {
        ret.push_back( *it );
        // recursively call and extend the return list
        if ( it->get_components().back() != "." &&
             it->get_components().back() != ".."   )
        {
            std::vector< chaos::io::sys::Path > d_ls( list_rec( *it ) );
            CHAOS_FOR_EACH( d_it, d_ls )
            {
                ret.push_back( *d_it );
            }
        }
    }

    return ret;
}

bool create_directory( const chaos::io::sys::Path& path )
{
    // does the path already exist?
    if ( exists( path ) )
    {
        // is this an ambiguous path?
        if ( !is_directory( path ) )
        {
            chaos::uni::UTF8String error_message;
            error_message << "Directory path: \'" << path << "\' failed to be ";
            error_message << "created as it already exists but is not a ";
            error_message << "directory.";
            throw AmbiguousPathError( error_message );
        }
        // no actions performed
        return false;
    }


#ifdef CHAOS_OS_UNIX

    if ( mkdir( path.to_unix().get_raw(), 0777 ) != 0 )
    {
        chaos::uni::UTF8String error_message;
        error_message << "Directory creation failed with OS error: ";
        error_message << chaos::os::get_last_system_error_message();
        throw CreateDirectoryError( error_message );
    }

    return true;

#elif defined( CHAOS_OS_WINDOWS )

    // utf-16
    std::size_t length = 0;
    const char* p = chaos::uni::utf8_to_utf16(
            path.to_windows().get_raw(),
            length,
            chaos::data::ENDIAN_LITTLE
    );

    BOOL result = CreateDirectoryW( ( const wchar_t* ) p, NULL );
    delete[] p;

    if ( !result )
    {
        chaos::uni::UTF8String error_message;
        error_message << "Directory creation failed with OS error: ";
        error_message << chaos::os::get_last_system_error_message();
        throw CreateDirectoryError( error_message );
    }

    return true;

#endif
}

void delete_path( const chaos::io::sys::Path& path )
{
    // does the file exist?
    if ( !exists( path ) )
    {
        chaos::uni::UTF8String error_message;
        error_message << "Cannot delete path because it does not exist: \'";
        error_message << path.to_native() << "\'";
        throw chaos::io::sys::InvalidPathError( error_message );
    }

#ifdef CHAOS_OS_UNIX

    if ( remove( path.to_unix().get_raw() ) != 0 )
    {
        chaos::uni::UTF8String error_message;
        error_message << "Failed to delete path: \'" << path.to_native();
        error_message << " \'. OS error: ";
        error_message << chaos::os::get_last_system_error_message();
        throw chaos::io::sys::InvalidPathError( error_message );
    }

#elif defined( CHAOS_OS_WINDOWS )

    // utf-16
    std::size_t length = 0;
    const char* p = chaos::uni::utf8_to_utf16(
            path.to_windows().get_raw(),
            length,
            chaos::data::ENDIAN_LITTLE
    );

    BOOL result = 0;
    if ( is_file( path ) )
    {
        result = DeleteFileW( ( const wchar_t* ) p );
    }
    else if ( is_directory( path ) )
    {
        result = RemoveDirectoryW( ( const wchar_t* ) p );
    }
    delete[] p;

    if ( !result )
    {
        chaos::uni::UTF8String error_message;
        error_message << "Deleting path failed with OS error: ";
        error_message << chaos::os::get_last_system_error_message();
        throw InvalidPathError( error_message );
    }


#endif
}

void delete_path_rec( const chaos::io::sys::Path& path )
{
    // does the file exist?
    if ( !exists( path ) )
    {
        chaos::uni::UTF8String error_message;
        error_message << "Cannot delete path because it does not exist: \'";
        error_message << path.to_native() << "\'";
        throw chaos::io::sys::InvalidPathError( error_message );
    }

    // is this a directory? do we need to traverse it?
    if ( is_directory( path ) )
    {
        std::vector< chaos::io::sys::Path > sub_paths = list( path );
        CHAOS_FOR_EACH( it, sub_paths )
        {
            // skip . and ..
            if ( it->is_empty()        ||
                 it->get_back() == "." ||
                 it->get_back() == ".."   )
            {
                continue;
            }

            // follow paths
            delete_path_rec( *it );
        }
    }

    // delete the path
    delete_path( path );
}

void validate( const chaos::io::sys::Path& path )
{
    // do nothing if the path is too short
    if ( path.get_length() < 2 )
    {
        return;
    }

    // iterate over the path ensuring each path exists
    for ( std::size_t i = 1; i < path.get_length(); ++i )
    {
        chaos::io::sys::Path p(
                path.get_components().begin(),
                path.get_components().begin() + i
        );
        create_directory( p );
    }
}

} // namespace sys
} // namespace io
} // namespace chaos
