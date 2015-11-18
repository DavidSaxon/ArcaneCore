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

const std::vector< chaos::str::UTF8String >& Path::get_components() const
{
    return m_components;
}

} // namespace file
} // namespace io
} // namespace chaos
