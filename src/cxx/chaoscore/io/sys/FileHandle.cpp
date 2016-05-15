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

FileHandle2::FileHandle2(FileHandle2&& other)
    :
    m_open    (other.m_open),
    m_path    (std::move(other.m_path)),
    m_encoding(other.m_encoding),
    m_newline (other.m_newline)
{
    // reset other resources
    other.m_open     = false;
    other.m_encoding = ENCODING_DETECT;
    other.m_newline  = NEWLINE_UNIX;
}

//------------------------------------------------------------------------------
//                            PUBLIC MEMBER FUNCTIONS
//------------------------------------------------------------------------------

bool FileHandle2::is_open() const
{
    return m_open;
}

const chaos::io::sys::Path& FileHandle2::get_path() const
{
    return m_path;
}

FileHandle2::Encoding FileHandle2::get_encoding() const
{
    return m_encoding;
}

FileHandle2::Newline FileHandle2::get_newline() const
{
    return m_newline;
}

void FileHandle2::set_path(const chaos::io::sys::Path& path)
{
    // ensure the handle isn't open
    if(m_open)
    {
        throw chaos::ex::StateError(
            "FileHandle path cannot be changed since the handle is open.");
    }

    m_path = path;
}

void FileHandle2::set_encoding(Encoding encoding)
{
    // ensure the handle isn't open
    if(m_open)
    {
        throw chaos::ex::StateError(
            "FileHandle encoding cannot be changed since the handle is "
            "open."
        );
    }

    m_encoding = encoding;
}

void FileHandle2::set_newline(Newline newline)
{
    // ensure the handle isn't open
    if(m_open)
    {
        throw chaos::ex::StateError(
            "FileHandle newline symbol cannot be changed since the handle is "
            "open."
        );
    }

    m_newline = newline;
}

void FileHandle2::open(const chaos::io::sys::Path& path)
{
    set_path(path);
    open();
}

//------------------------------------------------------------------------------
//                             PROTECTED CONSTRUCTORS
//------------------------------------------------------------------------------

FileHandle2::FileHandle2(Encoding encoding, Newline newline)
    :
    m_open    (false),
    m_encoding(encoding),
    m_newline (newline)
{
}

FileHandle2::FileHandle2(
        const chaos::io::sys::Path& path,
        Encoding encoding,
        Newline newline)
    :
    m_open    (false),
    m_path    (path),
    m_encoding(encoding),
    m_newline (newline)
{
}

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
