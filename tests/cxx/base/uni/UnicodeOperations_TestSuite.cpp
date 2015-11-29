#include "chaoscore/test/ChaosTest.hpp"

CHAOS_TEST_MODULE( base.uni.unicode_operations )

#include <cstring>

#include "chaoscore/base/uni/UnicodeOperations.hpp"

namespace unicode_operations_tests
{

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
//                                 UTF8 TO UTF16
//------------------------------------------------------------------------------

class UTF8ToUTF16Fixture : public chaos::test::Fixture
{
public:

    //----------------------------PUBLIC ATTRIBUTES-----------------------------

    std::vector< chaos::uni::UTF8String >       utf8;
    std::vector< std::vector< unsigned char > > utf16;
    std::vector< size_t >                       lengths;

    //-------------------------PUBLIC MEMBER FUNCTIONS--------------------------

    virtual void setup()
    {
        {
            utf8.push_back( "" );
            std::vector< unsigned char > u;
            u.push_back( 0x00 ); u.push_back( 0x00 );
            utf16.push_back( u );
            lengths.push_back( 2 );
        }

        {
            utf8.push_back( "a" );
            std::vector< unsigned char > u;
            u.push_back( 0x00 ); u.push_back( 0x61 ); // a
            u.push_back( 0x00 ); u.push_back( 0x00 );
            utf16.push_back( u );
            lengths.push_back( 4 );
        }

        {
            utf8.push_back( "Hello World" );
            std::vector< unsigned char > u;
            u.push_back( 0x00 ); u.push_back( 0x48 ); // H
            u.push_back( 0x00 ); u.push_back( 0x65 ); // e
            u.push_back( 0x00 ); u.push_back( 0x6C ); // l
            u.push_back( 0x00 ); u.push_back( 0x6C ); // l
            u.push_back( 0x00 ); u.push_back( 0x6F ); // o
            u.push_back( 0x00 ); u.push_back( 0x20 ); // [space]
            u.push_back( 0x00 ); u.push_back( 0x57 ); // W
            u.push_back( 0x00 ); u.push_back( 0x6F ); // o
            u.push_back( 0x00 ); u.push_back( 0x72 ); // r
            u.push_back( 0x00 ); u.push_back( 0x6C ); // l
            u.push_back( 0x00 ); u.push_back( 0x64 ); // d
            u.push_back( 0x00 ); u.push_back( 0x00 );
            utf16.push_back( u );
            lengths.push_back( 24 );
        }

        {
            utf8.push_back( "γειά σου Κόσμε" );
            std::vector< unsigned char > u;
            u.push_back( 0x03 ); u.push_back( 0xB3 ); // γ
            u.push_back( 0x03 ); u.push_back( 0xB5 ); // ε
            u.push_back( 0x03 ); u.push_back( 0xB9 ); // ι
            u.push_back( 0x03 ); u.push_back( 0xAC ); // ά
            u.push_back( 0x00 ); u.push_back( 0x20 ); // [space]
            u.push_back( 0x03 ); u.push_back( 0xC3 ); // σ
            u.push_back( 0x03 ); u.push_back( 0xBF ); // ο
            u.push_back( 0x03 ); u.push_back( 0xC5 ); // υ
            u.push_back( 0x00 ); u.push_back( 0x20 ); // [space]
            u.push_back( 0x03 ); u.push_back( 0x9A ); // Κ
            u.push_back( 0x03 ); u.push_back( 0xCC ); // ό
            u.push_back( 0x03 ); u.push_back( 0xC3 ); // σ
            u.push_back( 0x03 ); u.push_back( 0xBC ); // μ
            u.push_back( 0x03 ); u.push_back( 0xB5 ); // ε
            u.push_back( 0x00 ); u.push_back( 0x00 );
            utf16.push_back( u );
            lengths.push_back( 30 );
        }

        {
            utf8.push_back( "this is a مزيج of text" );
            std::vector< unsigned char > u;
            u.push_back( 0x00 ); u.push_back( 0x74 ); // t
            u.push_back( 0x00 ); u.push_back( 0x68 ); // h
            u.push_back( 0x00 ); u.push_back( 0x69 ); // i
            u.push_back( 0x00 ); u.push_back( 0x73 ); // s
            u.push_back( 0x00 ); u.push_back( 0x20 ); // [space]
            u.push_back( 0x00 ); u.push_back( 0x69 ); // i
            u.push_back( 0x00 ); u.push_back( 0x73 ); // s
            u.push_back( 0x00 ); u.push_back( 0x20 ); // [space]
            u.push_back( 0x00 ); u.push_back( 0x61 ); // q
            u.push_back( 0x00 ); u.push_back( 0x20 ); // [space]
            u.push_back( 0x06 ); u.push_back( 0x45 ); // م
            u.push_back( 0x06 ); u.push_back( 0x32 ); // ز
            u.push_back( 0x06 ); u.push_back( 0x4A ); // ي
            u.push_back( 0x06 ); u.push_back( 0x2C ); // ج
            u.push_back( 0x00 ); u.push_back( 0x20 ); // [space]
            u.push_back( 0x00 ); u.push_back( 0x6F ); // o
            u.push_back( 0x00 ); u.push_back( 0x66 ); // f
            u.push_back( 0x00 ); u.push_back( 0x20 ); // [space]
            u.push_back( 0x00 ); u.push_back( 0x74 ); // t
            u.push_back( 0x00 ); u.push_back( 0x65 ); // e
            u.push_back( 0x00 ); u.push_back( 0x78 ); // x
            u.push_back( 0x00 ); u.push_back( 0x74 ); // t
            u.push_back( 0x00 ); u.push_back( 0x00 );
            utf16.push_back( u );
            lengths.push_back( 46 );
        }

        {
            utf8.push_back( "간" );
            std::vector< unsigned char > u;
            u.push_back( 0xAC ); u.push_back( 0x04 ); // 간
            u.push_back( 0x00 ); u.push_back( 0x00 );
            utf16.push_back( u );
            lengths.push_back( 4 );
        }
    }
};

CHAOS_TEST_UNIT_FIXTURE( utf8_to_utf16, UTF8ToUTF16Fixture )
{
    CHAOS_TEST_MESSAGE( "Checking returned length" );
    for( size_t i = 0; i < fixture->utf8.size(); ++i )
    {
        size_t length = 0;
        const char* u = chaos::uni::utf8_to_utf16(
                fixture->utf8[ i ], length );
        CHAOS_CHECK_EQUAL( length, fixture->lengths [ i ] );
        delete[] u;
    }

    CHAOS_TEST_MESSAGE( "Checking contents" );
    for( size_t i = 0; i < fixture->utf8.size(); ++i )
    {
        size_t length = 0;
        const char* u = chaos::uni::utf8_to_utf16(
                fixture->utf8[ i ], length );
        CHAOS_CHECK_EQUAL(
                memcmp(
                        u,
                        reinterpret_cast< const char* >(
                                &fixture->utf16[ i ][ 0 ] ),
                        length
                ),
                0
        );
        delete[] u;
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

} // namespace unicode_operations_tests
