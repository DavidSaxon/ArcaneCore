#include "chaoscore/io/sys/FileHandle.hpp"

#include "chaoscore/base/BaseExceptions.hpp"

namespace chaos
{
namespace io
{
namespace sys
{

//------------------------------------------------------------------------------
//                            PUBLIC MEMBER FUNCTIONS
//------------------------------------------------------------------------------

void FileHandle::open( const chaos::io::sys::Path& path )
{
    set_path( path );
    open();
}

const chaos::io::sys::Path& FileHandle::get_path() const
{
    return m_path;
}

void FileHandle::set_path( const chaos::io::sys::Path& path )
{
    // ensure the handle isn't already open
    if ( m_open )
    {
        throw chaos::ex::StateError(
                "FileHandle path cannot be changed since the handle is "
                "currently open to a valid path"
        );
    }

    m_path = path;
}

chaos::uint32 FileHandle::get_flags() const
{
    return m_flags;
}

void FileHandle::set_flags( chaos::uint32 flags )
{
    // ensure the handle isn't already open
    if ( m_open )
    {
        throw chaos::ex::StateError(
                "FileHandle flags cannot be changed since the handle is "
                "currently open."
        );
    }

    m_flags = flags;
}

//------------------------------------------------------------------------------
//                             PROTECTED CONSTRUCTORS
//------------------------------------------------------------------------------

FileHandle::FileHandle( chaos::uint32 flags )
    :
    m_flags( flags ),
    m_open ( false )
{
}

FileHandle::FileHandle( const chaos::io::sys::Path& path, chaos::uint32 flags )
    :
    m_path ( path ),
    m_flags( flags ),
    m_open ( false )
{
}

} // namespace sys
} // namespace io
} // namespace chaos
