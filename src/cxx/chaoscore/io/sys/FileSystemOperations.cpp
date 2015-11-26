#include "chaoscore/io/sys/FileSystemOperations.hpp"

#include "chaoscore/io/sys/FileSystemExceptions.hpp"

#ifdef CHAOS_OS_UNIX

    #include <dirent.h>
    #include <unistd.h>
    #include <sys/types.h>

#elif defined( CHAOS_OS_WINDOWS )

#endif

// TODO: REMOVE ME
#include <iostream>

namespace chaos
{
namespace io
{
namespace sys
{

bool exists( const chaos::io::sys::Path& path )
{

#ifdef CHAOS_OS_UNIX

    // check for file
    if ( access( path.to_native().to_cstring(), F_OK ) != -1 )
    {
        return true;
    }
    // check for directory
    DIR* dir = opendir( path.to_native().to_cstring() );
    if ( dir )
    {
        return true;
    }

    return false;

#elif defined( CHAOS_OS_WINDOWS )

    // TODO:
    throw chaos::ex::NotImplementedError(
            "chaos::io::sys::exists has not yet been implemented for this "
            "platform"
    );

#else

    throw chaos::ex::NotImplementedError(
            "chaos::io::sys::exists has not yet been implemented for this "
            "platform"
    );

#endif

    return true;
}

bool is_file( const chaos::io::sys::Path& path )
{
    return true;
}

bool is_directory( const chaos::io::sys::Path& path )
{
    return true;
}

bool is_symbolic_link( const chaos::io::sys::Path& path )
{
    return true;
}

bool create_directory( const chaos::io::sys::Path& path )
{
    return true;
}

void validate( const chaos::io::sys::Path& path )
{

}

} // namespace sys
} // namespace io
} // namespace chaos
