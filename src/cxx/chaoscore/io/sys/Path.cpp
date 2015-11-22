#include "chaoscore/io/sys/Path.hpp"

#include <algorithm>

// TODO REMOVE ME
#include <iostream>

namespace chaos
{
namespace io
{
namespace sys
{

//------------------------------------------------------------------------------
//                                   CONSTANTS
//------------------------------------------------------------------------------

namespace
{

static const chaos::uni::UTF8String UNIX_SEP   ( "/" );
static const chaos::uni::UTF8String WINDOWS_SEP( "\\" );

} // namespace anonymous

//------------------------------------------------------------------------------
//                                  CONSTRUCTORS
//------------------------------------------------------------------------------

Path::Path()
{
}

Path::Path( const std::vector< chaos::uni::UTF8String >& components )
    :
    m_components( components )
{
}

Path::Path( const chaos::uni::UTF8String& string_path )
{
    // split the path into components based on the operating system
#ifdef CHAOS_OS_UNIX

    m_components = string_path.split( UNIX_SEP );

#elif defined( CHAOS_OS_WINDOWS )

    m_components = string_path.split( WINDOWS_SEP );

#endif
}

Path::Path( const Path& other )
    :
    m_components( other.m_components )
{
}

//------------------------------------------------------------------------------
//                                   OPERATORS
//------------------------------------------------------------------------------

const Path& Path::operator=( const Path& other )
{
    return *this;
}

bool Path::operator==( const Path& other ) const
{
    // check length first
    if ( m_components.size() != other.m_components.size() )
    {
        return false;
    }

    // check each component
    for ( size_t i = 0; i < m_components.size(); ++i )
    {
        if ( m_components[ i ] != other.m_components [ i ] )
        {
            return false;
        }
    }

    return true;
}

bool Path::operator!=( const Path& other ) const
{
    return !( ( *this ) == other );
}

bool Path::operator<( const Path& other ) const
{
    // size_t min = std::min( m_components.size(), other.m_components.size() );

    return true;
}

chaos::uni::UTF8String& Path::operator[]( size_t index )
{
    return m_components[ index ];
}

const chaos::uni::UTF8String& Path::operator[]( size_t index ) const
{
    return m_components[ index ];
}

Path Path::operator+( const Path& other ) const
{
    return Path();
}

const Path& Path::operator+=( const Path& other )
{
    return *this;
}

Path& Path::operator<<( const chaos::uni::UTF8String& component )
{
    return join( component );
}

//------------------------------------------------------------------------------
//                            PUBLIC MEMBER FUNCTIONS
//------------------------------------------------------------------------------

Path& Path::join( const chaos::uni::UTF8String& component )
{
    m_components.push_back( component );
    return *this;
}

void Path::insert( size_t index, const chaos::uni::UTF8String& component )
{
}

void Path::clear()
{
}

void Path::remove( size_t index )
{
}

chaos::uni::UTF8String Path::to_native() const
{
    return "";
}

chaos::uni::UTF8String Path::to_unix() const
{
    return "";
}

chaos::uni::UTF8String Path::to_windows() const
{
    return "";
}

//----------------------------------ACCESSORS-----------------------------------

size_t Path::get_length()
{
    return m_components.size();
}

const std::vector< chaos::uni::UTF8String >& Path::get_components() const
{
    return m_components;
}

chaos::uni::UTF8String Path::get_extension() const
{
    return "";
}

//------------------------------------------------------------------------------
//                               EXTERNAL OPERATORS
//------------------------------------------------------------------------------

chaos::uni::UTF8String& operator<<( chaos::uni::UTF8String& s, const Path& p )
{
    s << p.to_native();
    return s;
}

std::ostream& operator<<( std::ostream& stream, const Path& p )
{
    stream << p.to_native();
    return stream;
}

} // namespace sys
} // namespace io
} // namespace chaos
