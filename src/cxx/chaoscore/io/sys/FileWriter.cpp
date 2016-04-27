#include "chaoscore/io/sys/FileWriter.hpp"

#include <cstddef>
#include <fstream>

#include "chaoscore/base/BaseExceptions.hpp"
#include "chaoscore/base/str/UnicodeOperations.hpp"
#include "chaoscore/io/sys/FileSystemExceptions.hpp"

namespace chaos
{
namespace io
{
namespace sys
{

//------------------------------------------------------------------------------
//                                   CONSTANTS
//------------------------------------------------------------------------------

namespace
{

const unsigned char UTF8_BOM[3] = {0xEF, 0xBB, 0xBF};

} // namespace anonymous

//------------------------------------------------------------------------------
//                                  CONSTRUCTORS
//------------------------------------------------------------------------------

FileWriter::FileWriter(
        chaos::uint32 flags,
        chaos::str::Encoding encoding)
    :
    FileHandle(flags, encoding),
    m_stream  (nullptr)
{
    // TODO: encoding error
}

FileWriter::FileWriter(
        const chaos::io::sys::Path& path,
        chaos::uint32 flags,
        chaos::str::Encoding encoding)
    :
    FileHandle(path, flags, encoding),
    m_stream  (nullptr)
{
    // TODO: not implemented encoding errors
    open();
}

FileWriter::FileWriter(FileWriter&& other)
    :
    FileHandle(std::move(other)),
    m_stream  (other.m_stream)
{
    // reset other resources
    other.m_stream = nullptr;
}

//------------------------------------------------------------------------------
//                                   DESTRUCTOR
//------------------------------------------------------------------------------

FileWriter::~FileWriter()
{
    if (m_open)
    {
        m_stream->close();
    }
    if (m_stream)
    {
        delete m_stream;
    }
}

//------------------------------------------------------------------------------
//                                   OPERATORS
//------------------------------------------------------------------------------

FileWriter& FileWriter::operator<<( const chaos::str::UTF8String& text )
{
    write( text );

    return *this;
}

//------------------------------------------------------------------------------
//                            PUBLIC MEMBER FUNCTIONS
//------------------------------------------------------------------------------

void FileWriter::open()
{
    // ensure the file writer is not open
    if (m_open)
    {
        throw chaos::ex::StateError(
            "FileHandle cannot be opened since the handle is already open."
        );
    }

    // ensure we clean up the existing stream
    if (m_stream)
    {
        delete m_stream;
    }

    // convert flags
    std::ios_base::openmode flags = std::ios_base::out;
    if (m_flags & FLAG_BINARY)
    {
        flags |= std::ios_base::binary;
    }
    if (m_flags & FLAG_APPEND)
    {
        flags |= std::ios_base::app;
    }

    // TODO: support other encodings

    // create a new stream
#ifdef CHAOS_OS_WINDOWS

    // utf-16 path
    std::size_t length = 0;
    const char* p = chaos::str::utf8_to_utf16(
        m_path.to_windows().get_raw(),
        length,
        chaos::data::ENDIAN_LITTLE
    );

    m_stream = new std::ofstream((const wchar_t*) p, flags);

#else

    m_stream = new std::ofstream(m_path.to_native().get_raw(), flags);

#endif

    // did opening fail?
    if (!m_stream->good())
    {
        // clean up
        delete m_stream;

        // throw exception
        chaos::str::UTF8String error_message;
        error_message << "Failed to open FileWriter to path: \'";
        error_message << m_path.to_native() << "\'";
        throw chaos::io::sys::InvalidPathError(error_message);
    }

    // TODO: support other encodings
    // if we are not in binary mode or appending to the file write the UTF-8 BOM
    if (m_flags == FileWriter::FLAG_NONE)
    {
        (*m_stream) << UTF8_BOM;
    }

    // file writer is open
    m_open = true;
}

void FileWriter::open(const chaos::io::sys::Path& path)
{
    // just call super function, this function is only implemented here to avoid
    // C++ function hiding.
    FileHandle::open(path);
}

void FileWriter::close()
{
    // ensure the file writer is not already closed
    if (!m_open)
    {
        throw chaos::ex::StateError(
            "FileHandle cannot be closed since the handle is already closed.");
    }

    m_stream->close();

    // TODO: check for errors?

    // delete the stream
    delete m_stream;
    m_stream = nullptr;

    m_open = false;
}

void FileWriter::write( const chaos::str::UTF8String& text )
{
    // ensure the file writer if not already closed
    if ( !m_open )
    {
        throw chaos::ex::StateError(
                "FileWriter cannot be written to since the handle is closed."
        );
    }

    m_stream->write( text.get_raw(), text.get_byte_length() - 1 );
}

void FileWriter::write_line( const chaos::str::UTF8String& text )
{
    write( text );
    m_stream->write( "\n", 1 );
}

} // namespace sys
} // namespace io
} // namespace chaos
