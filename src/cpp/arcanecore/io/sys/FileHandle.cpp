#include "arcanecore/io/sys/FileHandle.hpp"

#include "arcanecore/base/Exceptions.hpp"

namespace arc
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
//                                   OPERATORS
//------------------------------------------------------------------------------

FileHandle& FileHandle::operator=(FileHandle&& other)
{
    // steal resources
    m_open = other.m_open;
    m_path = std::move(other.m_path);
    m_encoding = other.m_encoding;
    m_newline = other.m_newline;

    // reset other resources
    other.m_open = false;
    other.m_encoding = ENCODING_DETECT;
    other.m_newline  = NEWLINE_UNIX;

    return *this;
}

//-----------------------------------------------------------------------------
//                            PUBLIC MEMBER FUNCTIONS
//------------------------------------------------------------------------------

bool FileHandle::is_open() const
{
    return m_open;
}

const arc::io::sys::Path& FileHandle::get_path() const
{
    return m_path;
}

FileHandle::Encoding FileHandle::get_encoding() const
{
    return m_encoding;
}

FileHandle::Newline FileHandle::get_newline() const
{
    return m_newline;
}

void FileHandle::set_path(const arc::io::sys::Path& path)
{
    // ensure the handle isn't open
    if(m_open)
    {
        throw arc::ex::StateError(
            "FileHandle path cannot be changed since the handle is open.");
    }

    m_path = path;
}

void FileHandle::set_encoding(Encoding encoding)
{
    // ensure the handle isn't open
    if(m_open)
    {
        throw arc::ex::StateError(
            "FileHandle encoding cannot be changed since the handle is "
            "open."
        );
    }

    m_encoding = encoding;
}

void FileHandle::set_newline(Newline newline)
{
    // ensure the handle isn't open
    if(m_open)
    {
        throw arc::ex::StateError(
            "FileHandle newline symbol cannot be changed since the handle is "
            "open."
        );
    }

    m_newline = newline;
    handle_newline_detect();
}

void FileHandle::open(const arc::io::sys::Path& path)
{
    set_path(path);
    open();
}

std::size_t FileHandle::get_bom_size() const
{
    switch(m_encoding)
    {
        case ENCODING_UTF8:
            return arc::str::UTF8_BOM_SIZE;
        case ENCODING_UTF16_LITTLE_ENDIAN:
            return arc::str::UTF16_BOM_SIZE;
        case ENCODING_UTF16_BIG_ENDIAN:
            return arc::str::UTF16_BOM_SIZE;
        default:
            return 0;
    }
}

//------------------------------------------------------------------------------
//                             PROTECTED CONSTRUCTORS
//------------------------------------------------------------------------------

FileHandle::FileHandle(Encoding encoding, Newline newline)
    :
    m_open    (false),
    m_encoding(encoding),
    m_newline (newline)
{
    handle_newline_detect();
}

FileHandle::FileHandle(
        const arc::io::sys::Path& path,
        Encoding encoding,
        Newline newline)
    :
    m_open    (false),
    m_path    (path),
    m_encoding(encoding),
    m_newline (newline)
{
    handle_newline_detect();
}

//------------------------------------------------------------------------------
//                            PRIVATE MEMBER FUNCTIONS
//------------------------------------------------------------------------------

void FileHandle::handle_newline_detect()
{
    if(m_newline == NEWLINE_DETECT)
    {
#ifdef ARC_OS_WINDOWS
        m_newline = NEWLINE_WINDOWS;
#else
        m_newline = NEWLINE_UNIX;
#endif
    }
}

} // namespace sys
} // namespace io
} // namespace arc
