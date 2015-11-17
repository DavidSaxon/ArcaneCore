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

    /*!
     * \brief Component constructor.
     *
     * Creates a new Path from the given std::vector of components.
     *
     * For example the native Linux path:
     *
     * \code
     * path/to/file.txt
     * \endcode
     *
     * Would be passed to this constructor like so:
     *
     * \code
     * std::vector< chaos::str::UTF8String > components;
     * components.push_back( "path" );
     * components.push_back( "to" );
     * components.push_back( "file.txt" );
     *
     * chaos::io::file::Path p( components );
     * \endcode
     *
     */
    Path( const std::vector< chaos::str::UTF8String >& components );

    /*!
     * \brief Copy constructor.
     *
     * Creates a new Path by copying the contents of the provided Path.
     */
    Path( const Path& other );

    //--------------------------------------------------------------------------
    //                          PUBLIC MEMBER FUNCTIONS
    //--------------------------------------------------------------------------

    //--------------------------------ACCESSORS---------------------------------

    /*!
     * \brief Returns the individual components which make up this path.
     *
     * For example the native Linux path:
     *
     * \code
     * path/to/file.txt
     * \endcode
     *
     * Stored correctly in a Path object:
     *
     * \code
     * chaos::io::file::Path path;
     * path << "path" << "to" << "file.txt";
     * \endcode
     *
     * Would contain the components:
     *
     * \code
     * [ "path", "to", "file.txt" ]
     * \endcode
     */
    const std::vector< chaos::str::UTF8String >& get_components() const;

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


    // const chaos::str::UTF8String& to_string() const;

 private:

    //--------------------------------------------------------------------------
    //                             PRIVATE ATTRIBUTES
    //--------------------------------------------------------------------------

    /*!
     * \brief List containing each individual component of this path.
     */
    std::vector< chaos::str::UTF8String > m_components;
};

} // namespace file
} // namespace io
} // namespace chaos

#endif
