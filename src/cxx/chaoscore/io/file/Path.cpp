#include "chaoscore/io/file/Path.hpp"

namespace chaos
{
namespace io
{
namespace file
{

//------------------------------------------------------------------------------
//                                  CONSTRUCTORS
//------------------------------------------------------------------------------

Path::Path()
{
}

Path::Path( const std::vector< chaos::str::UTF8String >& components )
    :
    m_components( components )
{
}

Path::Path( const chaos::str::UTF8String& string_path )
{
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
    return true;
}

bool Path::operator!=( const Path& other ) const
{
    return false;
}

bool Path::operator<( const Path& other ) const
{
    return true;
}

chaos::str::UTF8String& Path::operator[]( size_t index )
{
    return m_components[ index ];
}

const chaos::str::UTF8String& Path::operator[]( size_t index ) const
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

Path& Path::operator<<( const chaos::str::UTF8String& component )
{
    return *this;
}

//------------------------------------------------------------------------------
//                            PUBLIC MEMBER FUNCTIONS
//------------------------------------------------------------------------------

Path& Path::join( const chaos::str::UTF8String& component )
{
    return *this;
}

void Path::insert( size_t index, const chaos::str::UTF8String& component )
{
}

void Path::clear()
{
}

void Path::remove( size_t index )
{
}

chaos::str::UTF8String Path::to_native() const
{
    return "";
}

chaos::str::UTF8String Path::to_unix() const
{
    return "";
}

chaos::str::UTF8String Path::to_windows() const
{
    return "";
}

bool Path::exists() const
{
    return true;
}

bool Path::is_file() const
{
    return true;
}

bool Path::is_directory() const
{
    return true;
}

bool Path::is_symlink() const
{
    return true;
}

//----------------------------------ACCESSORS-----------------------------------

size_t Path::get_length()
{
    return m_components.size();
}

const std::vector< chaos::str::UTF8String >& Path::get_components() const
{
    return m_components;
}

chaos::str::UTF8String Path::get_extension() const
{
    return "";
}

//------------------------------------------------------------------------------
//                               EXTERNAL OPERATORS
//------------------------------------------------------------------------------

chaos::str::UTF8String& operator<<( chaos::str::UTF8String& s, const Path& p )
{
    s << p.to_native();
    return s;
}

std::ostream& operator<<( std::ostream& stream, const Path& p )
{
    stream << p.to_native();
    return stream;
}

} // namespace file
} // namespace io
} // namespace chaos
