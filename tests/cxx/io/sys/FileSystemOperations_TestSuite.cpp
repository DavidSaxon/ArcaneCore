#include "chaoscore/test/ChaosTest.hpp"

CHAOS_TEST_MODULE( io.sys.file_system_operations )

namespace
{

//------------------------------------------------------------------------------
//                                   CONSTANTS
//------------------------------------------------------------------------------

static const std::vector< chaos::uni::UTF8String > TEST_PATH =
        chaos::uni::UTF8String( "tests/cxx/io/sys/file_system_test_objects" )
        .split( "/" );

} // namespace anonymous

//------------------------------------------------------------------------------
//                                GENERIC FIXTURE
//------------------------------------------------------------------------------

// TODO: fix this shit up
// TODO: use mixed unicode file paths

class PathGenericFixture : public chaos::test::Fixture
{
public:

    //----------------------------PUBLIC ATTRIBUTES-----------------------------

    std::vector< std::vector< chaos::uni::UTF8String > > all;
    std::vector< chaos::io::sys::Path > as_paths;

    std::vector< std::vector< chaos::uni::UTF8String > > directories;
    std::vector< std::vector< chaos::uni::UTF8String > > bad_directories;

    std::vector< std::vector< chaos::uni::UTF8String > > files;
    std::vector< std::vector< chaos::uni::UTF8String > > bad_files;

    std::vector< std::vector< chaos::uni::UTF8String > > symlinks;
    std::vector< std::vector< chaos::uni::UTF8String > > bad_symlinks;

    //-------------------------PUBLIC MEMBER FUNCTIONS--------------------------

    virtual void setup()
    {
        {
            std::vector< chaos::uni::UTF8String > v( TEST_PATH );
            directories.push_back( v );
            all.push_back( v );
            as_paths.push_back( chaos::io::sys::Path( v ) );
        }
        {
            std::vector< chaos::uni::UTF8String > v( TEST_PATH );
            v.push_back( "test_dir" );
            directories.push_back( v );
            all.push_back( v );
            as_paths.push_back( chaos::io::sys::Path( v ) );
        }

        {
            std::vector< chaos::uni::UTF8String > v( TEST_PATH );
            v.push_back( "does_not_exist" );
            bad_directories.push_back( v );
            all.push_back( v );
            as_paths.push_back( chaos::io::sys::Path( v ) );
        }
        {
            std::vector< chaos::uni::UTF8String > v( TEST_PATH );
            v.push_back( "test_dir" );
            v.push_back( "does_not_exist" );
            bad_directories.push_back( v );
            all.push_back( v );
            as_paths.push_back( chaos::io::sys::Path( v ) );
        }

        {
            std::vector< chaos::uni::UTF8String > v( TEST_PATH );
            v.push_back( "test_file.txt" );
            files.push_back( v );
            all.push_back( v );
            as_paths.push_back( chaos::io::sys::Path( v ) );
        }
        {
            std::vector< chaos::uni::UTF8String > v( TEST_PATH );
            v.push_back( "test_dir" );
            v.push_back( "test_file.txt" );
            files.push_back( v );
            all.push_back( v );
            as_paths.push_back( chaos::io::sys::Path( v ) );
        }

        {
            std::vector< chaos::uni::UTF8String > v( TEST_PATH );
            v.push_back( "test_file" );
            bad_files.push_back( v );
            all.push_back( v );
            as_paths.push_back( chaos::io::sys::Path( v ) );
        }
        {
            std::vector< chaos::uni::UTF8String > v( TEST_PATH );
            v.push_back( "test_dir" );
            v.push_back( "does_not_exist.txt" );
            bad_files.push_back( v );
            all.push_back( v );
            as_paths.push_back( chaos::io::sys::Path( v ) );
        }

        {
            std::vector< chaos::uni::UTF8String > v( TEST_PATH );
            v.push_back( "symlink" );
            symlinks.push_back( v );
            all.push_back( v );
            as_paths.push_back( chaos::io::sys::Path( v ) );
        }
        {
            std::vector< chaos::uni::UTF8String > v( TEST_PATH );
            v.push_back( "test_dir" );
            v.push_back( "symlink" );
            symlinks.push_back( v );
            all.push_back( v );
            as_paths.push_back( chaos::io::sys::Path( v ) );
        }

        {
            std::vector< chaos::uni::UTF8String > v( TEST_PATH );
            v.push_back( "symlink.txt" );
            bad_symlinks.push_back( v );
            all.push_back( v );
            as_paths.push_back( chaos::io::sys::Path( v ) );
        }
        {
            std::vector< chaos::uni::UTF8String > v( TEST_PATH );
            v.push_back( "test_dir" );
            v.push_back( "does_not_exist" );
            bad_symlinks.push_back( v );
            all.push_back( v );
            as_paths.push_back( chaos::io::sys::Path( v ) );
        }
    }
};
