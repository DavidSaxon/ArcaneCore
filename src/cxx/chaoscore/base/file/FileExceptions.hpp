/*!
 * \file
 * \author David Saxon
 */
#ifndef CHAOSCORE_BASE_FILE_EXCEPTIONS_HPP_
#define CHAOSCORE_BASE_FILE_EXCEPTIONS_HPP_

#include "chaoscore/base/BaseExceptions.hpp"

namespace chaos
{
namespace file
{
/*!
 * \brief Exceptions relating to the file system.
 */
namespace ex
{

/*!
 * \brief A generic error relating to the file system.
 *
 * All other file system exceptions inherit from this exception.
 */
class FileSystemError : public chaos::ex::ChaosException
{
public:

    FileSystemError( const chaos::str::UTF8String& message )
        :
        ChaosException( message )
    {
    }
};

/*!
 * \brief Warns that creating a directory has failed.
 */
class CreateDirectoryError : public FileSystemError
{
public:

    CreateDirectoryError( const chaos::str::UTF8String& message )
        :
        FileSystemError( message )
    {
    }
};

/*!
 * \brief Warns that has a request has been made to create a file or directory
 *        that results in a ambiguous file system path.
 *
 * An example is if a directory called 'my_name' was attempted to be created
 * where a file also called 'my_name' exists in the same directory.
 */
class AmbiguousPathError : public FileSystemError
{
public:

    AmbiguousPathError( const chaos::str::UTF8String& message )
        :
        FileSystemError( message )
    {
    }
};

} // namespace ex
} // namespace file
} // namespace chaos

#endif
