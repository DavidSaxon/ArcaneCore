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

//------------------------------------------------------------------------------
//                            PUBLIC MEMBER FUNCTIONS
//------------------------------------------------------------------------------

const chaos::str::UTF8String& Path::to_string() const
{
    return m_contents;
}

const char* Path::to_cstring() const
{
    return m_contents.to_cstring();
}

} // namespace file
} // namespace io
} // namespace chaos
