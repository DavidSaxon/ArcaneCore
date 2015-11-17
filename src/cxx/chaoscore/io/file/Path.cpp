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

Path::Path( const Path& other )
    :
    m_components( other.m_components )
{
}

//------------------------------------------------------------------------------
//                            PUBLIC MEMBER FUNCTIONS
//------------------------------------------------------------------------------

// const chaos::str::UTF8String& Path::to_string() const
// {
//     return m_components;
// }

} // namespace file
} // namespace io
} // namespace chaos
