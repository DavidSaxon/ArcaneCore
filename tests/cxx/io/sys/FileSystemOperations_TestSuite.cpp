#include "chaoscore/test/ChaosTest.hpp"

CHAOS_TEST_MODULE( io.sys.file_system_operations )

#include "chaoscore/io/sys/FileSystemOperations.hpp"

namespace file_system_operations_tests
{

//------------------------------------------------------------------------------
//                                  BASE FIXTURE
//------------------------------------------------------------------------------

class FileSysBaseFixture : public chaos::test::Fixture
{
public:

    chaos::io::sys::Path base_path;

    virtual void setup()
    {
        base_path << "tests" << "cxx" << "io" << "sys"
                  << "file_system_test_objects";
    }
};

//------------------------------------------------------------------------------
//                                GENERIC FIXTURE
//------------------------------------------------------------------------------

class FileSysGenericFixture : public FileSysBaseFixture
{
public:

    //----------------------------PUBLIC ATTRIBUTES-----------------------------

    std::vector< chaos::io::sys::Path > directories;
    std::vector< chaos::io::sys::Path > bad_directories;

    std::vector< chaos::io::sys::Path > files;
    std::vector< chaos::io::sys::Path > bad_files;

    std::vector< chaos::io::sys::Path > symlinks;
    std::vector< chaos::io::sys::Path > bad_symlinks;

    //-------------------------PUBLIC MEMBER FUNCTIONS--------------------------

    virtual void setup()
    {
        // super call
        FileSysBaseFixture::setup();

        {
            chaos::io::sys::Path p( base_path );
            p << "test_dir";
            directories.push_back( p );
        }
        {
            chaos::io::sys::Path p( base_path );
            p << "test_dir" << "test_dir";
            directories.push_back( p );
        }
        {
            chaos::io::sys::Path p( base_path );
            p << "測試_निर्देशिका";
            directories.push_back( p );
        }
        {
            chaos::io::sys::Path p( base_path );
            p << "測試_निर्देशिका" << "測試_निर्देशिका";
            directories.push_back( p );
        }

        {
            chaos::io::sys::Path p( base_path );
            p << "test_dir.txt";
            bad_directories.push_back( p );
        }
        {
            chaos::io::sys::Path p( base_path );
            p << "test_dir" << "testdir";
            bad_directories.push_back( p );
        }
        {
            chaos::io::sys::Path p( base_path );
            p << "test_dir" << "test_dir" << "test_dir";
            bad_directories.push_back( p );
        }
        {
            chaos::io::sys::Path p( base_path );
            p << "測試_निर्देशिका.txt";
            bad_directories.push_back( p );
        }
        {
            chaos::io::sys::Path p( base_path );
            p << "測試_निर्देशिका" << "測試_निर्दिका";
            bad_directories.push_back( p );
        }
        {
            chaos::io::sys::Path p( base_path );
            p << "測試_निर्देशिका" << "測試_निर्देशिका"
              << "測試_निर्देशिका";
            bad_directories.push_back( p );
        }

        {
            chaos::io::sys::Path p( base_path );
            p << "test_file.txt";
            files.push_back( p );
        }
        {
            chaos::io::sys::Path p( base_path );
            p << "test_dir" << "test_file.txt";
            files.push_back( p );
        }
        {
            chaos::io::sys::Path p( base_path );
            p << "ການທົດສອບ.טֶקסט";
            files.push_back( p );
        }
        {
            chaos::io::sys::Path p( base_path );
            p << "測試_निर्देशिका" << "ການທົດສອບ.טֶקסט";
            files.push_back( p );
        }

        {
            chaos::io::sys::Path p( base_path );
            p << "test_file";
            bad_files.push_back( p );
        }
        {
            chaos::io::sys::Path p( base_path );
            p << "test_file.png";
            bad_files.push_back( p );
        }
        {
            chaos::io::sys::Path p( base_path );
            p << "does_not_exist" << "test_file.txt";
            bad_files.push_back( p );
        }
        {
            chaos::io::sys::Path p( base_path );
            p << "test_dir" << "test__file.txt";
            bad_files.push_back( p );
        }
        {
            chaos::io::sys::Path p( base_path );
            p << "ການທົດສອບ";
            bad_files.push_back( p );
        }
        {
            chaos::io::sys::Path p( base_path );
            p << "ການທົקסטດສອບ.טֶקסט";
            bad_files.push_back( p );
        }
        {
            chaos::io::sys::Path p( base_path );
            p << "測試_निົດर्देशिका" << "ການທົດສອບ.טֶקסט";
            bad_files.push_back( p );
        }
        {
            chaos::io::sys::Path p( base_path );
            p << "測試_निर्देशिका" << "ການທົດສອບ.्देशि";
            bad_files.push_back( p );
        }

        {
            chaos::io::sys::Path p( base_path );
            p << "symlink";
            symlinks.push_back( p );
        }
        {
            chaos::io::sys::Path p( base_path );
            p << "test_dir" << "symlink";
            symlinks.push_back( p );
        }
        {
            chaos::io::sys::Path p( base_path );
            p << "rəmzi링크";
            symlinks.push_back( p );
        }
        {
            chaos::io::sys::Path p( base_path );
            p << "測試_निर्देशिका" << "प्रतिकात्मकਲਿੰਕ";
            symlinks.push_back( p );
        }

        {
            chaos::io::sys::Path p( base_path );
            p << "symlink.txt";
            bad_symlinks.push_back( p );
        }
        {
            chaos::io::sys::Path p( base_path );
            p << "smylink";
            bad_symlinks.push_back( p );
        }
        {
            chaos::io::sys::Path p( base_path );
            p << "test__dir" << "symlink";
            bad_symlinks.push_back( p );
        }
        {
            chaos::io::sys::Path p( base_path );
            p << "test_dir" << "symlink.txt";
            bad_symlinks.push_back( p );
        }
        {
            chaos::io::sys::Path p( base_path );
            p << "rəmzi링크.lnk";
            bad_symlinks.push_back( p );
        }
        {
            chaos::io::sys::Path p( base_path );
            p << "zi링rəm크";
            bad_symlinks.push_back( p );
        }
        {
            chaos::io::sys::Path p( base_path );
            p << "測試_निर्द__ेशिका" << "प्रतिकात्मकਲਿੰਕ";
            bad_symlinks.push_back( p );
        }
        {
            chaos::io::sys::Path p( base_path );
            p << "測試_निर्देशिका" << "प्रतिकमकਲਿੰਕ";
            bad_symlinks.push_back( p );
        }
    }
};

//------------------------------------------------------------------------------
//                                     EXISTS
//------------------------------------------------------------------------------

CHAOS_TEST_UNIT_FIXTURE( exists, FileSysGenericFixture )
{
    CHAOS_TEST_MESSAGE( "Checking directories that exist" );
    CHAOS_FOR_EACH( it_1, fixture->directories )
    {
        CHAOS_CHECK_TRUE( chaos::io::sys::exists( *it_1 ) );
    }

    CHAOS_TEST_MESSAGE( "Checking directories that do not exist" );
    CHAOS_FOR_EACH( it_2, fixture->bad_directories )
    {
        CHAOS_CHECK_FALSE( chaos::io::sys::exists( *it_2 ) );
    }

    CHAOS_TEST_MESSAGE( "Checking files that exist" );
    CHAOS_FOR_EACH( it_3, fixture->files )
    {
        CHAOS_CHECK_TRUE( chaos::io::sys::exists( *it_3 ) );
    }

    CHAOS_TEST_MESSAGE( "Checking files that do not exist" );
    CHAOS_FOR_EACH( it_4, fixture->bad_files )
    {
        CHAOS_CHECK_FALSE( chaos::io::sys::exists( *it_4 ) );
    }

// only test symlinks on Unix
#ifdef CHAOS_OS_UNIX

    CHAOS_TEST_MESSAGE( "Checking symlinks that exist" );
    CHAOS_FOR_EACH( it_5, fixture->symlinks )
    {
        CHAOS_CHECK_TRUE( chaos::io::sys::exists( *it_5 ) );
    }

    CHAOS_TEST_MESSAGE( "Checking symlinks that do not exist" );
    CHAOS_FOR_EACH( it_6, fixture->bad_symlinks )
    {
        CHAOS_CHECK_FALSE( chaos::io::sys::exists( *it_6 ) );
    }

#endif
}

} // namespace file_system_operations_tests
