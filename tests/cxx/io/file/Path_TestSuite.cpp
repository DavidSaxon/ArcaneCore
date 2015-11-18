#include "chaoscore/test/ChaosTest.hpp"

CHAOS_TEST_MODULE( io.file.path )

#include <algorithm>

#include "chaoscore/io/file/Path.hpp"

//------------------------------------------------------------------------------
//                                   CONSTANTS
//------------------------------------------------------------------------------

namespace
{

//------------------------------------------------------------------------------
//                                   CONSTANTS
//------------------------------------------------------------------------------

static const std::vector< chaos::str::UTF8String > TEST_PATH =
        chaos::str::UTF8String( "tests/cxx/io/file/file_system_test_objects" )
        .split( "/" );

} // namespace anonymous

//------------------------------------------------------------------------------
//                                GENERIC FIXTURE
//------------------------------------------------------------------------------

class FileUtilGenericFixture : public chaos::test::Fixture
{
public:

    //----------------------------PUBLIC ATTRIBUTES-----------------------------

    std::vector< std::vector< chaos::str::UTF8String > > all;
    std::vector< chaos::io::file::Path > as_paths;

    std::vector< std::vector< chaos::str::UTF8String > > directories;
    std::vector< std::vector< chaos::str::UTF8String > > bad_directories;

    std::vector< std::vector< chaos::str::UTF8String > > files;
    std::vector< std::vector< chaos::str::UTF8String > > bad_files;

    std::vector< std::vector< chaos::str::UTF8String > > symlinks;
    std::vector< std::vector< chaos::str::UTF8String > > bad_symlinks;

    //-------------------------PUBLIC MEMBER FUNCTIONS--------------------------

    virtual void setup()
    {
        {
            std::vector< chaos::str::UTF8String > v( TEST_PATH );
            directories.push_back( v );
            all.push_back( v );
            as_paths.push_back( chaos::io::file::Path( v ) );
        }
        {
            std::vector< chaos::str::UTF8String > v( TEST_PATH );
            v.push_back( "test_dir" );
            directories.push_back( v );
            all.push_back( v );
            as_paths.push_back( chaos::io::file::Path( v ) );
        }

        {
            std::vector< chaos::str::UTF8String > v( TEST_PATH );
            v.push_back( "does_not_exist" );
            bad_directories.push_back( v );
            all.push_back( v );
            as_paths.push_back( chaos::io::file::Path( v ) );
        }
        {
            std::vector< chaos::str::UTF8String > v( TEST_PATH );
            v.push_back( "test_dir" );
            v.push_back( "does_not_exist" );
            bad_directories.push_back( v );
            all.push_back( v );
            as_paths.push_back( chaos::io::file::Path( v ) );
        }

        {
            std::vector< chaos::str::UTF8String > v( TEST_PATH );
            v.push_back( "test_file.txt" );
            files.push_back( v );
            all.push_back( v );
            as_paths.push_back( chaos::io::file::Path( v ) );
        }
        {
            std::vector< chaos::str::UTF8String > v( TEST_PATH );
            v.push_back( "test_dir" );
            v.push_back( "test_file.txt" );
            files.push_back( v );
            all.push_back( v );
            as_paths.push_back( chaos::io::file::Path( v ) );
        }

        {
            std::vector< chaos::str::UTF8String > v( TEST_PATH );
            v.push_back( "test_file" );
            bad_files.push_back( v );
            all.push_back( v );
            as_paths.push_back( chaos::io::file::Path( v ) );
        }
        {
            std::vector< chaos::str::UTF8String > v( TEST_PATH );
            v.push_back( "test_dir" );
            v.push_back( "does_not_exist.txt" );
            bad_files.push_back( v );
            all.push_back( v );
            as_paths.push_back( chaos::io::file::Path( v ) );
        }

        {
            std::vector< chaos::str::UTF8String > v( TEST_PATH );
            v.push_back( "symlink" );
            symlinks.push_back( v );
            all.push_back( v );
            as_paths.push_back( chaos::io::file::Path( v ) );
        }
        {
            std::vector< chaos::str::UTF8String > v( TEST_PATH );
            v.push_back( "test_dir" );
            v.push_back( "symlink" );
            symlinks.push_back( v );
            all.push_back( v );
            as_paths.push_back( chaos::io::file::Path( v ) );
        }

        {
            std::vector< chaos::str::UTF8String > v( TEST_PATH );
            v.push_back( "symlink.txt" );
            bad_symlinks.push_back( v );
            all.push_back( v );
            as_paths.push_back( chaos::io::file::Path( v ) );
        }
        {
            std::vector< chaos::str::UTF8String > v( TEST_PATH );
            v.push_back( "test_dir" );
            v.push_back( "does_not_exist" );
            bad_symlinks.push_back( v );
            all.push_back( v );
            as_paths.push_back( chaos::io::file::Path( v ) );
        }
    }
};

//------------------------------------------------------------------------------
//                              DEFAULT CONSTRUCTOR
//------------------------------------------------------------------------------

CHAOS_TEST_UNIT( default_constructor )
{
    chaos::io::file::Path empty;
    CHAOS_CHECK_TRUE( empty.get_components().empty() );
}

//------------------------------------------------------------------------------
//                             COMPONENT CONSTRUCTOR
//------------------------------------------------------------------------------

CHAOS_TEST_UNIT_FIXTURE( component_constructor, FileUtilGenericFixture )
{
    std::vector< chaos::io::file::Path > paths;
    CHAOS_FOR_EACH( it, fixture->all )
    {
        paths.push_back( chaos::io::file::Path( *it ) );
    }

    CHAOS_TEST_MESSAGE( "Checking internal component lengths" );
    for ( size_t i = 0; i < paths.size(); ++i )
    {
        CHAOS_CHECK_EQUAL(
                paths[ i ].get_components().size(),
                fixture->all[ i ].size()
        );
    }

    CHAOS_TEST_MESSAGE( "Checking internal components" );
    for ( size_t i = 0; i < paths.size(); ++i )
    {
        size_t min = std::min(
                paths[ i ].get_components().size(),
                fixture->all[ i ].size()
        );
        for ( size_t j = 0; j < min; ++j )
        {
            CHAOS_CHECK_EQUAL(
                    paths[ i ].get_components()[ j ],
                    fixture->all[ i ][ j ]
            );
        }
    }
}

//------------------------------------------------------------------------------
//                                COPY CONSTRUCTOR
//------------------------------------------------------------------------------

CHAOS_TEST_UNIT_FIXTURE( copy_constructor, FileUtilGenericFixture )
{
    std::vector< chaos::io::file::Path > paths;
    CHAOS_FOR_EACH( it, fixture->all )
    {
        paths.push_back( chaos::io::file::Path( *it ) );
    }

    CHAOS_TEST_MESSAGE( "Checking internal component lengths" );
    for ( size_t i = 0; i < paths.size(); ++i )
    {
        CHAOS_CHECK_EQUAL(
                paths[ i ].get_components().size(),
                fixture->as_paths[ i ].get_components().size()
        );
    }

    CHAOS_TEST_MESSAGE( "Checking internal components" );
    for ( size_t i = 0; i < paths.size(); ++i )
    {
        size_t min = std::min(
                paths[ i ].get_components().size(),
                fixture->as_paths[ i ].get_components().size()
        );
        for ( size_t j = 0; j < min; ++j )
        {
            CHAOS_CHECK_EQUAL(
                    paths[ i ].get_components()[ j ],
                    fixture->as_paths[ i ].get_components()[ j ]
            );
        }
    }
}
