#include "arcanecore/test/ArcTest.hpp"

ARC_TEST_MODULE( io.sys.path )

#include <algorithm>
#include <cstring>

#include "arcanecore/base/str/StringOperations.hpp"
#include "arcanecore/io/sys/Path.hpp"

namespace path_tests
{

//------------------------------------------------------------------------------
//                                GENERIC FIXTURE
//------------------------------------------------------------------------------

class PathGenericFixture : public arc::test::Fixture
{
public:

    //----------------------------PUBLIC ATTRIBUTES-----------------------------

    std::vector< std::vector< arc::str::UTF8String > > all;
    std::vector< arc::str::UTF8String > unix;
    std::vector< arc::str::UTF8String > windows;
    std::vector< arc::str::UTF8String > extensions;
    std::vector< arc::io::sys::Path > as_paths;

    //-------------------------PUBLIC MEMBER FUNCTIONS--------------------------

    virtual void setup()
    {
        {
            std::vector< arc::str::UTF8String > v;
            all.push_back( v );
            unix.push_back( "" );
            windows.push_back( "" );
            extensions.push_back( "" );
            as_paths.push_back( arc::io::sys::Path( v ) );
        }
        {
            std::vector< arc::str::UTF8String > v;
            v.push_back( "test_dir" );
            all.push_back( v );
            unix.push_back( "test_dir" );
            windows.push_back( "test_dir" );
            extensions.push_back( "" );
            as_paths.push_back( arc::io::sys::Path( v ) );
        }
        {
            std::vector< arc::str::UTF8String > v;
            v.push_back( "test_dir" );
            v.push_back( "another_dir" );
            v.push_back( "file.txt" );
            all.push_back( v );
            unix.push_back( "test_dir/another_dir/file.txt" );
            windows.push_back( "test_dir\\another_dir\\file.txt" );
            extensions.push_back( "txt" );
            as_paths.push_back( arc::io::sys::Path( v ) );
        }
        {
            std::vector< arc::str::UTF8String > v;
            v.push_back( "/" );
            v.push_back( "path" );
            v.push_back( "from" );
            v.push_back( "root.png" );
            all.push_back( v );
            unix.push_back( "/path/from/root.png" );
            windows.push_back( "/\\path\\from\\root.png" );
            extensions.push_back( "png" );
            as_paths.push_back( arc::io::sys::Path( v ) );
        }
        {
            std::vector< arc::str::UTF8String > v;
            v.push_back( "~" );
            v.push_back( "path" );
            v.push_back( "from" );
            v.push_back( "home" );
            v.push_back( "dir" );
            all.push_back( v );
            unix.push_back( "~/path/from/home/dir" );
            windows.push_back( "~\\path\\from\\home\\dir" );
            extensions.push_back( "" );
            as_paths.push_back( arc::io::sys::Path( v ) );
        }
        {
            std::vector< arc::str::UTF8String > v;
            v.push_back( "." );
            v.push_back( "current" );
            v.push_back( "dir" );
            v.push_back( "path.jpg" );
            all.push_back( v );
            unix.push_back( "./current/dir/path.jpg" );
            windows.push_back( ".\\current\\dir\\path.jpg" );
            extensions.push_back( "jpg" );
            as_paths.push_back( arc::io::sys::Path( v ) );
        }
        {
            std::vector< arc::str::UTF8String > v;
            v.push_back( ".." );
            v.push_back( ".." );
            v.push_back( "up" );
            v.push_back( "two" );
            v.push_back( "directories" );
            all.push_back( v );
            unix.push_back( "../../up/two/directories" );
            windows.push_back( "..\\..\\up\\two\\directories" );
            extensions.push_back( "" );
            as_paths.push_back( arc::io::sys::Path( v ) );
        }
        {
            std::vector< arc::str::UTF8String > v;
            v.push_back( "path" );
            v.push_back( "with a" );
            v.push_back( "space" );
            v.push_back( "in it.pdf" );
            all.push_back( v );
            unix.push_back( "path/with a/space/in it.pdf" );
            windows.push_back( "path\\with a\\space\\in it.pdf" );
            extensions.push_back( "pdf" );
            as_paths.push_back( arc::io::sys::Path( v ) );
        }
        {
            std::vector< arc::str::UTF8String > v;
            v.push_back( "γειά" );
            v.push_back( "σου" );
            v.push_back( "Κόσμε" );
            all.push_back( v );
            unix.push_back( "γειά/σου/Κόσμε" );
            windows.push_back( "γειά\\σου\\Κόσμε" );
            extensions.push_back( "" );
            as_paths.push_back( arc::io::sys::Path( v ) );
        }
        {
            std::vector< arc::str::UTF8String > v;
            v.push_back( "this" );
            v.push_back( "path" );
            v.push_back( "has a" );
            v.push_back( "مزيج of" );
            v.push_back( "text.간" );
            all.push_back( v );
            unix.push_back( "this/path/has a/مزيج of/text.간" );
            windows.push_back( "this\\path\\has a\\مزيج of\\text.간" );
            extensions.push_back( "간" );
            as_paths.push_back( arc::io::sys::Path( v ) );
        }
    }
};

//------------------------------------------------------------------------------
//                              DEFAULT CONSTRUCTOR
//------------------------------------------------------------------------------

ARC_TEST_UNIT( default_constructor )
{
    arc::io::sys::Path empty;
    ARC_CHECK_TRUE( empty.get_components().empty() );
}

//------------------------------------------------------------------------------
//                             COMPONENT CONSTRUCTOR
//------------------------------------------------------------------------------

ARC_TEST_UNIT_FIXTURE( component_constructor, PathGenericFixture )
{
    std::vector< arc::io::sys::Path > paths;
    ARC_FOR_EACH( it, fixture->all )
    {
        paths.push_back( arc::io::sys::Path( *it ) );
    }

    ARC_TEST_MESSAGE( "Checking internal component lengths" );
    for ( std::size_t i = 0; i < paths.size(); ++i )
    {
        ARC_CHECK_EQUAL(
                paths[ i ].get_components().size(),
                fixture->all[ i ].size()
        );
    }

    ARC_TEST_MESSAGE( "Checking internal components" );
    for ( std::size_t i = 0; i < paths.size(); ++i )
    {
        std::size_t min = std::min(
                paths[ i ].get_components().size(),
                fixture->all[ i ].size()
        );
        for ( std::size_t j = 0; j < min; ++j )
        {
            ARC_CHECK_EQUAL(
                    paths[ i ].get_components()[ j ],
                    fixture->all[ i ][ j ]
            );
        }
    }
}

//------------------------------------------------------------------------------
//                              ITERATOR CONSTRUCTOR
//------------------------------------------------------------------------------

ARC_TEST_UNIT_FIXTURE( iterator_constructor, PathGenericFixture )
{
    std::vector< arc::io::sys::Path > paths;
    ARC_FOR_EACH( it, fixture->all )
    {
        paths.push_back( arc::io::sys::Path( it->begin(), it->end() ) );
    }

    ARC_TEST_MESSAGE( "Checking internal component lengths" );
    for ( std::size_t i = 0; i < paths.size(); ++i )
    {
        ARC_CHECK_EQUAL(
                paths[ i ].get_components().size(),
                fixture->all[ i ].size()
        );
    }

    ARC_TEST_MESSAGE( "Checking internal components" );
    for ( std::size_t i = 0; i < paths.size(); ++i )
    {
        std::size_t min = std::min(
                paths[ i ].get_components().size(),
                fixture->all[ i ].size()
        );
        for ( std::size_t j = 0; j < min; ++j )
        {
            ARC_CHECK_EQUAL(
                    paths[ i ].get_components()[ j ],
                    fixture->all[ i ][ j ]
            );
        }
    }
}

//------------------------------------------------------------------------------
//                               STRING CONSTRUCTOR
//------------------------------------------------------------------------------

class StringConstructorFixture : public arc::test::Fixture
{
public:

    //----------------------------PUBLIC ATTRIBUTES-----------------------------

    std::vector< arc::str::UTF8String > inputs;
    std::vector< arc::str::UTF8String > results;

    //-------------------------PUBLIC MEMBER FUNCTIONS--------------------------

    virtual void setup()
    {
#ifdef ARC_OS_WINDOWS
        const arc::str::UTF8String sep( "\\" );
#else
        const arc::str::UTF8String sep( "/" );
#endif

        {
            arc::str::UTF8String p;
            p << "path" << sep << "to" << sep << "file.txt";
            inputs.push_back( p );
            results.push_back( p );
        }

        {
            arc::str::UTF8String p;
            p << "longer" << sep << "path" << sep << "to" << sep << "file.txt";
            inputs.push_back( p );
            results.push_back( p );
        }

        {
            arc::str::UTF8String p;
            p << "even" << sep << "longer" << sep << "path" << sep << "to"
              << sep << "file.txt";
            inputs.push_back( p );
            results.push_back( p );
        }

        {
            arc::str::UTF8String p;
            p << "path" << sep << "to" << sep << "directory";
            inputs.push_back( p );
            results.push_back( p );
        }

        {
            arc::str::UTF8String p;
            p << "path" << sep << "to" << sep << "directory" << sep
              << "separator_end";
            results.push_back( p );
            p << sep;
            inputs.push_back( p );
        }

        {
            arc::str::UTF8String p;
            p << "path" << sep << sep << "with" << sep << "double" << sep << sep
              << "separators";
            inputs.push_back( p );
            arc::str::UTF8String p2;
            p2 << "path" << sep << "with" << sep << "double" << sep
               << "separators";
            results.push_back( p2 );
        }

        {
            arc::str::UTF8String p;
            p << "path" << sep << sep << sep << sep << "with" << sep << sep
              << sep << "lots" << sep << sep << "of" << sep << "separators";
            inputs.push_back( p );
            arc::str::UTF8String p2;
            p2 << "path" << sep << "with" << sep << "lots" << sep << "of" << sep
               << "separators";
            results.push_back( p2 );
        }

        {
            arc::str::UTF8String p;
            p << sep << "path" << sep << "from" << sep << "root";
            inputs.push_back( p );
            results.push_back( p );
        }

        {
            arc::str::UTF8String p;
            p << sep << "path" << sep << "from" << sep << "root";
            results.push_back( p );
            p << sep;
            inputs.push_back( p );
        }
    }
};

ARC_TEST_UNIT_FIXTURE( string_constructor, StringConstructorFixture )
{
    for( std::size_t i = 0; i < fixture->inputs.size(); ++i )
    {
        arc::io::sys::Path p( fixture->inputs[ i ] );
        ARC_CHECK_EQUAL( p.to_native(), fixture->results[ i ] );
    }
}


//------------------------------------------------------------------------------
//                                COPY CONSTRUCTOR
//------------------------------------------------------------------------------

ARC_TEST_UNIT_FIXTURE( copy_constructor, PathGenericFixture )
{
    std::vector< arc::io::sys::Path > paths;
    ARC_FOR_EACH( it, fixture->all )
    {
        paths.push_back( arc::io::sys::Path( *it ) );
    }

    ARC_TEST_MESSAGE( "Checking internal component lengths" );
    for ( std::size_t i = 0; i < paths.size(); ++i )
    {
        ARC_CHECK_EQUAL(
                paths[ i ].get_components().size(),
                fixture->as_paths[ i ].get_components().size()
        );
    }

    ARC_TEST_MESSAGE( "Checking internal components" );
    for ( std::size_t i = 0; i < paths.size(); ++i )
    {
        std::size_t min = std::min(
                paths[ i ].get_components().size(),
                fixture->as_paths[ i ].get_components().size()
        );
        for ( std::size_t j = 0; j < min; ++j )
        {
            ARC_CHECK_EQUAL(
                    paths[ i ].get_components()[ j ],
                    fixture->as_paths[ i ].get_components()[ j ]
            );
        }
    }
}

//------------------------------------------------------------------------------
//                              ASSIGNMENT OPERATOR
//------------------------------------------------------------------------------

ARC_TEST_UNIT_FIXTURE( assignment_operator, PathGenericFixture )
{
    std::vector< arc::io::sys::Path > paths;
    ARC_FOR_EACH( it, fixture->as_paths )
    {
        arc::io::sys::Path p;
        p = *it;
        paths.push_back( p );
    }

    ARC_TEST_MESSAGE( "Checking internal component lengths" );
    for ( std::size_t i = 0; i < paths.size(); ++i )
    {
        ARC_CHECK_EQUAL(
                paths[ i ].get_components().size(),
                fixture->as_paths[ i ].get_components().size()
        );
    }

    ARC_TEST_MESSAGE( "Checking internal components" );
    for ( std::size_t i = 0; i < paths.size(); ++i )
    {
        std::size_t min = std::min(
                paths[ i ].get_components().size(),
                fixture->as_paths[ i ].get_components().size()
        );
        for ( std::size_t j = 0; j < min; ++j )
        {
            ARC_CHECK_EQUAL(
                    paths[ i ].get_components()[ j ],
                    fixture->as_paths[ i ].get_components()[ j ]
            );
        }
    }
}

//------------------------------------------------------------------------------
//                               EQUALITY OPERATOR
//------------------------------------------------------------------------------

class EqualityFixture : public arc::test::Fixture
{
public:

    //----------------------------PUBLIC ATTRIBUTES-----------------------------

    std::vector< arc::io::sys::Path > match;
    std::vector< arc::io::sys::Path > mismatch;

    //-------------------------PUBLIC MEMBER FUNCTIONS--------------------------

    virtual void setup()
    {
        {
            arc::io::sys::Path p1;
            p1 << "path" << "to" << "file.txt";
            match.push_back( p1 );

            arc::io::sys::Path p2;
            p2 << "longer" << "path" << "to" << "file.txt";
            mismatch.push_back( p2 );
        }

        {
            arc::io::sys::Path p1;
            p1 << "path" << "to" << "file.txt";
            match.push_back( p1 );

            arc::io::sys::Path p2;
            p2 << "path1" << "to" << "file.txt";
            mismatch.push_back( p2 );
        }

        {
            arc::io::sys::Path p1;
            p1 << "path" << "to" << "file.png";
            match.push_back( p1 );

            arc::io::sys::Path p2;
            p2 << "path" << "to" << "file.txt";
            mismatch.push_back( p2 );
        }

        {
            arc::io::sys::Path p1;
            p1 << "path" << "to1" << "file.txt";
            match.push_back( p1 );

            arc::io::sys::Path p2;
            p2 << "path" << "to" << "file.txt";
            mismatch.push_back( p2 );
        }

        {
            arc::io::sys::Path p1;
            p1 << "path" << "to" << "file.txt";
            match.push_back( p1 );

            arc::io::sys::Path p2;
            p2 << "path" << "to" << "to" << "file.txt";
            mismatch.push_back( p2 );
        }

        {
            arc::io::sys::Path p1;
            p1 << "path" << "to" << "file.txt";
            match.push_back( p1 );

            arc::io::sys::Path p2;
            p2 << "to" << "path" << "file.txt";
            mismatch.push_back( p2 );
        }
    }
};

ARC_TEST_UNIT_FIXTURE( equality_operator, EqualityFixture )
{
    ARC_FOR_EACH( it, fixture->match )
    {
        arc::io::sys::Path p( *it );
        ARC_CHECK_EQUAL( p, *it );
    }
    for ( std::size_t i = 0; i < fixture->match.size(); ++i )
    {
        ARC_CHECK_FALSE( ( fixture->match[ i ] == fixture->mismatch[ i ] ) );
    }
}

//------------------------------------------------------------------------------
//                              INEQUALITY OPERATOR
//------------------------------------------------------------------------------

ARC_TEST_UNIT_FIXTURE( inequality_operator, EqualityFixture )
{
    for ( std::size_t i = 0; i < fixture->match.size(); ++i )
    {
        ARC_CHECK_NOT_EQUAL( fixture->match[ i ], fixture->mismatch[ i ] );
    }
    for ( std::size_t i = 0; i < fixture->match.size(); ++i )
    {
        ARC_CHECK_FALSE( fixture->match[ i ] != fixture->match[ i ] );
    }
}

//------------------------------------------------------------------------------
//                               LESS THAN OPERATOR
//------------------------------------------------------------------------------

class LessThanFixture : public arc::test::Fixture
{
public:

    //----------------------------PUBLIC ATTRIBUTES-----------------------------

    std::vector< arc::io::sys::Path > paths1;
    std::vector< arc::io::sys::Path > paths2;

    //-------------------------PUBLIC MEMBER FUNCTIONS--------------------------

    virtual void setup()
    {
        {
            arc::io::sys::Path p1;
            p1 << "path" << "to" << "file.txt";
            paths1.push_back( p1 );

            arc::io::sys::Path p2;
            p2 << "longer" << "path" << "to" << "file.txt";
            paths2.push_back( p2 );
        }

        {
            arc::io::sys::Path p1;
            p1 << "path" << "to" << "file.txt";
            paths1.push_back( p1 );

            arc::io::sys::Path p2;
            p2 << "path1" << "to" << "file.txt";
            paths2.push_back( p2 );
        }

        {
            arc::io::sys::Path p1;
            p1 << "path" << "to" << "file.png";
            paths1.push_back( p1 );

            arc::io::sys::Path p2;
            p2 << "path" << "to" << "file.txt";
            paths2.push_back( p2 );
        }

        {
            arc::io::sys::Path p1;
            p1 << "path" << "to" << "file.txt";
            paths1.push_back( p1 );

            arc::io::sys::Path p2;
            p2 << "a" << "really" << "long" << "path" << "to" << "file.txt";
            paths2.push_back( p2 );
        }

        {
            arc::io::sys::Path p1;
            p1 << "path" << "to" << "file.txt";
            paths1.push_back( p1 );

            arc::io::sys::Path p2;
            p2 << "path" << "to" << "to" << "file.txt";
            paths2.push_back( p2 );
        }

        {
            arc::io::sys::Path p1;
            p1 << "path" << "to" << "file.txt";
            paths1.push_back( p1 );

            arc::io::sys::Path p2;
            p2 << "to" << "path" << "file.txt";
            paths2.push_back( p2 );
        }
    }
};

ARC_TEST_UNIT_FIXTURE( less_than_operator, LessThanFixture )
{
    ARC_TEST_MESSAGE( "Checking less than cases" );
    for ( std::size_t i = 0; i < fixture->paths1.size(); ++i )
    {
        ARC_CHECK_TRUE ( fixture->paths1[ i ] < fixture->paths2[ i ] );
    }

    ARC_TEST_MESSAGE( "Checking greater than cases" );
    for ( std::size_t i = 0; i < fixture->paths1.size(); ++i )
    {
        ARC_CHECK_FALSE( fixture->paths2[ i ] < fixture->paths1[ i ] );
    }

    ARC_TEST_MESSAGE( "Checking equals cases" );
    for ( std::size_t i = 0; i < fixture->paths1.size(); ++i )
    {
        ARC_CHECK_FALSE( fixture->paths1[ i ] < fixture->paths1[ i ] );
    }
    for ( std::size_t i = 0; i < fixture->paths2.size(); ++i )
    {
        ARC_CHECK_FALSE( fixture->paths2[ i ] < fixture->paths2[ i ] );
    }
}

//------------------------------------------------------------------------------
//                               SUBSCRIPT OPERATOR
//------------------------------------------------------------------------------

ARC_TEST_UNIT_FIXTURE( subscript_operator, PathGenericFixture )
{
    ARC_TEST_MESSAGE( "Checking non-const" );
    for ( std::size_t i = 0; i < fixture->all.size(); ++i )
    {
        arc::io::sys::Path p( fixture->all[ i ] );
        for ( std::size_t j = 0; j < fixture->all[ i ].size(); ++j )
        {
            ARC_CHECK_EQUAL( p[ j ], fixture->all[ i ][ j ] );
        }

    }
    for ( std::size_t i = 0; i < fixture->all.size(); ++i )
    {
        arc::io::sys::Path p( fixture->all[ i ] );
        for ( std::size_t j = 0; j < fixture->all[ i ].size(); ++j )
        {
            p[ j ] = "now_for_something_completly_different";
            ARC_CHECK_NOT_EQUAL( p[ j ], fixture->all[ i ][ j ] );
        }
    }

    ARC_TEST_MESSAGE( "Checking const" );
    for ( std::size_t i = 0; i < fixture->all.size(); ++i )
    {
        const arc::io::sys::Path p( fixture->all[ i ] );
        for ( std::size_t j = 0; j < fixture->all[ i ].size(); ++j )
        {
            ARC_CHECK_EQUAL( p[ j ], fixture->all[ i ][ j ] );
        }

    }
}

//------------------------------------------------------------------------------
//                               ADDITION OPERATOR
//------------------------------------------------------------------------------

ARC_TEST_UNIT_FIXTURE( addition_operator, PathGenericFixture )
{
    std::vector< arc::io::sys::Path > paths1;
    std::vector< arc::io::sys::Path > paths2;

    for ( std::size_t i = 0; i < fixture->all.size(); ++i )
    {
        arc::io::sys::Path p1;
        arc::io::sys::Path p2;

        std::size_t j = 0;
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

    ARC_TEST_MESSAGE( "Checking const addition" );
    for ( std::size_t i = 0; i < paths1.size(); ++i )
    {
        arc::io::sys::Path p( paths1[ i ] + paths2[ i ] );
        ARC_CHECK_EQUAL( p, fixture->as_paths[ i ] );
    }

    ARC_TEST_MESSAGE( "Checking compound addition" );
    for ( std::size_t i = 0; i < paths1.size(); ++i )
    {
        paths1[ i ] += paths2[ i ];
        ARC_CHECK_EQUAL( paths1[ i ], fixture->as_paths[ i ] );
    }
}

//------------------------------------------------------------------------------
//                                 JOIN OPERATOR
//------------------------------------------------------------------------------

ARC_TEST_UNIT_FIXTURE( join_operator, PathGenericFixture )
{
    ARC_TEST_MESSAGE( "Checking individual calls" );
    for ( std::size_t i = 0; i < fixture->all.size(); ++i )
    {
        arc::io::sys::Path p;
        ARC_FOR_EACH( it, fixture->all[ i ] )
        {
            p << *it;
        }

        ARC_CHECK_EQUAL( p, fixture->as_paths[ i ] );
    }

    ARC_TEST_MESSAGE( "Checking compound calls" );
    for ( std::size_t i = 0; i < fixture->all.size(); ++i )
    {
        arc::io::sys::Path p;

        if ( fixture->all[ i ].size() == 1 )
        {
            p << fixture->all[ i ][ 0 ];
        }
        else if ( fixture->all[ i ].size() == 2 )
        {
            p << fixture->all[ i ][ 0 ] << fixture->all[ i ][ 1 ];
        }
        else if ( fixture->all[ i ].size() == 3 )
        {
            p << fixture->all[ i ][ 0 ] << fixture->all[ i ][ 1 ]
              << fixture->all[ i ][ 2 ];
        }
        else if ( fixture->all[ i ].size() == 4 )
        {
            p << fixture->all[ i ][ 0 ] << fixture->all[ i ][ 1 ]
              << fixture->all[ i ][ 2 ] << fixture->all[ i ][ 3 ];
        }
        else if ( fixture->all[ i ].size() == 5 )
        {
            p << fixture->all[ i ][ 0 ] << fixture->all[ i ][ 1 ]
              << fixture->all[ i ][ 2 ] << fixture->all[ i ][ 3 ]
              << fixture->all[ i ][ 4 ];
        }
        else if ( fixture->all[ i ].size() == 6 )
        {
            p << fixture->all[ i ][ 0 ] << fixture->all[ i ][ 1 ]
              << fixture->all[ i ][ 2 ] << fixture->all[ i ][ 3 ]
              << fixture->all[ i ][ 4 ] << fixture->all[ i ][ 5 ];
        }

        ARC_CHECK_EQUAL( p, fixture->as_paths[ i ] );
    }
}

//------------------------------------------------------------------------------
//                                      JOIN
//------------------------------------------------------------------------------

ARC_TEST_UNIT_FIXTURE( join, PathGenericFixture )
{
    ARC_TEST_MESSAGE( "Checking individual calls" );
    for ( std::size_t i = 0; i < fixture->all.size(); ++i )
    {
        arc::io::sys::Path p;
        ARC_FOR_EACH( it, fixture->all[ i ] )
        {
            p.join( *it );
        }

        ARC_CHECK_EQUAL( p, fixture->as_paths[ i ] );
    }

    ARC_TEST_MESSAGE( "Checking compound calls" );
    for ( std::size_t i = 0; i < fixture->all.size(); ++i )
    {
        arc::io::sys::Path p;

        if ( fixture->all[ i ].size() == 1 )
        {
            p.join( fixture->all[ i ][ 0 ] );
        }
        else if ( fixture->all[ i ].size() == 2 )
        {
            p.join( fixture->all[ i ][ 0 ] ).join( fixture->all[ i ][ 1 ] );
        }
        else if ( fixture->all[ i ].size() == 3 )
        {
            p.join( fixture->all[ i ][ 0 ] ).join( fixture->all[ i ][ 1 ] )
             .join( fixture->all[ i ][ 2 ] );
        }
        else if ( fixture->all[ i ].size() == 4 )
        {
            p.join( fixture->all[ i ][ 0 ] ).join( fixture->all[ i ][ 1 ] )
             .join( fixture->all[ i ][ 2 ] ).join( fixture->all[ i ][ 3 ] );
        }
        else if ( fixture->all[ i ].size() == 5 )
        {
            p.join( fixture->all[ i ][ 0 ] ).join( fixture->all[ i ][ 1 ] )
             .join( fixture->all[ i ][ 2 ] ).join( fixture->all[ i ][ 3 ] )
             .join( fixture->all[ i ][ 4 ] );
        }
        else if ( fixture->all[ i ].size() == 6 )
        {
            p.join( fixture->all[ i ][ 0 ] ).join( fixture->all[ i ][ 1 ] )
             .join( fixture->all[ i ][ 2 ] ).join( fixture->all[ i ][ 3 ] )
             .join( fixture->all[ i ][ 4 ] ).join( fixture->all[ i ][ 5 ] );
        }

        ARC_CHECK_EQUAL( p, fixture->as_paths[ i ] );
    }
}

//------------------------------------------------------------------------------
//                                     INSERT
//------------------------------------------------------------------------------

ARC_TEST_UNIT_FIXTURE( insert, PathGenericFixture )
{
    ARC_TEST_MESSAGE( "Checking insert at beginning" );
    for ( std::size_t i = 0; i < fixture->all.size(); ++i )
    {
        arc::io::sys::Path p;
        for ( std::size_t j = fixture->all[ i ].size(); j > 0; --j )
        {
            p.insert( 0, fixture->all[ i ][ j - 1 ] );
        }
        ARC_CHECK_EQUAL( p, fixture->as_paths[ i ] );
    }

    ARC_TEST_MESSAGE( "Checking insert at end" );
    for ( std::size_t i = 0; i < fixture->all.size(); ++i )
    {
        arc::io::sys::Path p;
        for ( std::size_t j = 0; j < fixture->all[ i ].size(); ++j )
        {
            p.insert( j, fixture->all[ i ][ j ] );
        }
        ARC_CHECK_EQUAL( p, fixture->as_paths[ i ] );
    }

    ARC_TEST_MESSAGE( "Checking out of bounds" );
    for ( std::size_t i = 0; i < fixture->all.size(); ++i )
    {
        arc::io::sys::Path p;
        for ( std::size_t j = 0; j < fixture->all[ i ].size() / 2; ++j )
        {
            p.insert( j, fixture->all[ i ][ j ] );
        }

        ARC_CHECK_THROW(
                p.insert( ( fixture->all[ i ].size() * 2 ) + 1, "." ),
                arc::ex::IndexOutOfBoundsError
        );
    }
}

//------------------------------------------------------------------------------
//                                     CLEAR
//------------------------------------------------------------------------------

ARC_TEST_UNIT_FIXTURE( clear, PathGenericFixture )
{
    ARC_FOR_EACH( it, fixture->as_paths )
    {
        it->clear();
        ARC_CHECK_EQUAL(
                it->get_components().size(),
                static_cast< std::size_t >( 0 )
        );
    }
}

//------------------------------------------------------------------------------
//                                     REMOVE
//------------------------------------------------------------------------------

ARC_TEST_UNIT_FIXTURE( remove, PathGenericFixture )
{
    ARC_TEST_MESSAGE( "Checking remove at beginning" );
    for ( std::size_t i = 0; i < fixture->all.size(); ++i )
    {
        if ( fixture->all[ i ].size() == 0 )
        {
            continue;
        }

        arc::io::sys::Path p( fixture->all[ i ] );
        for ( std::size_t j = 0; j < fixture->all[ i ].size(); ++j )
        {
            p.remove( 0 );
            ARC_CHECK_EQUAL(
                    p.get_components().size(),
                    fixture->all[ i ].size() - ( j + 1 )
            );
        }
    }
    for ( std::size_t i = 0; i < fixture->all.size(); ++i )
    {
        if ( fixture->all[ i ].size() == 0 )
        {
            continue;
        }

        arc::io::sys::Path p( fixture->all[ i ] );
        for ( std::size_t j = 0; j < fixture->all[ i ].size() - 1; ++j )
        {
            p.remove( 0 );
            ARC_CHECK_EQUAL(
                    p.get_components()[ 0 ],
                    fixture->all[ i ][ j + 1 ]
            );
        }
    }

    ARC_TEST_MESSAGE( "Checking remove at end" );
    for ( std::size_t i = 0; i < fixture->all.size(); ++i )
    {
        if ( fixture->all[ i ].size() == 0 )
        {
            continue;
        }

        arc::io::sys::Path p( fixture->all[ i ] );
        for ( std::size_t j = fixture->all[ i ].size(); j > 0; --j )
        {
            p.remove( j - 1 );
            ARC_CHECK_EQUAL(
                    p.get_components().size(),
                    ( j - 1 )
            );
        }
    }
    for ( std::size_t i = 0; i < fixture->all.size(); ++i )
    {
        if ( fixture->all[ i ].size() == 0 )
        {
            continue;
        }

        arc::io::sys::Path p( fixture->all[ i ] );
        for ( std::size_t j = fixture->all[ i ].size(); j > 1; --j )
        {
            p.remove( j - 1 );
            ARC_CHECK_EQUAL(
                    p.get_components()[ j - 2 ],
                    fixture->all[ i ][ j - 2 ]
            );
        }
    }

    ARC_TEST_MESSAGE( "Checking out of bounds" );
    for ( std::size_t i = 0; i < fixture->all.size(); ++i )
    {
        if ( fixture->all[ i ].size() == 0 )
        {
            continue;
        }

        arc::io::sys::Path p( fixture->all[ i ] );
        ARC_CHECK_THROW(
                p.remove( fixture->all[ i ].size() ),
                arc::ex::IndexOutOfBoundsError
        );
    }
    for ( std::size_t i = 0; i < fixture->all.size(); ++i )
    {
        if ( fixture->all[ i ].size() == 0 )
        {
            continue;
        }

        arc::io::sys::Path p( fixture->all[ i ] );
        ARC_CHECK_THROW(
                p.remove( fixture->all[ i ].size() * 67 ),
                arc::ex::IndexOutOfBoundsError
        );
    }
}

//------------------------------------------------------------------------------
//                                   TO NATIVE
//------------------------------------------------------------------------------

ARC_TEST_UNIT_FIXTURE( to_native, PathGenericFixture )
{
    for ( std::size_t i = 0; i < fixture->all.size(); ++i )
    {
#ifdef ARC_OS_WINDOWS

        ARC_CHECK_EQUAL(
                fixture->as_paths[ i ].to_native(),
                fixture->windows[ i ]
        );

#else

        ARC_CHECK_EQUAL(
                fixture->as_paths[ i ].to_native(),
                fixture->unix[ i ]
        );

#endif
    }
}

//------------------------------------------------------------------------------
//                                    TO UNIX
//------------------------------------------------------------------------------

ARC_TEST_UNIT_FIXTURE( to_unix, PathGenericFixture )
{
    for ( std::size_t i = 0; i < fixture->all.size(); ++i )
    {
        ARC_CHECK_EQUAL(
                fixture->as_paths[ i ].to_unix(),
                fixture->unix[ i ]
        );
    }
}

//------------------------------------------------------------------------------
//                                   TO WINDOWS
//------------------------------------------------------------------------------

ARC_TEST_UNIT_FIXTURE( to_windows, PathGenericFixture )
{
    for ( std::size_t i = 0; i < fixture->all.size(); ++i )
    {
        ARC_CHECK_EQUAL(
                fixture->as_paths[ i ].to_windows(),
                fixture->windows[ i ]
        );
    }
}

//------------------------------------------------------------------------------
//                                   GET LENGTH
//------------------------------------------------------------------------------


ARC_TEST_UNIT_FIXTURE( get_length, PathGenericFixture )
{
    for ( std::size_t i = 0; i < fixture->all.size(); ++i )
    {
        ARC_CHECK_EQUAL(
                fixture->as_paths[ i ].get_length(),
                fixture->all[ i ].size()
        );
    }
}

//------------------------------------------------------------------------------
//                                    IS EMPTY
//------------------------------------------------------------------------------


class IsEmptyFixture : public arc::test::Fixture
{
public:

    //----------------------------PUBLIC ATTRIBUTES-----------------------------

    std::vector< arc::io::sys::Path > empty;
    std::vector< arc::io::sys::Path > not_empty;

    //-------------------------PUBLIC MEMBER FUNCTIONS--------------------------

    virtual void setup()
    {
        {
            arc::io::sys::Path p;
            empty.push_back( p );
        }

        {
            arc::io::sys::Path p;
            p << ".";
            not_empty.push_back( p );
        }
        {
            arc::io::sys::Path p;
            p << "..";
            not_empty.push_back( p );
        }
        {
            arc::io::sys::Path p;
            p << ".this" << "path" << "is" << "not" << "empty";
            not_empty.push_back( p );
        }
    }
};

ARC_TEST_UNIT_FIXTURE( is_empty, IsEmptyFixture )
{
    ARC_TEST_MESSAGE( "Checking empty paths" );
    ARC_FOR_EACH( it_1, fixture->empty )
    {
        ARC_CHECK_TRUE( it_1->is_empty() );
    }

    ARC_TEST_MESSAGE( "Checking non-empty paths" );
    ARC_FOR_EACH( it_2, fixture->not_empty )
    {
        ARC_CHECK_FALSE( it_2->is_empty() );
    }
}

//------------------------------------------------------------------------------
//                                 GET COMPONENTS
//------------------------------------------------------------------------------

ARC_TEST_UNIT_FIXTURE( get_components, PathGenericFixture )
{
    for ( std::size_t i = 0; i < fixture->all.size(); ++i )
    {
        for ( std::size_t j = 0; j < fixture->all[ i ].size(); ++j )
        {
            ARC_CHECK_EQUAL(
                    fixture->as_paths[ i ].get_components()[ j ],
                    fixture->all[ i ][ j ]
            );
        }
    }
}

//------------------------------------------------------------------------------
//                                   GET FRONT
//------------------------------------------------------------------------------

ARC_TEST_UNIT_FIXTURE( get_front, PathGenericFixture )
{
    ARC_TEST_MESSAGE( "Check valid cases" );
    for( std::size_t i = 0; i < fixture->as_paths.size(); ++i )
    {
        if ( fixture->as_paths[ i ].is_empty() )
        {
            continue;
        }

        ARC_CHECK_EQUAL(
                fixture->as_paths[ i ].get_front(),
                fixture->all[ i ].front()
        );
    }

    ARC_TEST_MESSAGE( "Checking IndexOutOfBoundsError" );
    arc::io::sys::Path p;
    ARC_CHECK_THROW( p.get_front(), arc::ex::IndexOutOfBoundsError );
}

//------------------------------------------------------------------------------
//                                    GET BACK
//------------------------------------------------------------------------------

ARC_TEST_UNIT_FIXTURE( get_back, PathGenericFixture )
{
    ARC_TEST_MESSAGE( "Check valid cases" );
    for( std::size_t i = 0; i < fixture->as_paths.size(); ++i )
    {
        if ( fixture->as_paths[ i ].is_empty() )
        {
            continue;
        }

        ARC_CHECK_EQUAL(
                fixture->as_paths[ i ].get_back(),
                fixture->all[ i ].back()
        );
    }

    ARC_TEST_MESSAGE( "Checking IndexOutOfBoundsError" );
    arc::io::sys::Path p;
    ARC_CHECK_THROW( p.get_back(), arc::ex::IndexOutOfBoundsError );
}

//------------------------------------------------------------------------------
//                                 GET EXTENSION
//------------------------------------------------------------------------------

ARC_TEST_UNIT_FIXTURE( get_extension, PathGenericFixture )
{
    for ( std::size_t i = 0; i < fixture->all.size(); ++i )
    {
        ARC_CHECK_EQUAL(
                fixture->as_paths[ i ].get_extension(),
                fixture->extensions[ i ]
        );
    }
}

} // namespace path_tests
