#include "chaoscore/io/sys/FileReader.hpp"

#include <fstream>

#include "chaoscore/base/str/UnicodeOperations.hpp"
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

FileReader::FileReader(
        chaos::uint32 flags,
        chaos::str::Encoding encoding)
    :
    FileHandle(flags, encoding),
    m_stream  (nullptr),
    m_size    (0)
{
    // TODO: not implemented encoding errors
}

FileReader::FileReader(
        const chaos::io::sys::Path& path,
        chaos::uint32 flags,
        chaos::str::Encoding encoding)
    :
    FileHandle(path, flags, encoding),
    m_stream  (nullptr),
    m_size    (0)
{
    // TODO: not implemented encoding errors
    open();
}

FileReader::FileReader(FileReader&& other)
    :
    FileHandle(std::move(other)),
    m_stream  (other.m_stream),
    m_size    (other.m_size)
{
    // reset other resources
    other.m_stream = nullptr;
    other.m_size = 0;
}

//------------------------------------------------------------------------------
//                                   DESTRUCTOR
//------------------------------------------------------------------------------

FileReader::~FileReader()
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

// TODO:

//------------------------------------------------------------------------------
//                            PUBLIC MEMBER FUNCTIONS
//------------------------------------------------------------------------------

void FileReader::open()
{
    // ensure the file reader is not open
    if (m_open)
    {
        throw chaos::ex::StateError(
            "FileReader cannot be opened since the handle is already open.");
    }

    // ensure we clean up the existing stream
    if (m_stream)
    {
        delete m_stream;
    }

    // convert flags
    std::ios_base::openmode flags = std::ios_base::in;
    if (m_flags & FLAG_BINARY)
    {
        flags |= std::ios_base::binary;
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

    m_stream = new std::ifstream((const wchar_t*) p, flags);

#else

    m_stream = new std::ifstream(m_path.to_native().get_raw(), flags);

#endif

    // did opening fail?
    if (!m_stream->good())
    {
        // clean up
        delete m_stream;

        // throw exception
        chaos::str::UTF8String error_message;
        error_message << "Failed to open FileReader to path: \'"
                      << m_path.to_native() << "\'";
        throw chaos::io::sys::InvalidPathError(error_message);
    }

    // retrieve the size of the file
    m_stream->seekg(0, std::ios_base::end);
    m_size = m_stream->tellg();
    m_stream->seekg(0, std::ios_base::beg);

    // file reader is open
    m_open = true;
}

void FileReader::open(const chaos::io::sys::Path& path)
{
    // just call super function, this function is only implemented here to avoid
    // C++ function hiding.
    FileHandle::open(path);
}

void FileReader::close()
{
    // ensure the file reader is not already closed
    if (!m_open)
    {
        throw chaos::ex::StateError(
            "FileReader cannot be closed since the handle is already closed.");
    }

    m_stream->close();

    // TODO: check for errors?

    // delete the stream
    delete m_stream;
    m_stream = nullptr;

    m_open = false;
}

chaos::int64 FileReader::get_size() const
{
    // TODO: should size be dynamic?

    // ensure the FileReader is open
    if (!m_open)
    {
        throw chaos::ex::StateError(
            "File size cannot be queried while the FileReader is closed.");
    }

    return m_size;
}

chaos::int64 FileReader::tell() const
{
    return m_stream->tellg();
}

void FileReader::seek(chaos::int64 index)
{
    m_stream->seekg(index);
}

bool FileReader::eof() const
{
    // TODO:
    return false;
}

void FileReader::read(char* data, chaos::int64 length)
{
    // get the current indicator position, this will check if the reader is
    // open
    chaos::int64 pos = tell();

    // zero data requested: do nothing
    if(length == 0)
    {
        return;
    }

    // check if the read extends past the end of the file
    if(pos + length > get_size())
    {
        throw chaos::io::sys::EOFError(
            "Cannot read data, as the requested length from the file position "
            "indicator extends past the end of the file."
        );
    }

    m_stream->read(data, length);
}

void FileReader::read_line(chaos::str::UTF8String& text)
{
    // TODO:
}


} // namespace sys
} // namespace io
} // namespace chaos
