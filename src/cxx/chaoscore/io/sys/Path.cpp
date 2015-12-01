#include "chaoscore/io/sys/Path.hpp"

#include <cstddef>
#include <cstring>

#include "chaoscore/base/BaseExceptions.hpp"
#include "chaoscore/base/uni/UnicodeOperations.hpp"

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
    :
    m_cstring_data( nullptr )
{
}

Path::Path( const std::vector< chaos::uni::UTF8String >& components )
    :
    m_components  ( components ),
    m_cstring_data( nullptr )
{
}

Path::Path(
        const std::vector< chaos::uni::UTF8String >::const_iterator& begin,
        const std::vector< chaos::uni::UTF8String >::const_iterator& end )
    :
    m_components  ( begin, end ),
    m_cstring_data( nullptr )
{
}

Path::Path( const chaos::uni::UTF8String& string_path )
    :
    m_cstring_data( nullptr )
{
    // split the path into components based on the operating system
#ifdef CHAOS_OS_UNIX

    chaos::uni::UTF8String santised_path( string_path );
    santised_path.remove_duplicates( UNIX_SEP );
    m_components = santised_path.split( UNIX_SEP );

    if ( m_components.size() > 0 && m_components[ 0 ] == "" )
    {
        m_components[ 0 ] = "/";
    }

#elif defined( CHAOS_OS_WINDOWS )

    chaos::uni::UTF8String santised_path( string_path );
    santised_path.remove_duplicates( WINDOWS_SEP );
    m_components = santised_path.split( WINDOWS_SEP );

#endif

    // remove final space if the path ended with /
    if ( m_components.size() > 0 && m_components.back() == "" )
    {
        m_components = std::vector< chaos::uni::UTF8String >(
            m_components.begin(), m_components.end() - 1 );
    }
}

Path::Path( const Path& other )
    :
    m_components  ( other.m_components ),
    m_cstring_data( nullptr )
{
}

//------------------------------------------------------------------------------
//                                   DESTRUCTOR
//------------------------------------------------------------------------------

Path::~Path()
{
    delete[] m_cstring_data;
}

//------------------------------------------------------------------------------
//                                   OPERATORS
//------------------------------------------------------------------------------

const Path& Path::operator=( const Path& other )
{
    m_components = other.m_components;
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
    for ( std::size_t i = 0; i < m_components.size(); ++i )
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
    // do the paths have the same length?
    if ( m_components.size() == other.m_components.size() )
    {
        // perform check on each component
        for ( std::size_t i = 0; i < m_components.size(); ++i )
        {
            if ( m_components[ i ] != other.m_components[ i ] )
            {
                return m_components[ i ] < other.m_components[ i ];
            }
        }
        return false;
    }

    // compare based on length
    return m_components.size() < other.m_components.size();
}

chaos::uni::UTF8String& Path::operator[]( std::size_t index )
{
    return m_components[ index ];
}

const chaos::uni::UTF8String& Path::operator[]( std::size_t index ) const
{
    return m_components[ index ];
}

Path Path::operator+( const Path& other ) const
{
    // create a new path which is a copy of this path
    Path copy( *this );
    // now use compound operator
    return copy += other;
}

const Path& Path::operator+=( const Path& other )
{
    // extend with other path's components
    CHAOS_FOR_EACH( it, other.m_components )
    {
        m_components.push_back( *it );
    }

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

void Path::insert( std::size_t index, const chaos::uni::UTF8String& component )
{
    // check bounds
    if ( index > m_components.size() )
    {
        chaos::uni::UTF8String error_message;
        error_message << "Provided index: " << index << " is greater than the "
                      << "number of components in the path: "
                      << m_components.size();
        throw chaos::ex::IndexOutOfBoundsError( error_message );
    }

    // new vector to contain components
    std::vector< chaos::uni::UTF8String > components;
    // copy with the insert
    for ( std::size_t i = 0; i <= m_components.size(); ++i )
    {
        if ( i < index )
        {
            components.push_back( m_components[ i ] );
        }
        else if ( i > index )
        {
            components.push_back( m_components[ i - 1 ] );
        }
        else
        {
            components.push_back( component );
        }
    }
    // replace the current list of components
    m_components = components;
}

void Path::clear()
{
    m_components.clear();
}

void Path::remove( std::size_t index )
{
    // check bounds
    if ( index >= m_components.size() )
    {
        chaos::uni::UTF8String error_message;
        error_message << "Provided index: " << index << " is greater or equal "
                      << "to the number of components in the path: "
                      << m_components.size();
        throw chaos::ex::IndexOutOfBoundsError( error_message );
    }

    // new vector to contain components
    std::vector< chaos::uni::UTF8String > components;
    // copy with the remove
    for ( std::size_t i = 0; i < m_components.size(); ++i )
    {
        if ( i < index )
        {
            components.push_back( m_components[ i ] );
        }
        else if ( i > index )
        {
            components.push_back( m_components[ i ] );
        }
    }
    // replace the current list of components
    m_components = components;
}

chaos::uni::UTF8String Path::to_native() const
{
#ifdef CHAOS_OS_UNIX

    return to_unix();

#elif defined( CHAOS_OS_WINDOWS )

    return to_windows();

#endif
}

chaos::uni::UTF8String Path::to_unix() const
{
    std::vector< chaos::uni::UTF8String > components;
    // special case for root ( / )
    bool is_root = false;
    if ( m_components.size() > 0 && m_components[ 0 ] == "/"  )
    {
        is_root = true;
        components = std::vector< chaos::uni::UTF8String >(
                m_components.begin() + 1, m_components.end() );
    }
    else
    {
        components = m_components;
    }

    chaos::uni::UTF8String ret = chaos::uni::join( components, "/" );
    if ( is_root )
    {
        ret = chaos::uni::UTF8String( "/" ) + ret;
    }

    return ret;
}

chaos::uni::UTF8String Path::to_windows() const
{
    return chaos::uni::join( m_components, "\\" );
}

//----------------------------------ACCESSORS-----------------------------------

std::size_t Path::get_length() const
{
    return m_components.size();
}

const std::vector< chaos::uni::UTF8String >& Path::get_components() const
{
    return m_components;
}

chaos::uni::UTF8String Path::get_extension() const
{
    // is there a final component?
    if ( !m_components.empty() )
    {
        // does the final component contain a period?
        std::size_t loc = m_components.back().find_last( "." );
        if ( loc != chaos::uni::npos )
        {
            // return the extension substring
            return m_components.back().substring(
                    loc + 1,
                    m_components.back().get_length()
            );
        }
    }
    // there is no extension, return an empty string
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
