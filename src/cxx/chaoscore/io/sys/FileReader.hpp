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
 * \brief Used for reading the contents of a file from disk.
 *
 * TODO: usage
 */
class FileReader : public chaos::io::sys::FileHandle2
{
private:

    CHAOS_DISALLOW_COPY_AND_ASSIGN(FileReader);

public:

    //--------------------------------------------------------------------------
    //                                CONSTRUCTORS
    //--------------------------------------------------------------------------

    /*!
     * \brief Default constructor.
     *
     * Creates a new unopened FileReader with no file path yet defined.
     *
     * \param encoding Defines the encoding of the contents of the file to read.
     *                 If chaos::io::sys::FileHandle2::ENCODING_DETECT is used
     *                 the FileReader will attempt to detect the encoding used
     *                 in the file at the time of opening. If the encoding
     *                 cannot be detected
     *                 chaos::io::sys::FileHandle2::ENCODING_RAW will be used.
     *                 The detected encoding can be queried using get_encoding()
     *                 once the file has been opened.
     * \param newline The newline symbol used in the file to read.
     *                See set_newline().
     */
    FileReader(
            Encoding encoding = ENCODING_DETECT,
            Newline newline   = NEWLINE_UNIX);

    /*!
     * \brief Path constructor.
     *
     * Creates a new FileReader opened to the given path.
     *
     * \param path The path to the file to read from.
     * \param encoding Defines the encoding of the contents of the file to read.
     *                 If chaos::io::sys::FileHandle2::ENCODING_DETECT is used
     *                 the FileReader will attempt to detect the encoding used
     *                 in the file at the time of opening. If the encoding
     *                 cannot be detected
     *                 chaos::io::sys::FileHandle2::ENCODING_RAW will be used.
     *                 The detected encoding can be queried using get_encoding()
     *                 once the file has been opened.
     * \param newline The newline symbol used in the file to read.
     *                See set_newline().
     *
     * \throws chaos::io::sys::InvalidPathError If the path cannot be opened.
     */
    FileReader(
            const chaos::io::sys::Path& path,
            Encoding encoding = ENCODING_DETECT,
            Newline newline   = NEWLINE_UNIX);

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

    // TODO: << char*

    // TODO: << chaos::str::UTF8String

    //--------------------------------------------------------------------------
    //                          PUBLIC MEMBER FUNCTIONS
    //--------------------------------------------------------------------------

    /*!
     * \brief Opens this FileReader to the internal path.
     *
     * \throws chaos::ex::StateError If this FileReader is already open.
     * \throws chaos::io::sys::InvalidPathError If the path cannot be opened.
     */
    virtual void open();

    // override to avoid C++ function hiding
    virtual void open(const chaos::io::sys::Path& path);

    /*!
     * \brief Closes this FileReader.
     */
    virtual void close();

    /*!
     * \brief Returns the size of the file being read in bytes.
     *
     * \throws chaos::ex::StateError If the FileReader is not open.
     */
    virtual chaos::int64 get_size() const;

    /*!
     * \brief Returns the index of the byte the file position indicator is
     *        currently at.
     *
     * \throws chaos::ex::StateError If the FileReader is not open.
     */
    virtual chaos::int64 tell() const;

    /*!
     * \brief Sets the file position indicator to the given byte index.
     *
     * \throws chaos::ex::StateError If the FileReader is not open.
     * \throws chaos::ex::IndexOutOfBoundsError If the given byte index is
     *                                          greater than the number of bytes
     *                                          in the file or is less than 0.
     */
    virtual void seek(chaos::int64 index);

    /*!
     * \brief Returns whether file position indicated is at the End of File.
     *
     * \throws chaos::ex::StateError If this FileReader is not open.
     */
    bool eof() const;

    /*!
     * \brief Returns whether this file starts with a Unicode Byte Order Marker.
     *
     * \note This function will only return ```true``` if the file starts with
     *       a BOM that matches the file's encoding, see get_encoding().
     *
     * \warning This function will cause a read into the file. The file position
     *          indicator will be moved from its current position to the
     *          beginning of the file to check for the BOM, then moved back to
     *          its initial position before this function was called.
     *
     * \throws chaos::ex::StateError If this FileReader is not open.
     */
    bool has_bom();

    /*!
     * \brief Reads a block of data from the file and moves the position
     *        indicator to the index beyond the last read character in the file.
     *
     * This function is a pure copy of data, the copied data will include the
     * Unicode BOM (if the file has one).
     *
     * TODO: move past BOM.
     *
     * continue (not null terminator)
     *
     * TODO: length greater than size?
     */
    void read(char* data, chaos::int64 length);

    // TODO: read line (and only do with UTF8String?)

    // TODO: UTF8String

// private:

    //--------------------------------------------------------------------------
    //                             PRIVATE ATTRIBUTES
    //--------------------------------------------------------------------------

    /*!
     * \brief The input stream used to read the file.
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
