#include "chaoscore/test/ChaosTest.hpp"

CHAOS_TEST_MODULE( base.types )

#include "chaoscore/base/Types.hpp"

namespace types_tests
{

//------------------------------------------------------------------------------
//                                  CHAOS::INT8
//------------------------------------------------------------------------------

CHAOS_TEST_UNIT( int8 )
{
    long long values[] = { 1024, 65, 0, -10, -455 };

    CHAOS_TEST_MESSAGE( "Checking byte size" );
    for ( std::size_t i = 0; i < sizeof( values ) / sizeof( long long ); ++i )
    {
        chaos::int8 v = static_cast< chaos::int8 >( values[ i ] );

        CHAOS_CHECK_EQUAL( sizeof( v ), static_cast< size_t >( 1 ) );
    }

    CHAOS_TEST_MESSAGE( "Checking cast to char" );
    for ( std::size_t i = 0; i < sizeof( values ) / sizeof( long long ); ++i )
    {
        chaos::int8 v = static_cast< chaos::int8 >( values[ i ] );
        signed char c = static_cast< signed char >( values[ i ] );

        CHAOS_CHECK_EQUAL(
                static_cast< char >( v ),
                static_cast< char >( c )
        );
    }

    CHAOS_TEST_MESSAGE( "Checking cast to signed char" );
    for ( std::size_t i = 0; i < sizeof( values ) / sizeof( long long ); ++i )
    {
        chaos::int8 v = static_cast< chaos::int8 >( values[ i ] );
        signed char c = static_cast< signed char >( values[ i ] );

        CHAOS_CHECK_EQUAL(
                static_cast< signed char >( v ),
                static_cast< signed char >( c )
        );
    }

    CHAOS_TEST_MESSAGE( "Checking cast to unsigned char" );
    for ( std::size_t i = 0; i < sizeof( values ) / sizeof( long long ); ++i )
    {
        chaos::int8 v = static_cast< chaos::int8 >( values[ i ] );
        signed char c = static_cast< signed char >( values[ i ] );

        CHAOS_CHECK_EQUAL(
                static_cast< unsigned char >( v ),
                static_cast< unsigned char >( c )
        );
    }

    CHAOS_TEST_MESSAGE( "Checking cast to signed short" );
    for ( std::size_t i = 0; i < sizeof( values ) / sizeof( long long ); ++i )
    {
        chaos::int8 v = static_cast< chaos::int8 >( values[ i ] );
        signed char c = static_cast< signed char >( values[ i ] );

        CHAOS_CHECK_EQUAL(
                static_cast< signed short >( v ),
                static_cast< signed short >( c )
        );
    }

    CHAOS_TEST_MESSAGE( "Checking cast to unsigned short" );
    for ( std::size_t i = 0; i < sizeof( values ) / sizeof( long long ); ++i )
    {
        chaos::int8 v = static_cast< chaos::int8 >( values[ i ] );
        signed char c = static_cast< signed char >( values[ i ] );

        CHAOS_CHECK_EQUAL(
                static_cast< unsigned short >( v ),
                static_cast< unsigned short >( c )
        );
    }

    CHAOS_TEST_MESSAGE( "Checking cast to signed int" );
    for ( std::size_t i = 0; i < sizeof( values ) / sizeof( long long ); ++i )
    {
        chaos::int8 v = static_cast< chaos::int8 >( values[ i ] );
        signed char c = static_cast< signed char >( values[ i ] );

        CHAOS_CHECK_EQUAL(
                static_cast< signed int >( v ),
                static_cast< signed int >( c )
        );
    }

    CHAOS_TEST_MESSAGE( "Checking cast to unsigned int" );
    for ( std::size_t i = 0; i < sizeof( values ) / sizeof( long long ); ++i )
    {
        chaos::int8 v = static_cast< chaos::int8 >( values[ i ] );
        signed char c = static_cast< signed char >( values[ i ] );

        CHAOS_CHECK_EQUAL(
                static_cast< unsigned int >( v ),
                static_cast< unsigned int >( c )
        );
    }

    CHAOS_TEST_MESSAGE( "Checking cast to signed long" );
    for ( std::size_t i = 0; i < sizeof( values ) / sizeof( long long ); ++i )
    {
        chaos::int8 v = static_cast< chaos::int8 >( values[ i ] );
        signed char c = static_cast< signed char >( values[ i ] );

        CHAOS_CHECK_EQUAL(
                static_cast< signed long >( v ),
                static_cast< signed long >( c )
        );
    }

    CHAOS_TEST_MESSAGE( "Checking cast to unsigned long" );
    for ( std::size_t i = 0; i < sizeof( values ) / sizeof( long long ); ++i )
    {
        chaos::int8 v = static_cast< chaos::int8 >( values[ i ] );
        signed char c = static_cast< signed char >( values[ i ] );

        CHAOS_CHECK_EQUAL(
                static_cast< unsigned long >( v ),
                static_cast< unsigned long >( c )
        );
    }

    CHAOS_TEST_MESSAGE( "Checking cast to chaos int8" );
    for ( std::size_t i = 0; i < sizeof( values ) / sizeof( long long ); ++i )
    {
        chaos::int8 v = static_cast< chaos::int8 >( values[ i ] );
        signed char c = static_cast< signed char >( values[ i ] );

        CHAOS_CHECK_EQUAL(
                static_cast< chaos::int8 >( v ),
                static_cast< chaos::int8 >( c )
        );
    }

    CHAOS_TEST_MESSAGE( "Checking cast to chaos uint8" );
    for ( std::size_t i = 0; i < sizeof( values ) / sizeof( long long ); ++i )
    {
        chaos::int8 v = static_cast< chaos::int8 >( values[ i ] );
        signed char c = static_cast< signed char >( values[ i ] );

        CHAOS_CHECK_EQUAL(
                static_cast< chaos::uint8 >( v ),
                static_cast< chaos::uint8 >( c )
        );
    }

    CHAOS_TEST_MESSAGE( "Checking cast to chaos int16" );
    for ( std::size_t i = 0; i < sizeof( values ) / sizeof( long long ); ++i )
    {
        chaos::int8 v = static_cast< chaos::int8 >( values[ i ] );
        signed char c = static_cast< signed char >( values[ i ] );

        CHAOS_CHECK_EQUAL(
                static_cast< chaos::int16 >( v ),
                static_cast< chaos::int16 >( c )
        );
    }

    CHAOS_TEST_MESSAGE( "Checking cast to chaos uint16" );
    for ( std::size_t i = 0; i < sizeof( values ) / sizeof( long long ); ++i )
    {
        chaos::int8 v = static_cast< chaos::int8 >( values[ i ] );
        signed char c = static_cast< signed char >( values[ i ] );

        CHAOS_CHECK_EQUAL(
                static_cast< chaos::uint16 >( v ),
                static_cast< chaos::uint16 >( c )
        );
    }

    CHAOS_TEST_MESSAGE( "Checking cast to chaos int32" );
    for ( std::size_t i = 0; i < sizeof( values ) / sizeof( long long ); ++i )
    {
        chaos::int8 v = static_cast< chaos::int8 >( values[ i ] );
        signed char c = static_cast< signed char >( values[ i ] );

        CHAOS_CHECK_EQUAL(
                static_cast< chaos::int32 >( v ),
                static_cast< chaos::int32 >( c )
        );
    }

    CHAOS_TEST_MESSAGE( "Checking cast to chaos uint32" );
    for ( std::size_t i = 0; i < sizeof( values ) / sizeof( long long ); ++i )
    {
        chaos::int8 v = static_cast< chaos::int8 >( values[ i ] );
        signed char c = static_cast< signed char >( values[ i ] );

        CHAOS_CHECK_EQUAL(
                static_cast< chaos::uint32 >( v ),
                static_cast< chaos::uint32 >( c )
        );
    }

    CHAOS_TEST_MESSAGE( "Checking cast to chaos int64" );
    for ( std::size_t i = 0; i < sizeof( values ) / sizeof( long long ); ++i )
    {
        chaos::int8 v = static_cast< chaos::int8 >( values[ i ] );
        signed char c = static_cast< signed char >( values[ i ] );

        CHAOS_CHECK_EQUAL(
                static_cast< chaos::int64 >( v ),
                static_cast< chaos::int64 >( c )
        );
    }

    CHAOS_TEST_MESSAGE( "Checking cast to chaos uint64" );
    for ( std::size_t i = 0; i < sizeof( values ) / sizeof( long long ); ++i )
    {
        chaos::int8 v = static_cast< chaos::int8 >( values[ i ] );
        signed char c = static_cast< signed char >( values[ i ] );

        CHAOS_CHECK_EQUAL(
                static_cast< chaos::uint64 >( v ),
                static_cast< chaos::uint64 >( c )
        );
    }
}

//------------------------------------------------------------------------------
//                                  CHAOS::UINT8
//------------------------------------------------------------------------------

CHAOS_TEST_UNIT( uint8 )
{
    long long values[] = { 1024, 65, 0, -10, -455 };

    CHAOS_TEST_MESSAGE( "Checking byte size" );
    for ( std::size_t i = 0; i < sizeof( values ) / sizeof( long long ); ++i )
    {
        chaos::uint8 v = static_cast< chaos::uint8 >( values[ i ] );

        CHAOS_CHECK_EQUAL( sizeof( v ), static_cast< std::size_t >( 1 ) );
    }

    CHAOS_TEST_MESSAGE( "Checking cast to char" );
    for ( std::size_t i = 0; i < sizeof( values ) / sizeof( long long ); ++i )
    {
        chaos::uint8 v = static_cast< chaos::uint8 >( values[ i ] );
        unsigned char c = static_cast< unsigned char >( values[ i ] );

        CHAOS_CHECK_EQUAL(
                static_cast< char >( v ),
                static_cast< char >( c )
        );
    }

    CHAOS_TEST_MESSAGE( "Checking cast to signed char" );
    for ( std::size_t i = 0; i < sizeof( values ) / sizeof( long long ); ++i )
    {
        chaos::uint8 v = static_cast< chaos::uint8 >( values[ i ] );
        unsigned char c = static_cast< unsigned char >( values[ i ] );

        CHAOS_CHECK_EQUAL(
                static_cast< signed char >( v ),
                static_cast< signed char >( c )
        );
    }

    CHAOS_TEST_MESSAGE( "Checking cast to unsigned char" );
    for ( std::size_t i = 0; i < sizeof( values ) / sizeof( long long ); ++i )
    {
        chaos::uint8 v = static_cast< chaos::uint8 >( values[ i ] );
        unsigned char c = static_cast< unsigned char >( values[ i ] );

        CHAOS_CHECK_EQUAL(
                static_cast< unsigned char >( v ),
                static_cast< unsigned char >( c )
        );
    }

    CHAOS_TEST_MESSAGE( "Checking cast to signed short" );
    for ( std::size_t i = 0; i < sizeof( values ) / sizeof( long long ); ++i )
    {
        chaos::uint8 v = static_cast< chaos::uint8 >( values[ i ] );
        unsigned char c = static_cast< unsigned char >( values[ i ] );

        CHAOS_CHECK_EQUAL(
                static_cast< signed short >( v ),
                static_cast< signed short >( c )
        );
    }

    CHAOS_TEST_MESSAGE( "Checking cast to unsigned short" );
    for ( std::size_t i = 0; i < sizeof( values ) / sizeof( long long ); ++i )
    {
        chaos::uint8 v = static_cast< chaos::uint8 >( values[ i ] );
        unsigned char c = static_cast< unsigned char >( values[ i ] );

        CHAOS_CHECK_EQUAL(
                static_cast< unsigned short >( v ),
                static_cast< unsigned short >( c )
        );
    }

    CHAOS_TEST_MESSAGE( "Checking cast to signed int" );
    for ( std::size_t i = 0; i < sizeof( values ) / sizeof( long long ); ++i )
    {
        chaos::uint8 v = static_cast< chaos::uint8 >( values[ i ] );
        unsigned char c = static_cast< unsigned char >( values[ i ] );

        CHAOS_CHECK_EQUAL(
                static_cast< signed int >( v ),
                static_cast< signed int >( c )
        );
    }

    CHAOS_TEST_MESSAGE( "Checking cast to unsigned int" );
    for ( std::size_t i = 0; i < sizeof( values ) / sizeof( long long ); ++i )
    {
        chaos::uint8 v = static_cast< chaos::uint8 >( values[ i ] );
        unsigned char c = static_cast< unsigned char >( values[ i ] );

        CHAOS_CHECK_EQUAL(
                static_cast< unsigned int >( v ),
                static_cast< unsigned int >( c )
        );
    }

    CHAOS_TEST_MESSAGE( "Checking cast to signed long" );
    for ( std::size_t i = 0; i < sizeof( values ) / sizeof( long long ); ++i )
    {
        chaos::uint8 v = static_cast< chaos::uint8 >( values[ i ] );
        unsigned char c = static_cast< unsigned char >( values[ i ] );

        CHAOS_CHECK_EQUAL(
                static_cast< signed long >( v ),
                static_cast< signed long >( c )
        );
    }

    CHAOS_TEST_MESSAGE( "Checking cast to unsigned long" );
    for ( std::size_t i = 0; i < sizeof( values ) / sizeof( long long ); ++i )
    {
        chaos::uint8 v = static_cast< chaos::uint8 >( values[ i ] );
        unsigned char c = static_cast< unsigned char >( values[ i ] );

        CHAOS_CHECK_EQUAL(
                static_cast< unsigned long >( v ),
                static_cast< unsigned long >( c )
        );
    }

    CHAOS_TEST_MESSAGE( "Checking cast to chaos int8" );
    for ( std::size_t i = 0; i < sizeof( values ) / sizeof( long long ); ++i )
    {
        chaos::uint8 v = static_cast< chaos::uint8 >( values[ i ] );
        unsigned char c = static_cast< unsigned char >( values[ i ] );

        CHAOS_CHECK_EQUAL(
                static_cast< chaos::int8 >( v ),
                static_cast< chaos::int8 >( c )
        );
    }

    CHAOS_TEST_MESSAGE( "Checking cast to chaos uint8" );
    for ( std::size_t i = 0; i < sizeof( values ) / sizeof( long long ); ++i )
    {
        chaos::uint8 v = static_cast< chaos::uint8 >( values[ i ] );
        unsigned char c = static_cast< unsigned char >( values[ i ] );

        CHAOS_CHECK_EQUAL(
                static_cast< chaos::uint8 >( v ),
                static_cast< chaos::uint8 >( c )
        );
    }

    CHAOS_TEST_MESSAGE( "Checking cast to chaos int16" );
    for ( std::size_t i = 0; i < sizeof( values ) / sizeof( long long ); ++i )
    {
        chaos::uint8 v = static_cast< chaos::uint8 >( values[ i ] );
        unsigned char c = static_cast< unsigned char >( values[ i ] );

        CHAOS_CHECK_EQUAL(
                static_cast< chaos::int16 >( v ),
                static_cast< chaos::int16 >( c )
        );
    }

    CHAOS_TEST_MESSAGE( "Checking cast to chaos uint16" );
    for ( std::size_t i = 0; i < sizeof( values ) / sizeof( long long ); ++i )
    {
        chaos::uint8 v = static_cast< chaos::uint8 >( values[ i ] );
        unsigned char c = static_cast< unsigned char >( values[ i ] );

        CHAOS_CHECK_EQUAL(
                static_cast< chaos::uint16 >( v ),
                static_cast< chaos::uint16 >( c )
        );
    }

    CHAOS_TEST_MESSAGE( "Checking cast to chaos int32" );
    for ( std::size_t i = 0; i < sizeof( values ) / sizeof( long long ); ++i )
    {
        chaos::uint8 v = static_cast< chaos::uint8 >( values[ i ] );
        unsigned char c = static_cast< unsigned char >( values[ i ] );

        CHAOS_CHECK_EQUAL(
                static_cast< chaos::int32 >( v ),
                static_cast< chaos::int32 >( c )
        );
    }

    CHAOS_TEST_MESSAGE( "Checking cast to chaos uint32" );
    for ( std::size_t i = 0; i < sizeof( values ) / sizeof( long long ); ++i )
    {
        chaos::uint8 v = static_cast< chaos::uint8 >( values[ i ] );
        unsigned char c = static_cast< unsigned char >( values[ i ] );

        CHAOS_CHECK_EQUAL(
                static_cast< chaos::uint32 >( v ),
                static_cast< chaos::uint32 >( c )
        );
    }

    CHAOS_TEST_MESSAGE( "Checking cast to chaos int64" );
    for ( std::size_t i = 0; i < sizeof( values ) / sizeof( long long ); ++i )
    {
        chaos::uint8 v = static_cast< chaos::uint8 >( values[ i ] );
        unsigned char c = static_cast< unsigned char >( values[ i ] );

        CHAOS_CHECK_EQUAL(
                static_cast< chaos::int64 >( v ),
                static_cast< chaos::int64 >( c )
        );
    }

    CHAOS_TEST_MESSAGE( "Checking cast to chaos uint64" );
    for ( std::size_t i = 0; i < sizeof( values ) / sizeof( long long ); ++i )
    {
        chaos::uint8 v = static_cast< chaos::uint8 >( values[ i ] );
        unsigned char c = static_cast< unsigned char >( values[ i ] );

        CHAOS_CHECK_EQUAL(
                static_cast< chaos::uint64 >( v ),
                static_cast< chaos::uint64 >( c )
        );
    }
}

//------------------------------------------------------------------------------
//                                  CHAOS::INT16
//------------------------------------------------------------------------------

CHAOS_TEST_UNIT( int16 )
{
    long long values[] = { 1200000, 60000, 3, -0, -20000 };

    CHAOS_TEST_MESSAGE( "Checking byte size" );
    for ( std::size_t i = 0; i < sizeof( values ) / sizeof( long long ); ++i )
    {
        chaos::int16 v = static_cast< chaos::int16 >( values[ i ] );

        CHAOS_CHECK_EQUAL( sizeof( v ), static_cast< std::size_t >( 2 ) );
    }

    CHAOS_TEST_MESSAGE( "Checking cast to char" );
    for ( std::size_t i = 0; i < sizeof( values ) / sizeof( long long ); ++i )
    {
        chaos::int16 v = static_cast< chaos::int16 >( values[ i ] );
        signed short c = static_cast< signed short >( values[ i ] );

        CHAOS_CHECK_EQUAL(
                static_cast< char >( v ),
                static_cast< char >( c )
        );
    }

    CHAOS_TEST_MESSAGE( "Checking cast to signed char" );
    for ( std::size_t i = 0; i < sizeof( values ) / sizeof( long long ); ++i )
    {
        chaos::int16 v = static_cast< chaos::int16 >( values[ i ] );
        signed short c = static_cast< signed short >( values[ i ] );

        CHAOS_CHECK_EQUAL(
                static_cast< signed char >( v ),
                static_cast< signed char >( c )
        );
    }

    CHAOS_TEST_MESSAGE( "Checking cast to unsigned char" );
    for ( std::size_t i = 0; i < sizeof( values ) / sizeof( long long ); ++i )
    {
        chaos::int16 v = static_cast< chaos::int16 >( values[ i ] );
        signed short c = static_cast< signed short >( values[ i ] );

        CHAOS_CHECK_EQUAL(
                static_cast< unsigned char >( v ),
                static_cast< unsigned char >( c )
        );
    }

    CHAOS_TEST_MESSAGE( "Checking cast to signed short" );
    for ( std::size_t i = 0; i < sizeof( values ) / sizeof( long long ); ++i )
    {
        chaos::int16 v = static_cast< chaos::int16 >( values[ i ] );
        signed short c = static_cast< signed short >( values[ i ] );

        CHAOS_CHECK_EQUAL(
                static_cast< signed short >( v ),
                static_cast< signed short >( c )
        );
    }

    CHAOS_TEST_MESSAGE( "Checking cast to unsigned short" );
    for ( std::size_t i = 0; i < sizeof( values ) / sizeof( long long ); ++i )
    {
        chaos::int16 v = static_cast< chaos::int16 >( values[ i ] );
        signed short c = static_cast< signed short >( values[ i ] );

        CHAOS_CHECK_EQUAL(
                static_cast< unsigned short >( v ),
                static_cast< unsigned short >( c )
        );
    }

    CHAOS_TEST_MESSAGE( "Checking cast to signed int" );
    for ( std::size_t i = 0; i < sizeof( values ) / sizeof( long long ); ++i )
    {
        chaos::int16 v = static_cast< chaos::int16 >( values[ i ] );
        signed short c = static_cast< signed short >( values[ i ] );

        CHAOS_CHECK_EQUAL(
                static_cast< signed int >( v ),
                static_cast< signed int >( c )
        );
    }

    CHAOS_TEST_MESSAGE( "Checking cast to unsigned int" );
    for ( std::size_t i = 0; i < sizeof( values ) / sizeof( long long ); ++i )
    {
        chaos::int16 v = static_cast< chaos::int16 >( values[ i ] );
        signed short c = static_cast< signed short >( values[ i ] );

        CHAOS_CHECK_EQUAL(
                static_cast< unsigned int >( v ),
                static_cast< unsigned int >( c )
        );
    }

    CHAOS_TEST_MESSAGE( "Checking cast to signed long" );
    for ( std::size_t i = 0; i < sizeof( values ) / sizeof( long long ); ++i )
    {
        chaos::int16 v = static_cast< chaos::int16 >( values[ i ] );
        signed short c = static_cast< signed short >( values[ i ] );

        CHAOS_CHECK_EQUAL(
                static_cast< signed long >( v ),
                static_cast< signed long >( c )
        );
    }

    CHAOS_TEST_MESSAGE( "Checking cast to unsigned long" );
    for ( std::size_t i = 0; i < sizeof( values ) / sizeof( long long ); ++i )
    {
        chaos::int16 v = static_cast< chaos::int16 >( values[ i ] );
        signed short c = static_cast< signed short >( values[ i ] );

        CHAOS_CHECK_EQUAL(
                static_cast< unsigned long >( v ),
                static_cast< unsigned long >( c )
        );
    }

    CHAOS_TEST_MESSAGE( "Checking cast to chaos int8" );
    for ( std::size_t i = 0; i < sizeof( values ) / sizeof( long long ); ++i )
    {
        chaos::int16 v = static_cast< chaos::int16 >( values[ i ] );
        signed short c = static_cast< signed short >( values[ i ] );

        CHAOS_CHECK_EQUAL(
                static_cast< chaos::int8 >( v ),
                static_cast< chaos::int8 >( c )
        );
    }

    CHAOS_TEST_MESSAGE( "Checking cast to chaos uint8" );
    for ( std::size_t i = 0; i < sizeof( values ) / sizeof( long long ); ++i )
    {
        chaos::int16 v = static_cast< chaos::int16 >( values[ i ] );
        signed short c = static_cast< signed short >( values[ i ] );

        CHAOS_CHECK_EQUAL(
                static_cast< chaos::uint8 >( v ),
                static_cast< chaos::uint8 >( c )
        );
    }

    CHAOS_TEST_MESSAGE( "Checking cast to chaos int16" );
    for ( std::size_t i = 0; i < sizeof( values ) / sizeof( long long ); ++i )
    {
        chaos::int16 v = static_cast< chaos::int16 >( values[ i ] );
        signed short c = static_cast< signed short >( values[ i ] );

        CHAOS_CHECK_EQUAL(
                static_cast< chaos::int16 >( v ),
                static_cast< chaos::int16 >( c )
        );
    }

    CHAOS_TEST_MESSAGE( "Checking cast to chaos uint16" );
    for ( std::size_t i = 0; i < sizeof( values ) / sizeof( long long ); ++i )
    {
        chaos::int16 v = static_cast< chaos::int16 >( values[ i ] );
        signed short c = static_cast< signed short >( values[ i ] );

        CHAOS_CHECK_EQUAL(
                static_cast< chaos::uint16 >( v ),
                static_cast< chaos::uint16 >( c )
        );
    }

    CHAOS_TEST_MESSAGE( "Checking cast to chaos int32" );
    for ( std::size_t i = 0; i < sizeof( values ) / sizeof( long long ); ++i )
    {
        chaos::int16 v = static_cast< chaos::int16 >( values[ i ] );
        signed short c = static_cast< signed short >( values[ i ] );

        CHAOS_CHECK_EQUAL(
                static_cast< chaos::int32 >( v ),
                static_cast< chaos::int32 >( c )
        );
    }

    CHAOS_TEST_MESSAGE( "Checking cast to chaos uint32" );
    for ( std::size_t i = 0; i < sizeof( values ) / sizeof( long long ); ++i )
    {
        chaos::int16 v = static_cast< chaos::int16 >( values[ i ] );
        signed short c = static_cast< signed short >( values[ i ] );

        CHAOS_CHECK_EQUAL(
                static_cast< chaos::uint32 >( v ),
                static_cast< chaos::uint32 >( c )
        );
    }

    CHAOS_TEST_MESSAGE( "Checking cast to chaos int64" );
    for ( std::size_t i = 0; i < sizeof( values ) / sizeof( long long ); ++i )
    {
        chaos::int16 v = static_cast< chaos::int16 >( values[ i ] );
        signed short c = static_cast< signed short >( values[ i ] );

        CHAOS_CHECK_EQUAL(
                static_cast< chaos::int64 >( v ),
                static_cast< chaos::int64 >( c )
        );
    }

    CHAOS_TEST_MESSAGE( "Checking cast to chaos uint64" );
    for ( std::size_t i = 0; i < sizeof( values ) / sizeof( long long ); ++i )
    {
        chaos::int16 v = static_cast< chaos::int16 >( values[ i ] );
        signed short c = static_cast< signed short >( values[ i ] );

        CHAOS_CHECK_EQUAL(
                static_cast< chaos::uint64 >( v ),
                static_cast< chaos::uint64 >( c )
        );
    }
}

//------------------------------------------------------------------------------
//                                 CHAOS::UINT16
//------------------------------------------------------------------------------

CHAOS_TEST_UNIT( uint16 )
{
    long long values[] = { 1200000, 60000, 3, -0, -20000 };

    CHAOS_TEST_MESSAGE( "Checking byte size" );
    for ( std::size_t i = 0; i < sizeof( values ) / sizeof( long long ); ++i )
    {
        chaos::uint16 v = static_cast< chaos::uint16 >( values[ i ] );

        CHAOS_CHECK_EQUAL( sizeof( v ), static_cast< std::size_t >( 2 ) );
    }

    CHAOS_TEST_MESSAGE( "Checking cast to char" );
    for ( std::size_t i = 0; i < sizeof( values ) / sizeof( long long ); ++i )
    {
        chaos::uint16 v = static_cast< chaos::uint16 >( values[ i ] );
        unsigned short c = static_cast< unsigned short >( values[ i ] );

        CHAOS_CHECK_EQUAL(
                static_cast< char >( v ),
                static_cast< char >( c )
        );
    }

    CHAOS_TEST_MESSAGE( "Checking cast to signed char" );
    for ( std::size_t i = 0; i < sizeof( values ) / sizeof( long long ); ++i )
    {
        chaos::uint16 v = static_cast< chaos::uint16 >( values[ i ] );
        unsigned short c = static_cast< unsigned short >( values[ i ] );

        CHAOS_CHECK_EQUAL(
                static_cast< signed char >( v ),
                static_cast< signed char >( c )
        );
    }

    CHAOS_TEST_MESSAGE( "Checking cast to unsigned char" );
    for ( std::size_t i = 0; i < sizeof( values ) / sizeof( long long ); ++i )
    {
        chaos::uint16 v = static_cast< chaos::uint16 >( values[ i ] );
        unsigned short c = static_cast< unsigned short >( values[ i ] );

        CHAOS_CHECK_EQUAL(
                static_cast< unsigned char >( v ),
                static_cast< unsigned char >( c )
        );
    }

    CHAOS_TEST_MESSAGE( "Checking cast to signed short" );
    for ( std::size_t i = 0; i < sizeof( values ) / sizeof( long long ); ++i )
    {
        chaos::uint16 v = static_cast< chaos::uint16 >( values[ i ] );
        unsigned short c = static_cast< unsigned short >( values[ i ] );

        CHAOS_CHECK_EQUAL(
                static_cast< signed short >( v ),
                static_cast< signed short >( c )
        );
    }

    CHAOS_TEST_MESSAGE( "Checking cast to unsigned short" );
    for ( std::size_t i = 0; i < sizeof( values ) / sizeof( long long ); ++i )
    {
        chaos::uint16 v = static_cast< chaos::uint16 >( values[ i ] );
        unsigned short c = static_cast< unsigned short >( values[ i ] );

        CHAOS_CHECK_EQUAL(
                static_cast< unsigned short >( v ),
                static_cast< unsigned short >( c )
        );
    }

    CHAOS_TEST_MESSAGE( "Checking cast to signed int" );
    for ( std::size_t i = 0; i < sizeof( values ) / sizeof( long long ); ++i )
    {
        chaos::uint16 v = static_cast< chaos::uint16 >( values[ i ] );
        unsigned short c = static_cast< unsigned short >( values[ i ] );

        CHAOS_CHECK_EQUAL(
                static_cast< signed int >( v ),
                static_cast< signed int >( c )
        );
    }

    CHAOS_TEST_MESSAGE( "Checking cast to unsigned int" );
    for ( std::size_t i = 0; i < sizeof( values ) / sizeof( long long ); ++i )
    {
        chaos::uint16 v = static_cast< chaos::uint16 >( values[ i ] );
        unsigned short c = static_cast< unsigned short >( values[ i ] );

        CHAOS_CHECK_EQUAL(
                static_cast< unsigned int >( v ),
                static_cast< unsigned int >( c )
        );
    }

    CHAOS_TEST_MESSAGE( "Checking cast to signed long" );
    for ( std::size_t i = 0; i < sizeof( values ) / sizeof( long long ); ++i )
    {
        chaos::uint16 v = static_cast< chaos::uint16 >( values[ i ] );
        unsigned short c = static_cast< unsigned short >( values[ i ] );

        CHAOS_CHECK_EQUAL(
                static_cast< signed long >( v ),
                static_cast< signed long >( c )
        );
    }

    CHAOS_TEST_MESSAGE( "Checking cast to unsigned long" );
    for ( std::size_t i = 0; i < sizeof( values ) / sizeof( long long ); ++i )
    {
        chaos::uint16 v = static_cast< chaos::uint16 >( values[ i ] );
        unsigned short c = static_cast< unsigned short >( values[ i ] );

        CHAOS_CHECK_EQUAL(
                static_cast< unsigned long >( v ),
                static_cast< unsigned long >( c )
        );
    }

    CHAOS_TEST_MESSAGE( "Checking cast to chaos int8" );
    for ( std::size_t i = 0; i < sizeof( values ) / sizeof( long long ); ++i )
    {
        chaos::uint16 v = static_cast< chaos::uint16 >( values[ i ] );
        unsigned short c = static_cast< unsigned short >( values[ i ] );

        CHAOS_CHECK_EQUAL(
                static_cast< chaos::int8 >( v ),
                static_cast< chaos::int8 >( c )
        );
    }

    CHAOS_TEST_MESSAGE( "Checking cast to chaos uint8" );
    for ( std::size_t i = 0; i < sizeof( values ) / sizeof( long long ); ++i )
    {
        chaos::uint16 v = static_cast< chaos::uint16 >( values[ i ] );
        unsigned short c = static_cast< unsigned short >( values[ i ] );

        CHAOS_CHECK_EQUAL(
                static_cast< chaos::uint8 >( v ),
                static_cast< chaos::uint8 >( c )
        );
    }

    CHAOS_TEST_MESSAGE( "Checking cast to chaos int16" );
    for ( std::size_t i = 0; i < sizeof( values ) / sizeof( long long ); ++i )
    {
        chaos::uint16 v = static_cast< chaos::uint16 >( values[ i ] );
        unsigned short c = static_cast< unsigned short >( values[ i ] );

        CHAOS_CHECK_EQUAL(
                static_cast< chaos::int16 >( v ),
                static_cast< chaos::int16 >( c )
        );
    }

    CHAOS_TEST_MESSAGE( "Checking cast to chaos uint16" );
    for ( std::size_t i = 0; i < sizeof( values ) / sizeof( long long ); ++i )
    {
        chaos::uint16 v = static_cast< chaos::uint16 >( values[ i ] );
        unsigned short c = static_cast< unsigned short >( values[ i ] );

        CHAOS_CHECK_EQUAL(
                static_cast< chaos::uint16 >( v ),
                static_cast< chaos::uint16 >( c )
        );
    }

    CHAOS_TEST_MESSAGE( "Checking cast to chaos int32" );
    for ( std::size_t i = 0; i < sizeof( values ) / sizeof( long long ); ++i )
    {
        chaos::uint16 v = static_cast< chaos::uint16 >( values[ i ] );
        unsigned short c = static_cast< unsigned short >( values[ i ] );

        CHAOS_CHECK_EQUAL(
                static_cast< chaos::int32 >( v ),
                static_cast< chaos::int32 >( c )
        );
    }

    CHAOS_TEST_MESSAGE( "Checking cast to chaos uint32" );
    for ( std::size_t i = 0; i < sizeof( values ) / sizeof( long long ); ++i )
    {
        chaos::uint16 v = static_cast< chaos::uint16 >( values[ i ] );
        unsigned short c = static_cast< unsigned short >( values[ i ] );

        CHAOS_CHECK_EQUAL(
                static_cast< chaos::uint32 >( v ),
                static_cast< chaos::uint32 >( c )
        );
    }

    CHAOS_TEST_MESSAGE( "Checking cast to chaos int64" );
    for ( std::size_t i = 0; i < sizeof( values ) / sizeof( long long ); ++i )
    {
        chaos::uint16 v = static_cast< chaos::uint16 >( values[ i ] );
        unsigned short c = static_cast< unsigned short >( values[ i ] );

        CHAOS_CHECK_EQUAL(
                static_cast< chaos::int64 >( v ),
                static_cast< chaos::int64 >( c )
        );
    }

    CHAOS_TEST_MESSAGE( "Checking cast to chaos uint64" );
    for ( std::size_t i = 0; i < sizeof( values ) / sizeof( long long ); ++i )
    {
        chaos::uint16 v = static_cast< chaos::uint16 >( values[ i ] );
        unsigned short c = static_cast< unsigned short >( values[ i ] );

        CHAOS_CHECK_EQUAL(
                static_cast< chaos::uint64 >( v ),
                static_cast< chaos::uint64 >( c )
        );
    }
}

//------------------------------------------------------------------------------
//                                  CHAOS::INT32
//------------------------------------------------------------------------------

CHAOS_TEST_UNIT( int32 )
{
    long long values[] = { 3242349234, 23, 0, -23495858, -42949672968 };

    CHAOS_TEST_MESSAGE( "Checking byte size" );
    for ( std::size_t i = 0; i < sizeof( values ) / sizeof( long long ); ++i )
    {
        chaos::int32 v = static_cast< chaos::int32 >( values[ i ] );

        CHAOS_CHECK_EQUAL( sizeof( v ), static_cast< std::size_t >( 4 ) );
    }

    CHAOS_TEST_MESSAGE( "Checking cast to char" );
    for ( std::size_t i = 0; i < sizeof( values ) / sizeof( long long ); ++i )
    {
        chaos::int32 v = static_cast< chaos::int32 >( values[ i ] );
        signed int c = static_cast< signed int >( values[ i ] );

        CHAOS_CHECK_EQUAL(
                static_cast< char >( v ),
                static_cast< char >( c )
        );
    }

    CHAOS_TEST_MESSAGE( "Checking cast to signed char" );
    for ( std::size_t i = 0; i < sizeof( values ) / sizeof( long long ); ++i )
    {
        chaos::int32 v = static_cast< chaos::int32 >( values[ i ] );
        signed int c = static_cast< signed int >( values[ i ] );

        CHAOS_CHECK_EQUAL(
                static_cast< signed char >( v ),
                static_cast< signed char >( c )
        );
    }

    CHAOS_TEST_MESSAGE( "Checking cast to unsigned char" );
    for ( std::size_t i = 0; i < sizeof( values ) / sizeof( long long ); ++i )
    {
        chaos::int32 v = static_cast< chaos::int32 >( values[ i ] );
        signed int c = static_cast< signed int >( values[ i ] );

        CHAOS_CHECK_EQUAL(
                static_cast< unsigned char >( v ),
                static_cast< unsigned char >( c )
        );
    }

    CHAOS_TEST_MESSAGE( "Checking cast to signed short" );
    for ( std::size_t i = 0; i < sizeof( values ) / sizeof( long long ); ++i )
    {
        chaos::int32 v = static_cast< chaos::int32 >( values[ i ] );
        signed int c = static_cast< signed int >( values[ i ] );

        CHAOS_CHECK_EQUAL(
                static_cast< signed short >( v ),
                static_cast< signed short >( c )
        );
    }

    CHAOS_TEST_MESSAGE( "Checking cast to unsigned short" );
    for ( std::size_t i = 0; i < sizeof( values ) / sizeof( long long ); ++i )
    {
        chaos::int32 v = static_cast< chaos::int32 >( values[ i ] );
        signed int c = static_cast< signed int >( values[ i ] );

        CHAOS_CHECK_EQUAL(
                static_cast< unsigned short >( v ),
                static_cast< unsigned short >( c )
        );
    }

    CHAOS_TEST_MESSAGE( "Checking cast to signed int" );
    for ( std::size_t i = 0; i < sizeof( values ) / sizeof( long long ); ++i )
    {
        chaos::int32 v = static_cast< chaos::int32 >( values[ i ] );
        signed int c = static_cast< signed int >( values[ i ] );

        CHAOS_CHECK_EQUAL(
                static_cast< signed int >( v ),
                static_cast< signed int >( c )
        );
    }

    CHAOS_TEST_MESSAGE( "Checking cast to unsigned int" );
    for ( std::size_t i = 0; i < sizeof( values ) / sizeof( long long ); ++i )
    {
        chaos::int32 v = static_cast< chaos::int32 >( values[ i ] );
        signed int c = static_cast< signed int >( values[ i ] );

        CHAOS_CHECK_EQUAL(
                static_cast< unsigned int >( v ),
                static_cast< unsigned int >( c )
        );
    }

    CHAOS_TEST_MESSAGE( "Checking cast to signed long" );
    for ( std::size_t i = 0; i < sizeof( values ) / sizeof( long long ); ++i )
    {
        chaos::int32 v = static_cast< chaos::int32 >( values[ i ] );
        signed int c = static_cast< signed int >( values[ i ] );

        CHAOS_CHECK_EQUAL(
                static_cast< signed long >( v ),
                static_cast< signed long >( c )
        );
    }

    CHAOS_TEST_MESSAGE( "Checking cast to unsigned long" );
    for ( std::size_t i = 0; i < sizeof( values ) / sizeof( long long ); ++i )
    {
        chaos::int32 v = static_cast< chaos::int32 >( values[ i ] );
        signed int c = static_cast< signed int >( values[ i ] );

        CHAOS_CHECK_EQUAL(
                static_cast< unsigned long >( v ),
                static_cast< unsigned long >( c )
        );
    }

    CHAOS_TEST_MESSAGE( "Checking cast to chaos int8" );
    for ( std::size_t i = 0; i < sizeof( values ) / sizeof( long long ); ++i )
    {
        chaos::int32 v = static_cast< chaos::int32 >( values[ i ] );
        signed int c = static_cast< signed int >( values[ i ] );

        CHAOS_CHECK_EQUAL(
                static_cast< chaos::int8 >( v ),
                static_cast< chaos::int8 >( c )
        );
    }

    CHAOS_TEST_MESSAGE( "Checking cast to chaos uint8" );
    for ( std::size_t i = 0; i < sizeof( values ) / sizeof( long long ); ++i )
    {
        chaos::int32 v = static_cast< chaos::int32 >( values[ i ] );
        signed int c = static_cast< signed int >( values[ i ] );

        CHAOS_CHECK_EQUAL(
                static_cast< chaos::uint8 >( v ),
                static_cast< chaos::uint8 >( c )
        );
    }

    CHAOS_TEST_MESSAGE( "Checking cast to chaos int16" );
    for ( std::size_t i = 0; i < sizeof( values ) / sizeof( long long ); ++i )
    {
        chaos::int32 v = static_cast< chaos::int32 >( values[ i ] );
        signed int c = static_cast< signed int >( values[ i ] );

        CHAOS_CHECK_EQUAL(
                static_cast< chaos::int16 >( v ),
                static_cast< chaos::int16 >( c )
        );
    }

    CHAOS_TEST_MESSAGE( "Checking cast to chaos uint16" );
    for ( std::size_t i = 0; i < sizeof( values ) / sizeof( long long ); ++i )
    {
        chaos::int32 v = static_cast< chaos::int32 >( values[ i ] );
        signed int c = static_cast< signed int >( values[ i ] );

        CHAOS_CHECK_EQUAL(
                static_cast< chaos::uint16 >( v ),
                static_cast< chaos::uint16 >( c )
        );
    }

    CHAOS_TEST_MESSAGE( "Checking cast to chaos int32" );
    for ( std::size_t i = 0; i < sizeof( values ) / sizeof( long long ); ++i )
    {
        chaos::int32 v = static_cast< chaos::int32 >( values[ i ] );
        signed int c = static_cast< signed int >( values[ i ] );

        CHAOS_CHECK_EQUAL(
                static_cast< chaos::int32 >( v ),
                static_cast< chaos::int32 >( c )
        );
    }

    CHAOS_TEST_MESSAGE( "Checking cast to chaos uint32" );
    for ( std::size_t i = 0; i < sizeof( values ) / sizeof( long long ); ++i )
    {
        chaos::int32 v = static_cast< chaos::int32 >( values[ i ] );
        signed int c = static_cast< signed int >( values[ i ] );

        CHAOS_CHECK_EQUAL(
                static_cast< chaos::uint32 >( v ),
                static_cast< chaos::uint32 >( c )
        );
    }

    CHAOS_TEST_MESSAGE( "Checking cast to chaos int64" );
    for ( std::size_t i = 0; i < sizeof( values ) / sizeof( long long ); ++i )
    {
        chaos::int32 v = static_cast< chaos::int32 >( values[ i ] );
        signed int c = static_cast< signed int >( values[ i ] );

        CHAOS_CHECK_EQUAL(
                static_cast< chaos::int64 >( v ),
                static_cast< chaos::int64 >( c )
        );
    }

    CHAOS_TEST_MESSAGE( "Checking cast to chaos uint64" );
    for ( std::size_t i = 0; i < sizeof( values ) / sizeof( long long ); ++i )
    {
        chaos::int32 v = static_cast< chaos::int32 >( values[ i ] );
        signed int c = static_cast< signed int >( values[ i ] );

        CHAOS_CHECK_EQUAL(
                static_cast< chaos::uint64 >( v ),
                static_cast< chaos::uint64 >( c )
        );
    }
}

//------------------------------------------------------------------------------
//                                 CHAOS::UINT32
//------------------------------------------------------------------------------

CHAOS_TEST_UNIT( uint32 )
{
    long long values[] = { 3242349234, 23, 0, -23495858, -42949672968 };

    CHAOS_TEST_MESSAGE( "Checking byte size" );
    for ( std::size_t i = 0; i < sizeof( values ) / sizeof( long long ); ++i )
    {
        chaos::uint32 v = static_cast< chaos::uint32 >( values[ i ] );

        CHAOS_CHECK_EQUAL( sizeof( v ), static_cast< std::size_t >( 4 ) );
    }

    CHAOS_TEST_MESSAGE( "Checking cast to char" );
    for ( std::size_t i = 0; i < sizeof( values ) / sizeof( long long ); ++i )
    {
        chaos::uint32 v = static_cast< chaos::uint32 >( values[ i ] );
        unsigned int c = static_cast< unsigned int >( values[ i ] );

        CHAOS_CHECK_EQUAL(
                static_cast< char >( v ),
                static_cast< char >( c )
        );
    }

    CHAOS_TEST_MESSAGE( "Checking cast to signed char" );
    for ( std::size_t i = 0; i < sizeof( values ) / sizeof( long long ); ++i )
    {
        chaos::uint32 v = static_cast< chaos::uint32 >( values[ i ] );
        unsigned int c = static_cast< unsigned int >( values[ i ] );

        CHAOS_CHECK_EQUAL(
                static_cast< signed char >( v ),
                static_cast< signed char >( c )
        );
    }

    CHAOS_TEST_MESSAGE( "Checking cast to unsigned char" );
    for ( std::size_t i = 0; i < sizeof( values ) / sizeof( long long ); ++i )
    {
        chaos::uint32 v = static_cast< chaos::uint32 >( values[ i ] );
        unsigned int c = static_cast< unsigned int >( values[ i ] );

        CHAOS_CHECK_EQUAL(
                static_cast< unsigned char >( v ),
                static_cast< unsigned char >( c )
        );
    }

    CHAOS_TEST_MESSAGE( "Checking cast to signed short" );
    for ( std::size_t i = 0; i < sizeof( values ) / sizeof( long long ); ++i )
    {
        chaos::uint32 v = static_cast< chaos::uint32 >( values[ i ] );
        unsigned int c = static_cast< unsigned int >( values[ i ] );

        CHAOS_CHECK_EQUAL(
                static_cast< signed short >( v ),
                static_cast< signed short >( c )
        );
    }

    CHAOS_TEST_MESSAGE( "Checking cast to unsigned short" );
    for ( std::size_t i = 0; i < sizeof( values ) / sizeof( long long ); ++i )
    {
        chaos::uint32 v = static_cast< chaos::uint32 >( values[ i ] );
        unsigned int c = static_cast< unsigned int >( values[ i ] );

        CHAOS_CHECK_EQUAL(
                static_cast< unsigned short >( v ),
                static_cast< unsigned short >( c )
        );
    }

    CHAOS_TEST_MESSAGE( "Checking cast to signed int" );
    for ( std::size_t i = 0; i < sizeof( values ) / sizeof( long long ); ++i )
    {
        chaos::uint32 v = static_cast< chaos::uint32 >( values[ i ] );
        unsigned int c = static_cast< unsigned int >( values[ i ] );

        CHAOS_CHECK_EQUAL(
                static_cast< signed int >( v ),
                static_cast< signed int >( c )
        );
    }

    CHAOS_TEST_MESSAGE( "Checking cast to unsigned int" );
    for ( std::size_t i = 0; i < sizeof( values ) / sizeof( long long ); ++i )
    {
        chaos::uint32 v = static_cast< chaos::uint32 >( values[ i ] );
        unsigned int c = static_cast< unsigned int >( values[ i ] );

        CHAOS_CHECK_EQUAL(
                static_cast< unsigned int >( v ),
                static_cast< unsigned int >( c )
        );
    }

    CHAOS_TEST_MESSAGE( "Checking cast to signed long" );
    for ( std::size_t i = 0; i < sizeof( values ) / sizeof( long long ); ++i )
    {
        chaos::uint32 v = static_cast< chaos::uint32 >( values[ i ] );
        unsigned int c = static_cast< unsigned int >( values[ i ] );

        CHAOS_CHECK_EQUAL(
                static_cast< signed long >( v ),
                static_cast< signed long >( c )
        );
    }

    CHAOS_TEST_MESSAGE( "Checking cast to unsigned long" );
    for ( std::size_t i = 0; i < sizeof( values ) / sizeof( long long ); ++i )
    {
        chaos::uint32 v = static_cast< chaos::uint32 >( values[ i ] );
        unsigned int c = static_cast< unsigned int >( values[ i ] );

        CHAOS_CHECK_EQUAL(
                static_cast< unsigned long >( v ),
                static_cast< unsigned long >( c )
        );
    }

    CHAOS_TEST_MESSAGE( "Checking cast to chaos int8" );
    for ( std::size_t i = 0; i < sizeof( values ) / sizeof( long long ); ++i )
    {
        chaos::uint32 v = static_cast< chaos::uint32 >( values[ i ] );
        unsigned int c = static_cast< unsigned int >( values[ i ] );

        CHAOS_CHECK_EQUAL(
                static_cast< chaos::int8 >( v ),
                static_cast< chaos::int8 >( c )
        );
    }

    CHAOS_TEST_MESSAGE( "Checking cast to chaos uint8" );
    for ( std::size_t i = 0; i < sizeof( values ) / sizeof( long long ); ++i )
    {
        chaos::uint32 v = static_cast< chaos::uint32 >( values[ i ] );
        unsigned int c = static_cast< unsigned int >( values[ i ] );

        CHAOS_CHECK_EQUAL(
                static_cast< chaos::uint8 >( v ),
                static_cast< chaos::uint8 >( c )
        );
    }

    CHAOS_TEST_MESSAGE( "Checking cast to chaos int16" );
    for ( std::size_t i = 0; i < sizeof( values ) / sizeof( long long ); ++i )
    {
        chaos::uint32 v = static_cast< chaos::uint32 >( values[ i ] );
        unsigned int c = static_cast< unsigned int >( values[ i ] );

        CHAOS_CHECK_EQUAL(
                static_cast< chaos::int16 >( v ),
                static_cast< chaos::int16 >( c )
        );
    }

    CHAOS_TEST_MESSAGE( "Checking cast to chaos uint16" );
    for ( std::size_t i = 0; i < sizeof( values ) / sizeof( long long ); ++i )
    {
        chaos::uint32 v = static_cast< chaos::uint32 >( values[ i ] );
        unsigned int c = static_cast< unsigned int >( values[ i ] );

        CHAOS_CHECK_EQUAL(
                static_cast< chaos::uint16 >( v ),
                static_cast< chaos::uint16 >( c )
        );
    }

    CHAOS_TEST_MESSAGE( "Checking cast to chaos int32" );
    for ( std::size_t i = 0; i < sizeof( values ) / sizeof( long long ); ++i )
    {
        chaos::uint32 v = static_cast< chaos::uint32 >( values[ i ] );
        unsigned int c = static_cast< unsigned int >( values[ i ] );

        CHAOS_CHECK_EQUAL(
                static_cast< chaos::int32 >( v ),
                static_cast< chaos::int32 >( c )
        );
    }

    CHAOS_TEST_MESSAGE( "Checking cast to chaos uint32" );
    for ( std::size_t i = 0; i < sizeof( values ) / sizeof( long long ); ++i )
    {
        chaos::uint32 v = static_cast< chaos::uint32 >( values[ i ] );
        unsigned int c = static_cast< unsigned int >( values[ i ] );

        CHAOS_CHECK_EQUAL(
                static_cast< chaos::uint32 >( v ),
                static_cast< chaos::uint32 >( c )
        );
    }

    CHAOS_TEST_MESSAGE( "Checking cast to chaos int64" );
    for ( std::size_t i = 0; i < sizeof( values ) / sizeof( long long ); ++i )
    {
        chaos::uint32 v = static_cast< chaos::uint32 >( values[ i ] );
        unsigned int c = static_cast< unsigned int >( values[ i ] );

        CHAOS_CHECK_EQUAL(
                static_cast< chaos::int64 >( v ),
                static_cast< chaos::int64 >( c )
        );
    }

    CHAOS_TEST_MESSAGE( "Checking cast to chaos uint64" );
    for ( std::size_t i = 0; i < sizeof( values ) / sizeof( long long ); ++i )
    {
        chaos::uint32 v = static_cast< chaos::uint32 >( values[ i ] );
        unsigned int c = static_cast< unsigned int >( values[ i ] );

        CHAOS_CHECK_EQUAL(
                static_cast< chaos::uint64 >( v ),
                static_cast< chaos::uint64 >( c )
        );
    }
}

//------------------------------------------------------------------------------
//                                  CHAOS::INT64
//------------------------------------------------------------------------------

CHAOS_TEST_UNIT( int64 )
{
    // TODO: hard to test negative values here due to Windows having 4 a byte
    // wide long
    long long values[] = { 3554534, 2353, 232, 23, 0 };

    CHAOS_TEST_MESSAGE( "Checking byte size" );
    for ( std::size_t i = 0; i < sizeof( values ) / sizeof( long long ); ++i )
    {
        chaos::int64 v = static_cast< chaos::int64 >( values[ i ] );

        CHAOS_CHECK_EQUAL( sizeof( v ), static_cast< std::size_t >( 8 ) );
    }

    CHAOS_TEST_MESSAGE( "Checking cast to char" );
    for ( std::size_t i = 0; i < sizeof( values ) / sizeof( long long ); ++i )
    {
        chaos::int64 v = static_cast< chaos::int64 >( values[ i ] );
        signed long c = static_cast< signed long >( values[ i ] );

        CHAOS_CHECK_EQUAL(
                static_cast< char >( v ),
                static_cast< char >( c )
        );
    }

    CHAOS_TEST_MESSAGE( "Checking cast to signed char" );
    for ( std::size_t i = 0; i < sizeof( values ) / sizeof( long long ); ++i )
    {
        chaos::int64 v = static_cast< chaos::int64 >( values[ i ] );
        signed long c = static_cast< signed long >( values[ i ] );

        CHAOS_CHECK_EQUAL(
                static_cast< signed char >( v ),
                static_cast< signed char >( c )
        );
    }

    CHAOS_TEST_MESSAGE( "Checking cast to unsigned char" );
    for ( std::size_t i = 0; i < sizeof( values ) / sizeof( long long ); ++i )
    {
        chaos::int64 v = static_cast< chaos::int64 >( values[ i ] );
        signed long c = static_cast< signed long >( values[ i ] );

        CHAOS_CHECK_EQUAL(
                static_cast< unsigned char >( v ),
                static_cast< unsigned char >( c )
        );
    }

    CHAOS_TEST_MESSAGE( "Checking cast to signed short" );
    for ( std::size_t i = 0; i < sizeof( values ) / sizeof( long long ); ++i )
    {
        chaos::int64 v = static_cast< chaos::int64 >( values[ i ] );
        signed long c = static_cast< signed long >( values[ i ] );

        CHAOS_CHECK_EQUAL(
                static_cast< signed short >( v ),
                static_cast< signed short >( c )
        );
    }

    CHAOS_TEST_MESSAGE( "Checking cast to unsigned short" );
    for ( std::size_t i = 0; i < sizeof( values ) / sizeof( long long ); ++i )
    {
        chaos::int64 v = static_cast< chaos::int64 >( values[ i ] );
        signed long c = static_cast< signed long >( values[ i ] );

        CHAOS_CHECK_EQUAL(
                static_cast< unsigned short >( v ),
                static_cast< unsigned short >( c )
        );
    }

    CHAOS_TEST_MESSAGE( "Checking cast to signed int" );
    for ( std::size_t i = 0; i < sizeof( values ) / sizeof( long long ); ++i )
    {
        chaos::int64 v = static_cast< chaos::int64 >( values[ i ] );
        signed long c = static_cast< signed long >( values[ i ] );

        CHAOS_CHECK_EQUAL(
                static_cast< signed int >( v ),
                static_cast< signed int >( c )
        );
    }

    CHAOS_TEST_MESSAGE( "Checking cast to unsigned int" );
    for ( std::size_t i = 0; i < sizeof( values ) / sizeof( long long ); ++i )
    {
        chaos::int64 v = static_cast< chaos::int64 >( values[ i ] );
        signed long c = static_cast< signed long >( values[ i ] );

        CHAOS_CHECK_EQUAL(
                static_cast< unsigned int >( v ),
                static_cast< unsigned int >( c )
        );
    }

    CHAOS_TEST_MESSAGE( "Checking cast to signed long" );
    for ( std::size_t i = 0; i < sizeof( values ) / sizeof( long long ); ++i )
    {
        chaos::int64 v = static_cast< chaos::int64 >( values[ i ] );
        signed long c = static_cast< signed long >( values[ i ] );

        CHAOS_CHECK_EQUAL(
                static_cast< signed long >( v ),
                static_cast< signed long >( c )
        );
    }

    CHAOS_TEST_MESSAGE( "Checking cast to unsigned long" );
    for ( std::size_t i = 0; i < sizeof( values ) / sizeof( long long ); ++i )
    {
        chaos::int64 v = static_cast< chaos::int64 >( values[ i ] );
        signed long c = static_cast< signed long >( values[ i ] );

        CHAOS_CHECK_EQUAL(
                static_cast< unsigned long >( v ),
                static_cast< unsigned long >( c )
        );
    }

    CHAOS_TEST_MESSAGE( "Checking cast to chaos int8" );
    for ( std::size_t i = 0; i < sizeof( values ) / sizeof( long long ); ++i )
    {
        chaos::int64 v = static_cast< chaos::int64 >( values[ i ] );
        signed long c = static_cast< signed long >( values[ i ] );

        CHAOS_CHECK_EQUAL(
                static_cast< chaos::int8 >( v ),
                static_cast< chaos::int8 >( c )
        );
    }

    CHAOS_TEST_MESSAGE( "Checking cast to chaos uint8" );
    for ( std::size_t i = 0; i < sizeof( values ) / sizeof( long long ); ++i )
    {
        chaos::int64 v = static_cast< chaos::int64 >( values[ i ] );
        signed long c = static_cast< signed long >( values[ i ] );

        CHAOS_CHECK_EQUAL(
                static_cast< chaos::uint8 >( v ),
                static_cast< chaos::uint8 >( c )
        );
    }

    CHAOS_TEST_MESSAGE( "Checking cast to chaos int16" );
    for ( std::size_t i = 0; i < sizeof( values ) / sizeof( long long ); ++i )
    {
        chaos::int64 v = static_cast< chaos::int64 >( values[ i ] );
        signed long c = static_cast< signed long >( values[ i ] );

        CHAOS_CHECK_EQUAL(
                static_cast< chaos::int16 >( v ),
                static_cast< chaos::int16 >( c )
        );
    }

    CHAOS_TEST_MESSAGE( "Checking cast to chaos uint16" );
    for ( std::size_t i = 0; i < sizeof( values ) / sizeof( long long ); ++i )
    {
        chaos::int64 v = static_cast< chaos::int64 >( values[ i ] );
        signed long c = static_cast< signed long >( values[ i ] );

        CHAOS_CHECK_EQUAL(
                static_cast< chaos::uint16 >( v ),
                static_cast< chaos::uint16 >( c )
        );
    }

    CHAOS_TEST_MESSAGE( "Checking cast to chaos int32" );
    for ( std::size_t i = 0; i < sizeof( values ) / sizeof( long long ); ++i )
    {
        chaos::int64 v = static_cast< chaos::int64 >( values[ i ] );
        signed long c = static_cast< signed long >( values[ i ] );

        CHAOS_CHECK_EQUAL(
                static_cast< chaos::int32 >( v ),
                static_cast< chaos::int32 >( c )
        );
    }

    CHAOS_TEST_MESSAGE( "Checking cast to chaos uint32" );
    for ( std::size_t i = 0; i < sizeof( values ) / sizeof( long long ); ++i )
    {
        chaos::int64 v = static_cast< chaos::int64 >( values[ i ] );
        signed long c = static_cast< signed long >( values[ i ] );

        CHAOS_CHECK_EQUAL(
                static_cast< chaos::uint32 >( v ),
                static_cast< chaos::uint32 >( c )
        );
    }

    CHAOS_TEST_MESSAGE( "Checking cast to chaos int64" );
    for ( std::size_t i = 0; i < sizeof( values ) / sizeof( long long ); ++i )
    {
        chaos::int64 v = static_cast< chaos::int64 >( values[ i ] );
        signed long c = static_cast< signed long >( values[ i ] );

        CHAOS_CHECK_EQUAL(
                static_cast< chaos::int64 >( v ),
                static_cast< chaos::int64 >( c )
        );
    }

    CHAOS_TEST_MESSAGE( "Checking cast to chaos uint64" );
    for ( std::size_t i = 0; i < sizeof( values ) / sizeof( long long ); ++i )
    {
        chaos::int64 v = static_cast< chaos::int64 >( values[ i ] );
        signed long c = static_cast< signed long >( values[ i ] );

        CHAOS_CHECK_EQUAL(
                static_cast< chaos::uint64 >( v ),
                static_cast< chaos::uint64 >( c )
        );
    }
}

//------------------------------------------------------------------------------
//                                 CHAOS::UINT64
//------------------------------------------------------------------------------


CHAOS_TEST_UNIT( uint64 )
{
    // TODO: hard to test negative values here due to Windows having 4 a byte
    // wide long
    long long values[] = { 3554534, 2353, 232, 23, 0 };

    CHAOS_TEST_MESSAGE( "Checking byte size" );
    for ( std::size_t i = 0; i < sizeof( values ) / sizeof( long long ); ++i )
    {
        chaos::uint64 v = static_cast< chaos::uint64 >( values[ i ] );

        CHAOS_CHECK_EQUAL( sizeof( v ), static_cast< std::size_t >( 8 ) );
    }

    CHAOS_TEST_MESSAGE( "Checking cast to char" );
    for ( std::size_t i = 0; i < sizeof( values ) / sizeof( long long ); ++i )
    {
        chaos::uint64 v = static_cast< chaos::uint64 >( values[ i ] );
        unsigned long c = static_cast< unsigned long >( values[ i ] );

        CHAOS_CHECK_EQUAL(
                static_cast< char >( v ),
                static_cast< char >( c )
        );
    }

    CHAOS_TEST_MESSAGE( "Checking cast to signed char" );
    for ( std::size_t i = 0; i < sizeof( values ) / sizeof( long long ); ++i )
    {
        chaos::uint64 v = static_cast< chaos::uint64 >( values[ i ] );
        unsigned long c = static_cast< unsigned long >( values[ i ] );

        CHAOS_CHECK_EQUAL(
                static_cast< signed char >( v ),
                static_cast< signed char >( c )
        );
    }

    CHAOS_TEST_MESSAGE( "Checking cast to unsigned char" );
    for ( std::size_t i = 0; i < sizeof( values ) / sizeof( long long ); ++i )
    {
        chaos::uint64 v = static_cast< chaos::uint64 >( values[ i ] );
        unsigned long c = static_cast< unsigned long >( values[ i ] );

        CHAOS_CHECK_EQUAL(
                static_cast< unsigned char >( v ),
                static_cast< unsigned char >( c )
        );
    }

    CHAOS_TEST_MESSAGE( "Checking cast to signed short" );
    for ( std::size_t i = 0; i < sizeof( values ) / sizeof( long long ); ++i )
    {
        chaos::uint64 v = static_cast< chaos::uint64 >( values[ i ] );
        unsigned long c = static_cast< unsigned long >( values[ i ] );

        CHAOS_CHECK_EQUAL(
                static_cast< signed short >( v ),
                static_cast< signed short >( c )
        );
    }

    CHAOS_TEST_MESSAGE( "Checking cast to unsigned short" );
    for ( std::size_t i = 0; i < sizeof( values ) / sizeof( long long ); ++i )
    {
        chaos::uint64 v = static_cast< chaos::uint64 >( values[ i ] );
        unsigned long c = static_cast< unsigned long >( values[ i ] );

        CHAOS_CHECK_EQUAL(
                static_cast< unsigned short >( v ),
                static_cast< unsigned short >( c )
        );
    }

    CHAOS_TEST_MESSAGE( "Checking cast to signed int" );
    for ( std::size_t i = 0; i < sizeof( values ) / sizeof( long long ); ++i )
    {
        chaos::uint64 v = static_cast< chaos::uint64 >( values[ i ] );
        unsigned long c = static_cast< unsigned long >( values[ i ] );

        CHAOS_CHECK_EQUAL(
                static_cast< signed int >( v ),
                static_cast< signed int >( c )
        );
    }

    CHAOS_TEST_MESSAGE( "Checking cast to unsigned int" );
    for ( std::size_t i = 0; i < sizeof( values ) / sizeof( long long ); ++i )
    {
        chaos::uint64 v = static_cast< chaos::uint64 >( values[ i ] );
        unsigned long c = static_cast< unsigned long >( values[ i ] );

        CHAOS_CHECK_EQUAL(
                static_cast< unsigned int >( v ),
                static_cast< unsigned int >( c )
        );
    }

    CHAOS_TEST_MESSAGE( "Checking cast to signed long" );
    for ( std::size_t i = 0; i < sizeof( values ) / sizeof( long long ); ++i )
    {
        chaos::uint64 v = static_cast< chaos::uint64 >( values[ i ] );
        unsigned long c = static_cast< unsigned long >( values[ i ] );

        CHAOS_CHECK_EQUAL(
                static_cast< signed long >( v ),
                static_cast< signed long >( c )
        );
    }

    CHAOS_TEST_MESSAGE( "Checking cast to unsigned long" );
    for ( std::size_t i = 0; i < sizeof( values ) / sizeof( long long ); ++i )
    {
        chaos::uint64 v = static_cast< chaos::uint64 >( values[ i ] );
        unsigned long c = static_cast< unsigned long >( values[ i ] );

        CHAOS_CHECK_EQUAL(
                static_cast< unsigned long >( v ),
                static_cast< unsigned long >( c )
        );
    }

    CHAOS_TEST_MESSAGE( "Checking cast to chaos int8" );
    for ( std::size_t i = 0; i < sizeof( values ) / sizeof( long long ); ++i )
    {
        chaos::uint64 v = static_cast< chaos::uint64 >( values[ i ] );
        unsigned long c = static_cast< unsigned long >( values[ i ] );

        CHAOS_CHECK_EQUAL(
                static_cast< chaos::int8 >( v ),
                static_cast< chaos::int8 >( c )
        );
    }

    CHAOS_TEST_MESSAGE( "Checking cast to chaos uint8" );
    for ( std::size_t i = 0; i < sizeof( values ) / sizeof( long long ); ++i )
    {
        chaos::uint64 v = static_cast< chaos::uint64 >( values[ i ] );
        unsigned long c = static_cast< unsigned long >( values[ i ] );

        CHAOS_CHECK_EQUAL(
                static_cast< chaos::uint8 >( v ),
                static_cast< chaos::uint8 >( c )
        );
    }

    CHAOS_TEST_MESSAGE( "Checking cast to chaos int16" );
    for ( std::size_t i = 0; i < sizeof( values ) / sizeof( long long ); ++i )
    {
        chaos::uint64 v = static_cast< chaos::uint64 >( values[ i ] );
        unsigned long c = static_cast< unsigned long >( values[ i ] );

        CHAOS_CHECK_EQUAL(
                static_cast< chaos::int16 >( v ),
                static_cast< chaos::int16 >( c )
        );
    }

    CHAOS_TEST_MESSAGE( "Checking cast to chaos uint16" );
    for ( std::size_t i = 0; i < sizeof( values ) / sizeof( long long ); ++i )
    {
        chaos::uint64 v = static_cast< chaos::uint64 >( values[ i ] );
        unsigned long c = static_cast< unsigned long >( values[ i ] );

        CHAOS_CHECK_EQUAL(
                static_cast< chaos::uint16 >( v ),
                static_cast< chaos::uint16 >( c )
        );
    }

    CHAOS_TEST_MESSAGE( "Checking cast to chaos int32" );
    for ( std::size_t i = 0; i < sizeof( values ) / sizeof( long long ); ++i )
    {
        chaos::uint64 v = static_cast< chaos::uint64 >( values[ i ] );
        unsigned long c = static_cast< unsigned long >( values[ i ] );

        CHAOS_CHECK_EQUAL(
                static_cast< chaos::int32 >( v ),
                static_cast< chaos::int32 >( c )
        );
    }

    CHAOS_TEST_MESSAGE( "Checking cast to chaos uint32" );
    for ( std::size_t i = 0; i < sizeof( values ) / sizeof( long long ); ++i )
    {
        chaos::uint64 v = static_cast< chaos::uint64 >( values[ i ] );
        unsigned long c = static_cast< unsigned long >( values[ i ] );

        CHAOS_CHECK_EQUAL(
                static_cast< chaos::uint32 >( v ),
                static_cast< chaos::uint32 >( c )
        );
    }

    CHAOS_TEST_MESSAGE( "Checking cast to chaos int64" );
    for ( std::size_t i = 0; i < sizeof( values ) / sizeof( long long ); ++i )
    {
        chaos::uint64 v = static_cast< chaos::uint64 >( values[ i ] );
        unsigned long c = static_cast< unsigned long >( values[ i ] );

        CHAOS_CHECK_EQUAL(
                static_cast< chaos::int64 >( v ),
                static_cast< chaos::int64 >( c )
        );
    }

    CHAOS_TEST_MESSAGE( "Checking cast to chaos uint64" );
    for ( std::size_t i = 0; i < sizeof( values ) / sizeof( long long ); ++i )
    {
        chaos::uint64 v = static_cast< chaos::uint64 >( values[ i ] );
        unsigned long c = static_cast< unsigned long >( values[ i ] );

        CHAOS_CHECK_EQUAL(
                static_cast< chaos::uint64 >( v ),
                static_cast< chaos::uint64 >( c )
        );
    }
}

} // namespace types_tests
