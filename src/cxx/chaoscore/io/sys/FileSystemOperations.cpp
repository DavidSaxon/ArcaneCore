#include "chaoscore/io/sys/FileSystemOperations.hpp"

#include <sys/stat.h>
#include <sys/types.h>

#ifdef CHAOS_OS_UNIX

    #include <cstring>
    #include <dirent.h>
    #include <errno.h>
    #include <unistd.h>


#elif defined( CHAOS_OS_WINDOWS )

    #include <windows.h>

#endif

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
        stat_ret = stat( path.to_unix().to_cstring(), &s );
    }
    else
    {
        stat_ret = lstat( path.to_unix().to_cstring(), &s );
    }

    // return based on the stat return code
    if (  stat_ret == 0 )
    {
        return true;
    }
    return false;

#elif defined( CHAOS_OS_WINDOWS )

    struct stat s;
    if ( stat( path.to_windows().to_cstring(), &s ) == 0 )
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
        stat_ret = stat( path.to_unix().to_cstring(), &s );
    }
    else
    {
        stat_ret = lstat( path.to_unix().to_cstring(), &s );
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

    struct stat s;
    if ( stat( path.to_windows().to_cstring(), &s ) == 0 )
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
        stat_ret = stat( path.to_unix().to_cstring(), &s );
    }
    else
    {
        stat_ret = lstat( path.to_unix().to_cstring(), &s );
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

    struct stat s;
    if ( stat( path.to_windows().to_cstring(), &s ) == 0 )
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
    if ( lstat( path.to_unix().to_cstring(), &s ) == 0 )
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

bool create_directory( const chaos::io::sys::Path& path )
{
    chaos::uni::UTF8String p = path.to_native();

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

    if ( mkdir( p.to_cstring(), 0777 ) != 0 )
    {
        chaos::uni::UTF8String error_message;
        error_message << "Directory creation failed with error code: ";
        error_message << errno << ": " << strerror( errno );
        throw CreateDirectoryError( error_message );
    }

    return true;

#elif defined( CHAOS_OS_WINDOWS )

    if ( !CreateDirectory( p.to_cstring(), NULL ) )
    {
        chaos::uni::UTF8String error_message;
        error_message << "Directory creation failed with error code: ";
        error_message << GetLastError();
        // << ": " << strerror( errno ); // TODO:
        throw CreateDirectoryError( error_message );

    }

    return true;

#endif
}

void validate( const chaos::io::sys::Path& path )
{
    // do nothing of the path is too short
    if ( path.get_length() < 2 )
    {
        return;
    }

    // iterate over the path ensuring each path exists
    // CHAOS_FOR_EACH( it, path.get_components() )
    // {
    //     chaos::io::sys::Path check_path(
    //             path.get_components().begin(), it - 1 );
    //     create_directory( check_path );
    // }
    for ( size_t i = 1; i < path.get_length(); ++i )
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
