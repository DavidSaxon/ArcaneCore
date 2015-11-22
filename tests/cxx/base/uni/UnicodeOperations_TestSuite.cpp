#include "chaoscore/test/ChaosTest.hpp"

#include "chaoscore/base/uni/UnicodeOperations.hpp"

CHAOS_TEST_MODULE( base.uni.unicode_operations )

//------------------------------------------------------------------------------
//                                 UTF8_IS_DIGIT
//------------------------------------------------------------------------------

class IsDigitFixture : public chaos::test::Fixture
{
public:

    //----------------------------PUBLIC ATTRIBUTES-----------------------------

    std::vector< chaos::uint32 > valid;
    std::vector< chaos::uint32 > invalid;

    //-------------------------PUBLIC MEMBER FUNCTIONS--------------------------

    virtual void setup()
    {
        valid.push_back( '0' );
        valid.push_back( '1' );
        valid.push_back( '2' );
        valid.push_back( '3' );
        valid.push_back( '4' );
        valid.push_back( '5' );
        valid.push_back( '6' );
        valid.push_back( '7' );
        valid.push_back( '8' );
        valid.push_back( '9' );

        invalid.push_back( 'A' );
        invalid.push_back( 'z' );
        invalid.push_back( '!' );
        invalid.push_back( '$' );
        invalid.push_back( '&' );
        invalid.push_back( '_' );
        invalid.push_back( '@' );
        invalid.push_back( 0 );
        invalid.push_back( 1024 );
        invalid.push_back( 2153595 );
    }
};

CHAOS_TEST_UNIT_FIXTURE( is_digit, IsDigitFixture )
{
    CHAOS_TEST_MESSAGE( "Checking valid code points" );
    CHAOS_FOR_EACH( it_1, fixture->valid )
    {
        CHAOS_CHECK_TRUE( chaos::uni::is_digit( *it_1 ) );
    }

    CHAOS_TEST_MESSAGE( "Checking invalid code points" );
    CHAOS_FOR_EACH( it_2, fixture->invalid )
    {
        CHAOS_CHECK_FALSE( chaos::uni::is_digit( *it_2 ) );
    }
}

//------------------------------------------------------------------------------
//                                      JOIN
//------------------------------------------------------------------------------

class JoinFixture : public chaos::test::Fixture
{
public:

    //----------------------------PUBLIC ATTRIBUTES-----------------------------

    std::vector< std::vector< chaos::uni::UTF8String > > components;
    std::vector < chaos::uni::UTF8String > separators;
    std::vector < chaos::uni::UTF8String > results;

    //-------------------------PUBLIC MEMBER FUNCTIONS--------------------------

    virtual void setup()
    {
        {
            std::vector< chaos::uni::UTF8String > c;
            c.push_back( "" );
            components.push_back( c );
            separators.push_back( "!" );
            results.push_back( "" );
        }
        {
            std::vector< chaos::uni::UTF8String > c;
            c.push_back( "Hello" );
            components.push_back( c );
            separators.push_back( "test" );
            results.push_back( "Hello" );
        }
        {
            std::vector< chaos::uni::UTF8String > c;
            c.push_back( "Hello" );
            c.push_back( "World" );
            components.push_back( c );
            separators.push_back( "_" );
            results.push_back( "Hello_World" );
        }
        {
            std::vector< chaos::uni::UTF8String > c;
            c.push_back( "this" );
            c.push_back( "is" );
            c.push_back( "a" );
            c.push_back( "lot" );
            c.push_back( "of components" );
            components.push_back( c );
            separators.push_back( "<separator>" );
            results.push_back(
                    "this<separator>is<separator>a<separator>lot<separator>"
                    "of components"
            );
        }
        {
            std::vector< chaos::uni::UTF8String > c;
            c.push_back( "γειά" );
            c.push_back( "σου" );
            c.push_back( "Κόσμε" );
            components.push_back( c );
            separators.push_back( " " );
            results.push_back( "γειά σου Κόσμε" );
        }
        {
            std::vector< chaos::uni::UTF8String > c;
            c.push_back( "this" );
            c.push_back( "is" );
            c.push_back( "a مزيج" );
            c.push_back( "of text" );
            components.push_back( c );
            separators.push_back( "간" );
            results.push_back( "this간is간a مزيج간of text" );
        }
    }
};

CHAOS_TEST_UNIT_FIXTURE( join, JoinFixture )
{
    for ( size_t i = 0; i < fixture->components.size(); ++i )
    {
        chaos::uni::UTF8String s = chaos::uni::join(
                fixture->components[ i ],
                fixture->separators[ i ]
        );
        CHAOS_CHECK_EQUAL( s, fixture->results[ i ] );
    }
}
