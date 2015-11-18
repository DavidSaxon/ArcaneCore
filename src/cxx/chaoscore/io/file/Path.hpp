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
    //                                 OPERATORS
    //--------------------------------------------------------------------------

    /*!
     * \brief Assignment operator.
     *
     * Assigns the internal data of this Path to be a copy of the data from
     * the given Path.
     *
     * \param other Path to copy from.
     * \return Reference to this Path after the assignment has taken place.
     */
    const Path& operator=( const Path& other );

    /*!
     * \brief Equality operator.
     *
     * Compares whether this Path and the other given Path are considered equal.
     *
     * \param other Path to compare this against.
     * \return Whether the paths are equal.
     */
    bool operator==( const Path& other ) const;

    /*!
     * \brief Inequality operator.
     *
     * Compares whether this Path and the other given Path are considered not
     * equal.
     *
     * \param other Path to compare this against.
     * \return Whether the paths are equal.
     */
    bool operator!=( const Path& other ) const;

    /*!
     * \brief Less than operator.
     *
     * Compares whether this Path is considered less than the other given Path.
     *
     * \note This operator is primarily supplied so Path objects can be stored
     *       in a std::map.
     *
     * Less than is defined by the number of components in a Path, and if two
     * paths have the same number of components then this resorts to a
     * UTF8String less than comparison of the Unix paths.
     *
     * \param other Path to compare this against.
     * \return Whether this Path is less than the other.
     */
    bool operator<( const Path& other ) const;

    /*!
     * \brief Returns a reference to the component of this Path at the given
     *        index.
     *
     * \throws chaos::ex::IndexOutOfBoundsError If the provided index is out of
     *                                          bounds of the number of
     *                                          components in this Path.
     */
    chaos::str::UTF8String& operator[]( size_t index );

    /*!
     * \brief Returns a const reference to the component of this Path at the
     *        given index.
     *
     * \throws chaos::ex::IndexOutOfBoundsError If the provided index is out of
     *                                          bounds of the number of
     *                                          components in this Path.
     */
    const chaos::str::UTF8String& operator[]( size_t index ) const;

    /*!
     * \brief Addition operator.
     *
     * Creates a new Path by extending the components of this Path with the
     * components of the other given Path.
     *
     * Example usage:
     *
     * \code
     * chaos::io::file::Path p1;
     * p1 << "two" << "part";
     *
     * chaos::io::file::Path p2;
     * p2 << "path" << "to" << "file.txt";
     *
     * chaos::io::file::Path p3 = p1 + p2;
     * // p3 contains [ "two", "part", "path", "to", "file.txt" ]
     * \endcode
     *
     */
    Path operator+( const Path& other ) const;

    /*!
     * \brief Compound addition operator.
     *
     * Extends this Path with the components of the other given Path.
     *
     * Example usage:
     *
     * \code
     * chaos::io::file::Path p1;
     * p1 << "two" << "part";
     *
     * chaos::io::file::Path p2;
     * p2 << "path" << "to" << "file.txt";
     *
     * p1 += p2;
     * // p1 contains [ "two", "part", "path", "to", "file.txt" ]
     * \endcode
     *
     */
    const Path& operator+=( const Path& other );

    /*!
     * \brief Join operator.
     *
     * Appends a new component to end of this path. This is the same as using
     * the join() function.
     *
     * Example usage:
     *
     * \code
     * chaos::io::file::Path p;
     * p << "path" << "to" << "file.txt";
     * // p now contains [ "path", "to", "file" ]
     * \endcode
     *
     * \param component String to be appended to the end of this Path as a
     *                  component.
     * \return Reference to this Path after the join has taken place.
     */
    Path& operator<<( const chaos::str::UTF8String& component );

    //--------------------------------------------------------------------------
    //                          PUBLIC MEMBER FUNCTIONS
    //--------------------------------------------------------------------------

    /*!
     * \brief Appends a new component to the end of this Path.
     *
     * Since this returns a non-const reference to this Path, these functions
     * can be chained.
     *
     * Example usage:
     *
     * \code
     * chaos::io::file::Path p;
     * p.join( "path" ).join( "to" ).join( "file.txt" );
     * // p now contains [ "path", "to", "file" ]
     * \endcode
     *
     * \param component chaos::str::UTF8String to be appended to the end of this
     *                  Path as a component.
     * \return Reference to this Path after the join has taken place.
     */
    Path& join( const chaos::str::UTF8String& component );

    /*!
     * \brief Inserts the component at the given index in this Path.
     *
     * If the index is less than the length of the string, the component
     * currently at the index and all following components will be shuffled
     * along one position.
     *
     * If the index is equal to the current number of components in this Path,
     * this function is the same as calling
     * join().
     *
     * If the index is greater than the number of components in this Path, an
     * exception will be thrown.
     *
     * Example usage:
     *
     * \code
     * chaos::io::file::Path p;
     * p << "path" << "file.txt";
     * p.insert( 1, "to" );
     * // p now contains ["path", "to", "file.txt"]
     * \endcode
     *
     * \throws chaos::ex::IndexOutOfBoundsError If the provided index is greater
     *                                          than the number of components
     *                                          currently in this Path.
     *
     * \param index Position to insert the new component at.
     * \param component chaos::str::UTF8String representing the new component to
     *                  be inserted.
     */
    void insert( size_t index, const chaos::str::UTF8String& component );

    // TODO: clear

    // TODO: remove

    // TODO: native

    // TODO: unix

    // TODO: windows

    // TODO: exists

    // TODO: is file

    // TODO: is directory

    // TODO: is symlink

    // TODO: how to deal with shortcuts

    // TODO: validate path

    // TODO: get extension

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

// TODO: STREAM OUTPUT

} // namespace file
} // namespace io
} // namespace chaos

#endif
