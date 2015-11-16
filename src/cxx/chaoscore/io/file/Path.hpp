/*!
 * \file
 * \author David Saxon
 */
#ifndef CHAOSCORE_IO_FILE_PATH_HPP_
#define CHAOSCORE_IO_FILE_PATH_HPP_

#include "chaoscore/base/string/UTF8String.hpp"

namespace chaos
{
namespace io
{
namespace file
{

/*!
 * \brief Represents a filesystem path.
 *
 * The path this represents does not necessarily exists, nor does it have to be
 * valid for the current operating system.
 *
 * However this object is intended to provided platform independent methods for
 * dealing with file system paths.
 *
 * \par Example Usage
 *
 * TODO:
 */
class Path
{
public:

    //--------------------------------------------------------------------------
    //                                CONSTRUCTORS
    //--------------------------------------------------------------------------

    /*!
     * \brief  Default constructor.
     *
     * Creates a new empty Path.
     */
     Path();

     //-------------------------------------------------------------------------
     //                          PUBLIC MEMBER FUNCTIONS
     //-------------------------------------------------------------------------

    /*!
     * \brief Returns the UTF8String representation of this path for the
     *        current operating system.
     *
     * For example the path returned on Unix platforms will use a `/` separator:
     *
     * \code
     * path/to/file.txt
     * \endcode
     *
     * While the path returned on Windows platforms will use a `\` separator:
     *
     * \code
     * path\to\file.txt
     * \endcode
     */
    const chaos::str::UTF8String& to_string() const;

    /*!
     * \brief Returns a C style string represntation of this path for the
     *        current operating system.
     *
     * \warning The returned data should not be deleted as it is a direct
     *          pointer to the internal data of this object.
     */
    const char* to_cstring() const;


 private:

    //--------------------------------------------------------------------------
    //                             PRIVATE ATTRIBUTES
    //--------------------------------------------------------------------------

    /*!
     * \brief String containing the contents of the path.
     */
    chaos::str::UTF8String m_contents;
};

} // namespace file
} // namespace io
} // namespace chaos

#endif
