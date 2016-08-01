#include "arcanecore/io/sys/FileReader.hpp"

#include <cstring>
#include <fstream>

#include "arcanecore/base/str/StringOperations.hpp"
#include "arcanecore/base/Exceptions.hpp"

namespace arc
{
namespace io
{
namespace sys
{

//------------------------------------------------------------------------------
//                                    OBJECTS
//------------------------------------------------------------------------------

/*!
 * \brief Simple object that can be used to check whether the given vector ends
 *        with a newline byte sequence.
 */
struct NewlineChecker
{
    //----------------------------PUBLIC ATTRIBUTES-----------------------------
    std::size_t sequence_length;
    char* newline_sequence;
    //-------------------------------CONSTRUCTOR--------------------------------
    NewlineChecker()
        :
        sequence_length (0),
        newline_sequence(nullptr)
    {
    }
    //--------------------------------DESTRUCTOR--------------------------------
    ~NewlineChecker()
    {
        delete[] newline_sequence;
    }
    //-------------------------PUBLIC MEMBER FUNCTIONS--------------------------
    bool check(const std::vector<char>& data)
    {
        if(data.size() < sequence_length)
        {
            return false;
        }
        // could perform some sort of caching?
        for(std::size_t i = 0; i < sequence_length; ++i)
        {
            if(data[data.size() - (sequence_length - i)]
               != newline_sequence[i])
            {
                return false;
            }
        }
        return true;
    }
};

//------------------------------------------------------------------------------
//                                  CONSTRUCTORS
//------------------------------------------------------------------------------

FileReader::FileReader(Encoding encoding, Newline newline)
    :
    FileHandle            (encoding, newline),
    m_stream               (nullptr),
    m_size                 (0),
    m_newline_checker_valid(false),
    m_newline_checker      (new NewlineChecker())
{
}


FileReader::FileReader(
        const arc::io::sys::Path& path,
        Encoding encoding,
        Newline newline)
    :
    FileHandle            (path, encoding, newline),
    m_stream               (nullptr),
    m_size                 (0),
    m_newline_checker_valid(false),
    m_newline_checker      (new NewlineChecker())
{
    open();
}

FileReader::FileReader(FileReader&& other)
    :
    FileHandle             (std::move(other)),
    m_stream               (other.m_stream),
    m_size                 (other.m_size),
    m_newline_checker_valid(other.m_newline_checker_valid),
    m_newline_checker      (std::move(other.m_newline_checker))
{
    // reset other resources
    other.m_stream = nullptr;
    other.m_size = 0;
    other.m_newline_checker_valid = false;
}

//------------------------------------------------------------------------------
//                                   OPERATORS
//------------------------------------------------------------------------------

FileReader& FileReader::operator=(FileReader&& other)
{
    // steal
    FileHandle::operator=(std::move(other));
    m_stream = other.m_stream;
    m_size = other.m_size;
    m_newline_checker_valid =  other.m_newline_checker_valid;
    m_newline_checker = std::move(other.m_newline_checker);

    // reset
    other.m_stream = nullptr;
    other.m_size = 0;
    other.m_newline_checker_valid = false;

    return *this;
}

//------------------------------------------------------------------------------
//                                   DESTRUCTOR
//------------------------------------------------------------------------------

FileReader::~FileReader()
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

void FileReader::open()
{
    // ensure the file reader is not already open
    if(m_open)
    {
        throw arc::ex::StateError(
            "FileReader cannot be opened since it is already open.");
    }

    // ensure we clean up the existing stream
    if (m_stream)
    {
        delete m_stream;
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

    m_stream = new std::ifstream(
        (const wchar_t*) p,
        std::ios_base::in | std::ios_base::binary
    );

    delete[] p;

#else

    m_stream = new std::ifstream(
        m_path.to_native().get_raw(),
        std::ios_base::in | std::ios_base::binary
    );

#endif

    // did opening fail?
    if(!m_stream->good())
    {
        // clean up
        delete m_stream;

        // throw exception
        arc::str::UTF8String error_message;
        error_message << "Failed to open FileReader to path: \'"
                      << m_path.to_native() << "\'.";
        throw arc::ex::IOError(error_message);
    }

    // retrieve the size of the file
    m_stream->seekg(0, std::ios_base::end);
    m_size = m_stream->tellg();
    m_stream->seekg(0, std::ios_base::beg);

    // should we detect the encoding, check for UTF-8 first since it's the most
    // common
    std::size_t size_st = static_cast<std::size_t>(m_size);
    if(m_encoding == ENCODING_DETECT && size_st >= arc::str::UTF8_BOM_SIZE)
    {
        char* bom = new char[arc::str::UTF8_BOM_SIZE];
        m_stream->read(bom, arc::str::UTF8_BOM_SIZE);
        if(memcmp(bom, arc::str::UTF8_BOM, arc::str::UTF8_BOM_SIZE) == 0)
        {
            m_encoding = ENCODING_UTF8;
        }
        m_stream->seekg(0);
        delete[] bom;
    }
    // the encoding still hasn't been detected, check for UTF-16 encodings next
    if(m_encoding == ENCODING_DETECT && size_st >= arc::str::UTF16_BOM_SIZE)
    {
        char* bom = new char[arc::str::UTF16_BOM_SIZE];
        m_stream->read(bom, arc::str::UTF16_BOM_SIZE);
        if(memcmp(bom, arc::str::UTF16LE_BOM, arc::str::UTF16_BOM_SIZE)
           == 0)
        {
            m_encoding = ENCODING_UTF16_LITTLE_ENDIAN;
        }
        else if(memcmp(bom, arc::str::UTF16BE_BOM, arc::str::UTF16_BOM_SIZE)
                == 0)
        {
            m_encoding = ENCODING_UTF16_BIG_ENDIAN;
        }
        m_stream->seekg(0);
        delete[] bom;
    }
    // still no encoding, assume RAW
    if(m_encoding == ENCODING_DETECT)
    {
        m_encoding = ENCODING_RAW;
    }

    // file reader is open
    m_open = true;
    m_newline_checker_valid = false;
}

void FileReader::open(const arc::io::sys::Path& path)
{
    // just call super function, this function is only implemented here to avoid
    // C++ function hiding.
    FileHandle::open(path);
}

void FileReader::close()
{
    // ensure the FileReader is not already closed
    if(!m_open)
    {
        throw arc::ex::StateError(
            "FileReader cannot be closed since it is already closed.");
    }

    // close and delete the stream
    m_stream->close();
    delete m_stream;
    m_stream = nullptr;
    m_open = false;
}

arc::int64 FileReader::get_size() const
{
    // TODO: should size be dynamic?

    // ensure the FileReader is open
    if(!m_open)
    {
        throw arc::ex::StateError(
            "File size cannot be queried while the FileReader is closed.");
    }

    return m_size;
}

arc::int64 FileReader::tell() const
{
    // ensure the FileReader is open
    if(!m_open)
    {
        throw arc::ex::StateError(
            "File position indicator cannot be queried while the FileReader is "
            "closed."
        );
    }

    return m_stream->tellg();
}

void FileReader::seek(arc::int64 index)
{
    // ensure the FileReader is open
    if(!m_open)
    {
        throw arc::ex::StateError(
            "File position indicator cannot be moved while the FileReader is "
            "closed."
        );
    }

    // TODO: check size

    m_stream->seekg(index);
}

bool FileReader::eof() const
{
    // ensure the FileReader is open
    if(!m_open)
    {
        throw arc::ex::StateError(
            "End of File cannot be queried while the FileReader is closed."
        );
    }

    return m_stream->eof();
}

bool FileReader::has_bom()
{
    // ensure the FileReader is open
    if(!m_open)
    {
        throw arc::ex::StateError(
            "Unicode BOM cannot be queried while the FileReader is closed."
        );
    }


    // does this encoding actually use a BOM? and is there actually enough data
    // in the file?
    arc::int64 bom_size = static_cast<arc::int64>(get_bom_size());
    std::size_t bom_size_t = static_cast<std::size_t>(bom_size);
    if(bom_size == 0 || m_size < bom_size)
    {
        return false;
    }

    // store the current position indicator
    arc::int64 pos = tell();
    // seek to the beginning of the file
    seek(0);
    // read the BOM character
    char* bom = new char[bom_size_t];
    read(bom, bom_size);

    bool correct = false;
    switch(m_encoding)
    {
        case ENCODING_UTF8:
            correct = memcmp(bom, arc::str::UTF8_BOM, bom_size_t) == 0;
            break;
        case ENCODING_UTF16_LITTLE_ENDIAN:
            correct = memcmp(bom, arc::str::UTF16LE_BOM, bom_size_t) == 0;
            break;
        case ENCODING_UTF16_BIG_ENDIAN:
            correct = memcmp(bom, arc::str::UTF16BE_BOM, bom_size_t) == 0;
            break;
        default:
            arc::str::UTF8String error_message;
            error_message << "Unexpected file encoding when checking for BOM: "
                          << m_encoding;
            throw arc::ex::NotImplementedError(error_message);
    }

    // clean up
    delete[] bom;
    seek(pos);

    return correct;
}

arc::int64 FileReader::seek_to_data_start()
{
    // does the file have a byte order marker, if so seek past it
    if(has_bom())
    {
        seek(static_cast<arc::int64>(get_bom_size()));
    }
    // else seek to the start of the file
    else
    {
        seek(0);
    }
    return tell();
}

void FileReader::read(char* data, arc::int64 length)
{
    check_can_read();

    m_stream->read(data, length);

    // little bit of a hack, but for some reason ifstream::read doesn't set the
    // EOF flag unless you read past the end of the file. So we will forcibly
    // set it if the we are at the end of the file.
    if(!eof() && tell() >= get_size())
    {
        m_stream->get();
    }
}

void FileReader::read(arc::str::UTF8String& data, arc::int64 length)
{
    check_can_read();

    // is length negative or greater than the remainder of the file
    arc::int64 remaining_length = get_size() - tell();
    if(length < 0 || length > remaining_length)
    {
        length = remaining_length;
    }

    // if we are the beginning of the file, skip the BOM if there is one.
    if(tell() == 0 && has_bom())
    {
        arc::int64 bom_size = static_cast<arc::int64>(get_bom_size());
        // are we not reading past the BOM?
        if(length < bom_size)
        {
            seek(length);
            data = "";
            return;
        }
        seek(bom_size);
        length -= bom_size;
    }

    // read from file
    std::size_t length_t = static_cast<std::size_t>(length);
    char* c_data = new char[length_t + 1];
    read(c_data, length);
    // ensure the data is null terminated
    c_data[length_t] = '\0';

    // do we need to convert the encoding
    switch(m_encoding)
    {
        case ENCODING_UTF16_LITTLE_ENDIAN:
        {
            data = arc::str::utf16_to_utf8(
                c_data,
                length_t,
                arc::data::ENDIAN_LITTLE
            );
            break;
        }
        case ENCODING_UTF16_BIG_ENDIAN:
        {
            data = arc::str::utf16_to_utf8(
                c_data,
                length_t,
                arc::data::ENDIAN_BIG
            );
            break;
        }
        default:
        {
            // TODO: optimised version of claim that takes length?
            // give the character data to the UTF8String
            data.claim(c_data);
            break;
        }
    }
}

std::size_t FileReader::read_line(char** data)
{
    check_can_read();

    // skip the BOM if we are at the start of the file.
    if(tell() == 0)
    {
        seek_to_data_start();
    }

    // get the newline checker to use
    NewlineChecker* newline_checker = get_newline_checker();

    // read characters into a vector
    std::vector<char> read_data;
    std::size_t data_size = 0;
    while(!m_stream->eof())
    {
        read_data.push_back('\0');
        m_stream->get(read_data[read_data.size() - 1]);
        data_size = read_data.size();
        // have we read the newline character?
        if(newline_checker->check(read_data))
        {
            data_size -= newline_checker->sequence_length;
            break;
        }
    }

    // allocate new data
    *data = new char[data_size + 1];
    // copy
    memcpy(*data, &read_data[0], data_size);
    // write null terminator
    (*data)[data_size] = '\0';

    return data_size;
}

void FileReader::read_line(arc::str::UTF8String& data)
{
    // get raw
    char* c_data;
    std::size_t length = read_line(&c_data);

    // set string data based on encoding
    switch(m_encoding)
    {
        case ENCODING_UTF16_LITTLE_ENDIAN:
        {
            data = arc::str::utf16_to_utf8(
                c_data,
                length,
                arc::data::ENDIAN_LITTLE
            );
            delete[] c_data;
            break;
        }
        case ENCODING_UTF16_BIG_ENDIAN:
        {
            data = arc::str::utf16_to_utf8(
                c_data,
                length,
                arc::data::ENDIAN_BIG
            );
            delete[] c_data;
            break;
        }
        default:
        {
            data.assign(c_data, length);
            break;
        }
    }
}

//------------------------------------------------------------------------------
//                            PRIVATE MEMBER FUNCTIONS
//------------------------------------------------------------------------------

NewlineChecker* FileReader::get_newline_checker()
{
    // does the new line checker need to be initialized?
    if(!m_newline_checker_valid)
    {
        // delete any data currently held by the checker
        if(m_newline_checker->newline_sequence)
        {
            delete[] m_newline_checker->newline_sequence;
        }

        // initialise based on encoding and file type
        switch(m_encoding)
        {
            case ENCODING_UTF16_LITTLE_ENDIAN:
            {
                if(m_newline == NEWLINE_WINDOWS)
                {
                    m_newline_checker->sequence_length  = 4;
                    m_newline_checker->newline_sequence = new char[4];
                    m_newline_checker->newline_sequence[0] = '\r';
                    m_newline_checker->newline_sequence[1] = '\0';
                    m_newline_checker->newline_sequence[2] = '\n';
                    m_newline_checker->newline_sequence[3] = '\0';
                }
                else
                {
                    m_newline_checker->sequence_length  = 2;
                    m_newline_checker->newline_sequence = new char[2];
                    m_newline_checker->newline_sequence[0] = '\n';
                    m_newline_checker->newline_sequence[1] = '\0';
                }
                break;
            }
            case ENCODING_UTF16_BIG_ENDIAN:
            {
                if(m_newline == NEWLINE_WINDOWS)
                {
                    m_newline_checker->sequence_length  = 4;
                    m_newline_checker->newline_sequence = new char[4];
                    m_newline_checker->newline_sequence[0] = '\0';
                    m_newline_checker->newline_sequence[1] = '\r';
                    m_newline_checker->newline_sequence[2] = '\0';
                    m_newline_checker->newline_sequence[3] = '\n';
                }
                else
                {
                    m_newline_checker->sequence_length  = 2;
                    m_newline_checker->newline_sequence = new char[2];
                    m_newline_checker->newline_sequence[0] = '\0';
                    m_newline_checker->newline_sequence[1] = '\n';
                }
                break;
            }
            default:
            {
                if(m_newline == NEWLINE_WINDOWS)
                {
                    m_newline_checker->sequence_length  = 2;
                    m_newline_checker->newline_sequence = new char[2];
                    m_newline_checker->newline_sequence[0] = '\r';
                    m_newline_checker->newline_sequence[1] = '\n';
                }
                else
                {
                    m_newline_checker->sequence_length  = 1;
                    m_newline_checker->newline_sequence = new char[1];
                    m_newline_checker->newline_sequence[0] = '\n';
                }
                break;
            }
        }
        m_newline_checker_valid = true;
    }
    // return the internal pointer
    return m_newline_checker.get();
}

void FileReader::check_can_read()
{
    if(!m_open)
    {
        throw arc::ex::StateError(
            "File read cannot be performed while the FileReader is closed.");
    }
    if(eof())
    {
        throw arc::ex::EOFError(
            "File read cannot be performed as the EOF marker has been reached."
        );
    }
}

} // namespace sys
} // namespace io
} // namespace arc
