#include "chaoscore/test/ChaosTest.hpp"

CHAOS_TEST_MODULE(base.str.StringOperations)

#include <cstring>

#include "chaoscore/base/str/StringOperations.hpp"

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
        CHAOS_CHECK_TRUE( chaos::str::is_digit( *it_1 ) );
    }

    CHAOS_TEST_MESSAGE( "Checking invalid code points" );
    CHAOS_FOR_EACH( it_2, fixture->invalid )
    {
        CHAOS_CHECK_FALSE( chaos::str::is_digit( *it_2 ) );
    }
}

//------------------------------------------------------------------------------
//                                 UTF8 TO UTF16
//------------------------------------------------------------------------------

class UTF8ToUTF16Fixture : public chaos::test::Fixture
{
public:

    //----------------------------PUBLIC ATTRIBUTES-----------------------------

    std::vector< chaos::str::UTF8String >       utf8;
    std::vector< std::vector< unsigned char > > little_endian;
    std::vector< std::vector< unsigned char > > big_endian;
    std::vector< std::size_t >                       lengths;

    //-------------------------PUBLIC MEMBER FUNCTIONS--------------------------

    virtual void setup()
    {
        {
            utf8.push_back( "" );
            std::vector< unsigned char > u;
            u.push_back( 0x00 ); u.push_back( 0x00 );
            little_endian.push_back( u );
            add_big_endian( u );
            lengths.push_back( 2 );
        }

        {
            utf8.push_back( "a" );
            std::vector< unsigned char > u;
            u.push_back( 0x61 ); u.push_back( 0x00 ); // a
            u.push_back( 0x00 ); u.push_back( 0x00 );
            little_endian.push_back( u );
            add_big_endian( u );
            lengths.push_back( 4 );
        }

        {
            utf8.push_back( "Hello World" );
            std::vector< unsigned char > u;
            u.push_back( 0x48 ); u.push_back( 0x00 ); // H
            u.push_back( 0x65 ); u.push_back( 0x00 ); // e
            u.push_back( 0x6C ); u.push_back( 0x00 ); // l
            u.push_back( 0x6C ); u.push_back( 0x00 ); // l
            u.push_back( 0x6F ); u.push_back( 0x00 ); // o
            u.push_back( 0x20 ); u.push_back( 0x00 ); // [space]
            u.push_back( 0x57 ); u.push_back( 0x00 ); // W
            u.push_back( 0x6F ); u.push_back( 0x00 ); // o
            u.push_back( 0x72 ); u.push_back( 0x00 ); // r
            u.push_back( 0x6C ); u.push_back( 0x00 ); // l
            u.push_back( 0x64 ); u.push_back( 0x00 ); // d
            u.push_back( 0x00 ); u.push_back( 0x00 );
            little_endian.push_back( u );
            add_big_endian( u );
            lengths.push_back( 24 );
        }

        {
            utf8.push_back( "γειά σου Κόσμε" );
            std::vector< unsigned char > u;
            u.push_back( 0xB3 ); u.push_back( 0x03 ); // γ
            u.push_back( 0xB5 ); u.push_back( 0x03 ); // ε
            u.push_back( 0xB9 ); u.push_back( 0x03 ); // ι
            u.push_back( 0xAC ); u.push_back( 0x03 ); // ά
            u.push_back( 0x20 ); u.push_back( 0x00 ); // [space]
            u.push_back( 0xC3 ); u.push_back( 0x03 ); // σ
            u.push_back( 0xBF ); u.push_back( 0x03 ); // ο
            u.push_back( 0xC5 ); u.push_back( 0x03 ); // υ
            u.push_back( 0x20 ); u.push_back( 0x00 ); // [space]
            u.push_back( 0x9A ); u.push_back( 0x03 ); // Κ
            u.push_back( 0xCC ); u.push_back( 0x03 ); // ό
            u.push_back( 0xC3 ); u.push_back( 0x03 ); // σ
            u.push_back( 0xBC ); u.push_back( 0x03 ); // μ
            u.push_back( 0xB5 ); u.push_back( 0x03 ); // ε
            u.push_back( 0x00 ); u.push_back( 0x00 );
            little_endian.push_back( u );
            add_big_endian( u );
            lengths.push_back( 30 );
        }

        {
            utf8.push_back( "this is a مزيج of text" );
            std::vector< unsigned char > u;
            u.push_back( 0x74 ); u.push_back( 0x00 ); // t
            u.push_back( 0x68 ); u.push_back( 0x00 ); // h
            u.push_back( 0x69 ); u.push_back( 0x00 ); // i
            u.push_back( 0x73 ); u.push_back( 0x00 ); // s
            u.push_back( 0x20 ); u.push_back( 0x00 ); // [space]
            u.push_back( 0x69 ); u.push_back( 0x00 ); // i
            u.push_back( 0x73 ); u.push_back( 0x00 ); // s
            u.push_back( 0x20 ); u.push_back( 0x00 ); // [space]
            u.push_back( 0x61 ); u.push_back( 0x00 ); // q
            u.push_back( 0x20 ); u.push_back( 0x00 ); // [space]
            u.push_back( 0x45 ); u.push_back( 0x06 ); // م
            u.push_back( 0x32 ); u.push_back( 0x06 ); // ز
            u.push_back( 0x4A ); u.push_back( 0x06 ); // ي
            u.push_back( 0x2C ); u.push_back( 0x06 ); // ج
            u.push_back( 0x20 ); u.push_back( 0x00 ); // [space]
            u.push_back( 0x6F ); u.push_back( 0x00 ); // o
            u.push_back( 0x66 ); u.push_back( 0x00 ); // f
            u.push_back( 0x20 ); u.push_back( 0x00 ); // [space]
            u.push_back( 0x74 ); u.push_back( 0x00 ); // t
            u.push_back( 0x65 ); u.push_back( 0x00 ); // e
            u.push_back( 0x78 ); u.push_back( 0x00 ); // x
            u.push_back( 0x74 ); u.push_back( 0x00 ); // t
            u.push_back( 0x00 ); u.push_back( 0x00 );
            little_endian.push_back( u );
            add_big_endian( u );
            lengths.push_back( 46 );
        }

        {
            utf8.push_back( "간" );
            std::vector< unsigned char > u;
            u.push_back( 0x04 ); u.push_back( 0xAC ); // 간
            u.push_back( 0x00 ); u.push_back( 0x00 );
            little_endian.push_back( u );
            add_big_endian( u );
            lengths.push_back( 4 );
        }

        {
            utf8.push_back("𝕽");
            std::vector<unsigned char> u;
            u.push_back(0x35); u.push_back(0xD8);
            u.push_back(0x7D); u.push_back(0xDD); // 𝕽
            u.push_back(0x00); u.push_back(0x00);
            little_endian.push_back(u);
            add_big_endian(u);
            lengths.push_back(6);
        }

        {
            utf8.push_back("𠭃");
            std::vector<unsigned char> u;
            u.push_back(0x42); u.push_back(0xD8);
            u.push_back(0x43); u.push_back(0xDF); // 𠭃
            u.push_back(0x00); u.push_back(0x00);
            little_endian.push_back(u);
            add_big_endian(u);
            lengths.push_back(6);
        }

        {
            utf8.push_back("𡝯");
            std::vector<unsigned char> u;
            u.push_back(0x45); u.push_back(0xD8);
            u.push_back(0x6F); u.push_back(0xDF); // 𡝯
            u.push_back(0x00); u.push_back(0x00);
            little_endian.push_back(u);
            add_big_endian(u);
            lengths.push_back(6);
        }

        {
            utf8.push_back("𝕽Hello World𡝯");
            std::vector<unsigned char> u;
            u.push_back(0x35); u.push_back(0xD8);
            u.push_back(0x7D); u.push_back(0xDD); // 𝕽
            u.push_back( 0x48 ); u.push_back( 0x00 ); // H
            u.push_back( 0x65 ); u.push_back( 0x00 ); // e
            u.push_back( 0x6C ); u.push_back( 0x00 ); // l
            u.push_back( 0x6C ); u.push_back( 0x00 ); // l
            u.push_back( 0x6F ); u.push_back( 0x00 ); // o
            u.push_back( 0x20 ); u.push_back( 0x00 ); // [space]
            u.push_back( 0x57 ); u.push_back( 0x00 ); // W
            u.push_back( 0x6F ); u.push_back( 0x00 ); // o
            u.push_back( 0x72 ); u.push_back( 0x00 ); // r
            u.push_back( 0x6C ); u.push_back( 0x00 ); // l
            u.push_back( 0x64 ); u.push_back( 0x00 ); // d
            u.push_back(0x45); u.push_back(0xD8);
            u.push_back(0x6F); u.push_back(0xDF); // 𡝯
            u.push_back(0x00); u.push_back(0x00);
            little_endian.push_back(u);
            add_big_endian(u);
            lengths.push_back(32);
        }
    }

    void add_big_endian(std::vector<unsigned char> l)
    {
        std::vector<unsigned char> b;
        for(std::size_t i = 0; i < l.size() - 1; i += 2)
        {
            b.push_back(l[i + 1]);
            b.push_back(l[i    ]);
        }
        big_endian.push_back(b);
    }
};

CHAOS_TEST_UNIT_FIXTURE(utf8_to_utf16, UTF8ToUTF16Fixture)
{
    CHAOS_TEST_MESSAGE("Checking little endian returned length");
    for(std::size_t i = 0; i < fixture->utf8.size(); ++i)
    {
        std::size_t length = 0;
        const char* u = chaos::str::utf8_to_utf16(
            fixture->utf8[i], length, chaos::data::ENDIAN_LITTLE);
        CHAOS_CHECK_EQUAL(length, fixture->lengths[i]);
        delete[] u;
    }

    CHAOS_TEST_MESSAGE("Checking little endian contents");
    for(std::size_t i = 0; i < fixture->utf8.size(); ++i)
    {
        std::size_t length = 0;
        const char* u = chaos::str::utf8_to_utf16(
            fixture->utf8[i], length, chaos::data::ENDIAN_LITTLE);
        CHAOS_CHECK_EQUAL(
            memcmp(
                u,
                reinterpret_cast<const char*>(
                        &fixture->little_endian[i][0]),
                length
            ),
            0
       );
        delete[] u;
    }

    CHAOS_TEST_MESSAGE("Checking big endian returned length");
    for(std::size_t i = 0; i <fixture->utf8.size(); ++i)
    {
        std::size_t length = 0;
        const char* u = chaos::str::utf8_to_utf16(
            fixture->utf8[i], length, chaos::data::ENDIAN_BIG);
        CHAOS_CHECK_EQUAL(length, fixture->lengths[i]);
        delete[] u;
    }

    CHAOS_TEST_MESSAGE("Checking big endian contents");
    for(std::size_t i = 0; i <fixture->utf8.size(); ++i)
    {
        std::size_t length = 0;
        const char* u = chaos::str::utf8_to_utf16(
            fixture->utf8[i], length, chaos::data::ENDIAN_BIG);
        CHAOS_CHECK_EQUAL(
            memcmp(
                u,
                reinterpret_cast<const char*>(
                        &fixture->big_endian[i][0]),
                length
            ),
            0
        );
        delete[] u;
    }
}

//------------------------------------------------------------------------------
//                                 UTF16 TO UTF8
//------------------------------------------------------------------------------

CHAOS_TEST_UNIT_FIXTURE(utf16_to_utf8, UTF8ToUTF16Fixture)
{
    CHAOS_TEST_MESSAGE("Checking little endian conversion");
    for(std::size_t i = 0; i < fixture->utf8.size(); ++i)
    {
        chaos::str::UTF8String u = chaos::str::utf16_to_utf8(
                (const char*) &fixture->little_endian[ i ][ 0 ],
                fixture->lengths[i] - 1,
                chaos::data::ENDIAN_LITTLE
        );
        CHAOS_CHECK_EQUAL(u, fixture->utf8[ i ]);
    }

    CHAOS_TEST_MESSAGE(
            "Checking little endian conversion with NULL terminator");
    for(std::size_t i = 0; i < fixture->utf8.size(); ++i)
    {
        chaos::str::UTF8String u = chaos::str::utf16_to_utf8(
                (const char*) &fixture->little_endian[ i ][ 0 ],
                chaos::str::npos,
                chaos::data::ENDIAN_LITTLE
        );
        CHAOS_CHECK_EQUAL(u, fixture->utf8[ i ]);
    }

    CHAOS_TEST_MESSAGE("Checking big endian conversion");
    for(std::size_t i = 0; i < fixture->utf8.size(); ++i)
    {
        chaos::str::UTF8String u = chaos::str::utf16_to_utf8(
                (const char*) &fixture->big_endian[ i ][ 0 ],
                fixture->lengths[i] - 1,
                chaos::data::ENDIAN_BIG
        );
        CHAOS_CHECK_EQUAL(u, fixture->utf8[ i ]);
    }

    CHAOS_TEST_MESSAGE(
            "Checking big endian conversion with NULL terminator");
    for(std::size_t i = 0; i < fixture->utf8.size(); ++i)
    {
        chaos::str::UTF8String u = chaos::str::utf16_to_utf8(
                (const char*) &fixture->big_endian[ i ][ 0 ],
                chaos::str::npos,
                chaos::data::ENDIAN_BIG
        );
        CHAOS_CHECK_EQUAL(u, fixture->utf8[ i ]);
    }
}

//------------------------------------------------------------------------------
//                                    IS_UTF8
//------------------------------------------------------------------------------

class IsUtf8Fixture : public chaos::test::Fixture
{
public:

    //----------------------------PUBLIC ATTRIBUTES-----------------------------

    std::vector<const char*> valid;
    std::vector<const char*> invalid;

    //-------------------------------CONSTRUCTOR--------------------------------

    virtual void setup()
    {
        valid.push_back("");
        valid.push_back("Hello World");
        valid.push_back("a");
        valid.push_back(
            "This is a really long string, that just keeps on going on and on "
            "and on! It never seems to end, but just when you think that it "
            "will not end. It ends.\n\n\n\n\nNope still going here.\t\t\tThe "
            "end!\n\n\n\t\t\t"
        );
        valid.push_back("γειά σου Κόσμε");
        valid.push_back("this is a مزيج of text");
        valid.push_back("간");
        valid.push_back("𐂣");

        invalid.push_back("\x80");
        invalid.push_back("\x0A\x80");
        invalid.push_back("\xC2\x80\x80");
        invalid.push_back("\xC8\x02");
        invalid.push_back("\xE1\x80\x80\x80");
        invalid.push_back("\xE3\x06");
        invalid.push_back("\xEE\x80\xC3");
        invalid.push_back("\xFA\x80\x80\x80\x80");
        invalid.push_back("\xFA\xC4");
        invalid.push_back("\xFA\x80\x05");
        invalid.push_back("\xFA\x80\x80\xEE");
    }
};

CHAOS_TEST_UNIT_FIXTURE(is_utf8, IsUtf8Fixture)
{
    CHAOS_TEST_MESSAGE("Checking valid data with null terminators");
    CHAOS_FOR_EACH(it, fixture->valid)
    {
        CHAOS_CHECK_TRUE(chaos::str::is_utf8(*it));
    }

    CHAOS_TEST_MESSAGE("Checking valid data without null terminators");
    CHAOS_FOR_EACH(it, fixture->valid)
    {
        // get the length of the data
        std::size_t length = strlen(*it);
        // create non null terminated data
        char* cpy = new char[length];
        memcpy(cpy, *it, length);
        // check
        CHAOS_CHECK_TRUE(chaos::str::is_utf8(cpy, length));
        // clean up
        delete[] cpy;
    }

    CHAOS_TEST_MESSAGE("Checking invalid data with null terminators");
    CHAOS_FOR_EACH(it, fixture->invalid)
    {
        CHAOS_CHECK_FALSE(chaos::str::is_utf8(*it));
    }

    CHAOS_TEST_MESSAGE("Checking invalid data without null terminators");
    CHAOS_FOR_EACH(it, fixture->invalid)
    {
        // get the length of the data
        std::size_t length = strlen(*it);
        // create non null terminated data
        char* cpy = new char[length];
        memcpy(cpy, *it, length);
        // check
        CHAOS_CHECK_FALSE(chaos::str::is_utf8(cpy, length));
    }
}

//------------------------------------------------------------------------------
//                                      JOIN
//------------------------------------------------------------------------------

class JoinFixture : public chaos::test::Fixture
{
public:

    //----------------------------PUBLIC ATTRIBUTES-----------------------------

    std::vector< std::vector< chaos::str::UTF8String > > components;
    std::vector < chaos::str::UTF8String > separators;
    std::vector < chaos::str::UTF8String > results;

    //-------------------------PUBLIC MEMBER FUNCTIONS--------------------------

    virtual void setup()
    {
        {
            std::vector< chaos::str::UTF8String > c;
            c.push_back( "" );
            components.push_back( c );
            separators.push_back( "!" );
            results.push_back( "" );
        }
        {
            std::vector< chaos::str::UTF8String > c;
            c.push_back( "Hello" );
            components.push_back( c );
            separators.push_back( "test" );
            results.push_back( "Hello" );
        }
        {
            std::vector< chaos::str::UTF8String > c;
            c.push_back( "Hello" );
            c.push_back( "World" );
            components.push_back( c );
            separators.push_back( "_" );
            results.push_back( "Hello_World" );
        }
        {
            std::vector< chaos::str::UTF8String > c;
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
            std::vector< chaos::str::UTF8String > c;
            c.push_back( "γειά" );
            c.push_back( "σου" );
            c.push_back( "Κόσμε" );
            components.push_back( c );
            separators.push_back( " " );
            results.push_back( "γειά σου Κόσμε" );
        }
        {
            std::vector< chaos::str::UTF8String > c;
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
    for ( std::size_t i = 0; i < fixture->components.size(); ++i )
    {
        chaos::str::UTF8String s = chaos::str::join(
                fixture->components[ i ],
                fixture->separators[ i ]
        );
        CHAOS_CHECK_EQUAL( s, fixture->results[ i ] );
    }
}

} // namespace unicode_operations_tests
