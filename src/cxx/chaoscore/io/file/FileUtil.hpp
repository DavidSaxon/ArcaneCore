/*!
 * \file
 * \brief Utility functions relating to the file system.
 * \author David Saxon
 */
#ifndef CHAOSCORE_IO_FILE_FILEUTIL_HPP_
#define CHAOSCORE_IO_FILE_FILEUTIL_HPP_

#include "chaoscore/base/string/UTF8String.hpp"

namespace chaos
{
namespace io
{
/*!
 * \brief FileSystem related classes and operations.
 */
namespace file
{

//------------------------------------------------------------------------------
//                                   FUNCTIONS
//------------------------------------------------------------------------------

/*!
 * \brief Checks whether the given path exists on disk.
 *
 * This check does not include the type of the path, i.e. it can be a directory,
 * file, symbolic link, etc.
 *
 * \param path The path to check for existence.
 * \return Returns True if the path exists, false otherwise.
 */
bool exists( const chaos::str::UTF8String& path );

/*!
 * \brief Returns whether the given path is a file.
 *
 * \note If the path does not exist this operation will return false.
 */
bool is_file( const chaos::str::UTF8String& path );

/*!
 * \brief Returns whether the given path is a directory.
 *
 * \note If the path does not exist this operation will return false.
 */
bool is_directory( const chaos::str::UTF8String& path );

/*!
 * \brief Attempts to create the directory with the given path.
 */
void create_directory( const chaos::str::UTF8String& path );

/*!
 * \brief Attempts to directories to the given path if they don't exist.
 *
 * This operation will ensure that the given path is available for writing. For
 * example, providing the path:
 * \code
 * "example/path/to/file.txt"
 * \endcode
 * Will attempt ensure the this directory structure exists:
 * \code
 * "example/path/to/
 * \endcode
 * If the path ends with a '/' (or '\' only on Windows) the entire path will be
 * validated. For example, providing the path:
 * \code
 * "example/path/to/directory/"
 * \endcode
 * Will attempt to ensure that the entire path exists.
 */
void validate_path( const chaos::str::UTF8String& path );

} // namespace file
} // namespace io
} // namespace chaos

#endif
