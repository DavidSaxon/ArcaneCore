#include "chaoscore/io/sys/FileHandle.hpp"

#include "chaoscore/base/BaseExceptions.hpp"

namespace chaos
{
namespace io
{
namespace sys
{

//------------------------------------------------------------------------------
//                                MOVE CONSTRUCTOR
//------------------------------------------------------------------------------

FileHandle::FileHandle(FileHandle&& other)
    :
    m_path    (std::move(other.m_path)),
    m_flags   (other.m_flags),
    m_encoding(other.m_encoding),
    m_open    (other.m_open)
{
    // reset other resources
    other.m_flags = 0;
    other.m_encoding = chaos::str::ENCODING_UTF8;
    other.m_open = false;
}

//------------------------------------------------------------------------------
//                            PUBLIC MEMBER FUNCTIONS
//------------------------------------------------------------------------------

bool FileHandle::is_open() const
{
    return m_open;
}

void FileHandle::open(const chaos::io::sys::Path& path)
{
    set_path(path);
    open();
}

const chaos::io::sys::Path& FileHandle::get_path() const
{
    return m_path;
}

void FileHandle::set_path(const chaos::io::sys::Path& path)
{
    // ensure the handle isn't already open
    if (m_open)
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

void FileHandle::set_flags(chaos::uint32 flags)
{
    // ensure the handle isn't already open
    if (m_open)
    {
        throw chaos::ex::StateError(
                "FileHandle flags cannot be changed since the handle is "
                "currently open."
        );
    }

    m_flags = flags;
}

chaos::str::Encoding FileHandle::get_encoding() const
{
    return m_encoding;
}

void FileHandle::set_encoding(chaos::str::Encoding encoding)
{
    // ensure the handle isn't already open
    if (m_open)
    {
        throw chaos::ex::StateError(
                "FileHandle encoding cannot be set since the handle is "
                "currently open."
        );
    }

    m_encoding = encoding;
}

//------------------------------------------------------------------------------
//                             PROTECTED CONSTRUCTORS
//------------------------------------------------------------------------------

FileHandle::FileHandle(
        chaos::uint32 flags,
        chaos::str::Encoding encoding)
    :
    m_flags   (flags),
    m_encoding(encoding),
    m_open    (false)
{
}

FileHandle::FileHandle(
        const chaos::io::sys::Path& path,
        chaos::uint32 flags,
        chaos::str::Encoding encoding)
    :
    m_path    (path),
    m_flags   (flags),
    m_encoding(encoding),
    m_open    (false)
{
}

} // namespace sys
} // namespace io
} // namespace chaos
