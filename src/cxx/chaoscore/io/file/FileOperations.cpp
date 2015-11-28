#include "chaoscore/io/file/FileOperations.hpp"

#include <boost/filesystem.hpp>

#ifdef CHAOS_OS_UNIX
    #include <sys/stat.h>
#elif defined( CHAOS_OS_WINDOWS )
    #include <direct.h>
#endif

#include "chaoscore/io/file/FileExceptions.hpp"

namespace chaos
{
namespace io
{
namespace file
{

//------------------------------------------------------------------------------
//                                   FUNCTIONS
//------------------------------------------------------------------------------

bool exists( const chaos::uni::UTF8String& path )
{
    // TODO: should really have a system for representing paths...
    // can contain most of these operations

    boost::filesystem::path p( path.get_raw() );

    return boost::filesystem::exists( p ) ||
           boost::filesystem::symbolic_link_exists( p );
}

bool is_file( const chaos::uni::UTF8String& path )
{
    return boost::filesystem::is_regular_file(
            boost::filesystem::path( path.get_raw() )
    );
}

bool is_directory( const chaos::uni::UTF8String& path )
{
    return boost::filesystem::is_directory(
            boost::filesystem::path( path.get_raw() )
    );
}

void create_directory( const chaos::uni::UTF8String& path )
{

#ifdef CHAOS_OS_UNIX

    mkdir( path.get_raw(), 0777 );

#elif defined( CHAOS_OS_WINDOWS )

    _mkdir( path.get_raw() );

#endif

}

void validate_path( const chaos::uni::UTF8String& path )
{
    chaos::uni::UTF8String s_path;
    // TODO: how to support '\' properly
    // if we are on windows, replace '\' for '/' if it's not followed by a space
#ifdef CHAOS_OS_WINDOWS

    for ( size_t i = 0; i < path.get_length(); ++i )
    {
        chaos::uni::UTF8String symbol( path.get_symbol( i ) );
        // is this a '\'
        if ( symbol == "\\" )
        {
            // is there another symbol after this which is a space?
            if ( i < path.get_length() - 1 && path.get_symbol( i + 1 ) != " " )
            {
                symbol = "/";
            }
            else if ( i == path.get_length() - 1 )
            {
                symbol = "/";
            }
        }
        // append
        s_path += symbol;
    }

#else

    s_path = path;

#endif

    // does the path start with '/'?
    bool root_path = false;
    if ( s_path.get_symbol( 0 ) == "/" )
    {
        root_path = true;
    }

    // does the path end with '/'?
    bool directory_path = false;
    if ( s_path.get_symbol( s_path.get_length() - 1 ) == "/" )
    {
        directory_path = true;
    }

    // split the file path at separators
    std::vector< chaos::uni::UTF8String > elements = s_path.split( "/" );

    // traverse the path and validate it as we descend
    chaos::uni::UTF8String build_path;
    if ( root_path )
    {
        build_path = "/";
    }
    for ( size_t i = 0; i < elements.size(); ++i )
    {
        if ( !directory_path && i == elements.size() - 1 )
        {
            break;
        }

        // extend the path
        build_path += elements[ i ];
        // does it exists as a directory?
        if ( exists( build_path ) )
        {
            // is the existing path a directory?
            if ( !is_directory( build_path ) )
            {
                // TODO: STREAM
                chaos::uni::UTF8String error_message;
                error_message << "Failed to create path \'" << path << "\' "
                              << "because \'" << build_path << "\' already "
                              << "exists but is not a directory.";
                throw chaos::io::file::ex::AmbiguousPathError( error_message );
            }
            build_path += "/";
            continue;
        }
        build_path += "/";

        // create the directory
        create_directory( build_path );

        // ensure that it exists now
        if ( !exists( build_path ) )
        {
            chaos::uni::UTF8String error_message;
            error_message << "Failed to create the directory \'" << build_path
                          << "\'";
            throw chaos::io::file::ex::CreateDirectoryError( error_message );
        }
    }
}

} // namespace file
} // namespace io
} // namespace chaos
