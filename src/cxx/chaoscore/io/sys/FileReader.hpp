/*!
 * \file
 * \author David Saxon
 */
#ifndef CHAOSCORE_IO_SYS_FILEREADER_HPP_
#define CHAOSCORE_IO_SYS_FILEREADER_HPP_

#include "chaoscore/io/sys/FileHandle.hpp"

class ifstream;

namespace chaos
{
namespace io
{
namespace sys
{

/*!
 * \brief TODO:
 *
 * TODO:
 */
class FileReader : public chaos::io::sys::FileHandle
{
private:

    CHAOS_DISALLOW_COPY_AND_ASSIGN(FileReader);

public:

    //--------------------------------------------------------------------------
    //                                 ENUMERATOR
    //--------------------------------------------------------------------------

    /*!
     * \brief Flags that can be used to describe how the file handle should be
     *        opened.
     *
     * These flags can be combined together using the logical OR operator.
     */
    enum Flag
    {
        /// No flags specified
        FLAG_NONE   = 0,
        /// Operations are performed in binary mode rather than text mode.
        FLAG_BINARY = 1U << 0
    };

    //--------------------------------------------------------------------------
    //                                CONSTRUCTORS
    //--------------------------------------------------------------------------

    /*!
     * \brief Default constructor.
     *
     * Creates a new unopened FileReader with no initial path set.
     *
     * \param flags Flags used to describe how the FileReader should be opened.
     *              See chaos::io::sys::FileReader::Flag for more details.
     * \param encoding The encoding that will be used to read text from the
     *                 file.
     */
    FileReader(
            chaos::uint32 flags = FileReader::FLAG_NONE,
            chaos::str::Encoding encoding = chaos::str::ENCODING_UTF8);

    /*!
     * \brief Open constructor.
     *
     * Creates a new FileReader and attempts to open it to the given path.
     *
     * \throws chaos::io::sys::InvalidPathError If the path cannot be opened.
     *
     * \param path Path to open this FileReader to.
     * \param flags Flags used to describe how the FileReader should be opened.
     *              See chaos::io::sys::FileReader::Flag for more details.
     * \param encoding The encoding that will be used to read text from the
     *                 file.
     */
    FileReader(
            const chaos::io::sys::Path& path,
            chaos::uint32 flags = FileReader::FLAG_NONE,
            chaos::str::Encoding encoding = chaos::str::ENCODING_UTF8);

    /*!
     * \brief Move constructor.
     *
     * \param other The FileReader to move resources from.
     */
    FileReader(FileReader&& other);

    //--------------------------------------------------------------------------
    //                                 DESTRUCTOR
    //--------------------------------------------------------------------------

    ~FileReader();

    //--------------------------------------------------------------------------
    //                                 OPERATORS
    //--------------------------------------------------------------------------

    /*!
     * \brief chaos::str::UTF8String stream operator.
     *
     * Reads a line from the file into the given chaos::str::UTF8String.
     *
     * \throws chaos::ex::StateError If this file handle is not open.
     * \throws chaos::io::sys::EOFError If the position indicator is at the end
     *                                  of the file.
     */
    // FileReader& operator>>(chaos::str::UTF8String& text);

    //--------------------------------------------------------------------------
    //                          PUBLIC MEMBER FUNCTIONS
    //--------------------------------------------------------------------------

    /*!
     * \brief Opens the reader to the internal path.
     *
     *
     * \throws chaos::ex::StateError If this FileReader is already open.
     * \throws chaos::io::sys::InvalidPathError If the path cannot be opened.
     */
    virtual void open();

    /*!
     * \brief Sets the path and opens the reader to it.
     *
     * This function is synonymous to:
     *
     * \code
     * my_file_reader.set_path(path);
     * my_file_reader.open();
     * \endcode
     *
     * \throws chaos::ex::StateError If this FileReader is already open.
     *
     * \throws chaos::io::sys::InvalidPathError If the path cannot be opened.
     */
    virtual void open(const chaos::io::sys::Path& path);

    /*!
     * \brief Closes this reader.
     *
     * Once the file has been closed, read operations cannot be performed until
     * the reader is reopened.
     *
     * This function does not need to be explicitly called. When this object is
     * destroyed it will ensure that the file handle is closed.
     *
     * \throws chaos::ex::StateError If this file handle is not open.
     */
    virtual void close();

    /*!
     * \brief Returns the size of the file in bytes.
     *
     * \throws chaos::ex::StateError If this FileReader is not open.
     */
    chaos::int64 get_size() const;

    /*!
     * \brief Returns the index of the byte the file position indicator is
     *        currently at.
     *
     * \throws chaos::ex::StateError If this FileReader is not open.
     */
    chaos::int64 tell() const;

    /*!
     * \brief Sets the file position indicator to the given byte index.
     *
     * \throws chaos::ex::StateError If this FileReader is not open.
     * \throws chaos::ex::IndexOutOfBoundsError If the given byte index is
     *                                          greater than the number of bytes
     *                                          in the file.
     */
    void seek(chaos::int64 index);

    /*!
     * \brief Returns whether the file indicator position is at the End of File
     *        indicator.
     *
     * \throws chaos::ex::StateError If this FileReader is not open.
     */
    bool eof() const;

    // TODO: c string variations of the read functions

    /*!
     * \brief Reads byte data from the file into the given character array.
     *
     * Once the read has taken place the file position indicator will be set to
     * the next position beyond the read data.
     *
     * \param data character array the data will be read into.
     * \param The number of bytes from the file position indicator to read from
     *        the file. This should not extend past the end of the file.
     *
     * \throws chaos::ex::StateError If this FileReader is not open.
     * \throws chaos::io::sys::EOFError If the length from the file position
     *                                  indicator extends past the end of the
     *                                  file.
     */
    void read(char* data, chaos::int64 length);

    /*!
     * \brief Reads a line from the file into the given chaos::str::UTF8String.
     *
     * Once the read has taken place the file position indicator will be set to
     * the position of the next line.
     *
     * \throws chaos::ex::StateError If this FileReader is not open.
     * \throws chaos::io::sys::EOFError If the position indicator is at the end
     *                                  of the file.
     */
    void read_line(chaos::str::UTF8String& text);

private:

    //--------------------------------------------------------------------------
    //                             PRIVATE ATTRIBUTES
    //--------------------------------------------------------------------------

    /*!
     * \brief The input stream being used to read from disk.
     */
    std::ifstream* m_stream;

    /*!
     * \brief The size of the file in bytes.
     */
    chaos::int64 m_size;

};

} // namespace sys
} // namespace io
} // namespace chaos

#endif
