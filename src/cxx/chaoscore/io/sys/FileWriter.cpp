#include "chaoscore/io/sys/FileWriter.hpp"

#include <cstddef>
#include <fstream>

#include "chaoscore/base/BaseExceptions.hpp"
#include "chaoscore/base/str/StringOperations.hpp"
#include "chaoscore/io/sys/FileSystemExceptions.hpp"

namespace chaos
{
namespace io
{
namespace sys
{

//------------------------------------------------------------------------------
//                                  CONSTRUCTORS
//------------------------------------------------------------------------------

FileWriter2::FileWriter2(
        OpenMode open_mode,
        Encoding encoding,
        Newline newline)
    :
    FileHandle2(encoding, newline),
    m_open_mode(open_mode),
    m_stream   (nullptr)
{
}

FileWriter2::FileWriter2(
        const chaos::io::sys::Path& path,
        OpenMode open_mode,
        Encoding encoding,
        Newline newline)
    :
    FileHandle2(path, encoding, newline),
    m_open_mode(open_mode),
    m_stream   (nullptr)
{
    open();
}

FileWriter2::FileWriter2(FileWriter2&& other)
    :
    FileHandle2(std::move(other)),
    m_open_mode(other.m_open_mode),
    m_stream   (other.m_stream)
{
    // reset other resources
    other.m_stream = nullptr;
}

//------------------------------------------------------------------------------
//                                   DESTRUCTOR
//------------------------------------------------------------------------------

FileWriter2::~FileWriter2()
{
    if(m_open)
    {
        m_stream->close();
    }
    if(m_stream)
    {
        delete m_stream;
    }
}

//------------------------------------------------------------------------------
//                            PUBLIC MEMBER FUNCTIONS
//------------------------------------------------------------------------------

void FileWriter2::open()
{
    // ensure the file writer is not already open
    if(m_open)
    {
        throw chaos::ex::StateError(
            "FileWriter cannot be opened since it is already open.");
    }

    // ensure we clean up the existing stream
    if (m_stream)
    {
        delete m_stream;
    }

    // set up the flags for the stream
    std::ios_base::openmode stream_flags
            = std::ios_base::out | std::ios_base::binary;
    if(m_open_mode == OPEN_TRUNCATE)
    {
        stream_flags |= std::ios_base::trunc;
    }
    else
    {
        stream_flags |= std::ios_base::app;
    }

    // create a new stream
#ifdef CHAOS_OS_WINDOWS

    // utf-16 path
    std::size_t length = 0;
    const char* p = chaos::str::utf8_to_utf16(
        m_path.to_windows(),
        length,
        chaos::data::ENDIAN_LITTLE
    );

    m_stream = new std::ofstream((const wchar_t*) p, stream_flags);

    delete[] p;

#else

    m_stream = new std::ofstream(m_path.to_native(), stream_flags);

#endif

    // did opening fail?
    if(!m_stream->good())
    {
        // clean up
        delete m_stream;

        // throw exception
        chaos::str::UTF8String error_message;
        error_message << "Failed to open FileWriter to path: \'"
                      << m_path.to_native() << "\'.";
        throw chaos::io::sys::InvalidPathError(error_message);
    }

    // TODO: write BOM

    // write the BOM based on the encoding
    switch(m_encoding)
    {
        case ENCODING_UTF8:
        {
            m_stream->write(chaos::str::UTF8_BOM, chaos::str::UTF8_BOM_SIZE);
            break;
        }
        case ENCODING_UTF16_LITTLE_ENDIAN:
        {
            m_stream->write(
                chaos::str::UTF16LE_BOM,
                chaos::str::UTF16_BOM_SIZE
            );
            break;
        }
        case ENCODING_UTF16_BIG_ENDIAN:
        {
            m_stream->write(
                chaos::str::UTF16BE_BOM,
                chaos::str::UTF16_BOM_SIZE
            );
            break;
        }
        default:
        {
            // no BOM
            break;
        }
    }

    // file write is open
    m_open = true;
}

void FileWriter2::open(const chaos::io::sys::Path& path)
{
    // just call super function, this function is only implemented here to avoid
    // C++ function hiding.
    FileHandle2::open(path);
}

void FileWriter2::close()
{
    // ensure the FileWriter is not already closed
    if(!m_open)
    {
        throw chaos::ex::StateError(
            "FileWriter cannot be closed since it is already closed.");
    }

    // close and delete the stream
    m_stream->close();
    delete m_stream;
    m_stream = nullptr;
    m_open = false;
}

chaos::int64 FileWriter2::get_size() const
{
    // ensure the FileWriter is open
    if(!m_open)
    {
        throw chaos::ex::StateError(
            "File size cannot be queried while the FileWriter is closed.");
    }

    // dynamically find the size
    chaos::int64 current = m_stream->tellp();
    m_stream->seekp(0, std::ios_base::end);
    chaos::int64 size = m_stream->tellp();
    m_stream->seekp(current, std::ios_base::beg);

    return size;
}

chaos::int64 FileWriter2::tell() const
{
    // ensure the FileWriter is open
    if(!m_open)
    {
        throw chaos::ex::StateError(
            "File position indicator cannot be queried while the FileWriter is "
            "closed."
        );
    }

    return m_stream->tellp();
}

void FileWriter2::seek(chaos::int64 index)
{
    // ensure the FileWriter is open
    if(!m_open)
    {
        throw chaos::ex::StateError(
            "File position indicator cannot be moved while the FileWriter is "
            "closed."
        );
    }

    // TODO: check size

    m_stream->seekp(index);
}

void FileWriter2::write(const char* data, std::size_t length)
{
    // ensure the FileWriter is open
    if(!m_open)
    {
        throw chaos::ex::StateError(
            "File write cannot be performed while the FileWriter is closed.");
    }

    m_stream->write(data, length);
}

void FileWriter2::write(const chaos::str::UTF8String& data)
{
    // ensure the FileWriter is open
    if(!m_open)
    {
        throw chaos::ex::StateError(
            "File write cannot be performed while the FileWriter is closed.");
    }

    // write based on encoding
    switch(m_encoding)
    {
        case ENCODING_UTF16_LITTLE_ENDIAN:
        {
            std::size_t data_length = 0;
            const char* u_data = chaos::str::utf8_to_utf16(
                data,
                data_length,
                chaos::data::ENDIAN_LITTLE,
                false
            );
            write(u_data, data_length);
            delete[] u_data;
            break;
        }
        case ENCODING_UTF16_BIG_ENDIAN:
        {
            std::size_t data_length = 0;
            const char* u_data = chaos::str::utf8_to_utf16(
                data,
                data_length,
                chaos::data::ENDIAN_BIG,
                false
            );
            write(u_data, data_length);
            delete[] u_data;
            break;
        }
        default:
        {
            write(data.get_raw(), data.get_byte_length() - 1);
            break;
        }
    }
}


void FileWriter2::write_line(const char* data, std::size_t length)
{
    // straight write the bytes first
    if(length > 0)
    {
        write(data, length);
    }

    // followed by a newline symbol
    switch(m_encoding)
    {
        case ENCODING_UTF16_LITTLE_ENDIAN:
        {
            if(m_newline == NEWLINE_WINDOWS)
            {
                const std::size_t newline_length = 4;
                const char newline_symbol[newline_length]
                    = {'\r', '\0', '\n', '\0'};
                write(newline_symbol, newline_length);
            }
            else
            {
                const std::size_t newline_length = 2;
                const char newline_symbol[newline_length] = {'\n', '\0'};
                write(newline_symbol, newline_length);
            }
            break;
        }
        case ENCODING_UTF16_BIG_ENDIAN:
        {
            if(m_newline == NEWLINE_WINDOWS)
            {
                const std::size_t newline_length = 4;
                const char newline_symbol[newline_length]
                    = {'\0', '\r', '\0', '\n'};
                write(newline_symbol, newline_length);
            }
            else
            {
                const std::size_t newline_length = 2;
                const char newline_symbol[newline_length] = {'\0', '\n'};
                write(newline_symbol, newline_length);
            }
            break;
        }
        default:
        {
            if(m_newline == NEWLINE_WINDOWS)
            {
                const std::size_t newline_length = 2;
                const char newline_symbol[newline_length] = {'\r', '\n'};
                write(newline_symbol, newline_length);
            }
            else
            {
                const std::size_t newline_length = 1;
                const char newline_symbol[newline_length] = {'\n'};
                write(newline_symbol, newline_length);
            }
            break;
        }
    }
}

void FileWriter2::write_line(const chaos::str::UTF8String& data)
{
    // write string
    write(data);
    // then write newline
    write_line("", 0);
}








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
