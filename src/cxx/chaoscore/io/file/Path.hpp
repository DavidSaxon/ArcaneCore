/*!
 * \file
 * \author David Saxon
 */
#ifndef CHAOSCORE_IO_FILE_PATH_HPP_
#define CHAOSCORE_IO_FILE_PATH_HPP_

#include <ostream>

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
     * \brief Attempts to create a Path object from the given single string
     *        using the current operating system's path rules.
     *
     * \note This constructor method should be avoided where possible. Instead
     *       constructing paths using the << operator or join() function is
     *       recommended.
     *
     * On Unix systems this will split the given string into components using
     * the "/" symbol. Likewise on Windows systems the "\" symbol will be used.
     *
     */
    Path( const chaos::str::UTF8String& string_path );

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
     * UTF8String less than comparison on each component until a mismatch is
     * found.
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
     * // p now contains [ "path", "to", "file.txt" ]
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

    /*!
     * \brief Reverts this Path to be an empty path.
     *
     * Clears any current components this Path has.
     */
    void clear();

    /*!
     * \brief Removes the component from this Path at the given index.
     *
     * \throws chaos::ex::IndexOutOfBoundsError If the provided index is out of
     *                                          bounds of the number of
     *                                          components in this Path.
     *
     * \param index The index of the component to remove from this path.
     */
    void remove( size_t index );

    /*!
     * \brief Returns the chaos::str::UTF8String representation of this Path for
     *        the current operating system.
     *
     * Example usage:
     *
     * \code
     * chaos::io::file::Path p;
     * p << "path" << "to" << "file.txt";
     * chaos::str::UTF8String s = p.to_native();
     * // on Unix systems s will be "path/to/file.txt"
     * // on Windows systems s will be "path\to\file.txt"
     * \endcode
     */
    chaos::str::UTF8String to_native() const;

    /*!
     * \brief Returns the chaos::str::UTF8String representation of this Path for
     *        Unix based operating systems.
     *
     * Example usage:
     *
     * \code
     * chaos::io::file::Path p;
     * p << "path" << "to" << "file.txt";
     * chaos::str::UTF8String s = p.to_unix();
     * // s is "path/to/file.txt"
     * \endcode
     *
     */
    chaos::str::UTF8String to_unix() const;

    /*!
     * \brief Returns the chaos::str::UTF8String representation of this Path for
     *        Windows based operating systems.
     *
     * Example usage:
     *
     * \code
     * chaos::io::file::Path p;
     * p << "path" << "to" << "file.txt";
     * chaos::str::UTF8String s = p.to_windows();
     * // s is "path\to\file.txt"
     * \endcode
     *
     */
    chaos::str::UTF8String to_windows() const;

    // TODO: MOVE THESE OUT

    /*!
     * \brief Returns whether this Path exists.
     *
     * This function doesn't taken into account the type of the path, the path
     * can point to a directory, file, or symlink for this to evaluate true.
     */
    bool exists() const;

    /*!
     * \brief Returns whether this path is a valid file.
     *
     * This function will return false if the path exists but is not a file, or
     * if the path simply does not exist.
     */
    bool is_file() const;

    /*!
     * \brief Returns whether this path is a valid directory.
     *
     * This function will return false if the path exists but is not a
     * directory, or if the path simply does not exist.
     */
    bool is_directory() const;

    /*!
     * \brief Returns whether this path is a valid symbolic link.
     *
     * This function will return false if the path exists but is not a symbolic
     * link, or if the path simply does not exist.
     */
    bool is_symlink() const;

    //--------------------------------ACCESSORS---------------------------------

    /*!
     * \brief Returns the number of components in this path.
     *
     * Example usage:
     *
     * \code
     * chaos::io::file::Path p;
     * p << "path" << "to" << "file.txt";
     * p.get_length(); // returns: 3
     * \endcode
     */
    size_t get_length();

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
     * \brief Returns the file extension of the leaf component of this Path.
     *
     * Example usage:
     *
     * \code
     * chaos::io::file::Path p;
     * p << "path" << "to" << "file.txt";
     * chaos::str::UTF8String ext = p.get_extension();
     * // ext is "txt"
     * \endcode
     *
     */
    chaos::str::UTF8String get_extension() const;

 private:

    //--------------------------------------------------------------------------
    //                             PRIVATE ATTRIBUTES
    //--------------------------------------------------------------------------

    /*!
     * \brief List containing each individual component of this path.
     */
    std::vector< chaos::str::UTF8String > m_components;
};

//------------------------------------------------------------------------------
//                               EXTERNAL OPERATORS
//------------------------------------------------------------------------------

chaos::str::UTF8String& operator<<( chaos::str::UTF8String& s, const Path& p );

std::ostream& operator<<( std::ostream& stream, const Path& p );

} // namespace file
} // namespace io
} // namespace chaos

#endif
