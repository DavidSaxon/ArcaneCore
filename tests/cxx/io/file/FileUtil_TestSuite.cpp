#include "chaoscore/test/ChaosTest.hpp"

CHAOS_TEST_MODULE( io.file.fileutil )

#include "chaoscore/io/file/FileUtil.hpp"

namespace
{

//------------------------------------------------------------------------------
//                                   CONSTANTS
//------------------------------------------------------------------------------

// the path to the test directory
static const chaos::str::UTF8String TEST_PATH(
        "tests/cxx/io/file/file_system_test_objects" );

} // namespace anonymous

//------------------------------------------------------------------------------
//                                GENERIC FIXTURE
//------------------------------------------------------------------------------

class FileUtilGenericFixture : public chaos::test::Fixture
{
public:

    //----------------------------PUBLIC ATTRIBUTES-----------------------------

    // paths to directories
    std::vector< chaos::str::UTF8String > directories;
    std::vector< chaos::str::UTF8String > bad_directories;
    // paths to files
    std::vector< chaos::str::UTF8String > files;
    std::vector< chaos::str::UTF8String > bad_files;
    // path to symlinks
    std::vector< chaos::str::UTF8String > symlinks;
    std::vector< chaos::str::UTF8String > bad_symlinks;

    //-------------------------PUBLIC MEMBER FUNCTIONS--------------------------

    virtual void setup()
    {
        directories.push_back( TEST_PATH );
        directories.push_back( TEST_PATH + "/test_dir" );
        bad_directories.push_back( TEST_PATH + "abc" );
        bad_directories.push_back( TEST_PATH + "/does_not_exist" );

        files.push_back( TEST_PATH + "/test_file.txt" );
        files.push_back( TEST_PATH + "/test_dir/test_file.txt" );
        bad_files.push_back( TEST_PATH + "/test_file" );
        bad_files.push_back( TEST_PATH + "/test_dir/does_not_exist.txt" );

        symlinks.push_back( TEST_PATH + "/symlink" );
        symlinks.push_back( TEST_PATH + "/test_dir/symlink" );
        bad_symlinks.push_back( TEST_PATH + "/symlink.txt" );
        bad_symlinks.push_back( TEST_PATH + "/test_dir/does_not_exist" );
    }
};

//------------------------------------------------------------------------------
//                                     EXISTS
//------------------------------------------------------------------------------

CHAOS_TEST_UNIT_FIXTURE( exists, FileUtilGenericFixture )
{
    CHAOS_TEST_MESSAGE( "Checking directories" );
    CHAOS_FOR_EACH( d_it, fixture->directories )
    {
        CHAOS_CHECK_TRUE( chaos::io::file::exists( *d_it ) );
    }
    CHAOS_FOR_EACH( b_d_it, fixture->bad_directories )
    {
        CHAOS_CHECK_FALSE( chaos::io::file::exists( *b_d_it ) );
    }

    CHAOS_TEST_MESSAGE( "Checking files" );
    CHAOS_FOR_EACH( f_it, fixture->files )
    {
        CHAOS_CHECK_TRUE( chaos::io::file::exists( *f_it ) );
    }
    CHAOS_FOR_EACH( b_f_it, fixture->bad_files )
    {
        CHAOS_CHECK_FALSE( chaos::io::file::exists( *b_f_it ) );
    }

    CHAOS_TEST_MESSAGE( "Checking symlinks" );
    CHAOS_FOR_EACH( s_it, fixture->symlinks )
    {
        CHAOS_CHECK_TRUE( chaos::io::file::exists( *s_it ) );
    }
    CHAOS_FOR_EACH( b_s_it, fixture->bad_symlinks )
    {
        CHAOS_CHECK_FALSE( chaos::io::file::exists( *b_s_it ) );
    }
}
