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
//                            PUBLIC MEMBER FUNCTIONS
//------------------------------------------------------------------------------

const std::vector< chaos::str::UTF8String >& Path::get_components() const
{
    return m_components;
}

} // namespace file
} // namespace io
} // namespace chaos
