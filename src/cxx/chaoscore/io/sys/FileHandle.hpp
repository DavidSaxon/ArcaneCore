/*!
 * \file
 * \author David Saxon
 */
#ifndef CHAOSCORE_IO_SYS_FILEHANDLE_HPP_
#define CHAOSCORE_IO_SYS_FILEHANDLE_HPP_

#include "chaoscore/base/Types.hpp"
#include "chaoscore/io/sys/Path.hpp"

namespace chaos
{
namespace io
{
namespace sys
{

/*!
 * \brief Abstract base class that represents an object used for providing
 *        access to a file.
 */
class FileHandle2
{
private:

    CHAOS_DISALLOW_COPY_AND_ASSIGN(FileHandle2);

public:

    //--------------------------------------------------------------------------
    //                                 ENUMERATOR
    //--------------------------------------------------------------------------

    /*!
     * \brief The possible encodings for FileHandles.
     */
    enum Encoding
    {
        /// The FileHandle will attempt to detect the encoding of the file.
        ENCODING_DETECT = 0,
        /// The file is pure single byte data, this represents binary or ASCII
        /// files.
        ENCODING_RAW,
        /// The file is encoded in UTF-8 Unicode.
        ENCODING_UTF8,
        /// The file is encoded in little endian UTF-16 Unicode.
        ENCODING_UTF16_LITTLE_ENDIAN,
        /// The file is encoded in big endian UTF-16 Unicode.
        ENCODING_UTF16_BIG_ENDIAN
    };

    /*!
     * \brief The possible newline symbols for FileHandles to use.
     */
    enum Newline
    {
        /// Line endings will be detected based on the current operating system.
        NEWLINE_DETECT = 0,
        /// Unix style newlines will be used: ```'\n'```.
        NEWLINE_UNIX,
        /// Windows style newlines will be used: ```'\r\n'```.
        NEWLINE_WINDOWS
    };

    //--------------------------------------------------------------------------
    //                              MOVE CONSTRUCTOR
    //--------------------------------------------------------------------------

    /*!
     * \brief Move constructor.
     *
     * \param other The FileHandle2 to move resources from.
     */
    FileHandle2(FileHandle2&& other);

    //--------------------------------------------------------------------------
    //                                 DESTRUCTOR
    //--------------------------------------------------------------------------

    virtual ~FileHandle2()
    {
    }

    //--------------------------------------------------------------------------
    //                          PUBLIC MEMBER FUNCTIONS
    //--------------------------------------------------------------------------

    /*!
     * \brief Returns whether the FileHandle2 is currently open or not.
     */
    bool is_open() const;

    /*!
     * \brief Returns the path being used by this FileHandle.
     */
    const chaos::io::sys::Path& get_path() const;

    /*!
     * \brief Returns the encoding being used by this FileHandle.
     */
    Encoding get_encoding() const;

    /*!
     * \brief Returns the newline symbol being used by this FileHandle.
     */
    Newline get_newline() const;

    /*!
     * \brief Sets the path to be used by this FileHandle.
     *
     * \note The path can only be set if this FileHandle is not currently open.
     *
     * \throws chaos::ex::StateError If this FileHandle is open.
     */
    void set_path(const chaos::io::sys::Path& path);

    /*!
     * \brief Sets the encoding to be used by this FileHandle.
     *
     * \note The encoding can only be set if this FileHandle is not currently
     *       open.
     *
     * \throws chaos::ex::StateError If this FileHandle is open.
     */
    void set_encoding(Encoding encoding);

    /*!
     * \brief Sets the newline symbol to be used by this FileHandle.
     *
     * \note The newline symbol can only be set if this FileHandle is not
     *       currently open.
     *
     * \throws chaos::ex::StateError If this FileHandle is open.
     */
    void set_newline(Newline newline);

    /*!
     * \brief Opens the FileHandle to the internal path.
     *
     * \throws chaos::ex::StateError If this FileHandle is already open.
     * \throws chaos::io::sys::InvalidPathError If the path cannot be opened.
     */
    virtual void open() = 0;

    /*!
     * \brief Sets the path and opens the FileHandle to the path.
     *
     * This function is shorthand for:
     *
     * \code
     * my_file_handle.set_path(my_path);
     * my_file_handle.open();
     * \endcode
     *
     * \param path The path to the file to use.
     *
     * \throws chaos::ex::StateError If this FileHandle is already open.
     * \throws chaos::io::sys::InvalidPathError If the path cannot be opened.
     */
    virtual void open(const chaos::io::sys::Path& path);

    /*!
     * \brief Closes this FileHandle.
     */
    virtual void close() = 0;

    /*!
     * \brief Returns the size of the file in bytes.
     *
     * \throws chaos::ex::StateError If the FileHandle is not open.
     */
    virtual chaos::int64 get_size() const = 0;

    /*!
     * \brief Returns the index of the byte the file position indicator is
     *        currently at.
     *
     * \throws chaos::ex::StateError If the FileHandle is not open.
     */
    virtual chaos::int64 tell() const = 0;

    /*!
     * \brief Sets the file position indicator to the given byte index.
     *
     * \throws chaos::ex::StateError If the FileHandle is not open.
     * \throws chaos::ex::IndexOutOfBoundsError If the given byte index is
     *                                          greater than the number of bytes
     *                                          in the file or is less than 0.
     */
    virtual void seek(chaos::int64 index) = 0;

protected:

    //--------------------------------------------------------------------------
    //                            PROTECTED ATTRIBUTES
    //--------------------------------------------------------------------------

    /*!
     * \brief Whether this FileHandle is open or not.
     */
    bool m_open;

    /*!
     * \brief The path this FileHandle is using.
     */
    chaos::io::sys::Path m_path;
    /*!
     * \brief The encoding this FileHandle is using.
     */
    Encoding m_encoding;
    /*!
     * \brief The newline symbol this FileHandle is using.
     */
    Newline m_newline;

    //--------------------------------------------------------------------------
    //                           PROTECTED CONSTRUCTORS
    //--------------------------------------------------------------------------

    /*!
     * \brief Default super constructor.
     *
     * Creates a new unopened FileHandle.
     *
     * \param encoding The encoding that will be used for the contents of the
     *                 file.
     * \param newline The newline symbol which the FileHandle will use.
     */
    FileHandle2(
            Encoding encoding = ENCODING_DETECT,
            Newline newline   = NEWLINE_UNIX);

    /*!
     * \brief Path super constructor.
     *
     * Creates a new FileHandle with the given path and opens this FileHandle to
     * it.
     *
     * \note Derived must call the open member function, as this base
     *       constructor cannot and should not call a pure virtual member
     *       function.
     *
     * \param path The path to the file to use.
     * \param encoding The encoding that will be used for the contents of the
     *                 file.
     * \param newline The newline symbol which the FileHandle will use.
     */
    FileHandle2(
            const chaos::io::sys::Path& path,
            Encoding encoding = ENCODING_DETECT,
            Newline newline   = NEWLINE_UNIX);
};

/*!
 * \brief Abstract base class used for representing an object that is writing or
 *        reading to/from a file.
 *
 * This object defines the specifications for chaos::io::sys::FileReader and
 * chaos::io::sys::FileWriter.
 */
class FileHandle
{
private:

    CHAOS_DISALLOW_COPY_AND_ASSIGN(FileHandle);

public:

    //--------------------------------------------------------------------------
    //                              MOVE CONSTRUCTOR
    //--------------------------------------------------------------------------

    /*!
     * \brief Move constructor.
     *
     * \param other The FileHandle to move resources from.
     */
    FileHandle(FileHandle&& other);

    //--------------------------------------------------------------------------
    //                                 DESTRUCTOR
    //--------------------------------------------------------------------------

    virtual ~FileHandle()
    {
    }

    //--------------------------------------------------------------------------
    //                          PUBLIC MEMBER FUNCTIONS
    //--------------------------------------------------------------------------

    /*!
     * brief Returns whether the file handle is currently open or not.
     */
    bool is_open() const;

    /*!
     * \brief Opens the file handle to the internal path.
     *
     * \note This function is to be implemented by derived classes.
     *
     * \throws chaos::ex::StateError If this file handle is already open.
     *
     * \throws chaos::io::sys::InvalidPathError If the path cannot be opened
     */
    virtual void open() = 0;

    /*!
     * \brief Sets the path and opens this handle to it.
     *
     * This function is short hand for:
     *
     * \code
     * my_file_handle.set_path(path);
     * my_file_handle.open();
     * \endcode
     *
     * \throws chaos::ex::StateError If this file handle is already open.
     *
     ** \throws chaos::io::sys::InvalidPathError If the path cannot be opened
     */
    void open(const chaos::io::sys::Path& path);

    /*!
     * \brief Closes this file handle.
     *
     * \note This function is to be implemented by derived classes.
     */
    virtual void close() = 0;

    /*!
     * \brief Returns the path being used by this file handle.
     */
    const chaos::io::sys::Path& get_path() const;

    /*!
     * \brief Sets the path to be used by this file handle.
     *
     * The path may only be set if the file handle is not currently open.
     *
     * \throws chaos::ex::StateError If this file handle is open.
     */
    void set_path(const chaos::io::sys::Path& path);

    /*!
     * \brief Returns the descriptor flags of the this file handle.
     */
    chaos::uint32 get_flags() const;

    /*!
     * \brief Sets the descriptor flags to be used by this file handle.
     *
     * Flags can only be set if the file handle is not currently open.
     *
     * \throws chaos::ex::StateError If this file handle is open.
     */
    void set_flags(chaos::uint32 flags);

    /*!
     * \brief Returns the string encoding being used by the file handle.
     */
    chaos::str::Encoding get_encoding() const;

    /*!
     * \brief Sets the string encoding to be used by the file handle.
     *
     * The encoding can only be set if the file handle is not currently open.
     *
     * \throws chaos::ex::StateError If this file handle is open.
     */
    void set_encoding(chaos::str::Encoding encoding);


protected:

    //--------------------------------------------------------------------------
    //                            PROTECTED ATTRIBUTES
    //--------------------------------------------------------------------------

    /*!
     * \brief The file path this handle is currently using.
     */
    chaos::io::sys::Path m_path;
    /*!
     * \brief Descriptor flags of the file handle.
     */
    chaos::uint32 m_flags;
    /*!
     * \brief Encoding of the file handle.
     */
    chaos::str::Encoding m_encoding;

    /*!
     * \brief Whether the file handle is currently open or not.
     */
    bool m_open;

    //--------------------------------------------------------------------------
    //                           PROTECTED CONSTRUCTORS
    //--------------------------------------------------------------------------

    /*!
     * \brief Default super constructor.
     *
     * Super constructor used to create a new unopened file handle.
     *
     * \param flags Flags used to describe how the file handle should be opened.
     * \param encoding The encoding of the file handle.
     */
    FileHandle(
            chaos::uint32 flags = 0U,
            chaos::str::Encoding encoding = chaos::str::ENCODING_UTF8);

    /*!
     * \brief Path super constructor.
     *
     * This does not open the File Handle. But the derived constructors for
     * chaos::io::sys::FileReader and chaos::io::sys::FileWriter will open the
     * file handle.
     *
     * \param path Path to the file to open.
     * \param flags Flags used to describe how the file handle should be opened.
     * \param encoding The encoding of the file handle.
     */
    FileHandle(
            const chaos::io::sys::Path& path,
            chaos::uint32 flags = 0U,
            chaos::str::Encoding encoding = chaos::str::ENCODING_UTF8);
};

} // namespace sys
} // namespace io
} // namespace chaos

#endif
