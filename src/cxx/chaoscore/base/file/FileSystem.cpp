#include "chaoscore/base/file/FileSystem.hpp"

#include <boost/filesystem.hpp>

#ifdef CHAOS_OS_UNIX
    #include <sys/stat.h>
#elif defined( CHAOS_OS_WINDOWS )
    #include <direct.h>
#endif

#include "chaoscore/base/file/FileExceptions.hpp"

// TODO: REMOVE ME
#include <iostream>

namespace chaos
{
namespace file
{

//------------------------------------------------------------------------------
//                                   FUNCTIONS
//------------------------------------------------------------------------------

bool exists( const chaos::str::UTF8String& path )
{
    return boost::filesystem::exists(
            boost::filesystem::path( path.getCString() )
    );
}

bool isFile( const chaos::str::UTF8String& path )
{
    return boost::filesystem::is_regular_file(
            boost::filesystem::path( path.getCString() )
    );
}

bool isDirectory( const chaos::str::UTF8String& path )
{
    return boost::filesystem::is_directory(
            boost::filesystem::path( path.getCString() )
    );
}

void createDirectory( const chaos::str::UTF8String& path )
{

#ifdef CHAOS_OS_UNIX

    mkdir( path.getCString(), 0777 );

#elif defined( CHAOS_OS_WINDOWS )

    _mkdir( path.getCString() );

#endif

}

void validatePath( const chaos::str::UTF8String& path )
{
    chaos::str::UTF8String sPath;
    // TODO: how to support '\' properly
    // if we are on windows, replace '\' for '/' if it's not followed by a space
#ifdef CHAOS_OS_WINDOWS

    for ( size_t i = 0; i < path.getLength(); ++i )
    {
        chaos::str::UTF8String symbol( path.getSymbol( i ) );
        // is this a '\'
        if ( symbol == "\\" )
        {
            // is there another symbol after this which is a space?
            if ( i < path.getLength() - 1 && path.getSymbol( i + 1 ) != " " )
            {
                symbol = "/";
            }
            else if ( i == path.getLength() - 1 )
            {
                symbol = "/";
            }
        }
        // append
        sPath += symbol;
    }

#else

    sPath = path;

#endif

    // does the path start with '/'?
    bool rootPath = false;
    if ( sPath.getSymbol( 0 ) == "/" )
    {
        rootPath = true;
    }

    // does the path end with '/'?
    bool directoryPath = false;
    if ( sPath.getSymbol( sPath.getLength() - 1 ) == "/" )
    {
        directoryPath = true;
    }

    // split the file path at separators
    std::vector< chaos::str::UTF8String > elements = sPath.split( "/" );

    // traverse the path and validate it as we descend
    chaos::str::UTF8String buildPath;
    if ( rootPath )
    {
        buildPath = "/";
    }
    for ( size_t i = 0; i < elements.size(); ++i )
    {
        if ( !directoryPath && i == elements.size() - 1 )
        {
            break;
        }

        // extend the path
        buildPath += elements[ i ];
        // does it exists as a directory?
        if ( exists( buildPath ) )
        {
            // is the existing path a directory?
            if ( !isDirectory( buildPath ) )
            {
                chaos::str::UTF8String message( "Failed to create path \'" );
                message += path + "\' because \'";
                message += buildPath + "\' already exists but is not a ";
                message += "directory.";
                throw chaos::file::ex::AmbiguousPathError( message );
            }
            buildPath += "/";
            continue;
        }
        buildPath += "/";

        // create the directory
        createDirectory( buildPath );

        // ensure that it exists now
        if ( !exists( buildPath ) )
        {
            chaos::str::UTF8String errorMessage( "Failed to create the " );
            errorMessage += "directory \'";
            errorMessage += buildPath + "\'";
            throw chaos::file::ex::CreateDirectoryError( errorMessage );
        }
    }
}

} // namespace chaos
} // namespace file
