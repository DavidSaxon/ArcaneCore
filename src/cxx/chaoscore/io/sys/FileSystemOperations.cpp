#include "chaoscore/io/sys/FileSystemOperations.hpp"

namespace chaos
{
namespace io
{
namespace sys
{

bool exists( const chaos::io::sys::Path& path )
{
    return true;
}

bool is_file( const chaos::io::sys::Path& path )
{
    return true;
}

bool is_directory( const chaos::io::sys::Path& path )
{
    return true;
}

bool is_symbolic_link( const chaos::io::sys::Path& path )
{
    return true;
}

bool create_directory( const chaos::io::sys::Path& path )
{
    return true;
}

void validate( const chaos::io::sys::Path& path )
{

}

} // namespace sys
} // namespace io
} // namespace chaos
