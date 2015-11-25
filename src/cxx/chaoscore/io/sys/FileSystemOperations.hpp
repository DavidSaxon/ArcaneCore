/*!
 * \file
 * \brief Operations relating to the file system.
 * \author David Saxon
 */
#ifndef CHAOSCORE_IO_SYS_FILESYSTEMOPERATIONS
#define CHAOSCORE_IO_SYS_FILESYSTEMOPERATIONS

#include "chaoscore/io/sys/Path.hpp"

namespace chaos
{
namespace io
{
namespace sys
{

/*!
 * \brief Checks whether the given path exists on the file system.
 *
 * This operation does not concern with the type of the path, this will return
 * true if the path is a directory, file, symbolic link, or hard link.
 *
 * \param path The path to check for existence.
 * \return Returns True if the path exists, false otherwise.
 */
bool exists( const chaos::io::sys::Path& path );

/*!
 * \brief Returns whether the given path is a regular file.
 *
 * \note If the path does not exist this operation will return false.
 */
bool is_file( const chaos::io::sys::Path& path );

/*!
 * \brief Returns whether the given path is a directory.
 *
 * \note If the path does not exist this operation will return false.
 */
bool is_directory( const chaos::io::sys::Path& path );

/*!
 * \brief Returns whether the given path is a symbolic link.
 *
 * \note If the path does not exist this operation will return false.
 */
bool is_symbolic_link( const chaos::io::sys::Path& path );

/*!
 * \brief Attempts to create the directory at the given path.
 *
 * \throws chaos::io::sys::AmbiguousPathError If the path already exists on the
 *                                            file system but is not a directory
 *
 * \throws chaos::io::sys::CreateDirectoryError If directory creation was
 *                                              attempted but failed.
 *
 * \return True is a new directory was created, false if the directory already
 *         exists.
 */
bool create_directory( const chaos::io::sys::Path& path );

/*!
 * \brief Attempts to ensure all directories in the provided path exist and are
 *        available for writing.
 *
 * If any directories in this path do not exist this operation will attempt to
 * create them. If the given path cannot be validated this will fail with an
 * exception.
 *
 * Example usage:
 *
 * \code
 * chaos::io::sys::Path p;
 * p << "example" << "path" << "to" << "directory";
 * chaos::io::sys::validate_path( p );
 * // this will attempt to ensure example/path/to/directory exists.
 * \endcode
 *
 * \throws chaos::io::sys::AmbiguousPathError If one of the directories in the
 *                                           path already exists but is not a
 *                                           directory.
 * \throws chaos::io::sys::CreateDirectoryError If one of the directories in the
 *                                              path was attempted to be created
 *                                              but failed.
 */
 void validate( const chaos::io::sys::Path& path );

} // namespace sys
} // namespace io
} // namespace chaos

#endif
