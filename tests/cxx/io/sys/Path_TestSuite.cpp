#include "chaoscore/test/ChaosTest.hpp"

CHAOS_TEST_MODULE( io.sys.path )

#include <algorithm>

#include "chaoscore/io/sys/Path.hpp"

//------------------------------------------------------------------------------
//                                   CONSTANTS
//------------------------------------------------------------------------------

namespace
{

//------------------------------------------------------------------------------
//                                   CONSTANTS
//------------------------------------------------------------------------------

static const std::vector< chaos::str::UTF8String > TEST_PATH =
        chaos::str::UTF8String( "tests/cxx/io/sys/file_system_test_objects" )
        .split( "/" );

} // namespace anonymous

//------------------------------------------------------------------------------
//                                GENERIC FIXTURE
//------------------------------------------------------------------------------

class PathGenericFixture : public chaos::test::Fixture
{
public:

    //----------------------------PUBLIC ATTRIBUTES-----------------------------

    std::vector< std::vector< chaos::str::UTF8String > > all;
    std::vector< chaos::io::sys::Path > as_paths;

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
            as_paths.push_back( chaos::io::sys::Path( v ) );
        }
        {
            std::vector< chaos::str::UTF8String > v( TEST_PATH );
            v.push_back( "test_dir" );
            directories.push_back( v );
            all.push_back( v );
            as_paths.push_back( chaos::io::sys::Path( v ) );
        }

        {
            std::vector< chaos::str::UTF8String > v( TEST_PATH );
            v.push_back( "does_not_exist" );
            bad_directories.push_back( v );
            all.push_back( v );
            as_paths.push_back( chaos::io::sys::Path( v ) );
        }
        {
            std::vector< chaos::str::UTF8String > v( TEST_PATH );
            v.push_back( "test_dir" );
            v.push_back( "does_not_exist" );
            bad_directories.push_back( v );
            all.push_back( v );
            as_paths.push_back( chaos::io::sys::Path( v ) );
        }

        {
            std::vector< chaos::str::UTF8String > v( TEST_PATH );
            v.push_back( "test_file.txt" );
            files.push_back( v );
            all.push_back( v );
            as_paths.push_back( chaos::io::sys::Path( v ) );
        }
        {
            std::vector< chaos::str::UTF8String > v( TEST_PATH );
            v.push_back( "test_dir" );
            v.push_back( "test_file.txt" );
            files.push_back( v );
            all.push_back( v );
            as_paths.push_back( chaos::io::sys::Path( v ) );
        }

        {
            std::vector< chaos::str::UTF8String > v( TEST_PATH );
            v.push_back( "test_file" );
            bad_files.push_back( v );
            all.push_back( v );
            as_paths.push_back( chaos::io::sys::Path( v ) );
        }
        {
            std::vector< chaos::str::UTF8String > v( TEST_PATH );
            v.push_back( "test_dir" );
            v.push_back( "does_not_exist.txt" );
            bad_files.push_back( v );
            all.push_back( v );
            as_paths.push_back( chaos::io::sys::Path( v ) );
        }

        {
            std::vector< chaos::str::UTF8String > v( TEST_PATH );
            v.push_back( "symlink" );
            symlinks.push_back( v );
            all.push_back( v );
            as_paths.push_back( chaos::io::sys::Path( v ) );
        }
        {
            std::vector< chaos::str::UTF8String > v( TEST_PATH );
            v.push_back( "test_dir" );
            v.push_back( "symlink" );
            symlinks.push_back( v );
            all.push_back( v );
            as_paths.push_back( chaos::io::sys::Path( v ) );
        }

        {
            std::vector< chaos::str::UTF8String > v( TEST_PATH );
            v.push_back( "symlink.txt" );
            bad_symlinks.push_back( v );
            all.push_back( v );
            as_paths.push_back( chaos::io::sys::Path( v ) );
        }
        {
            std::vector< chaos::str::UTF8String > v( TEST_PATH );
            v.push_back( "test_dir" );
            v.push_back( "does_not_exist" );
            bad_symlinks.push_back( v );
            all.push_back( v );
            as_paths.push_back( chaos::io::sys::Path( v ) );
        }
    }
};

//------------------------------------------------------------------------------
//                              DEFAULT CONSTRUCTOR
//------------------------------------------------------------------------------

CHAOS_TEST_UNIT( default_constructor )
{
    chaos::io::sys::Path empty;
    CHAOS_CHECK_TRUE( empty.get_components().empty() );
}

//------------------------------------------------------------------------------
//                             COMPONENT CONSTRUCTOR
//------------------------------------------------------------------------------

CHAOS_TEST_UNIT_FIXTURE( component_constructor, PathGenericFixture )
{
    std::vector< chaos::io::sys::Path > paths;
    CHAOS_FOR_EACH( it, fixture->all )
    {
        paths.push_back( chaos::io::sys::Path( *it ) );
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
//                               STRING CONSTRUCTOR
//------------------------------------------------------------------------------

class StringConstructorFixture : public chaos::test::Fixture
{
public:

    //----------------------------PUBLIC ATTRIBUTES-----------------------------

    std::vector< chaos::str::UTF8String > inputs;
    std::vector< chaos::str::UTF8String > results;

    //-------------------------PUBLIC MEMBER FUNCTIONS--------------------------

    virtual void setup()
    {
#ifdef CHAOS_OS_WINDOWS
        const chaos::str::UTF8String sep( "\\" );
#else
        const chaos::str::UTF8String sep( "/" );
#endif

        {
            chaos::str::UTF8String p;
            p << "path" << sep << "to" << sep << "file.txt";
            inputs.push_back( p );
            results.push_back( p );
        }

        {
            chaos::str::UTF8String p;
            p << "longer" << sep << "path" << sep << "to" << sep << "file.txt";
            inputs.push_back( p );
            results.push_back( p );
        }

        {
            chaos::str::UTF8String p;
            p << "even" << sep << "longer" << sep << "path" << sep << "to"
              << sep << "file.txt";
            inputs.push_back( p );
            results.push_back( p );
        }

        {
            chaos::str::UTF8String p;
            p << "path" << sep << "to" << sep << "directory";
            inputs.push_back( p );
            results.push_back( p );
        }

        {
            chaos::str::UTF8String p;
            p << "path" << sep << "to" << sep << "directory" << sep
              << "separator_end";
            results.push_back( p );
            p << sep;
            inputs.push_back( p );
        }

        {
            chaos::str::UTF8String p;
            p << "path" << sep << sep << "with" << sep << "double" << sep << sep
              << "separators";
            inputs.push_back( p );
            chaos::str::UTF8String p2;
            p2 << "path" << sep << "with" << sep << "double" << sep
               << "separators";
            results.push_back( p2 );
        }

        {
            chaos::str::UTF8String p;
            p << sep << "path" << sep << "from" << sep << "root";
            inputs.push_back( p );
            results.push_back( p );
        }

        {
            chaos::str::UTF8String p;
            p << sep << "path" << sep << "from" << sep << "root";
            results.push_back( p );
            p << sep;
            inputs.push_back( p );
        }
    }
};

CHAOS_TEST_UNIT_FIXTURE( string_constructor, StringConstructorFixture )
{
    for( size_t i = 0; i < fixture->inputs.size(); ++i )
    {
        chaos::io::sys::Path p( fixture->inputs[ i ] );
        CHAOS_CHECK_EQUAL( p.to_native(), fixture->results[ i ] );
    }
}


//------------------------------------------------------------------------------
//                                COPY CONSTRUCTOR
//------------------------------------------------------------------------------

CHAOS_TEST_UNIT_FIXTURE( copy_constructor, PathGenericFixture )
{
    std::vector< chaos::io::sys::Path > paths;
    CHAOS_FOR_EACH( it, fixture->all )
    {
        paths.push_back( chaos::io::sys::Path( *it ) );
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

//------------------------------------------------------------------------------
//                              ASSIGNMENT OPERATOR
//------------------------------------------------------------------------------

CHAOS_TEST_UNIT_FIXTURE( assignment_operator, PathGenericFixture )
{
    std::vector< chaos::io::sys::Path > paths;
    CHAOS_FOR_EACH( it, fixture->as_paths )
    {
        chaos::io::sys::Path p;
        p = *it;
        paths.push_back( p );
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

//------------------------------------------------------------------------------
//                               EQUALITY OPERATOR
//------------------------------------------------------------------------------

class EqualityFixture : public chaos::test::Fixture
{
public:

    //----------------------------PUBLIC ATTRIBUTES-----------------------------

    std::vector< chaos::io::sys::Path > match;
    std::vector< chaos::io::sys::Path > mismatch;

    //-------------------------PUBLIC MEMBER FUNCTIONS--------------------------

    virtual void setup()
    {
        {
            chaos::io::sys::Path p1;
            p1 << "path" << "to" << "file.txt";
            match.push_back( p1 );

            chaos::io::sys::Path p2;
            p2 << "longer" << "path" << "to" << "file.txt";
            mismatch.push_back( p2 );
        }

        {
            chaos::io::sys::Path p1;
            p1 << "path" << "to" << "file.txt";
            match.push_back( p1 );

            chaos::io::sys::Path p2;
            p2 << "path1" << "to" << "file.txt";
            mismatch.push_back( p2 );
        }

        {
            chaos::io::sys::Path p1;
            p1 << "path" << "to" << "file.png";
            match.push_back( p1 );

            chaos::io::sys::Path p2;
            p2 << "path" << "to" << "file.txt";
            mismatch.push_back( p2 );
        }

        {
            chaos::io::sys::Path p1;
            p1 << "path" << "to1" << "file.txt";
            match.push_back( p1 );

            chaos::io::sys::Path p2;
            p2 << "path" << "to" << "file.txt";
            mismatch.push_back( p2 );
        }

        {
            chaos::io::sys::Path p1;
            p1 << "path" << "to" << "file.txt";
            match.push_back( p1 );

            chaos::io::sys::Path p2;
            p2 << "path" << "to" << "to" << "file.txt";
            mismatch.push_back( p2 );
        }

        {
            chaos::io::sys::Path p1;
            p1 << "path" << "to" << "file.txt";
            match.push_back( p1 );

            chaos::io::sys::Path p2;
            p2 << "to" << "path" << "file.txt";
            mismatch.push_back( p2 );
        }
    }
};

CHAOS_TEST_UNIT_FIXTURE( equality_operator, EqualityFixture )
{
    CHAOS_FOR_EACH( it, fixture->match )
    {
        chaos::io::sys::Path p( *it );
        CHAOS_CHECK_EQUAL( p, *it );
    }
}

//------------------------------------------------------------------------------
//                              INEQUALITY OPERATOR
//------------------------------------------------------------------------------

CHAOS_TEST_UNIT_FIXTURE( inequality_operator, EqualityFixture )
{
    for ( size_t i = 0; i < fixture->match.size(); ++i )
    {
        CHAOS_CHECK_NOT_EQUAL( fixture->match[ i ], fixture->mismatch[ i ] );
    }
}

//------------------------------------------------------------------------------
//                               LESS THAN OPERATOR
//------------------------------------------------------------------------------

class LessThanFixture : public chaos::test::Fixture
{
public:

    //----------------------------PUBLIC ATTRIBUTES-----------------------------

    std::vector< chaos::io::sys::Path > paths1;
    std::vector< chaos::io::sys::Path > paths2;

    //-------------------------PUBLIC MEMBER FUNCTIONS--------------------------

    virtual void setup()
    {
        {
            chaos::io::sys::Path p1;
            p1 << "path" << "to" << "file.txt";
            paths1.push_back( p1 );

            chaos::io::sys::Path p2;
            p2 << "longer" << "path" << "to" << "file.txt";
            paths2.push_back( p2 );
        }

        {
            chaos::io::sys::Path p1;
            p1 << "path" << "to" << "file.txt";
            paths1.push_back( p1 );

            chaos::io::sys::Path p2;
            p2 << "path1" << "to" << "file.txt";
            paths2.push_back( p2 );
        }

        {
            chaos::io::sys::Path p1;
            p1 << "path" << "to" << "file.png";
            paths1.push_back( p1 );

            chaos::io::sys::Path p2;
            p2 << "path" << "to" << "file.txt";
            paths2.push_back( p2 );
        }

        {
            chaos::io::sys::Path p1;
            p1 << "path" << "to" << "file.txt";
            paths1.push_back( p1 );

            chaos::io::sys::Path p2;
            p2 << "a" << "really" << "long" << "path" << "to" << "file.txt";
            paths2.push_back( p2 );
        }

        {
            chaos::io::sys::Path p1;
            p1 << "path" << "to" << "file.txt";
            paths1.push_back( p1 );

            chaos::io::sys::Path p2;
            p2 << "path" << "to" << "to" << "file.txt";
            paths2.push_back( p2 );
        }

        {
            chaos::io::sys::Path p1;
            p1 << "to" << "path" << "file.txt";
            paths1.push_back( p1 );

            chaos::io::sys::Path p2;
            p2 << "path" << "to" << "file.txt";
            paths2.push_back( p2 );
        }
    }
};

CHAOS_TEST_UNIT_FIXTURE( less_than_operator, LessThanFixture )
{
    for ( size_t i = 0; i < fixture->paths1.size(); ++i )
    {
        CHAOS_CHECK_TRUE ( fixture->paths1[ i ] < fixture->paths2[ i ] );
        CHAOS_CHECK_FALSE( fixture->paths2[ i ] < fixture->paths1[ i ] );
    }
}

//------------------------------------------------------------------------------
//                               SUBSCRIPT OPERATOR
//------------------------------------------------------------------------------

CHAOS_TEST_UNIT_FIXTURE( subscript_operator, PathGenericFixture )
{
    CHAOS_TEST_MESSAGE( "Checking non-const" );
    for ( size_t i = 0; i < fixture->all.size(); ++i )
    {
        chaos::io::sys::Path p( fixture->all[ i ] );
        for ( size_t j = 0; j < fixture->all[ i ].size(); ++j )
        {
            CHAOS_CHECK_EQUAL( p[ j ], fixture->all[ i ][ j ] );
        }

    }
    for ( size_t i = 0; i < fixture->all.size(); ++i )
    {
        chaos::io::sys::Path p( fixture->all[ i ] );
        for ( size_t j = 0; j < fixture->all[ i ].size(); ++j )
        {
            p[ j ] = "now_for_something_completly_different";
            CHAOS_CHECK_NOT_EQUAL( p[ j ], fixture->all[ i ][ j ] );
        }
    }

    CHAOS_TEST_MESSAGE( "Checking const" );
    for ( size_t i = 0; i < fixture->all.size(); ++i )
    {
        const chaos::io::sys::Path p( fixture->all[ i ] );
        for ( size_t j = 0; j < fixture->all[ i ].size(); ++j )
        {
            CHAOS_CHECK_EQUAL( p[ j ], fixture->all[ i ][ j ] );
        }

    }
}

//------------------------------------------------------------------------------
//                               ADDITION OPERATOR
//------------------------------------------------------------------------------

CHAOS_TEST_UNIT_FIXTURE( addition_operator, PathGenericFixture )
{
    std::vector< chaos::io::sys::Path > paths1;
    std::vector< chaos::io::sys::Path > paths2;

    for ( size_t i = 0; i < fixture->all.size(); ++i )
    {
        chaos::io::sys::Path p1;
        chaos::io::sys::Path p2;

        size_t j = 0;
        for ( ; j < fixture->all[ i ].size() / 2; ++j )
        {
            p1 << fixture->all[ i ][ j ];
        }
        for ( ; j < fixture->all[ i ].size(); ++j )
        {
            p2 << fixture->all[ i ][ j ];
        }

        paths1.push_back( p1 );
        paths2.push_back( p2 );
    }

    CHAOS_TEST_MESSAGE( "Checking const addition" );
    for ( size_t i = 0; i < paths1.size(); ++i )
    {
        chaos::io::sys::Path p( paths1[ i ] + paths2[ i ] );
        CHAOS_CHECK_EQUAL( p, fixture->as_paths[ i ] );
    }

    CHAOS_TEST_MESSAGE( "Checking compound addition" );
    for ( size_t i = 0; i < paths1.size(); ++i )
    {
        paths1[ i ] += paths2[ i ];
        CHAOS_CHECK_EQUAL( paths1[ i ], fixture->as_paths[ i ] );
    }
}

//------------------------------------------------------------------------------
//                                 JOIN OPERATOR
//------------------------------------------------------------------------------

