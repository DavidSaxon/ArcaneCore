#include "arcanecore/test/ArcTest.hpp"

ARC_TEST_MODULE( io.sys.FileSystemOperations )

#include <algorithm>

#include "arcanecore/io/sys/FileSystemOperations.hpp"
#include "arcanecore/io/sys/FileWriter.hpp"

namespace file_system_operations_tests
{

//------------------------------------------------------------------------------
//                                  BASE FIXTURE
//------------------------------------------------------------------------------

class FileSysBaseFixture : public arc::test::Fixture
{
public:

    //----------------------------PUBLIC ATTRIBUTES-----------------------------

    arc::io::sys::Path base_path;

    //-------------------------PUBLIC MEMBER FUNCTIONS--------------------------

    virtual void setup()
    {
        base_path << "tests" << "data" << "file_system";
    }
};

//------------------------------------------------------------------------------
//                                GENERIC FIXTURE
//------------------------------------------------------------------------------

class FileSysGenericFixture : public FileSysBaseFixture
{
public:

    //----------------------------PUBLIC ATTRIBUTES-----------------------------

    std::vector< arc::io::sys::Path > directories;
    std::vector< arc::io::sys::Path > bad_directories;

    std::vector< arc::io::sys::Path > files;
    std::vector< arc::io::sys::Path > bad_files;

    std::vector< arc::io::sys::Path > symlinks;
    std::vector< arc::io::sys::Path > bad_symlinks;
    std::vector< arc::io::sys::Path > broken_symlinks;
    std::vector< arc::io::sys::Path > file_symlinks;
    std::vector< arc::io::sys::Path > directory_symlinks;

    //-------------------------PUBLIC MEMBER FUNCTIONS--------------------------

    virtual void setup()
    {
        // super call
        FileSysBaseFixture::setup();

        {
            arc::io::sys::Path p( base_path );
            p << "test_dir";
            directories.push_back( p );
        }
        {
            arc::io::sys::Path p( base_path );
            p << "test_dir" << "test_dir";
            directories.push_back( p );
        }
        {
            arc::io::sys::Path p( base_path );
            p << "測試_निर्देशिका";
            directories.push_back( p );
        }
        {
            arc::io::sys::Path p( base_path );
            p << "測試_निर्देशिका" << "測試_निर्देशिका";
            directories.push_back( p );
        }

        {
            arc::io::sys::Path p( base_path );
            p << "test_dir.txt";
            bad_directories.push_back( p );
        }
        {
            arc::io::sys::Path p( base_path );
            p << "test_dir" << "testdir";
            bad_directories.push_back( p );
        }
        {
            arc::io::sys::Path p( base_path );
            p << "test_dir" << "test_dir" << "test_dir";
            bad_directories.push_back( p );
        }
        {
            arc::io::sys::Path p( base_path );
            p << "測試_निर्देशिका.txt";
            bad_directories.push_back( p );
        }
        {
            arc::io::sys::Path p( base_path );
            p << "測試_निर्देशिका" << "測試_निर्दिका";
            bad_directories.push_back( p );
        }
        {
            arc::io::sys::Path p( base_path );
            p << "測試_निर्देशिका" << "測試_निर्देशिका"
              << "測試_निर्देशिका";
            bad_directories.push_back( p );
        }

        {
            arc::io::sys::Path p( base_path );
            p << "test_file.txt";
            files.push_back( p );
        }
        {
            arc::io::sys::Path p( base_path );
            p << "test_dir" << "test_file.txt";
            files.push_back( p );
        }
        {
            arc::io::sys::Path p( base_path );
            p << "file with spaces.png";
            files.push_back( p );
        }
        {
            arc::io::sys::Path p( base_path );
            p << "ການທົດສອບ.טֶקסט";
            files.push_back( p );
        }
        {
            arc::io::sys::Path p( base_path );
            p << "測試_निर्देशिका" << "ການທົດສອບ.טֶקסט";
            files.push_back( p );
        }

        {
            arc::io::sys::Path p( base_path );
            p << "test_file";
            bad_files.push_back( p );
        }
        {
            arc::io::sys::Path p( base_path );
            p << "test_file.png";
            bad_files.push_back( p );
        }
        {
            arc::io::sys::Path p( base_path );
            p << "does_not_exist" << "test_file.txt";
            bad_files.push_back( p );
        }
        {
            arc::io::sys::Path p( base_path );
            p << "test_dir" << "test__file.txt";
            bad_files.push_back( p );
        }
        {
            arc::io::sys::Path p( base_path );
            p << "ການທົດສອບ";
            bad_files.push_back( p );
        }
        {
            arc::io::sys::Path p( base_path );
            p << "ການທົקסטດສອບ.טֶקסט";
            bad_files.push_back( p );
        }
        {
            arc::io::sys::Path p( base_path );
            p << "測試_निົດर्देशिका" << "ການທົດສອບ.טֶקסט";
            bad_files.push_back( p );
        }
        {
            arc::io::sys::Path p( base_path );
            p << "測試_निर्देशिका" << "ການທົດສອບ.्देशि";
            bad_files.push_back( p );
        }

        {
            arc::io::sys::Path p( base_path );
            p << "symlink";
            symlinks.push_back( p );
            file_symlinks.push_back( p );
        }
        {
            arc::io::sys::Path p( base_path );
            p << "test_dir" << "symlink";
            symlinks.push_back( p );
            file_symlinks.push_back( p );
        }
        {
            arc::io::sys::Path p( base_path );
            p << "rəmzi링크";
            symlinks.push_back( p );
            file_symlinks.push_back( p );
        }
        {
            arc::io::sys::Path p( base_path );
            p << "測試_निर्देशिका" << "प्रतिकात्मकਲਿੰਕ";
            symlinks.push_back( p );
            file_symlinks.push_back( p );
        }
        {
            arc::io::sys::Path p( base_path );
            p << "dir_symlink";
            symlinks.push_back( p );
            directory_symlinks.push_back( p );
        }
        {
            arc::io::sys::Path p( base_path );
            p << "test_dir" << "dir_symlink";
            symlinks.push_back( p );
            directory_symlinks.push_back( p );
        }

        {
            arc::io::sys::Path p( base_path );
            p << "symlink.txt";
            bad_symlinks.push_back( p );
        }
        {
            arc::io::sys::Path p( base_path );
            p << "smylink";
            bad_symlinks.push_back( p );
        }
        {
            arc::io::sys::Path p( base_path );
            p << "test__dir" << "symlink";
            bad_symlinks.push_back( p );
        }
        {
            arc::io::sys::Path p( base_path );
            p << "test_dir" << "symlink.txt";
            bad_symlinks.push_back( p );
        }
        {
            arc::io::sys::Path p( base_path );
            p << "rəmzi링크.lnk";
            bad_symlinks.push_back( p );
        }
        {
            arc::io::sys::Path p( base_path );
            p << "zi링rəm크";
            bad_symlinks.push_back( p );
        }
        {
            arc::io::sys::Path p( base_path );
            p << "測試_निर्द__ेशिका" << "प्रतिकात्मकਲਿੰਕ";
            bad_symlinks.push_back( p );
        }
        {
            arc::io::sys::Path p( base_path );
            p << "測試_निर्देशिका" << "प्रतिकमकਲਿੰਕ";
            bad_symlinks.push_back( p );
        }

        {
            arc::io::sys::Path p( base_path );
            p << "broken_link";
            broken_symlinks.push_back( p );
        }
        {
            arc::io::sys::Path p( base_path );
            p << "test_dir" << "broken_link";
            broken_symlinks.push_back( p );
        }
    }
};

//------------------------------------------------------------------------------
//                                     EXISTS
//------------------------------------------------------------------------------

ARC_TEST_UNIT_FIXTURE( exists, FileSysGenericFixture )
{
    ARC_TEST_MESSAGE( "Checking directories that exist" );
    ARC_FOR_EACH( it_1, fixture->directories )
    {
        ARC_CHECK_TRUE( arc::io::sys::exists( *it_1 ) );
    }

    ARC_TEST_MESSAGE( "Checking directories that do not exist" );
    ARC_FOR_EACH( it_2, fixture->bad_directories )
    {
        ARC_CHECK_FALSE( arc::io::sys::exists( *it_2 ) );
    }

    ARC_TEST_MESSAGE( "Checking files that exist" );
    ARC_FOR_EACH( it_3, fixture->files )
    {
        ARC_CHECK_TRUE( arc::io::sys::exists( *it_3 ) );
    }

    ARC_TEST_MESSAGE( "Checking files that do not exist" );
    ARC_FOR_EACH( it_4, fixture->bad_files )
    {
        ARC_CHECK_FALSE( arc::io::sys::exists( *it_4 ) );
    }

// only test symlinks on Unix
#ifdef ARC_OS_UNIX

    ARC_TEST_MESSAGE( "Checking symlinks that exist" );
    ARC_FOR_EACH( it_5, fixture->symlinks )
    {
        ARC_CHECK_TRUE( arc::io::sys::exists( *it_5, true ) );
    }

    ARC_TEST_MESSAGE( "Checking symlinks that do not exist" );
    ARC_FOR_EACH( it_6, fixture->bad_symlinks )
    {
        ARC_CHECK_FALSE( arc::io::sys::exists( *it_6, true ) );
    }

    ARC_TEST_MESSAGE( "Checking resolved broken symlinks" );
    ARC_FOR_EACH( it_7, fixture->broken_symlinks )
    {
        ARC_CHECK_FALSE( arc::io::sys::exists( *it_7, true ) );
    }

    ARC_TEST_MESSAGE( "Checking non-resolved broken symlinks" );
    ARC_FOR_EACH( it_8, fixture->broken_symlinks )
    {
        ARC_CHECK_TRUE( arc::io::sys::exists( *it_8, false ) );
    }


#endif
}

//------------------------------------------------------------------------------
//                                    IS FILE
//------------------------------------------------------------------------------

ARC_TEST_UNIT_FIXTURE( is_file, FileSysGenericFixture )
{
    ARC_TEST_MESSAGE( "Checking files" );
    ARC_FOR_EACH( it_1, fixture->files )
    {
        ARC_CHECK_TRUE( arc::io::sys::is_file( *it_1 ) );
    }

    ARC_TEST_MESSAGE( "Checking non-existent files" );
    ARC_FOR_EACH( it_2, fixture->bad_files )
    {
        ARC_CHECK_FALSE( arc::io::sys::is_file( *it_2 ) );
    }

    ARC_TEST_MESSAGE( "Checking non-files" );
    ARC_FOR_EACH( it_3, fixture->directories )
    {
        ARC_CHECK_FALSE( arc::io::sys::is_file( *it_3 ) );
    }

// only test symlinks on Unix
#ifdef ARC_OS_UNIX

    ARC_TEST_MESSAGE( "Checking resolved file symlinks" );
    ARC_FOR_EACH( it_4, fixture->file_symlinks )
    {
        ARC_CHECK_TRUE( arc::io::sys::is_file( *it_4, true ) );
    }

    ARC_TEST_MESSAGE( "Checking non-resolved file symlinks" );
    ARC_FOR_EACH( it_5, fixture->file_symlinks )
    {
        ARC_CHECK_FALSE( arc::io::sys::is_file( *it_5, false ) );
    }

    ARC_TEST_MESSAGE( "Checking resolved non-file symlinks" );
    ARC_FOR_EACH( it_6, fixture->directory_symlinks )
    {
        ARC_CHECK_FALSE( arc::io::sys::is_file( *it_6, true ) );
    }

#endif
}

//------------------------------------------------------------------------------
//                                  IS DIRECTORY
//------------------------------------------------------------------------------

ARC_TEST_UNIT_FIXTURE( is_directory, FileSysGenericFixture )
{
    ARC_TEST_MESSAGE( "Checking directories" );
    ARC_FOR_EACH( it_1, fixture->directories )
    {
        ARC_CHECK_TRUE( arc::io::sys::is_directory( *it_1 ) );
    }

    ARC_TEST_MESSAGE( "Checking non-existent directories" );
    ARC_FOR_EACH( it_2, fixture->bad_directories )
    {
        ARC_CHECK_FALSE( arc::io::sys::is_directory( *it_2 ) );
    }

    ARC_TEST_MESSAGE( "Checking non-directories" );
    ARC_FOR_EACH( it_3, fixture->files )
    {
        ARC_CHECK_FALSE( arc::io::sys::is_directory( *it_3 ) );
    }

// only test symlinks on Unix
#ifdef ARC_OS_UNIX

    ARC_TEST_MESSAGE( "Checking resolved directory symlinks" );
    ARC_FOR_EACH( it_4, fixture->directory_symlinks )
    {
        ARC_CHECK_TRUE( arc::io::sys::is_directory( *it_4, true ) );
    }

    ARC_TEST_MESSAGE( "Checking non-resolved directory symlinks" );
    ARC_FOR_EACH( it_5, fixture->directory_symlinks )
    {
        ARC_CHECK_FALSE( arc::io::sys::is_directory( *it_5, false ) );
    }

    ARC_TEST_MESSAGE( "Checking resolved non-directory symlinks" );
    ARC_FOR_EACH( it_6, fixture->file_symlinks )
    {
        ARC_CHECK_FALSE( arc::io::sys::is_directory( *it_6, true ) );
    }

#endif
}

//------------------------------------------------------------------------------
//                                IS SYMBOLIC LINK
//------------------------------------------------------------------------------

ARC_TEST_UNIT_FIXTURE( is_symbolic_link, FileSysGenericFixture )
{
// only test symlinks on Unix
#ifdef ARC_OS_UNIX

    ARC_TEST_MESSAGE( "Checking symlinks" );
    ARC_FOR_EACH( it_1, fixture->symlinks )
    {
        ARC_CHECK_TRUE( arc::io::sys::is_symbolic_link( *it_1 ) );
    }
    ARC_TEST_MESSAGE( "Checking broken symlinks" );
    ARC_FOR_EACH( it_2, fixture->broken_symlinks )
    {
        ARC_CHECK_TRUE( arc::io::sys::is_symbolic_link( *it_2 ) );
    }

#endif

    ARC_TEST_MESSAGE( "Checking non-existing symlinks" );
    ARC_FOR_EACH( it_3, fixture->bad_symlinks )
    {
        ARC_CHECK_FALSE( arc::io::sys::is_symbolic_link( *it_3 ) );
    }

    ARC_TEST_MESSAGE( "Checking non-symlinks" );
    ARC_FOR_EACH( it_4, fixture->files )
    {
        ARC_CHECK_FALSE( arc::io::sys::is_symbolic_link( *it_4 ) );
    }
    ARC_FOR_EACH( it_5, fixture->directories )
    {
        ARC_CHECK_FALSE( arc::io::sys::is_symbolic_link( *it_5 ) );
    }
}

//------------------------------------------------------------------------------
//                                      LIST
//------------------------------------------------------------------------------

class ListFixture : public FileSysBaseFixture
{
public:

    //----------------------------PUBLIC ATTRIBUTES-----------------------------

    std::vector< arc::io::sys::Path > dirs;
    std::vector< std::vector< arc::io::sys::Path > > results;

    //-------------------------PUBLIC MEMBER FUNCTIONS--------------------------

    virtual void setup()
    {
        // super call
        FileSysBaseFixture::setup();

        {
            arc::io::sys::Path p( base_path );
            p << "test_file.txt";
            dirs.push_back( p );
            std::vector< arc::io::sys::Path > result;
            results.push_back( result );
        }

        {
            arc::io::sys::Path p( base_path );
            p << "list_dir";
            dirs.push_back( p );
            std::vector< arc::io::sys::Path > result;
            {
                arc::io::sys::Path r( p );
                r << ".";
                result.push_back( r );
            }
            {
                arc::io::sys::Path r( p );
                r << "..";
                result.push_back( r );
            }
            {
                arc::io::sys::Path r( p );
                r << "dir_a_1";
                result.push_back( r );
            }
            {
                arc::io::sys::Path r( p );
                r << "dir_a_2";
                result.push_back( r );
            }
            {
                arc::io::sys::Path r( p );
                r << "file_a_1";
                result.push_back( r );
            }
            {
                arc::io::sys::Path r( p );
                r << "file_a_2";
                result.push_back( r );
            }
            // {
            //     arc::io::sys::Path r( p );
            //     r << "infinite_loop_a";
            //     result.push_back( r );
            // }
            results.push_back( result );
        }

        {
            arc::io::sys::Path p( base_path );
            p << "list_dir" << "dir_a_1";
            dirs.push_back( p );
            std::vector< arc::io::sys::Path > result;
            {
                arc::io::sys::Path r( p );
                r << ".";
                result.push_back( r );
            }
            {
                arc::io::sys::Path r( p );
                r << "..";
                result.push_back( r );
            }
            {
                arc::io::sys::Path r( p );
                r << "dir_b_1";
                result.push_back( r );
            }
            {
                arc::io::sys::Path r( p );
                r << "dir_b_2";
                result.push_back( r );
            }
            {
                arc::io::sys::Path r( p );
                r << "file_b_1";
                result.push_back( r );
            }
            {
                arc::io::sys::Path r( p );
                r << "file_b_2";
                result.push_back( r );
            }
            // {
            //     arc::io::sys::Path r( p );
            //     r << "infinite_loop_b";
            //     result.push_back( r );
            // }
            results.push_back( result );
        }

        {
            arc::io::sys::Path p( base_path );
            p << "list_dir" << "dir_a_1" << "dir_b_1";
            dirs.push_back( p );
            std::vector< arc::io::sys::Path > result;
            {
                arc::io::sys::Path r( p );
                r << ".";
                result.push_back( r );
            }
            {
                arc::io::sys::Path r( p );
                r << "..";
                result.push_back( r );
            }
            {
                arc::io::sys::Path r( p );
                r << "file_d_1";
                result.push_back( r );
            }
            {
                arc::io::sys::Path r( p );
                r << "file_d_2";
                result.push_back( r );
            }
            results.push_back( result );
        }
    }
};

ARC_TEST_UNIT_FIXTURE(list, ListFixture)
{
    ARC_TEST_MESSAGE("Checking including special paths");
    {
        std::vector<std::vector< arc::io::sys::Path>> l;
        ARC_FOR_EACH(it, fixture->dirs)
        {
            l.push_back(arc::io::sys::list(*it, true));
        }


        ARC_TEST_MESSAGE("Checking returned lengths");
        for (std::size_t i = 0; i < fixture->dirs.size(); ++i)
        {
            ARC_CHECK_EQUAL(l[i].size(), fixture->results[i].size());
        }

        ARC_TEST_MESSAGE("Checking returned elements");
        for (std::size_t i = 0; i < fixture->dirs.size(); ++i)
        {
            std::size_t s = std::min(l[i].size(), fixture->results[i].size());
            for (std::size_t j = 0; j < s; ++j)
            {
                ARC_CHECK_EQUAL(l[i][j], fixture->results[i][j]);
            }
        }
    }

    ARC_TEST_MESSAGE("Checking not including special paths");
    {
        std::vector<std::vector< arc::io::sys::Path>> l;
        ARC_FOR_EACH(it, fixture->dirs)
        {
            l.push_back(arc::io::sys::list(*it, false));
        }


        ARC_TEST_MESSAGE("Checking returned lengths");
        for (std::size_t i = 0; i < fixture->dirs.size(); ++i)
        {
            std::size_t check_size = fixture->results[i].size();
            if(check_size >= 2)
            {
                check_size -= 2;
            }
            ARC_CHECK_EQUAL(l[i].size(), check_size);
        }

        ARC_TEST_MESSAGE("Checking returned elements");
        for (std::size_t i = 0; i < fixture->dirs.size(); ++i)
        {
            std::size_t s = std::min(l[i].size(), fixture->results[i].size());
            std::size_t j_ = 0;
            for (std::size_t j = 0; j < s; ++j)
            {
                // skip special
                if(fixture->results[i][j].get_back() == "." ||
                   fixture->results[i][j].get_back() == "..")
                {
                    continue;
                }

                ARC_CHECK_EQUAL(l[i][j_], fixture->results[i][j]);
                ++j_;
            }
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

    std::vector< arc::io::sys::Path > dirs;
    std::vector< std::vector< arc::io::sys::Path > > results;

    //-------------------------PUBLIC MEMBER FUNCTIONS--------------------------

    virtual void setup()
    {
        // super call
        FileSysBaseFixture::setup();

        {
            arc::io::sys::Path p( base_path );
            p << "test_file.txt";
            dirs.push_back( p );
            std::vector< arc::io::sys::Path > result;
            results.push_back( result );
        }

        {
            arc::io::sys::Path p( base_path );
            p << "list_dir";
            dirs.push_back( p );
            std::vector< arc::io::sys::Path > result;
            {
                arc::io::sys::Path r( p );
                r << ".";
                result.push_back( r );
            }
            {
                arc::io::sys::Path r( p );
                r << "..";
                result.push_back( r );
            }
            {
                arc::io::sys::Path r( p );
                r << "dir_a_1";
                result.push_back( r );
                {
                    arc::io::sys::Path r1( r );
                    r1 << ".";
                    result.push_back( r1 );
                }
                {
                    arc::io::sys::Path r1( r );
                    r1 << "..";
                    result.push_back( r1 );
                }
                {
                    arc::io::sys::Path r1( r );
                    r1 << "dir_b_1";
                    result.push_back( r1 );
                    {
                        arc::io::sys::Path r2( r1 );
                        r2 << ".";
                        result.push_back( r2 );
                    }
                    {
                        arc::io::sys::Path r2( r1 );
                        r2 << "..";
                        result.push_back( r2 );
                    }
                    {
                        arc::io::sys::Path r2( r1 );
                        r2 << "file_d_1";
                        result.push_back( r2 );
                    }
                    {
                        arc::io::sys::Path r2( r1 );
                        r2 << "file_d_2";
                        result.push_back( r2 );
                    }
                }
                {
                    arc::io::sys::Path r1( r );
                    r1 << "dir_b_2";
                    result.push_back( r1 );
                    {
                        arc::io::sys::Path r2( r1 );
                        r2 << ".";
                        result.push_back( r2 );
                    }
                    {
                        arc::io::sys::Path r2( r1 );
                        r2 << "..";
                        result.push_back( r2 );
                    }
                    {
                        arc::io::sys::Path r2( r1 );
                        r2 << "file_e_1";
                        result.push_back( r2 );
                    }
                    {
                        arc::io::sys::Path r2( r1 );
                        r2 << "file_e_2";
                        result.push_back( r2 );
                    }
                }
                {
                    arc::io::sys::Path r1( r );
                    r1 << "file_b_1";
                    result.push_back( r1 );
                }
                {
                    arc::io::sys::Path r1( r );
                    r1 << "file_b_2";
                    result.push_back( r1 );
                }
                // {
                //     arc::io::sys::Path r1( r );
                //     r1 << "infinite_loop_b";
                //     result.push_back( r1 );
                // }
            }
            {
                arc::io::sys::Path r( p );
                r << "dir_a_2";
                result.push_back( r );
                {
                    arc::io::sys::Path r1( r );
                    r1 << ".";
                    result.push_back( r1 );
                }
                {
                    arc::io::sys::Path r1( r );
                    r1 << "..";
                    result.push_back( r1 );
                }
                {
                    arc::io::sys::Path r1( r );
                    r1 << "dir_c_1";
                    result.push_back( r1 );
                    {
                        arc::io::sys::Path r2( r1 );
                        r2 << ".";
                        result.push_back( r2 );
                    }
                    {
                        arc::io::sys::Path r2( r1 );
                        r2 << "..";
                        result.push_back( r2 );
                    }
                    {
                        arc::io::sys::Path r2( r1 );
                        r2 << "file_f_1";
                        result.push_back( r2 );
                    }
                    {
                        arc::io::sys::Path r2( r1 );
                        r2 << "file_f_2";
                        result.push_back( r2 );
                    }
                }
                {
                    arc::io::sys::Path r1( r );
                    r1 << "dir_c_2";
                    result.push_back( r1 );
                    {
                        arc::io::sys::Path r2( r1 );
                        r2 << ".";
                        result.push_back( r2 );
                    }
                    {
                        arc::io::sys::Path r2( r1 );
                        r2 << "..";
                        result.push_back( r2 );
                    }
                    {
                        arc::io::sys::Path r2( r1 );
                        r2 << "file_g_1";
                        result.push_back( r2 );
                    }
                    {
                        arc::io::sys::Path r2( r1 );
                        r2 << "file_g_2";
                        result.push_back( r2 );
                    }
                }
                {
                    arc::io::sys::Path r1( r );
                    r1 << "file_c_1";
                    result.push_back( r1 );
                }
                {
                    arc::io::sys::Path r1( r );
                    r1 << "file_c_2";
                    result.push_back( r1 );
                }
                // {
                //     arc::io::sys::Path r1( r );
                //     r1 << "infinite_loop_c";
                //     result.push_back( r1 );
                // }
            }
            {
                arc::io::sys::Path r( p );
                r << "file_a_1";
                result.push_back( r );
            }
            {
                arc::io::sys::Path r( p );
                r << "file_a_2";
                result.push_back( r );
            }
            // {
            //     arc::io::sys::Path r( p );
            //     r << "infinite_loop_a";
            //     result.push_back( r );
            // }
            results.push_back( result );
        }
    }
};

ARC_TEST_UNIT_FIXTURE(list_rec, ListRecFixture)
{
    std::vector< std::vector<arc::io::sys::Path>> l;
    ARC_FOR_EACH(it, fixture->dirs)
    {
        l.push_back(arc::io::sys::list_rec(*it, true));
    }


    ARC_TEST_MESSAGE("Checking returned lengths");
    for (std::size_t i = 0; i < fixture->dirs.size(); ++i)
    {
        ARC_CHECK_EQUAL(l[i].size(), fixture->results[i].size());
    }

    ARC_TEST_MESSAGE("Checking returned elements");
    for (std::size_t i = 0; i < fixture->dirs.size(); ++i)
    {
        std::size_t s = std::min(l[i].size(), fixture->results[i].size());
        for (std::size_t j = 0; j < s; ++j)
        {
            ARC_CHECK_EQUAL(l[i][j], fixture->results[i][j]);
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

    std::vector< arc::io::sys::Path > valid;
    std::vector< arc::io::sys::Path > existing;
    std::vector< arc::io::sys::Path > ambiguous;
    std::vector< arc::io::sys::Path > invalid;

    //-------------------------PUBLIC MEMBER FUNCTIONS--------------------------

    virtual void setup()
    {
        // super call
        FileSysBaseFixture::setup();

        {
            arc::io::sys::Path p( base_path );
            p << "new_dir";
            valid.push_back( p );
        }
        {
            arc::io::sys::Path p( base_path );
            p << "test_dir" << "new_dir";
            valid.push_back( p );
        }
        {
            arc::io::sys::Path p( base_path );
            p << "test_dir" << "test_dir" << "new_dir";
            valid.push_back( p );
        }

        {
            arc::io::sys::Path p( base_path );
            p << "test_dir";
            existing.push_back( p );
        }
        {
            arc::io::sys::Path p( base_path );
            p << "test_dir" << "test_dir";
            existing.push_back( p );
        }

        // only test symlinks on Unix
        #ifdef ARC_OS_UNIX
            {
                arc::io::sys::Path p( base_path );
                p << "dir_symlink";
                existing.push_back( p );
            }
            {
                arc::io::sys::Path p( base_path );
                p << "test_dir" << "dir_symlink";
                existing.push_back( p );
            }
        #endif

        {
            arc::io::sys::Path p( base_path );
            p << "test_file.txt";
            ambiguous.push_back( p );
        }
        {
            arc::io::sys::Path p( base_path );
            p << "test_dir" << "test_file.txt";
            ambiguous.push_back( p );
        }
        {
            arc::io::sys::Path p( base_path );
            p << "file with spaces.png";
            ambiguous.push_back( p );
        }
        {
            arc::io::sys::Path p( base_path );
            p << "ການທົດສອບ.טֶקסט";
            ambiguous.push_back( p );
        }
        {
            arc::io::sys::Path p( base_path );
            p << "測試_निर्देशिका" << "ການທົດສອບ.טֶקסט";
            ambiguous.push_back( p );
        }

        // only test symlinks on Unix
        #ifdef ARC_OS_UNIX
            {
                arc::io::sys::Path p( base_path );
                p << "symlink";
                ambiguous.push_back( p );
            }
            {
                arc::io::sys::Path p( base_path );
                p << "test_dir" << "symlink";
                ambiguous.push_back( p );
            }
            {
                arc::io::sys::Path p( base_path );
                p << "rəmzi링크";
                ambiguous.push_back( p );
            }
            {
                arc::io::sys::Path p( base_path );
                p << "測試_निर्देशिका" << "प्रतिकात्मकਲਿੰਕ";
                ambiguous.push_back( p );
            }
        #endif

        {
            arc::io::sys::Path p( base_path );
            p << "does_not_exist" << "new_dir";
            invalid.push_back( p );
        }
        {
            arc::io::sys::Path p( base_path );
            p << "test_dir" << "does_not_exist" << "new_dir";
            invalid.push_back( p );
        }
        {
            arc::io::sys::Path p( base_path );
            p << "test_dir" << "test_dir" << "does_not_exist" << "new_dir";
            invalid.push_back( p );
        }
    }

    virtual void teardown()
    {
        // delete the valid file paths
        ARC_FOR_EACH( it, valid )
        {
            if ( arc::io::sys::exists( *it ) )
            {
                arc::io::sys::delete_path_rec( *it );
            }
        }
    }
};

ARC_TEST_UNIT_FIXTURE( create_directory, FileSysCreateDirectoryFixture )
{
    ARC_TEST_MESSAGE( "Checking valid" );
    ARC_FOR_EACH( it_1, fixture->valid )
    {
        bool ret = arc::io::sys::create_directory( *it_1 );
        ARC_CHECK_TRUE( ret );
    }
    ARC_FOR_EACH( it_2, fixture->valid )
    {
        ARC_CHECK_TRUE(
                arc::io::sys::exists      ( *it_2 ) &&
                arc::io::sys::is_directory( *it_2 )
        );
    }

    ARC_TEST_MESSAGE( "Checking existing" );
    ARC_FOR_EACH( it_3, fixture->existing )
    {
        bool ret = arc::io::sys::create_directory( *it_3 );
        ARC_CHECK_FALSE( ret );
    }

    ARC_TEST_MESSAGE( "Checking ambiguous" );
    ARC_FOR_EACH( it_4, fixture->ambiguous )
    {
        ARC_CHECK_THROW(
                arc::io::sys::create_directory( *it_4 ),
                arc::ex::InvalidPathError
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

    std::vector< arc::io::sys::Path > directories;
    std::vector< arc::io::sys::Path > files;
    std::vector< arc::io::sys::Path > invalid;

    //-------------------------PUBLIC MEMBER FUNCTIONS--------------------------

    virtual void setup()
    {
        // super call
        FileSysBaseFixture::setup();

        {
            arc::io::sys::Path p( base_path );
            p << "delete_me";
            directories.push_back( p );
            arc::io::sys::create_directory( p );
        }
        {
            arc::io::sys::Path p( base_path );
            p << "бришење";
            directories.push_back( p );
            arc::io::sys::create_directory( p );
        }
        {
            arc::io::sys::Path p( base_path );
            p << "test_dir" << "delete_me";
            directories.push_back( p );
            arc::io::sys::create_directory( p );
        }
        {
            arc::io::sys::Path p( base_path );
            p << "測試_निर्देशिका" << "silmək";
            directories.push_back( p );
            arc::io::sys::create_directory( p );
        }

        {
            arc::io::sys::Path p( base_path );
            p << "delete_me.txt";
            files.push_back( p );

            arc::io::sys::FileWriter w(p);
            w.write_line("Hello World!");
        }
        {
            arc::io::sys::Path p( base_path );
            p << "文件名.ಪಠ್ಯ";
            files.push_back( p );

            arc::io::sys::FileWriter w( p );
            w.write_line( "Hello World!" );
        }
        {
            arc::io::sys::Path p( base_path );
            p << "test_dir" << "delete_me.txt";
            files.push_back( p );

            arc::io::sys::FileWriter w( p );
            w.write_line( "Hello World!" );
        }
        {
            arc::io::sys::Path p( base_path );
            p << "測試_निर्देशिका" << "文件名.ಪಠ್ಯ";
            files.push_back( p );

            arc::io::sys::FileWriter w( p );
            w.write_line( "Hello World!" );
        }

        {
            arc::io::sys::Path p( base_path );
            p << "does not exist";
            invalid.push_back( p );
        }
        {
            arc::io::sys::Path p( base_path );
            p << "не існує";
            invalid.push_back( p );
        }
        {
            arc::io::sys::Path p( base_path );
            p << "test_dir";
            invalid.push_back( p );
        }
        {
            arc::io::sys::Path p( base_path );
            p << "list_dir" << "dir_a_1" << "dir_b_1";
            invalid.push_back( p );
        }
    }
};

ARC_TEST_UNIT_FIXTURE( delete_path, DeletePathFixture )
{
    ARC_TEST_MESSAGE( "Checking deleting directories" );
    ARC_FOR_EACH( it_1, fixture->directories )
    {
        arc::io::sys::delete_path( *it_1 );
        ARC_CHECK_FALSE( arc::io::sys::exists( *it_1 ) );
    }

    ARC_TEST_MESSAGE( "Checking deleting files" );
    ARC_FOR_EACH( it_2, fixture->files )
    {
        arc::io::sys::delete_path( *it_2 );
        ARC_CHECK_FALSE( arc::io::sys::exists( *it_2 ) );
    }

    ARC_TEST_MESSAGE( "Checking InvalidPathError" );
    ARC_FOR_EACH( it_3, fixture->invalid )
    {
        ARC_CHECK_THROW(
                arc::io::sys::delete_path( *it_3 ),
                arc::ex::InvalidPathError
        );
    }
}

//------------------------------------------------------------------------------
//                                DELETE PATH REC
//------------------------------------------------------------------------------

class DeletePathRecFixture : public FileSysBaseFixture
{
public:

    //----------------------------PUBLIC ATTRIBUTES-----------------------------

    std::vector< arc::io::sys::Path > directories;
    std::vector< arc::io::sys::Path > files;
    std::vector< arc::io::sys::Path > invalid;

    //-------------------------PUBLIC MEMBER FUNCTIONS--------------------------

    virtual void setup()
    {
        // super call
        FileSysBaseFixture::setup();

        {
            arc::io::sys::Path p( base_path );
            p << "delete_me";
            directories.push_back( p );
            arc::io::sys::create_directory( p );
        }
        {
            arc::io::sys::Path p( base_path );
            p << "бришење";
            directories.push_back( p );
            arc::io::sys::create_directory( p );
        }
        {
            arc::io::sys::Path p( base_path );
            p << "test_dir" << "delete_me";
            directories.push_back( p );
            arc::io::sys::create_directory( p );
        }
        {
            arc::io::sys::Path p( base_path );
            p << "測試_निर्देशिका" << "silmək";
            directories.push_back( p );
            arc::io::sys::create_directory( p );
        }

        {
            arc::io::sys::Path p( base_path );
            p << "has_sub";
            directories.push_back( p );
            arc::io::sys::create_directory( p );
            {
                arc::io::sys::Path p1( p );
                p1 << "sub_dir_1";
                arc::io::sys::create_directory( p1 );
            }
            {
                arc::io::sys::Path p1( p );
                p1 << "sub_dir_2";
                arc::io::sys::create_directory( p1 );
            }
            {
                arc::io::sys::Path p1( p );
                p1 << "sub_file_1.txt";
                arc::io::sys::FileWriter w( p1 );
                w.write_line( "Hello World!" );
            }
            {
                arc::io::sys::Path p1( p );
                p1 << "sub_file_2.png";
                arc::io::sys::FileWriter w( p1 );
                w.write_line( "Hello World!" );
            }
        }

        {
            arc::io::sys::Path p( base_path );
            p << "has_more_subs";
            directories.push_back( p );
            arc::io::sys::create_directory( p );
            {
                arc::io::sys::Path p1( p );
                p1 << "sub_dir_1";
                arc::io::sys::create_directory( p1 );
                {
                    arc::io::sys::Path p2( p1 );
                    p2 << "sub_dir_1";
                    arc::io::sys::create_directory( p2 );
                }
                {
                    arc::io::sys::Path p2( p1 );
                    p2 << "sub_dir_2";
                    arc::io::sys::create_directory( p2 );
                }
            }
            {
                arc::io::sys::Path p1( p );
                p1 << "sub_dir_2";
                arc::io::sys::create_directory( p1 );
                {
                    arc::io::sys::Path p2( p1 );
                    p2 << "sub_file_1.txt";
                    arc::io::sys::FileWriter w( p2 );
                    w.write_line( "Hello World!" );
                }
                {
                    arc::io::sys::Path p2( p1 );
                    p2 << "sub_file_2.png";
                    arc::io::sys::FileWriter w( p2 );
                    w.write_line( "Hello World!" );
                }
            }
            {
                arc::io::sys::Path p1( p );
                p1 << "sub_file_1.txt";
                arc::io::sys::FileWriter w( p1 );
                w.write_line( "Hello World!" );
            }
            {
                arc::io::sys::Path p1( p );
                p1 << "sub_file_2.png";
                arc::io::sys::FileWriter w( p1 );
                w.write_line( "Hello World!" );
            }
        }

        {
            arc::io::sys::Path p( base_path );
            p << "delete_me.txt";
            files.push_back( p );

            arc::io::sys::FileWriter w( p );
            w.write_line( "Hello World!" );
        }
        {
            arc::io::sys::Path p( base_path );
            p << "文件名.ಪಠ್ಯ";
            files.push_back( p );

            arc::io::sys::FileWriter w( p );
            w.write_line( "Hello World!" );
        }
        {
            arc::io::sys::Path p( base_path );
            p << "test_dir" << "delete_me.txt";
            files.push_back( p );

            arc::io::sys::FileWriter w( p );
            w.write_line( "Hello World!" );
        }
        {
            arc::io::sys::Path p( base_path );
            p << "測試_निर्देशिका" << "文件名.ಪಠ್ಯ";
            files.push_back( p );

            arc::io::sys::FileWriter w( p );
            w.write_line( "Hello World!" );
        }

        {
            arc::io::sys::Path p( base_path );
            p << "does not exist";
            invalid.push_back( p );
        }
        {
            arc::io::sys::Path p( base_path );
            p << "не існує";
            invalid.push_back( p );
        }
    }
};

ARC_TEST_UNIT_FIXTURE( delete_path_rec, DeletePathRecFixture )
{
    ARC_TEST_MESSAGE( "Checking deleting directories" );
    ARC_FOR_EACH( it_1, fixture->directories )
    {
        arc::io::sys::delete_path_rec( *it_1 );
        ARC_CHECK_FALSE( arc::io::sys::exists( *it_1 ) );
    }

    ARC_TEST_MESSAGE( "Checking deleting files" );
    ARC_FOR_EACH( it_2, fixture->files )
    {
        arc::io::sys::delete_path_rec( *it_2 );
        ARC_CHECK_FALSE( arc::io::sys::exists( *it_2 ) );
    }

    ARC_TEST_MESSAGE( "Checking InvalidPathError" );
    ARC_FOR_EACH( it_3, fixture->invalid )
    {
        ARC_CHECK_THROW(
                arc::io::sys::delete_path_rec( *it_3 ),
                arc::ex::InvalidPathError
        );
    }
}

//------------------------------------------------------------------------------
//                                    VALIDATE
//------------------------------------------------------------------------------

class FileSysValidateFixture : public FileSysBaseFixture
{
public:

    //----------------------------PUBLIC ATTRIBUTES-----------------------------

    std::vector< arc::io::sys::Path > valid;
    std::vector< arc::io::sys::Path > ambiguous;

    //-------------------------PUBLIC MEMBER FUNCTIONS--------------------------

    virtual void setup()
    {
        // super call
        FileSysBaseFixture::setup();

        {
            arc::io::sys::Path p( base_path );
            p << "new_dir" << "newfile.txt";
            valid.push_back( p );
        }
        {
            arc::io::sys::Path p( base_path );
            p << "new_dir" << "another new dir" << "newfile.txt";
            valid.push_back( p );
        }
        {
            arc::io::sys::Path p( base_path );
            p << "nový_ディレクトリ" << "newfile.txt";
            valid.push_back( p );
        }
        {
            arc::io::sys::Path p( base_path );
            p << "nový_ディレクトリ" << "다른" << "newfile.txt";
            valid.push_back( p );
        }

        {
            arc::io::sys::Path p( base_path );
            p << "test_file.txt" << "new_dir" << "newfile.txt";
            ambiguous.push_back( p );
        }
        {
            arc::io::sys::Path p( base_path );
            p << "test_dir" << "test_file.txt" << "newfile.txt";
            ambiguous.push_back( p );
        }
        {
            arc::io::sys::Path p( base_path );
            p << "file with spaces.png" << "new dir" << "newfile.txt";
            ambiguous.push_back( p );
        }
        {
            arc::io::sys::Path p( base_path );
            p << "ການທົດສອບ.טֶקסט" << "nový_ディレクトリ" << "newfile.txt";
            ambiguous.push_back( p );
        }
        {
            arc::io::sys::Path p( base_path );
            p << "測試_निर्देशिका" << "ການທົດສອບ.טֶקסט" << "newfile.txt";
            ambiguous.push_back( p );
        }
    }

    virtual void teardown()
    {
        {
            arc::io::sys::Path p( base_path );
            p << "new_dir";
            if ( arc::io::sys::exists( p ) )
            {
                arc::io::sys::delete_path_rec( p );
            }
        }
        {
            arc::io::sys::Path p( base_path );
            p << "nový_ディレクトリ";
            if ( arc::io::sys::exists( p ) )
            {
                arc::io::sys::delete_path_rec( p );
            }
        }
    }
};

ARC_TEST_UNIT_FIXTURE( validate, FileSysValidateFixture )
{
    ARC_TEST_MESSAGE( "Checking valid" );
    ARC_FOR_EACH( it_1, fixture->valid )
    {
        arc::io::sys::validate( *it_1 );

        // copy the path without the final component.
        arc::io::sys::Path check(
                it_1->get_components().begin(),
                it_1->get_components().end() - 1 );
        ARC_CHECK_TRUE(
                arc::io::sys::exists      ( check ) &&
                arc::io::sys::is_directory( check )
        );
    }

    ARC_TEST_MESSAGE( "Checking ambiguous" );
    ARC_FOR_EACH( it_2, fixture->ambiguous )
    {
        ARC_CHECK_THROW(
                arc::io::sys::validate( *it_2 ),
                arc::ex::InvalidPathError
        );
    }
}

} // namespace file_system_operations_tests
