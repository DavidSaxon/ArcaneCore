#include "chaoscore/test/ChaosTest.hpp"

CHAOS_TEST_MODULE( io.sys.file_system_operations )

#include <algorithm>

#include "chaoscore/io/sys/FileSystemOperations.hpp"
#include "chaoscore/io/sys/FileWriter.hpp"

namespace file_system_operations_tests
{

//------------------------------------------------------------------------------
//                                  BASE FIXTURE
//------------------------------------------------------------------------------

class FileSysBaseFixture : public chaos::test::Fixture
{
public:

    //----------------------------PUBLIC ATTRIBUTES-----------------------------

    chaos::io::sys::Path base_path;

    //-------------------------PUBLIC MEMBER FUNCTIONS--------------------------

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
    std::vector< chaos::io::sys::Path > broken_symlinks;
    std::vector< chaos::io::sys::Path > file_symlinks;
    std::vector< chaos::io::sys::Path > directory_symlinks;

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
            p << "file with spaces.png";
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

        // File symbolic link tests are currently disable since Dropbox resolves
        // them. To run these tests the valid symlinks will need to be
        // recreated
        // {
        //     chaos::io::sys::Path p( base_path );
        //     p << "symlink";
        //     symlinks.push_back( p );
        //     file_symlinks.push_back( p );
        // }
        // {
        //     chaos::io::sys::Path p( base_path );
        //     p << "test_dir" << "symlink";
        //     symlinks.push_back( p );
        //     file_symlinks.push_back( p );
        // }
        // {
        //     chaos::io::sys::Path p( base_path );
        //     p << "rəmzi링크";
        //     symlinks.push_back( p );
        //     file_symlinks.push_back( p );
        // }
        // {
        //     chaos::io::sys::Path p( base_path );
        //     p << "測試_निर्देशिका" << "प्रतिकात्मकਲਿੰਕ";
        //     symlinks.push_back( p );
        //     file_symlinks.push_back( p );
        // }
        // ---- end of disabled block ----
        {
            chaos::io::sys::Path p( base_path );
            p << "dir_symlink";
            symlinks.push_back( p );
            directory_symlinks.push_back( p );
        }
        {
            chaos::io::sys::Path p( base_path );
            p << "test_dir" << "dir_symlink";
            symlinks.push_back( p );
            directory_symlinks.push_back( p );
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

        {
            chaos::io::sys::Path p( base_path );
            p << "broken_link";
            broken_symlinks.push_back( p );
        }
        {
            chaos::io::sys::Path p( base_path );
            p << "test_dir" << "broken_link";
            broken_symlinks.push_back( p );
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
        CHAOS_CHECK_TRUE( chaos::io::sys::exists( *it_5, true ) );
    }

    CHAOS_TEST_MESSAGE( "Checking symlinks that do not exist" );
    CHAOS_FOR_EACH( it_6, fixture->bad_symlinks )
    {
        CHAOS_CHECK_FALSE( chaos::io::sys::exists( *it_6, true ) );
    }

    CHAOS_TEST_MESSAGE( "Checking resolved broken symlinks" );
    CHAOS_FOR_EACH( it_7, fixture->broken_symlinks )
    {
        CHAOS_CHECK_FALSE( chaos::io::sys::exists( *it_7, true ) );
    }

    CHAOS_TEST_MESSAGE( "Checking non-resolved broken symlinks" );
    CHAOS_FOR_EACH( it_8, fixture->broken_symlinks )
    {
        CHAOS_CHECK_TRUE( chaos::io::sys::exists( *it_8, false ) );
    }


#endif
}

//------------------------------------------------------------------------------
//                                    IS FILE
//------------------------------------------------------------------------------

CHAOS_TEST_UNIT_FIXTURE( is_file, FileSysGenericFixture )
{
    CHAOS_TEST_MESSAGE( "Checking files" );
    CHAOS_FOR_EACH( it_1, fixture->files )
    {
        CHAOS_CHECK_TRUE( chaos::io::sys::is_file( *it_1 ) );
    }

    CHAOS_TEST_MESSAGE( "Checking non-existent files" );
    CHAOS_FOR_EACH( it_2, fixture->bad_files )
    {
        CHAOS_CHECK_FALSE( chaos::io::sys::is_file( *it_2 ) );
    }

    CHAOS_TEST_MESSAGE( "Checking non-files" );
    CHAOS_FOR_EACH( it_3, fixture->directories )
    {
        CHAOS_CHECK_FALSE( chaos::io::sys::is_file( *it_3 ) );
    }

// only test symlinks on Unix
#ifdef CHAOS_OS_UNIX

    CHAOS_TEST_MESSAGE( "Checking resolved file symlinks" );
    CHAOS_FOR_EACH( it_4, fixture->file_symlinks )
    {
        CHAOS_CHECK_TRUE( chaos::io::sys::is_file( *it_4, true ) );
    }

    CHAOS_TEST_MESSAGE( "Checking non-resolved file symlinks" );
    CHAOS_FOR_EACH( it_5, fixture->file_symlinks )
    {
        CHAOS_CHECK_FALSE( chaos::io::sys::is_file( *it_5, false ) );
    }

    CHAOS_TEST_MESSAGE( "Checking resolved non-file symlinks" );
    CHAOS_FOR_EACH( it_6, fixture->directory_symlinks )
    {
        CHAOS_CHECK_FALSE( chaos::io::sys::is_file( *it_6, true ) );
    }

#endif
}

//------------------------------------------------------------------------------
//                                  IS DIRECTORY
//------------------------------------------------------------------------------

CHAOS_TEST_UNIT_FIXTURE( is_directory, FileSysGenericFixture )
{
    CHAOS_TEST_MESSAGE( "Checking directories" );
    CHAOS_FOR_EACH( it_1, fixture->directories )
    {
        CHAOS_CHECK_TRUE( chaos::io::sys::is_directory( *it_1 ) );
    }

    CHAOS_TEST_MESSAGE( "Checking non-existent directories" );
    CHAOS_FOR_EACH( it_2, fixture->bad_directories )
    {
        CHAOS_CHECK_FALSE( chaos::io::sys::is_directory( *it_2 ) );
    }

    CHAOS_TEST_MESSAGE( "Checking non-directories" );
    CHAOS_FOR_EACH( it_3, fixture->files )
    {
        CHAOS_CHECK_FALSE( chaos::io::sys::is_directory( *it_3 ) );
    }

// only test symlinks on Unix
#ifdef CHAOS_OS_UNIX

    CHAOS_TEST_MESSAGE( "Checking resolved directory symlinks" );
    CHAOS_FOR_EACH( it_4, fixture->directory_symlinks )
    {
        CHAOS_CHECK_TRUE( chaos::io::sys::is_directory( *it_4, true ) );
    }

    CHAOS_TEST_MESSAGE( "Checking non-resolved directory symlinks" );
    CHAOS_FOR_EACH( it_5, fixture->directory_symlinks )
    {
        CHAOS_CHECK_FALSE( chaos::io::sys::is_directory( *it_5, false ) );
    }

    CHAOS_TEST_MESSAGE( "Checking resolved non-directory symlinks" );
    CHAOS_FOR_EACH( it_6, fixture->file_symlinks )
    {
        CHAOS_CHECK_FALSE( chaos::io::sys::is_directory( *it_6, true ) );
    }

#endif
}

//------------------------------------------------------------------------------
//                                IS SYMBOLIC LINK
//------------------------------------------------------------------------------

CHAOS_TEST_UNIT_FIXTURE( is_symbolic_link, FileSysGenericFixture )
{
// only test symlinks on Unix
#ifdef CHAOS_OS_UNIX

    CHAOS_TEST_MESSAGE( "Checking symlinks" );
    CHAOS_FOR_EACH( it_1, fixture->symlinks )
    {
        CHAOS_CHECK_TRUE( chaos::io::sys::is_symbolic_link( *it_1 ) );
    }
    CHAOS_TEST_MESSAGE( "Checking broken symlinks" );
    CHAOS_FOR_EACH( it_2, fixture->broken_symlinks )
    {
        CHAOS_CHECK_TRUE( chaos::io::sys::is_symbolic_link( *it_2 ) );
    }

#endif

    CHAOS_TEST_MESSAGE( "Checking non-existing symlinks" );
    CHAOS_FOR_EACH( it_3, fixture->bad_symlinks )
    {
        CHAOS_CHECK_FALSE( chaos::io::sys::is_symbolic_link( *it_3 ) );
    }

    CHAOS_TEST_MESSAGE( "Checking non-symlinks" );
    CHAOS_FOR_EACH( it_4, fixture->files )
    {
        CHAOS_CHECK_FALSE( chaos::io::sys::is_symbolic_link( *it_4 ) );
    }
    CHAOS_FOR_EACH( it_5, fixture->directories )
    {
        CHAOS_CHECK_FALSE( chaos::io::sys::is_symbolic_link( *it_5 ) );
    }
}

//------------------------------------------------------------------------------
//                                      LIST
//------------------------------------------------------------------------------

class ListFixture : public FileSysBaseFixture
{
public:

    //----------------------------PUBLIC ATTRIBUTES-----------------------------

    std::vector< chaos::io::sys::Path > dirs;
    std::vector< std::vector< chaos::io::sys::Path > > results;

    //-------------------------PUBLIC MEMBER FUNCTIONS--------------------------

    virtual void setup()
    {
        // super call
        FileSysBaseFixture::setup();

        {
            chaos::io::sys::Path p( base_path );
            p << "test_file.txt";
            dirs.push_back( p );
            std::vector< chaos::io::sys::Path > result;
            results.push_back( result );
        }

        {
            chaos::io::sys::Path p( base_path );
            p << "list_dir";
            dirs.push_back( p );
            std::vector< chaos::io::sys::Path > result;
            {
                chaos::io::sys::Path r( p );
                r << ".";
                result.push_back( r );
            }
            {
                chaos::io::sys::Path r( p );
                r << "..";
                result.push_back( r );
            }
            {
                chaos::io::sys::Path r( p );
                r << "dir_a_1";
                result.push_back( r );
            }
            {
                chaos::io::sys::Path r( p );
                r << "dir_a_2";
                result.push_back( r );
            }
            {
                chaos::io::sys::Path r( p );
                r << "file_a_1";
                result.push_back( r );
            }
            {
                chaos::io::sys::Path r( p );
                r << "file_a_2";
                result.push_back( r );
            }
            // {
            //     chaos::io::sys::Path r( p );
            //     r << "infinite_loop_a";
            //     result.push_back( r );
            // }
            results.push_back( result );
        }

        {
            chaos::io::sys::Path p( base_path );
            p << "list_dir" << "dir_a_1";
            dirs.push_back( p );
            std::vector< chaos::io::sys::Path > result;
            {
                chaos::io::sys::Path r( p );
                r << ".";
                result.push_back( r );
            }
            {
                chaos::io::sys::Path r( p );
                r << "..";
                result.push_back( r );
            }
            {
                chaos::io::sys::Path r( p );
                r << "dir_b_1";
                result.push_back( r );
            }
            {
                chaos::io::sys::Path r( p );
                r << "dir_b_2";
                result.push_back( r );
            }
            {
                chaos::io::sys::Path r( p );
                r << "file_b_1";
                result.push_back( r );
            }
            {
                chaos::io::sys::Path r( p );
                r << "file_b_2";
                result.push_back( r );
            }
            // {
            //     chaos::io::sys::Path r( p );
            //     r << "infinite_loop_b";
            //     result.push_back( r );
            // }
            results.push_back( result );
        }

        {
            chaos::io::sys::Path p( base_path );
            p << "list_dir" << "dir_a_1" << "dir_b_1";
            dirs.push_back( p );
            std::vector< chaos::io::sys::Path > result;
            {
                chaos::io::sys::Path r( p );
                r << ".";
                result.push_back( r );
            }
            {
                chaos::io::sys::Path r( p );
                r << "..";
                result.push_back( r );
            }
            {
                chaos::io::sys::Path r( p );
                r << "file_d_1";
                result.push_back( r );
            }
            {
                chaos::io::sys::Path r( p );
                r << "file_d_2";
                result.push_back( r );
            }
            results.push_back( result );
        }
    }
};

CHAOS_TEST_UNIT_FIXTURE( list, ListFixture )
{
    std::vector< std::vector< chaos::io::sys::Path > > l;
    CHAOS_FOR_EACH( it, fixture->dirs )
    {
        l.push_back( chaos::io::sys::list( *it ) );
    }


    CHAOS_TEST_MESSAGE( "Checking returned lengths" );
    for ( std::size_t i = 0; i < fixture->dirs.size(); ++i )
    {
        CHAOS_CHECK_EQUAL( l[ i ].size(), fixture->results[ i ].size() );
    }

    CHAOS_TEST_MESSAGE( "Checking returned elements" );
    for ( std::size_t i = 0; i < fixture->dirs.size(); ++i )
    {
        std::size_t s = std::min( l[ i ].size(), fixture->results[ i ].size() );
        for ( std::size_t j = 0; j < s; ++j )
        {
            CHAOS_CHECK_EQUAL( l[ i ][ j ], fixture->results[ i ][ j ] );
        }
    }
}

//------------------------------------------------------------------------------
//                                    LIST REC
//------------------------------------------------------------------------------

class ListRecFixture : public FileSysBaseFixture
{
public:

    //----------------------------PUBLIC ATTRIBUTES-----------------------------

    std::vector< chaos::io::sys::Path > dirs;
    std::vector< std::vector< chaos::io::sys::Path > > results;

    //-------------------------PUBLIC MEMBER FUNCTIONS--------------------------

    virtual void setup()
    {
        // super call
        FileSysBaseFixture::setup();

        {
            chaos::io::sys::Path p( base_path );
            p << "test_file.txt";
            dirs.push_back( p );
            std::vector< chaos::io::sys::Path > result;
            results.push_back( result );
        }

        {
            chaos::io::sys::Path p( base_path );
            p << "list_dir";
            dirs.push_back( p );
            std::vector< chaos::io::sys::Path > result;
            {
                chaos::io::sys::Path r( p );
                r << ".";
                result.push_back( r );
            }
            {
                chaos::io::sys::Path r( p );
                r << "..";
                result.push_back( r );
            }
            {
                chaos::io::sys::Path r( p );
                r << "dir_a_1";
                result.push_back( r );
                {
                    chaos::io::sys::Path r1( r );
                    r1 << ".";
                    result.push_back( r1 );
                }
                {
                    chaos::io::sys::Path r1( r );
                    r1 << "..";
                    result.push_back( r1 );
                }
                {
                    chaos::io::sys::Path r1( r );
                    r1 << "dir_b_1";
                    result.push_back( r1 );
                    {
                        chaos::io::sys::Path r2( r1 );
                        r2 << ".";
                        result.push_back( r2 );
                    }
                    {
                        chaos::io::sys::Path r2( r1 );
                        r2 << "..";
                        result.push_back( r2 );
                    }
                    {
                        chaos::io::sys::Path r2( r1 );
                        r2 << "file_d_1";
                        result.push_back( r2 );
                    }
                    {
                        chaos::io::sys::Path r2( r1 );
                        r2 << "file_d_2";
                        result.push_back( r2 );
                    }
                }
                {
                    chaos::io::sys::Path r1( r );
                    r1 << "dir_b_2";
                    result.push_back( r1 );
                    {
                        chaos::io::sys::Path r2( r1 );
                        r2 << ".";
                        result.push_back( r2 );
                    }
                    {
                        chaos::io::sys::Path r2( r1 );
                        r2 << "..";
                        result.push_back( r2 );
                    }
                    {
                        chaos::io::sys::Path r2( r1 );
                        r2 << "file_e_1";
                        result.push_back( r2 );
                    }
                    {
                        chaos::io::sys::Path r2( r1 );
                        r2 << "file_e_2";
                        result.push_back( r2 );
                    }
                }
                {
                    chaos::io::sys::Path r1( r );
                    r1 << "file_b_1";
                    result.push_back( r1 );
                }
                {
                    chaos::io::sys::Path r1( r );
                    r1 << "file_b_2";
                    result.push_back( r1 );
                }
                // {
                //     chaos::io::sys::Path r1( r );
                //     r1 << "infinite_loop_b";
                //     result.push_back( r1 );
                // }
            }
            {
                chaos::io::sys::Path r( p );
                r << "dir_a_2";
                result.push_back( r );
                {
                    chaos::io::sys::Path r1( r );
                    r1 << ".";
                    result.push_back( r1 );
                }
                {
                    chaos::io::sys::Path r1( r );
                    r1 << "..";
                    result.push_back( r1 );
                }
                {
                    chaos::io::sys::Path r1( r );
                    r1 << "dir_c_1";
                    result.push_back( r1 );
                    {
                        chaos::io::sys::Path r2( r1 );
                        r2 << ".";
                        result.push_back( r2 );
                    }
                    {
                        chaos::io::sys::Path r2( r1 );
                        r2 << "..";
                        result.push_back( r2 );
                    }
                    {
                        chaos::io::sys::Path r2( r1 );
                        r2 << "file_f_1";
                        result.push_back( r2 );
                    }
                    {
                        chaos::io::sys::Path r2( r1 );
                        r2 << "file_f_2";
                        result.push_back( r2 );
                    }
                }
                {
                    chaos::io::sys::Path r1( r );
                    r1 << "dir_c_2";
                    result.push_back( r1 );
                    {
                        chaos::io::sys::Path r2( r1 );
                        r2 << ".";
                        result.push_back( r2 );
                    }
                    {
                        chaos::io::sys::Path r2( r1 );
                        r2 << "..";
                        result.push_back( r2 );
                    }
                    {
                        chaos::io::sys::Path r2( r1 );
                        r2 << "file_g_1";
                        result.push_back( r2 );
                    }
                    {
                        chaos::io::sys::Path r2( r1 );
                        r2 << "file_g_2";
                        result.push_back( r2 );
                    }
                }
                {
                    chaos::io::sys::Path r1( r );
                    r1 << "file_c_1";
                    result.push_back( r1 );
                }
                {
                    chaos::io::sys::Path r1( r );
                    r1 << "file_c_2";
                    result.push_back( r1 );
                }
                // {
                //     chaos::io::sys::Path r1( r );
                //     r1 << "infinite_loop_c";
                //     result.push_back( r1 );
                // }
            }
            {
                chaos::io::sys::Path r( p );
                r << "file_a_1";
                result.push_back( r );
            }
            {
                chaos::io::sys::Path r( p );
                r << "file_a_2";
                result.push_back( r );
            }
            // {
            //     chaos::io::sys::Path r( p );
            //     r << "infinite_loop_a";
            //     result.push_back( r );
            // }
            results.push_back( result );
        }
    }
};

CHAOS_TEST_UNIT_FIXTURE( list_rec, ListRecFixture )
{
    std::vector< std::vector< chaos::io::sys::Path > > l;
    CHAOS_FOR_EACH( it, fixture->dirs )
    {
        l.push_back( chaos::io::sys::list_rec( *it ) );
    }


    CHAOS_TEST_MESSAGE( "Checking returned lengths" );
    for ( std::size_t i = 0; i < fixture->dirs.size(); ++i )
    {
        CHAOS_CHECK_EQUAL( l[ i ].size(), fixture->results[ i ].size() );
    }

    CHAOS_TEST_MESSAGE( "Checking returned elements" );
    for ( std::size_t i = 0; i < fixture->dirs.size(); ++i )
    {
        std::size_t s = std::min( l[ i ].size(), fixture->results[ i ].size() );
        for ( std::size_t j = 0; j < s; ++j )
        {
            CHAOS_CHECK_EQUAL( l[ i ][ j ], fixture->results[ i ][ j ] );
        }
    }
}

//------------------------------------------------------------------------------
//                                CREATE DIRECTORY
//------------------------------------------------------------------------------

class FileSysCreateDirectoryFixture : public FileSysBaseFixture
{
public:

    //----------------------------PUBLIC ATTRIBUTES-----------------------------

    std::vector< chaos::io::sys::Path > valid;
    std::vector< chaos::io::sys::Path > existing;
    std::vector< chaos::io::sys::Path > ambiguous;
    std::vector< chaos::io::sys::Path > invalid;

    //-------------------------PUBLIC MEMBER FUNCTIONS--------------------------

    virtual void setup()
    {
        // super call
        FileSysBaseFixture::setup();

        {
            chaos::io::sys::Path p( base_path );
            p << "new_dir";
            valid.push_back( p );
        }
        {
            chaos::io::sys::Path p( base_path );
            p << "test_dir" << "new_dir";
            valid.push_back( p );
        }
        {
            chaos::io::sys::Path p( base_path );
            p << "test_dir" << "test_dir" << "new_dir";
            valid.push_back( p );
        }

        {
            chaos::io::sys::Path p( base_path );
            p << "test_dir";
            existing.push_back( p );
        }
        {
            chaos::io::sys::Path p( base_path );
            p << "test_dir" << "test_dir";
            existing.push_back( p );
        }
        {
            chaos::io::sys::Path p( base_path );
            p << "dir_symlink";
            existing.push_back( p );
        }
        {
            chaos::io::sys::Path p( base_path );
            p << "test_dir" << "dir_symlink";
            existing.push_back( p );
        }

        {
            chaos::io::sys::Path p( base_path );
            p << "test_file.txt";
            ambiguous.push_back( p );
        }
        {
            chaos::io::sys::Path p( base_path );
            p << "test_dir" << "test_file.txt";
            ambiguous.push_back( p );
        }
        {
            chaos::io::sys::Path p( base_path );
            p << "file with spaces.png";
            ambiguous.push_back( p );
        }
        {
            chaos::io::sys::Path p( base_path );
            p << "ການທົດສອບ.טֶקסט";
            ambiguous.push_back( p );
        }
        {
            chaos::io::sys::Path p( base_path );
            p << "測試_निर्देशिका" << "ການທົດສອບ.טֶקסט";
            ambiguous.push_back( p );
        }
        // File symbolic link tests are currently disable since Dropbox resolves
        // them. To run these tests the valid symlinks will need to be
        // recreated
        // {
        //     chaos::io::sys::Path p( base_path );
        //     p << "symlink";
        //     ambiguous.push_back( p );
        // }
        // {
        //     chaos::io::sys::Path p( base_path );
        //     p << "test_dir" << "symlink";
        //     ambiguous.push_back( p );
        // }
        // {
        //     chaos::io::sys::Path p( base_path );
        //     p << "rəmzi링크";
        //     ambiguous.push_back( p );
        // }
        // {
        //     chaos::io::sys::Path p( base_path );
        //     p << "測試_निर्देशिका" << "प्रतिकात्मकਲਿੰਕ";
        //     ambiguous.push_back( p );
        // }

        {
            chaos::io::sys::Path p( base_path );
            p << "does_not_exist" << "new_dir";
            invalid.push_back( p );
        }
        {
            chaos::io::sys::Path p( base_path );
            p << "test_dir" << "does_not_exist" << "new_dir";
            invalid.push_back( p );
        }
        {
            chaos::io::sys::Path p( base_path );
            p << "test_dir" << "test_dir" << "does_not_exist" << "new_dir";
            invalid.push_back( p );
        }
    }

    virtual void teardown()
    {
        // delete the valid file paths
        CHAOS_FOR_EACH( it, valid )
        {
            std::cout << "delete!" << *it << std::endl;
            remove( it->to_native().get_raw() );
        }
    }
};

CHAOS_TEST_UNIT_FIXTURE( create_directory, FileSysCreateDirectoryFixture )
{
    CHAOS_TEST_MESSAGE( "Checking valid" );
    CHAOS_FOR_EACH( it_1, fixture->valid )
    {
        bool ret = chaos::io::sys::create_directory( *it_1 );
        CHAOS_CHECK_TRUE( ret );
    }
    CHAOS_FOR_EACH( it_2, fixture->valid )
    {
        CHAOS_CHECK_TRUE(
                chaos::io::sys::exists      ( *it_2 ) &&
                chaos::io::sys::is_directory( *it_2 )
        );
    }

    CHAOS_TEST_MESSAGE( "Checking existing" );
    CHAOS_FOR_EACH( it_3, fixture->existing )
    {
        bool ret = chaos::io::sys::create_directory( *it_3 );
        CHAOS_CHECK_FALSE( ret );
    }

    CHAOS_TEST_MESSAGE( "Checking ambiguous" );
    CHAOS_FOR_EACH( it_4, fixture->ambiguous )
    {
        CHAOS_CHECK_THROW(
                chaos::io::sys::create_directory( *it_4 ),
                chaos::io::sys::AmbiguousPathError
        );
    }

    CHAOS_TEST_MESSAGE( "Checking invalid" );
    CHAOS_FOR_EACH( it_5, fixture->invalid )
    {
        CHAOS_CHECK_THROW(
                chaos::io::sys::create_directory( *it_5 ),
                chaos::io::sys::CreateDirectoryError
        );
    }
}

//------------------------------------------------------------------------------
//                                  DELETE PATH
//------------------------------------------------------------------------------

class DeletePathFixture : public FileSysBaseFixture
{
public:

    //----------------------------PUBLIC ATTRIBUTES-----------------------------

    std::vector< chaos::io::sys::Path > directories;
    std::vector< chaos::io::sys::Path > files;

    //-------------------------PUBLIC MEMBER FUNCTIONS--------------------------

    virtual void setup()
    {
        // super call
        FileSysBaseFixture::setup();

        {
            chaos::io::sys::Path p( base_path );
            p << "delete_me";
            directories.push_back( p );
            chaos::io::sys::create_directory( p );
        }
        {
            chaos::io::sys::Path p( base_path );
            p << "бришење";
            directories.push_back( p );
            chaos::io::sys::create_directory( p );
        }

        {
            chaos::io::sys::Path p( base_path );
            p << "test_dir" << "delete_me";
            directories.push_back( p );
            chaos::io::sys::create_directory( p );
        }
        {
            chaos::io::sys::Path p( base_path );
            p << "測試_निर्देशिका" << "silmək";
            directories.push_back( p );
            chaos::io::sys::create_directory( p );
        }

        {
            chaos::io::sys::Path p( base_path );
            p << "delete_me.txt";
            files.push_back( p );

            chaos::io::sys::FileWriter w( p );
            w.write_line( "Hello World!" );
        }
        {
            chaos::io::sys::Path p( base_path );
            p << "文件名.ಪಠ್ಯ";
            files.push_back( p );

            chaos::io::sys::FileWriter w( p );
            w.write_line( "Hello World!" );
        }
        {
            chaos::io::sys::Path p( base_path );
            p << "test_dir" << "delete_me.txt";
            files.push_back( p );

            chaos::io::sys::FileWriter w( p );
            w.write_line( "Hello World!" );
        }
        {
            chaos::io::sys::Path p( base_path );
            p << "測試_निर्देशिका" << "文件名.ಪಠ್ಯ";
            files.push_back( p );

            chaos::io::sys::FileWriter w( p );
            w.write_line( "Hello World!" );
        }
    }
};

CHAOS_TEST_UNIT_FIXTURE( delete_path, DeletePathFixture )
{
    CHAOS_TEST_MESSAGE( "Checking deleting directories" );
    CHAOS_FOR_EACH( it_1, fixture->directories )
    {
        chaos::io::sys::delete_path( *it_1 );
        CHAOS_CHECK_FALSE( chaos::io::sys::exists( *it_1 ) );
    }

    CHAOS_TEST_MESSAGE( "Checking deleting files" );
    CHAOS_FOR_EACH( it_2, fixture->files )
    {
        chaos::io::sys::delete_path( *it_2 );
        CHAOS_CHECK_FALSE( chaos::io::sys::exists( *it_2 ) );
    }
}

//------------------------------------------------------------------------------
//                                    VALIDATE
//------------------------------------------------------------------------------

class FileSysValidateFixture : public FileSysBaseFixture
{
public:

    //----------------------------PUBLIC ATTRIBUTES-----------------------------

    std::vector< chaos::io::sys::Path > valid;
    std::vector< chaos::io::sys::Path > ambiguous;

    //-------------------------PUBLIC MEMBER FUNCTIONS--------------------------

    virtual void setup()
    {
        // super call
        FileSysBaseFixture::setup();

        {
            chaos::io::sys::Path p( base_path );
            p << "new_dir" << "newfile.txt";
            valid.push_back( p );
        }
        {
            chaos::io::sys::Path p( base_path );
            p << "new_dir" << "another new dir" << "newfile.txt";
            valid.push_back( p );
        }
        {
            chaos::io::sys::Path p( base_path );
            p << "nový_ディレクトリ" << "newfile.txt";
            valid.push_back( p );
        }
        {
            chaos::io::sys::Path p( base_path );
            p << "nový_ディレクトリ" << "다른" << "newfile.txt";
            valid.push_back( p );
        }

        {
            chaos::io::sys::Path p( base_path );
            p << "test_file.txt" << "new_dir" << "newfile.txt";
            ambiguous.push_back( p );
        }
        {
            chaos::io::sys::Path p( base_path );
            p << "test_dir" << "test_file.txt" << "newfile.txt";
            ambiguous.push_back( p );
        }
        {
            chaos::io::sys::Path p( base_path );
            p << "file with spaces.png" << "new dir" << "newfile.txt";
            ambiguous.push_back( p );
        }
        {
            chaos::io::sys::Path p( base_path );
            p << "ການທົດສອບ.טֶקסט" << "nový_ディレクトリ" << "newfile.txt";
            ambiguous.push_back( p );
        }
        {
            chaos::io::sys::Path p( base_path );
            p << "測試_निर्देशिका" << "ການທົດສອບ.טֶקסט" << "newfile.txt";
            ambiguous.push_back( p );
        }
    }

    virtual void teardown()
    {
        // TODO: use hard-delete here when implemented
        CHAOS_FOR_EACH( it, valid )
        {
            for( std::size_t i = it->get_length() - 1;
                 i > base_path.get_length();
                 --i )
            {
                // create a new path to be cleaned up
                chaos::io::sys::Path p(
                        it->get_components().begin(),
                        it->get_components().begin() + i
                );

                remove( p.to_native().get_raw() );
            }
        }
    }
};

CHAOS_TEST_UNIT_FIXTURE( validate, FileSysValidateFixture )
{
    CHAOS_TEST_MESSAGE( "Checking valid" );
    CHAOS_FOR_EACH( it_1, fixture->valid )
    {
        chaos::io::sys::validate( *it_1 );

        // copy the path without the final component.
        chaos::io::sys::Path check(
                it_1->get_components().begin(),
                it_1->get_components().end() - 1 );
        CHAOS_CHECK_TRUE(
                chaos::io::sys::exists      ( check ) &&
                chaos::io::sys::is_directory( check )
        );
    }

    CHAOS_TEST_MESSAGE( "Checking ambiguous" );
    CHAOS_FOR_EACH( it_2, fixture->ambiguous )
    {
        CHAOS_CHECK_THROW(
                chaos::io::sys::validate( *it_2 ),
                chaos::io::sys::AmbiguousPathError
        );
    }
}

} // namespace file_system_operations_tests
