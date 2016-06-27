#include "arcanecore/io/sys/FileWriter.hpp"

#include <cstddef>
#include <fstream>

#include "arcanecore/base/Exceptions.hpp"
#include "arcanecore/base/str/StringOperations.hpp"

namespace arc
{
namespace io
{
namespace sys
{

//------------------------------------------------------------------------------
//                                  CONSTRUCTORS
//------------------------------------------------------------------------------

FileWriter::FileWriter(
        OpenMode open_mode,
        Encoding encoding,
        Newline newline)
    :
    FileHandle(encoding, newline),
    m_open_mode(open_mode),
    m_stream   (nullptr)
{
}

FileWriter::FileWriter(
        const arc::io::sys::Path& path,
        OpenMode open_mode,
        Encoding encoding,
        Newline newline)
    :
    FileHandle(path, encoding, newline),
    m_open_mode(open_mode),
    m_stream   (nullptr)
{
    open();
}

FileWriter::FileWriter(FileWriter&& other)
    :
    FileHandle(std::move(other)),
    m_open_mode(other.m_open_mode),
    m_stream   (other.m_stream)
{
    // reset other resources
    other.m_stream = nullptr;
}

//------------------------------------------------------------------------------
//                                   DESTRUCTOR
//------------------------------------------------------------------------------

FileWriter::~FileWriter()
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
//                                   OPERATORS
//------------------------------------------------------------------------------

FileWriter& FileWriter::operator=(FileWriter&& other)
{
    // steal
    FileHandle::operator=(std::move(other));
    m_open_mode = other.m_open_mode;
    m_stream = other.m_stream;

    // reset
    other.m_stream = nullptr;

    return *this;
}

//------------------------------------------------------------------------------
//                            PUBLIC MEMBER FUNCTIONS
//------------------------------------------------------------------------------

FileWriter::OpenMode FileWriter::get_open_mode() const
{
    return m_open_mode;
}

void FileWriter::set_open_mode(OpenMode open_mode)
{
    // ensure the file writer isn't open
    if(m_open)
    {
        throw arc::ex::StateError(
            "FileWriter OpenMode cannot be changed since the writer is open.");
    }

    m_open_mode = open_mode;
}

void FileWriter::open()
{
    // ensure the file writer is not already open
    if(m_open)
    {
        throw arc::ex::StateError(
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
#ifdef ARC_OS_WINDOWS

    // utf-16 path
    std::size_t length = 0;
    const char* p = arc::str::utf8_to_utf16(
        m_path.to_windows(),
        length,
        arc::data::ENDIAN_LITTLE
    );

    m_stream = new std::ofstream((const wchar_t*) p, stream_flags);

    delete[] p;

#else

    m_stream = new std::ofstream(m_path.to_native().get_raw(), stream_flags);

#endif

    // did opening fail?
    if(!m_stream->good())
    {
        // clean up
        delete m_stream;

        // throw exception
        arc::str::UTF8String error_message;
        error_message << "Failed to open FileWriter to path: \'"
                      << m_path.to_native() << "\'.";
        throw arc::ex::InvalidPathError(error_message);
    }

    // write the BOM based on the encoding
    switch(m_encoding)
    {
        case ENCODING_UTF8:
        {
            m_stream->write(arc::str::UTF8_BOM, arc::str::UTF8_BOM_SIZE);
            break;
        }
        case ENCODING_UTF16_LITTLE_ENDIAN:
        {
            m_stream->write(
                arc::str::UTF16LE_BOM,
                arc::str::UTF16_BOM_SIZE
            );
            break;
        }
        case ENCODING_UTF16_BIG_ENDIAN:
        {
            m_stream->write(
                arc::str::UTF16BE_BOM,
                arc::str::UTF16_BOM_SIZE
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

void FileWriter::open(const arc::io::sys::Path& path)
{
    // just call super function, this function is only implemented here to avoid
    // C++ function hiding.
    FileHandle::open(path);
}

void FileWriter::close()
{
    // ensure the FileWriter is not already closed
    if(!m_open)
    {
        throw arc::ex::StateError(
            "FileWriter cannot be closed since it is already closed.");
    }

    // close and delete the stream
    m_stream->close();
    delete m_stream;
    m_stream = nullptr;
    m_open = false;
}

arc::int64 FileWriter::get_size() const
{
    // ensure the FileWriter is open
    if(!m_open)
    {
        throw arc::ex::StateError(
            "File size cannot be queried while the FileWriter is closed.");
    }

    // dynamically find the size
    arc::int64 current = m_stream->tellp();
    m_stream->seekp(0, std::ios_base::end);
    arc::int64 size = m_stream->tellp();
    m_stream->seekp(current, std::ios_base::beg);

    return size;
}

arc::int64 FileWriter::tell() const
{
    // ensure the FileWriter is open
    if(!m_open)
    {
        throw arc::ex::StateError(
            "File position indicator cannot be queried while the FileWriter is "
            "closed."
        );
    }

    return m_stream->tellp();
}

void FileWriter::seek(arc::int64 index)
{
    // ensure the FileWriter is open
    if(!m_open)
    {
        throw arc::ex::StateError(
            "File position indicator cannot be moved while the FileWriter is "
            "closed."
        );
    }

    // TODO: check size

    m_stream->seekp(index);
}

void FileWriter::write(const char* data, std::size_t length, bool _flush)
{
    // ensure the FileWriter is open
    if(!m_open)
    {
        throw arc::ex::StateError(
            "File write cannot be performed while the FileWriter is closed.");
    }

    m_stream->write(data, length);

    // flush?
    if(_flush)
    {
        flush();
    }
}

void FileWriter::write(const arc::str::UTF8String& data, bool _flush)
{
    // ensure the FileWriter is open
    if(!m_open)
    {
        throw arc::ex::StateError(
            "File write cannot be performed while the FileWriter is closed.");
    }

    // write based on encoding
    switch(m_encoding)
    {
        case ENCODING_UTF16_LITTLE_ENDIAN:
        {
            std::size_t data_length = 0;
            const char* u_data = arc::str::utf8_to_utf16(
                data,
                data_length,
                arc::data::ENDIAN_LITTLE,
                false
            );
            write(u_data, data_length, false);
            delete[] u_data;
            break;
        }
        case ENCODING_UTF16_BIG_ENDIAN:
        {
            std::size_t data_length = 0;
            const char* u_data = arc::str::utf8_to_utf16(
                data,
                data_length,
                arc::data::ENDIAN_BIG,
                false
            );
            write(u_data, data_length, false);
            delete[] u_data;
            break;
        }
        default:
        {
            write(data.get_raw(), data.get_byte_length() - 1, false);
            break;
        }
    }

    // flush?
    if(_flush)
    {
        flush();
    }
}


void FileWriter::write_line(const char* data, std::size_t length, bool _flush)
{
    // straight write the bytes first
    if(length > 0)
    {
        write(data, length, false);
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
                write(newline_symbol, newline_length, false);
            }
            else
            {
                const std::size_t newline_length = 2;
                const char newline_symbol[newline_length] = {'\n', '\0'};
                write(newline_symbol, newline_length, false);
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
                write(newline_symbol, newline_length, false);
            }
            else
            {
                const std::size_t newline_length = 2;
                const char newline_symbol[newline_length] = {'\0', '\n'};
                write(newline_symbol, newline_length, false);
            }
            break;
        }
        default:
        {
            if(m_newline == NEWLINE_WINDOWS)
            {
                const std::size_t newline_length = 2;
                const char newline_symbol[newline_length] = {'\r', '\n'};
                write(newline_symbol, newline_length, false);
            }
            else
            {
                const std::size_t newline_length = 1;
                const char newline_symbol[newline_length] = {'\n'};
                write(newline_symbol, newline_length, false);
            }
            break;
        }
    }

    // flush?
    if(_flush)
    {
        flush();
    }
}

void FileWriter::write_line(const arc::str::UTF8String& data, bool _flush)
{
    // write string
    write(data, false);
    // then write newline
    write_line("", 0, _flush);
}

void FileWriter::flush()
{
    // ensure the FileWriter is open
    if(!m_open)
    {
        throw arc::ex::StateError(
            "Flush cannot be performed while the FileWriter is closed.");
    }

    m_stream->flush();
}

} // namespace sys
} // namespace io
} // namespace arc
