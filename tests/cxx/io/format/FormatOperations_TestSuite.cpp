#include "chaoscore/test/ChaosTest.hpp"

CHAOS_TEST_MODULE( io.format.format_operations )

#include "chaoscore/io/format/FormatOperations.hpp"

namespace format_operations_tests
{

//------------------------------------------------------------------------------
//                                 INT TO BINARY
//------------------------------------------------------------------------------

class IntToBinaryFixture : public chaos::test::Fixture
{
public:

    //----------------------------PUBLIC ATTRIBUTES-----------------------------

    std::vector< chaos::int16 > int16;
    std::vector< chaos::uni::UTF8String > int16_pad;
    std::vector< chaos::uni::UTF8String > int16_nopad;

    std::vector< chaos::uint16 > uint16;
    std::vector< chaos::uni::UTF8String > uint16_pad;
    std::vector< chaos::uni::UTF8String > uint16_nopad;

    std::vector< chaos::int32 > int32;
    std::vector< chaos::uni::UTF8String > int32_pad;
    std::vector< chaos::uni::UTF8String > int32_nopad;

    std::vector< chaos::uint32 > uint32;
    std::vector< chaos::uni::UTF8String > uint32_pad;
    std::vector< chaos::uni::UTF8String > uint32_nopad;

    std::vector< chaos::int64 > int64;
    std::vector< chaos::uni::UTF8String > int64_pad;
    std::vector< chaos::uni::UTF8String > int64_nopad;

    std::vector< chaos::uint64 > uint64;
    std::vector< chaos::uni::UTF8String > uint64_pad;
    std::vector< chaos::uni::UTF8String > uint64_nopad;

    //-------------------------PUBLIC MEMBER FUNCTIONS--------------------------

    virtual void setup()
    {
        // --- int16 ---

        int16.push_back( 0 );
        int16_pad.push_back( "0b0000000000000000" );
        int16_nopad.push_back( "0b0" );

        int16.push_back( 3 );
        int16_pad.push_back( "0b0000000000000011" );
        int16_nopad.push_back( "0b11" );

        int16.push_back( 93 );
        int16_pad.push_back( "0b0000000001011101" );
        int16_nopad.push_back( "0b1011101" );

        int16.push_back( 48934 );
        int16_pad.push_back( "0b1011111100100110" );
        int16_nopad.push_back( "0b1011111100100110" );

        int16.push_back( -2 );
        int16_pad.push_back( "0b1111111111111110" );
        int16_nopad.push_back( "0b1111111111111110" );

        int16.push_back( -9584 );
        int16_pad.push_back( "0b1101101010010000" );
        int16_nopad.push_back( "0b1101101010010000" );

        // -- uint16 ---

        uint16.push_back( 0 );
        uint16_pad.push_back( "0b0000000000000000" );
        uint16_nopad.push_back( "0b0" );

        uint16.push_back( 4 );
        uint16_pad.push_back( "0b0000000000000100" );
        uint16_nopad.push_back( "0b100" );

        uint16.push_back( 64 );
        uint16_pad.push_back( "0b0000000001000000" );
        uint16_nopad.push_back( "0b1000000" );

        uint16.push_back( 5894 );
        uint16_pad.push_back( "0b0001011100000110" );
        uint16_nopad.push_back( "0b1011100000110" );

        uint16.push_back( 45905 );
        uint16_pad.push_back( "0b1011001101010001" );
        uint16_nopad.push_back( "0b1011001101010001" );

        // --- int32 ---

        int32.push_back( 0 );
        int32_pad.push_back( "0b00000000000000000000000000000000" );
        int32_nopad.push_back( "0b0" );

        int32.push_back( -0 );
        int32_pad.push_back( "0b00000000000000000000000000000000" );
        int32_nopad.push_back( "0b0" );

        int32.push_back( 2 );
        int32_pad.push_back( "0b00000000000000000000000000000010" );
        int32_nopad.push_back( "0b10" );

        int32.push_back( 34234 );
        int32_pad.push_back( "0b00000000000000001000010110111010" );
        int32_nopad.push_back( "0b1000010110111010" );

        int32.push_back( 894053793 );
        int32_pad.push_back( "0b00110101010010100010110110100001" );
        int32_nopad.push_back( "0b110101010010100010110110100001" );

        int32.push_back( -47 );
        int32_pad.push_back( "0b11111111111111111111111111010001" );
        int32_nopad.push_back( "0b11111111111111111111111111010001" );

        int32.push_back( -589452181 );
        int32_pad.push_back( "0b11011100110111011010110001101011" );
        int32_nopad.push_back( "0b11011100110111011010110001101011" );

        // --- uint32 ---

        uint32.push_back( 0 );
        uint32_pad.push_back( "0b00000000000000000000000000000000" );
        uint32_nopad.push_back( "0b0" );

        uint32.push_back( 10 );
        uint32_pad.push_back( "0b00000000000000000000000000001010" );
        uint32_nopad.push_back( "0b1010" );

        uint32.push_back( 975 );
        uint32_pad.push_back( "0b00000000000000000000001111001111" );
        uint32_nopad.push_back( "0b1111001111" );

        uint32.push_back( 34892347 );
        uint32_pad.push_back( "0b00000010000101000110101000111011" );
        uint32_nopad.push_back( "0b10000101000110101000111011" );

        uint32.push_back( 1989340349 );
        uint32_pad.push_back( "0b01110110100100101110110010111101" );
        uint32_nopad.push_back( "0b1110110100100101110110010111101" );

        // --- int64 ---

        int64.push_back( 0 );
        int64_pad.push_back( "0b00000000000000000000000000000000000000000000000"
                             "00000000000000000" );
        int64_nopad.push_back( "0b0" );

        int64.push_back( 9 );
        int64_pad.push_back( "0b00000000000000000000000000000000000000000000000"
                             "00000000000001001" );
        int64_nopad.push_back( "0b1001" );

        int64.push_back( 348923434 );
        int64_pad.push_back( "0b00000000000000000000000000000000000101001100110"
                             "00010011000101010" );
        int64_nopad.push_back( "0b10100110011000010011000101010" );

        int64.push_back( 3248249234982402434 );
        int64_pad.push_back( "0b00101101000101000001100101111000001000010000111"
                             "10111100110000010" );
        int64_nopad.push_back( "0b101101000101000001100101111000001000010000111"
                               "10111100110000010" );

        int64.push_back( -1 );
        int64_pad.push_back( "0b11111111111111111111111111111111111111111111111"
                             "11111111111111111" );
        int64_nopad.push_back( "0b111111111111111111111111111111111111111111111"
                               "1111111111111111111" );

        int64.push_back( -3472847234365765373 );
        int64_pad.push_back( "0b11001111110011011111011111010111000111000110111"
                             "00100100100000011" );
        int64_nopad.push_back( "0b110011111100110111110111110101110001110001101"
                               "1100100100100000011" );

        // --- uint64 ---

        uint64.push_back( 0 );
        uint64_pad.push_back( "0b0000000000000000000000000000000000000000000000"
                              "000000000000000000" );
        uint64_nopad.push_back( "0b0" );

        uint64.push_back( 5 );
        uint64_pad.push_back( "0b0000000000000000000000000000000000000000000000"
                              "000000000000000101" );
        uint64_nopad.push_back( "0b101" );

        uint64.push_back( 1239348 );
        uint64_pad.push_back( "0b0000000000000000000000000000000000000000000100"
                              "101110100100110100" );
        uint64_nopad.push_back( "0b100101110100100110100" );

        uint64.push_back( 34892489205 );
        uint64_pad.push_back( "0b0000000000000000000000000000100000011111110000"
                              "010010000111110101" );
        uint64_nopad.push_back( "0b100000011111110000010010000111110101" );

        uint64.push_back( 15499834893509375902ULL );
        uint64_pad.push_back( "0b1101011100011010011110011011011011001000110101"
                              "001011011110011110" );
        uint64_nopad.push_back( "0b11010111000110100111100110110110110010001101"
                                "01001011011110011110" );
    }
};

CHAOS_TEST_UNIT_FIXTURE( int_to_binary, IntToBinaryFixture )
{
    // --- int16 ---

    CHAOS_TEST_MESSAGE( "Checking padded int16" );
    for ( std::size_t i = 0; i < fixture->int16.size(); ++i )
    {
        CHAOS_CHECK_EQUAL(
                chaos::io::format::int_to_binary( fixture->int16[ i ], true ),
                fixture->int16_pad[ i ]
        );
    }
    CHAOS_TEST_MESSAGE( "Checking no pad int16" );
    for ( std::size_t i = 0; i < fixture->int16.size(); ++i )
    {
        CHAOS_CHECK_EQUAL(
                chaos::io::format::int_to_binary( fixture->int16[ i ], false ),
                fixture->int16_nopad[ i ]
        );
    }

    // --- uint16 ---

    CHAOS_TEST_MESSAGE( "Checking padded uint16" );
    for ( std::size_t i = 0; i < fixture->uint16.size(); ++i )
    {
        CHAOS_CHECK_EQUAL(
                chaos::io::format::int_to_binary( fixture->uint16[ i ], true ),
                fixture->uint16_pad[ i ]
        );
    }
    CHAOS_TEST_MESSAGE( "Checking no pad uint16" );
    for ( std::size_t i = 0; i < fixture->uint16.size(); ++i )
    {
        CHAOS_CHECK_EQUAL(
                chaos::io::format::int_to_binary( fixture->uint16[ i ], false ),
                fixture->uint16_nopad[ i ]
        );
    }

    // --- int32 ---

    CHAOS_TEST_MESSAGE( "Checking padded int32" );
    for ( std::size_t i = 0; i < fixture->int32.size(); ++i )
    {
        CHAOS_CHECK_EQUAL(
                chaos::io::format::int_to_binary( fixture->int32[ i ], true ),
                fixture->int32_pad[ i ]
        );
    }
    CHAOS_TEST_MESSAGE( "Checking no pad int32" );
    for ( std::size_t i = 0; i < fixture->int32.size(); ++i )
    {
        CHAOS_CHECK_EQUAL(
                chaos::io::format::int_to_binary( fixture->int32[ i ], false ),
                fixture->int32_nopad[ i ]
        );
    }

    // --- uint32 ---

    CHAOS_TEST_MESSAGE( "Checking padded uint32" );
    for ( std::size_t i = 0; i < fixture->uint32.size(); ++i )
    {
        CHAOS_CHECK_EQUAL(
                chaos::io::format::int_to_binary( fixture->uint32[ i ], true ),
                fixture->uint32_pad[ i ]
        );
    }
    CHAOS_TEST_MESSAGE( "Checking no pad uint32" );
    for ( std::size_t i = 0; i < fixture->uint32.size(); ++i )
    {
        CHAOS_CHECK_EQUAL(
                chaos::io::format::int_to_binary( fixture->uint32[ i ], false ),
                fixture->uint32_nopad[ i ]
        );
    }

    // --- int64 ---

    CHAOS_TEST_MESSAGE( "Checking padded int64" );
    for ( std::size_t i = 0; i < fixture->int64.size(); ++i )
    {
        CHAOS_CHECK_EQUAL(
                chaos::io::format::int_to_binary( fixture->int64[ i ], true ),
                fixture->int64_pad[ i ]
        );
    }
    CHAOS_TEST_MESSAGE( "Checking no pad int64" );
    for ( std::size_t i = 0; i < fixture->int64.size(); ++i )
    {
        CHAOS_CHECK_EQUAL(
                chaos::io::format::int_to_binary( fixture->int64[ i ], false ),
                fixture->int64_nopad[ i ]
        );
    }

    // --- uint64 --

    CHAOS_TEST_MESSAGE( "Checking padded uint64" );
    for ( std::size_t i = 0; i < fixture->uint64.size(); ++i )
    {
        CHAOS_CHECK_EQUAL(
                chaos::io::format::int_to_binary( fixture->uint64[ i ], true ),
                fixture->uint64_pad[ i ]
        );
    }
    CHAOS_TEST_MESSAGE( "Checking no pad uint64" );
    for ( std::size_t i = 0; i < fixture->uint64.size(); ++i )
    {
        CHAOS_CHECK_EQUAL(
                chaos::io::format::int_to_binary( fixture->uint64[ i ], false ),
                fixture->uint64_nopad[ i ]
        );
    }
}

//------------------------------------------------------------------------------
//                                   INT TO HEX
//------------------------------------------------------------------------------

class IntToHexFixture : public chaos::test::Fixture
{
public:

    //----------------------------PUBLIC ATTRIBUTES-----------------------------

    std::vector< chaos::int16 > int16;
    std::vector< chaos::uni::UTF8String > int16_pad;
    std::vector< chaos::uni::UTF8String > int16_nopad;

    std::vector< chaos::uint16 > uint16;
    std::vector< chaos::uni::UTF8String > uint16_pad;
    std::vector< chaos::uni::UTF8String > uint16_nopad;

    std::vector< chaos::int32 > int32;
    std::vector< chaos::uni::UTF8String > int32_pad;
    std::vector< chaos::uni::UTF8String > int32_nopad;

    std::vector< chaos::uint32 > uint32;
    std::vector< chaos::uni::UTF8String > uint32_pad;
    std::vector< chaos::uni::UTF8String > uint32_nopad;

    std::vector< chaos::int64 > int64;
    std::vector< chaos::uni::UTF8String > int64_pad;
    std::vector< chaos::uni::UTF8String > int64_nopad;

    std::vector< chaos::uint64 > uint64;
    std::vector< chaos::uni::UTF8String > uint64_pad;
    std::vector< chaos::uni::UTF8String > uint64_nopad;

    //-------------------------PUBLIC MEMBER FUNCTIONS--------------------------

    virtual void setup()
    {
        // --- int16 ---

        int16.push_back( 0 );
        int16_pad.push_back( "0x0000" );
        int16_nopad.push_back( "0x0" );

        int16.push_back( 3 );
        int16_pad.push_back( "0x0003" );
        int16_nopad.push_back( "0x3" );

        int16.push_back( 93 );
        int16_pad.push_back( "0x005D" );
        int16_nopad.push_back( "0x5D" );

        int16.push_back( 48934 );
        int16_pad.push_back( "0xBF26" );
        int16_nopad.push_back( "0xBF26" );

        int16.push_back( -2 );
        int16_pad.push_back( "0xFFFE" );
        int16_nopad.push_back( "0xFFFE" );

        int16.push_back( -9584 );
        int16_pad.push_back( "0xDA90" );
        int16_nopad.push_back( "0xDA90" );

        // -- uint16 ---

        uint16.push_back( 0 );
        uint16_pad.push_back( "0x0000" );
        uint16_nopad.push_back( "0x0" );

        uint16.push_back( 4 );
        uint16_pad.push_back( "0x0004" );
        uint16_nopad.push_back( "0x4" );

        uint16.push_back( 64 );
        uint16_pad.push_back( "0x0040" );
        uint16_nopad.push_back( "0x40" );

        uint16.push_back( 5894 );
        uint16_pad.push_back( "0x1706" );
        uint16_nopad.push_back( "0x1706" );

        uint16.push_back( 45905 );
        uint16_pad.push_back( "0xB351" );
        uint16_nopad.push_back( "0xB351" );

        // --- int32 ---

        int32.push_back( 0 );
        int32_pad.push_back( "0x00000000" );
        int32_nopad.push_back( "0x0" );

        int32.push_back( -0 );
        int32_pad.push_back( "0x00000000" );
        int32_nopad.push_back( "0x0" );

        int32.push_back( 2 );
        int32_pad.push_back( "0x00000002" );
        int32_nopad.push_back( "0x2" );

        int32.push_back( 34234 );
        int32_pad.push_back( "0x000085BA" );
        int32_nopad.push_back( "0x85BA" );

        int32.push_back( 894053793 );
        int32_pad.push_back( "0x354A2DA1" );
        int32_nopad.push_back( "0x354A2DA1" );

        int32.push_back( -47 );
        int32_pad.push_back( "0xFFFFFFD1" );
        int32_nopad.push_back( "0xFFFFFFD1" );

        int32.push_back( -589452181 );
        int32_pad.push_back( "0xDCDDAC6B" );
        int32_nopad.push_back( "0xDCDDAC6B" );

        // --- uint32 ---

        uint32.push_back( 0 );
        uint32_pad.push_back( "0x00000000" );
        uint32_nopad.push_back( "0x0" );

        uint32.push_back( 10 );
        uint32_pad.push_back( "0x0000000A" );
        uint32_nopad.push_back( "0xA" );

        uint32.push_back( 975 );
        uint32_pad.push_back( "0x000003CF" );
        uint32_nopad.push_back( "0x3CF" );

        uint32.push_back( 34892347 );
        uint32_pad.push_back( "0x02146A3B" );
        uint32_nopad.push_back( "0x2146A3B" );

        uint32.push_back( 1989340349 );
        uint32_pad.push_back( "0x7692ECBD" );
        uint32_nopad.push_back( "0x7692ECBD" );

        // --- int64 ---

        int64.push_back( 0 );
        int64_pad.push_back( "0x0000000000000000" );
        int64_nopad.push_back( "0x0" );

        int64.push_back( 9 );
        int64_pad.push_back( "0x0000000000000009" );
        int64_nopad.push_back( "0x9" );

        int64.push_back( 348923434 );
        int64_pad.push_back( "0x0000000014CC262A" );
        int64_nopad.push_back( "0x14CC262A" );

        int64.push_back( 3248249234982402434 );
        int64_pad.push_back( "0x2D141978210F7982" );
        int64_nopad.push_back( "0x2D141978210F7982" );

        int64.push_back( -1 );
        int64_pad.push_back( "0xFFFFFFFFFFFFFFFF" );
        int64_nopad.push_back( "0xFFFFFFFFFFFFFFFF" );

        int64.push_back( -3472847234365765373 );
        int64_pad.push_back( "0xCFCDF7D71C6E4903" );
        int64_nopad.push_back( "0xCFCDF7D71C6E4903" );

        // --- uint64 ---

        uint64.push_back( 0 );
        uint64_pad.push_back( "0x0000000000000000" );
        uint64_nopad.push_back( "0x0" );

        uint64.push_back( 5 );
        uint64_pad.push_back( "0x0000000000000005" );
        uint64_nopad.push_back( "0x5" );

        uint64.push_back( 1239348 );
        uint64_pad.push_back( "0x000000000012E934" );
        uint64_nopad.push_back( "0x12E934" );

        uint64.push_back( 34892489205 );
        uint64_pad.push_back( "0x000000081FC121F5" );
        uint64_nopad.push_back( "0x81FC121F5" );

        uint64.push_back( 15499834893509375902ULL );
        uint64_pad.push_back( "0xD71A79B6C8D4B79E" );
        uint64_nopad.push_back( "0xD71A79B6C8D4B79E" );
    }
};

CHAOS_TEST_UNIT_FIXTURE( int_to_hex, IntToHexFixture )
{
    // --- int16 ---

    CHAOS_TEST_MESSAGE( "Checking padded int16" );
    for ( std::size_t i = 0; i < fixture->int16.size(); ++i )
    {
        CHAOS_CHECK_EQUAL(
                chaos::io::format::int_to_hex( fixture->int16[ i ], true ),
                fixture->int16_pad[ i ]
        );
    }
    CHAOS_TEST_MESSAGE( "Checking no pad int16" );
    for ( std::size_t i = 0; i < fixture->int16.size(); ++i )
    {
        CHAOS_CHECK_EQUAL(
                chaos::io::format::int_to_hex( fixture->int16[ i ], false ),
                fixture->int16_nopad[ i ]
        );
    }

    // --- uint16 ---

    CHAOS_TEST_MESSAGE( "Checking padded uint16" );
    for ( std::size_t i = 0; i < fixture->uint16.size(); ++i )
    {
        CHAOS_CHECK_EQUAL(
                chaos::io::format::int_to_hex( fixture->uint16[ i ], true ),
                fixture->uint16_pad[ i ]
        );
    }
    CHAOS_TEST_MESSAGE( "Checking no pad uint16" );
    for ( std::size_t i = 0; i < fixture->uint16.size(); ++i )
    {
        CHAOS_CHECK_EQUAL(
                chaos::io::format::int_to_hex( fixture->uint16[ i ], false ),
                fixture->uint16_nopad[ i ]
        );
    }

    // --- int32 ---

    CHAOS_TEST_MESSAGE( "Checking padded int32" );
    for ( std::size_t i = 0; i < fixture->int32.size(); ++i )
    {
        CHAOS_CHECK_EQUAL(
                chaos::io::format::int_to_hex( fixture->int32[ i ], true ),
                fixture->int32_pad[ i ]
        );
    }
    CHAOS_TEST_MESSAGE( "Checking no pad int32" );
    for ( std::size_t i = 0; i < fixture->int32.size(); ++i )
    {
        CHAOS_CHECK_EQUAL(
                chaos::io::format::int_to_hex( fixture->int32[ i ], false ),
                fixture->int32_nopad[ i ]
        );
    }

    // --- uint32 ---

    CHAOS_TEST_MESSAGE( "Checking padded uint32" );
    for ( std::size_t i = 0; i < fixture->uint32.size(); ++i )
    {
        CHAOS_CHECK_EQUAL(
                chaos::io::format::int_to_hex( fixture->uint32[ i ], true ),
                fixture->uint32_pad[ i ]
        );
    }
    CHAOS_TEST_MESSAGE( "Checking no pad uint32" );
    for ( std::size_t i = 0; i < fixture->uint32.size(); ++i )
    {
        CHAOS_CHECK_EQUAL(
                chaos::io::format::int_to_hex( fixture->uint32[ i ], false ),
                fixture->uint32_nopad[ i ]
        );
    }

    // --- int64 ---

    CHAOS_TEST_MESSAGE( "Checking padded int64" );
    for ( std::size_t i = 0; i < fixture->int64.size(); ++i )
    {
        CHAOS_CHECK_EQUAL(
                chaos::io::format::int_to_hex( fixture->int64[ i ], true ),
                fixture->int64_pad[ i ]
        );
    }
    CHAOS_TEST_MESSAGE( "Checking no pad int64" );
    for ( std::size_t i = 0; i < fixture->int64.size(); ++i )
    {
        CHAOS_CHECK_EQUAL(
                chaos::io::format::int_to_hex( fixture->int64[ i ], false ),
                fixture->int64_nopad[ i ]
        );
    }

    // --- uint64 --

    CHAOS_TEST_MESSAGE( "Checking padded uint64" );
    for ( std::size_t i = 0; i < fixture->uint64.size(); ++i )
    {
        CHAOS_CHECK_EQUAL(
                chaos::io::format::int_to_hex( fixture->uint64[ i ], true ),
                fixture->uint64_pad[ i ]
        );
    }
    CHAOS_TEST_MESSAGE( "Checking no pad uint64" );
    for ( std::size_t i = 0; i < fixture->uint64.size(); ++i )
    {
        CHAOS_CHECK_EQUAL(
                chaos::io::format::int_to_hex( fixture->uint64[ i ], false ),
                fixture->uint64_nopad[ i ]
        );
    }
}

//------------------------------------------------------------------------------
//                                  CENTRE TEXT
//------------------------------------------------------------------------------

class CentreTextFixture : public chaos::test::Fixture
{
public:

    //----------------------------PUBLIC ATTRIBUTES-----------------------------

    std::vector< chaos::uni::UTF8String > input;
    std::vector< chaos::uint32 > line_lengths;
    std::vector< chaos::uni::UTF8String > no_trim_results;
    std::vector< chaos::uni::UTF8String > trim_results;

    //-------------------------PUBLIC MEMBER FUNCTIONS--------------------------

    virtual void setup()
    {
        input.push_back( "Hello World" );
        line_lengths.push_back( 20 );
        no_trim_results.push_back( "     Hello World    " );
        trim_results.push_back( "     Hello World" );

        input.push_back( "γειά σου Κόσμε" );
        line_lengths.push_back( 24 );
        no_trim_results.push_back( "     γειά σου Κόσμε     " );
        trim_results.push_back( "     γειά σου Κόσμε" );

        input.push_back( "this is a مزيج of text" );
        line_lengths.push_back( 80 );
        no_trim_results.push_back(
                "                             this is a مزيج of text           "
                "                  "
        );
        trim_results.push_back(
                "                             this is a مزيج of text"
        );

        input.push_back( "간" );
        line_lengths.push_back( 13 );
        no_trim_results.push_back( "      간      " );
        trim_results.push_back( "      간" );

        input.push_back( "Hello World" );
        line_lengths.push_back( 12 );
        no_trim_results.push_back( " Hello World" );
        trim_results.push_back( " Hello World" );

        input.push_back( "Hello World" );
        line_lengths.push_back( 8 );
        no_trim_results.push_back( "Hello World" );
        trim_results.push_back( "Hello World" );

        input.push_back( "γειά σου Κόσμε" );
        line_lengths.push_back( 1 );
        no_trim_results.push_back( "γειά σου Κόσμε" );
        trim_results.push_back( "γειά σου Κόσμε" );

        input.push_back( " مزيج " );
        line_lengths.push_back( 0 );
        no_trim_results.push_back( " مزيج " );
        trim_results.push_back( " مزيج " );
    }
};

CHAOS_TEST_UNIT_FIXTURE( centre_text, CentreTextFixture )
{
    CHAOS_TEST_MESSAGE( "Checking no trim trailing spaces" );
    for ( std::size_t i = 0; i < fixture->input.size(); ++i )
    {
        chaos::uni::UTF8String u( fixture->input[ i ] );
        chaos::io::format::centre_text( u, fixture->line_lengths[ i ] );

        CHAOS_CHECK_EQUAL( u, fixture->no_trim_results[ i ] );
    }

    CHAOS_TEST_MESSAGE( "Checking trim trailing spaces" );
    for ( std::size_t i = 0; i < fixture->input.size(); ++i )
    {
        chaos::uni::UTF8String u( fixture->input[ i ] );
        chaos::io::format::centre_text( u, fixture->line_lengths[ i ], true );

        CHAOS_CHECK_EQUAL( u, fixture->trim_results[ i ] );
    }
}

} // format_operations_tests
