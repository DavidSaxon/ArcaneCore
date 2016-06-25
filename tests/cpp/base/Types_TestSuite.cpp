#include "arcanecore/test/ArcTest.hpp"

ARC_TEST_MODULE(base.Types)

#include "arcanecore/base/Types.hpp"

namespace types_tests
{

//------------------------------------------------------------------------------
//                                  ARC::INT8
//------------------------------------------------------------------------------

ARC_TEST_UNIT( int8 )
{
    long long values[] = { 1024, 65, 0, -10, -455 };

    ARC_TEST_MESSAGE( "Checking byte size" );
    for ( std::size_t i = 0; i < sizeof( values ) / sizeof( long long ); ++i )
    {
        arc::int8 v = static_cast< arc::int8 >( values[ i ] );

        ARC_CHECK_EQUAL( sizeof( v ), static_cast< size_t >( 1 ) );
    }

    ARC_TEST_MESSAGE( "Checking cast to char" );
    for ( std::size_t i = 0; i < sizeof( values ) / sizeof( long long ); ++i )
    {
        arc::int8 v = static_cast< arc::int8 >( values[ i ] );
        signed char c = static_cast< signed char >( values[ i ] );

        ARC_CHECK_EQUAL(
                static_cast< char >( v ),
                static_cast< char >( c )
        );
    }

    ARC_TEST_MESSAGE( "Checking cast to signed char" );
    for ( std::size_t i = 0; i < sizeof( values ) / sizeof( long long ); ++i )
    {
        arc::int8 v = static_cast< arc::int8 >( values[ i ] );
        signed char c = static_cast< signed char >( values[ i ] );

        ARC_CHECK_EQUAL(
                static_cast< signed char >( v ),
                static_cast< signed char >( c )
        );
    }

    ARC_TEST_MESSAGE( "Checking cast to unsigned char" );
    for ( std::size_t i = 0; i < sizeof( values ) / sizeof( long long ); ++i )
    {
        arc::int8 v = static_cast< arc::int8 >( values[ i ] );
        signed char c = static_cast< signed char >( values[ i ] );

        ARC_CHECK_EQUAL(
                static_cast< unsigned char >( v ),
                static_cast< unsigned char >( c )
        );
    }

    ARC_TEST_MESSAGE( "Checking cast to signed short" );
    for ( std::size_t i = 0; i < sizeof( values ) / sizeof( long long ); ++i )
    {
        arc::int8 v = static_cast< arc::int8 >( values[ i ] );
        signed char c = static_cast< signed char >( values[ i ] );

        ARC_CHECK_EQUAL(
                static_cast< signed short >( v ),
                static_cast< signed short >( c )
        );
    }

    ARC_TEST_MESSAGE( "Checking cast to unsigned short" );
    for ( std::size_t i = 0; i < sizeof( values ) / sizeof( long long ); ++i )
    {
        arc::int8 v = static_cast< arc::int8 >( values[ i ] );
        signed char c = static_cast< signed char >( values[ i ] );

        ARC_CHECK_EQUAL(
                static_cast< unsigned short >( v ),
                static_cast< unsigned short >( c )
        );
    }

    ARC_TEST_MESSAGE( "Checking cast to signed int" );
    for ( std::size_t i = 0; i < sizeof( values ) / sizeof( long long ); ++i )
    {
        arc::int8 v = static_cast< arc::int8 >( values[ i ] );
        signed char c = static_cast< signed char >( values[ i ] );

        ARC_CHECK_EQUAL(
                static_cast< signed int >( v ),
                static_cast< signed int >( c )
        );
    }

    ARC_TEST_MESSAGE( "Checking cast to unsigned int" );
    for ( std::size_t i = 0; i < sizeof( values ) / sizeof( long long ); ++i )
    {
        arc::int8 v = static_cast< arc::int8 >( values[ i ] );
        signed char c = static_cast< signed char >( values[ i ] );

        ARC_CHECK_EQUAL(
                static_cast< unsigned int >( v ),
                static_cast< unsigned int >( c )
        );
    }

    ARC_TEST_MESSAGE( "Checking cast to signed long" );
    for ( std::size_t i = 0; i < sizeof( values ) / sizeof( long long ); ++i )
    {
        arc::int8 v = static_cast< arc::int8 >( values[ i ] );
        signed char c = static_cast< signed char >( values[ i ] );

        ARC_CHECK_EQUAL(
                static_cast< signed long >( v ),
                static_cast< signed long >( c )
        );
    }

    ARC_TEST_MESSAGE( "Checking cast to unsigned long" );
    for ( std::size_t i = 0; i < sizeof( values ) / sizeof( long long ); ++i )
    {
        arc::int8 v = static_cast< arc::int8 >( values[ i ] );
        signed char c = static_cast< signed char >( values[ i ] );

        ARC_CHECK_EQUAL(
                static_cast< unsigned long >( v ),
                static_cast< unsigned long >( c )
        );
    }

    ARC_TEST_MESSAGE( "Checking cast to arc int8" );
    for ( std::size_t i = 0; i < sizeof( values ) / sizeof( long long ); ++i )
    {
        arc::int8 v = static_cast< arc::int8 >( values[ i ] );
        signed char c = static_cast< signed char >( values[ i ] );

        ARC_CHECK_EQUAL(
                static_cast< arc::int8 >( v ),
                static_cast< arc::int8 >( c )
        );
    }

    ARC_TEST_MESSAGE( "Checking cast to arc uint8" );
    for ( std::size_t i = 0; i < sizeof( values ) / sizeof( long long ); ++i )
    {
        arc::int8 v = static_cast< arc::int8 >( values[ i ] );
        signed char c = static_cast< signed char >( values[ i ] );

        ARC_CHECK_EQUAL(
                static_cast< arc::uint8 >( v ),
                static_cast< arc::uint8 >( c )
        );
    }

    ARC_TEST_MESSAGE( "Checking cast to arc int16" );
    for ( std::size_t i = 0; i < sizeof( values ) / sizeof( long long ); ++i )
    {
        arc::int8 v = static_cast< arc::int8 >( values[ i ] );
        signed char c = static_cast< signed char >( values[ i ] );

        ARC_CHECK_EQUAL(
                static_cast< arc::int16 >( v ),
                static_cast< arc::int16 >( c )
        );
    }

    ARC_TEST_MESSAGE( "Checking cast to arc uint16" );
    for ( std::size_t i = 0; i < sizeof( values ) / sizeof( long long ); ++i )
    {
        arc::int8 v = static_cast< arc::int8 >( values[ i ] );
        signed char c = static_cast< signed char >( values[ i ] );

        ARC_CHECK_EQUAL(
                static_cast< arc::uint16 >( v ),
                static_cast< arc::uint16 >( c )
        );
    }

    ARC_TEST_MESSAGE( "Checking cast to arc int32" );
    for ( std::size_t i = 0; i < sizeof( values ) / sizeof( long long ); ++i )
    {
        arc::int8 v = static_cast< arc::int8 >( values[ i ] );
        signed char c = static_cast< signed char >( values[ i ] );

        ARC_CHECK_EQUAL(
                static_cast< arc::int32 >( v ),
                static_cast< arc::int32 >( c )
        );
    }

    ARC_TEST_MESSAGE( "Checking cast to arc uint32" );
    for ( std::size_t i = 0; i < sizeof( values ) / sizeof( long long ); ++i )
    {
        arc::int8 v = static_cast< arc::int8 >( values[ i ] );
        signed char c = static_cast< signed char >( values[ i ] );

        ARC_CHECK_EQUAL(
                static_cast< arc::uint32 >( v ),
                static_cast< arc::uint32 >( c )
        );
    }

    ARC_TEST_MESSAGE( "Checking cast to arc int64" );
    for ( std::size_t i = 0; i < sizeof( values ) / sizeof( long long ); ++i )
    {
        arc::int8 v = static_cast< arc::int8 >( values[ i ] );
        signed char c = static_cast< signed char >( values[ i ] );

        ARC_CHECK_EQUAL(
                static_cast< arc::int64 >( v ),
                static_cast< arc::int64 >( c )
        );
    }

    ARC_TEST_MESSAGE( "Checking cast to arc uint64" );
    for ( std::size_t i = 0; i < sizeof( values ) / sizeof( long long ); ++i )
    {
        arc::int8 v = static_cast< arc::int8 >( values[ i ] );
        signed char c = static_cast< signed char >( values[ i ] );

        ARC_CHECK_EQUAL(
                static_cast< arc::uint64 >( v ),
                static_cast< arc::uint64 >( c )
        );
    }
}

//------------------------------------------------------------------------------
//                                  ARC::UINT8
//------------------------------------------------------------------------------

ARC_TEST_UNIT( uint8 )
{
    long long values[] = { 1024, 65, 0, -10, -455 };

    ARC_TEST_MESSAGE( "Checking byte size" );
    for ( std::size_t i = 0; i < sizeof( values ) / sizeof( long long ); ++i )
    {
        arc::uint8 v = static_cast< arc::uint8 >( values[ i ] );

        ARC_CHECK_EQUAL( sizeof( v ), static_cast< std::size_t >( 1 ) );
    }

    ARC_TEST_MESSAGE( "Checking cast to char" );
    for ( std::size_t i = 0; i < sizeof( values ) / sizeof( long long ); ++i )
    {
        arc::uint8 v = static_cast< arc::uint8 >( values[ i ] );
        unsigned char c = static_cast< unsigned char >( values[ i ] );

        ARC_CHECK_EQUAL(
                static_cast< char >( v ),
                static_cast< char >( c )
        );
    }

    ARC_TEST_MESSAGE( "Checking cast to signed char" );
    for ( std::size_t i = 0; i < sizeof( values ) / sizeof( long long ); ++i )
    {
        arc::uint8 v = static_cast< arc::uint8 >( values[ i ] );
        unsigned char c = static_cast< unsigned char >( values[ i ] );

        ARC_CHECK_EQUAL(
                static_cast< signed char >( v ),
                static_cast< signed char >( c )
        );
    }

    ARC_TEST_MESSAGE( "Checking cast to unsigned char" );
    for ( std::size_t i = 0; i < sizeof( values ) / sizeof( long long ); ++i )
    {
        arc::uint8 v = static_cast< arc::uint8 >( values[ i ] );
        unsigned char c = static_cast< unsigned char >( values[ i ] );

        ARC_CHECK_EQUAL(
                static_cast< unsigned char >( v ),
                static_cast< unsigned char >( c )
        );
    }

    ARC_TEST_MESSAGE( "Checking cast to signed short" );
    for ( std::size_t i = 0; i < sizeof( values ) / sizeof( long long ); ++i )
    {
        arc::uint8 v = static_cast< arc::uint8 >( values[ i ] );
        unsigned char c = static_cast< unsigned char >( values[ i ] );

        ARC_CHECK_EQUAL(
                static_cast< signed short >( v ),
                static_cast< signed short >( c )
        );
    }

    ARC_TEST_MESSAGE( "Checking cast to unsigned short" );
    for ( std::size_t i = 0; i < sizeof( values ) / sizeof( long long ); ++i )
    {
        arc::uint8 v = static_cast< arc::uint8 >( values[ i ] );
        unsigned char c = static_cast< unsigned char >( values[ i ] );

        ARC_CHECK_EQUAL(
                static_cast< unsigned short >( v ),
                static_cast< unsigned short >( c )
        );
    }

    ARC_TEST_MESSAGE( "Checking cast to signed int" );
    for ( std::size_t i = 0; i < sizeof( values ) / sizeof( long long ); ++i )
    {
        arc::uint8 v = static_cast< arc::uint8 >( values[ i ] );
        unsigned char c = static_cast< unsigned char >( values[ i ] );

        ARC_CHECK_EQUAL(
                static_cast< signed int >( v ),
                static_cast< signed int >( c )
        );
    }

    ARC_TEST_MESSAGE( "Checking cast to unsigned int" );
    for ( std::size_t i = 0; i < sizeof( values ) / sizeof( long long ); ++i )
    {
        arc::uint8 v = static_cast< arc::uint8 >( values[ i ] );
        unsigned char c = static_cast< unsigned char >( values[ i ] );

        ARC_CHECK_EQUAL(
                static_cast< unsigned int >( v ),
                static_cast< unsigned int >( c )
        );
    }

    ARC_TEST_MESSAGE( "Checking cast to signed long" );
    for ( std::size_t i = 0; i < sizeof( values ) / sizeof( long long ); ++i )
    {
        arc::uint8 v = static_cast< arc::uint8 >( values[ i ] );
        unsigned char c = static_cast< unsigned char >( values[ i ] );

        ARC_CHECK_EQUAL(
                static_cast< signed long >( v ),
                static_cast< signed long >( c )
        );
    }

    ARC_TEST_MESSAGE( "Checking cast to unsigned long" );
    for ( std::size_t i = 0; i < sizeof( values ) / sizeof( long long ); ++i )
    {
        arc::uint8 v = static_cast< arc::uint8 >( values[ i ] );
        unsigned char c = static_cast< unsigned char >( values[ i ] );

        ARC_CHECK_EQUAL(
                static_cast< unsigned long >( v ),
                static_cast< unsigned long >( c )
        );
    }

    ARC_TEST_MESSAGE( "Checking cast to arc int8" );
    for ( std::size_t i = 0; i < sizeof( values ) / sizeof( long long ); ++i )
    {
        arc::uint8 v = static_cast< arc::uint8 >( values[ i ] );
        unsigned char c = static_cast< unsigned char >( values[ i ] );

        ARC_CHECK_EQUAL(
                static_cast< arc::int8 >( v ),
                static_cast< arc::int8 >( c )
        );
    }

    ARC_TEST_MESSAGE( "Checking cast to arc uint8" );
    for ( std::size_t i = 0; i < sizeof( values ) / sizeof( long long ); ++i )
    {
        arc::uint8 v = static_cast< arc::uint8 >( values[ i ] );
        unsigned char c = static_cast< unsigned char >( values[ i ] );

        ARC_CHECK_EQUAL(
                static_cast< arc::uint8 >( v ),
                static_cast< arc::uint8 >( c )
        );
    }

    ARC_TEST_MESSAGE( "Checking cast to arc int16" );
    for ( std::size_t i = 0; i < sizeof( values ) / sizeof( long long ); ++i )
    {
        arc::uint8 v = static_cast< arc::uint8 >( values[ i ] );
        unsigned char c = static_cast< unsigned char >( values[ i ] );

        ARC_CHECK_EQUAL(
                static_cast< arc::int16 >( v ),
                static_cast< arc::int16 >( c )
        );
    }

    ARC_TEST_MESSAGE( "Checking cast to arc uint16" );
    for ( std::size_t i = 0; i < sizeof( values ) / sizeof( long long ); ++i )
    {
        arc::uint8 v = static_cast< arc::uint8 >( values[ i ] );
        unsigned char c = static_cast< unsigned char >( values[ i ] );

        ARC_CHECK_EQUAL(
                static_cast< arc::uint16 >( v ),
                static_cast< arc::uint16 >( c )
        );
    }

    ARC_TEST_MESSAGE( "Checking cast to arc int32" );
    for ( std::size_t i = 0; i < sizeof( values ) / sizeof( long long ); ++i )
    {
        arc::uint8 v = static_cast< arc::uint8 >( values[ i ] );
        unsigned char c = static_cast< unsigned char >( values[ i ] );

        ARC_CHECK_EQUAL(
                static_cast< arc::int32 >( v ),
                static_cast< arc::int32 >( c )
        );
    }

    ARC_TEST_MESSAGE( "Checking cast to arc uint32" );
    for ( std::size_t i = 0; i < sizeof( values ) / sizeof( long long ); ++i )
    {
        arc::uint8 v = static_cast< arc::uint8 >( values[ i ] );
        unsigned char c = static_cast< unsigned char >( values[ i ] );

        ARC_CHECK_EQUAL(
                static_cast< arc::uint32 >( v ),
                static_cast< arc::uint32 >( c )
        );
    }

    ARC_TEST_MESSAGE( "Checking cast to arc int64" );
    for ( std::size_t i = 0; i < sizeof( values ) / sizeof( long long ); ++i )
    {
        arc::uint8 v = static_cast< arc::uint8 >( values[ i ] );
        unsigned char c = static_cast< unsigned char >( values[ i ] );

        ARC_CHECK_EQUAL(
                static_cast< arc::int64 >( v ),
                static_cast< arc::int64 >( c )
        );
    }

    ARC_TEST_MESSAGE( "Checking cast to arc uint64" );
    for ( std::size_t i = 0; i < sizeof( values ) / sizeof( long long ); ++i )
    {
        arc::uint8 v = static_cast< arc::uint8 >( values[ i ] );
        unsigned char c = static_cast< unsigned char >( values[ i ] );

        ARC_CHECK_EQUAL(
                static_cast< arc::uint64 >( v ),
                static_cast< arc::uint64 >( c )
        );
    }
}

//------------------------------------------------------------------------------
//                                  ARC::INT16
//------------------------------------------------------------------------------

ARC_TEST_UNIT( int16 )
{
    long long values[] = { 1200000, 60000, 3, -0, -20000 };

    ARC_TEST_MESSAGE( "Checking byte size" );
    for ( std::size_t i = 0; i < sizeof( values ) / sizeof( long long ); ++i )
    {
        arc::int16 v = static_cast< arc::int16 >( values[ i ] );

        ARC_CHECK_EQUAL( sizeof( v ), static_cast< std::size_t >( 2 ) );
    }

    ARC_TEST_MESSAGE( "Checking cast to char" );
    for ( std::size_t i = 0; i < sizeof( values ) / sizeof( long long ); ++i )
    {
        arc::int16 v = static_cast< arc::int16 >( values[ i ] );
        signed short c = static_cast< signed short >( values[ i ] );

        ARC_CHECK_EQUAL(
                static_cast< char >( v ),
                static_cast< char >( c )
        );
    }

    ARC_TEST_MESSAGE( "Checking cast to signed char" );
    for ( std::size_t i = 0; i < sizeof( values ) / sizeof( long long ); ++i )
    {
        arc::int16 v = static_cast< arc::int16 >( values[ i ] );
        signed short c = static_cast< signed short >( values[ i ] );

        ARC_CHECK_EQUAL(
                static_cast< signed char >( v ),
                static_cast< signed char >( c )
        );
    }

    ARC_TEST_MESSAGE( "Checking cast to unsigned char" );
    for ( std::size_t i = 0; i < sizeof( values ) / sizeof( long long ); ++i )
    {
        arc::int16 v = static_cast< arc::int16 >( values[ i ] );
        signed short c = static_cast< signed short >( values[ i ] );

        ARC_CHECK_EQUAL(
                static_cast< unsigned char >( v ),
                static_cast< unsigned char >( c )
        );
    }

    ARC_TEST_MESSAGE( "Checking cast to signed short" );
    for ( std::size_t i = 0; i < sizeof( values ) / sizeof( long long ); ++i )
    {
        arc::int16 v = static_cast< arc::int16 >( values[ i ] );
        signed short c = static_cast< signed short >( values[ i ] );

        ARC_CHECK_EQUAL(
                static_cast< signed short >( v ),
                static_cast< signed short >( c )
        );
    }

    ARC_TEST_MESSAGE( "Checking cast to unsigned short" );
    for ( std::size_t i = 0; i < sizeof( values ) / sizeof( long long ); ++i )
    {
        arc::int16 v = static_cast< arc::int16 >( values[ i ] );
        signed short c = static_cast< signed short >( values[ i ] );

        ARC_CHECK_EQUAL(
                static_cast< unsigned short >( v ),
                static_cast< unsigned short >( c )
        );
    }

    ARC_TEST_MESSAGE( "Checking cast to signed int" );
    for ( std::size_t i = 0; i < sizeof( values ) / sizeof( long long ); ++i )
    {
        arc::int16 v = static_cast< arc::int16 >( values[ i ] );
        signed short c = static_cast< signed short >( values[ i ] );

        ARC_CHECK_EQUAL(
                static_cast< signed int >( v ),
                static_cast< signed int >( c )
        );
    }

    ARC_TEST_MESSAGE( "Checking cast to unsigned int" );
    for ( std::size_t i = 0; i < sizeof( values ) / sizeof( long long ); ++i )
    {
        arc::int16 v = static_cast< arc::int16 >( values[ i ] );
        signed short c = static_cast< signed short >( values[ i ] );

        ARC_CHECK_EQUAL(
                static_cast< unsigned int >( v ),
                static_cast< unsigned int >( c )
        );
    }

    ARC_TEST_MESSAGE( "Checking cast to signed long" );
    for ( std::size_t i = 0; i < sizeof( values ) / sizeof( long long ); ++i )
    {
        arc::int16 v = static_cast< arc::int16 >( values[ i ] );
        signed short c = static_cast< signed short >( values[ i ] );

        ARC_CHECK_EQUAL(
                static_cast< signed long >( v ),
                static_cast< signed long >( c )
        );
    }

    ARC_TEST_MESSAGE( "Checking cast to unsigned long" );
    for ( std::size_t i = 0; i < sizeof( values ) / sizeof( long long ); ++i )
    {
        arc::int16 v = static_cast< arc::int16 >( values[ i ] );
        signed short c = static_cast< signed short >( values[ i ] );

        ARC_CHECK_EQUAL(
                static_cast< unsigned long >( v ),
                static_cast< unsigned long >( c )
        );
    }

    ARC_TEST_MESSAGE( "Checking cast to arc int8" );
    for ( std::size_t i = 0; i < sizeof( values ) / sizeof( long long ); ++i )
    {
        arc::int16 v = static_cast< arc::int16 >( values[ i ] );
        signed short c = static_cast< signed short >( values[ i ] );

        ARC_CHECK_EQUAL(
                static_cast< arc::int8 >( v ),
                static_cast< arc::int8 >( c )
        );
    }

    ARC_TEST_MESSAGE( "Checking cast to arc uint8" );
    for ( std::size_t i = 0; i < sizeof( values ) / sizeof( long long ); ++i )
    {
        arc::int16 v = static_cast< arc::int16 >( values[ i ] );
        signed short c = static_cast< signed short >( values[ i ] );

        ARC_CHECK_EQUAL(
                static_cast< arc::uint8 >( v ),
                static_cast< arc::uint8 >( c )
        );
    }

    ARC_TEST_MESSAGE( "Checking cast to arc int16" );
    for ( std::size_t i = 0; i < sizeof( values ) / sizeof( long long ); ++i )
    {
        arc::int16 v = static_cast< arc::int16 >( values[ i ] );
        signed short c = static_cast< signed short >( values[ i ] );

        ARC_CHECK_EQUAL(
                static_cast< arc::int16 >( v ),
                static_cast< arc::int16 >( c )
        );
    }

    ARC_TEST_MESSAGE( "Checking cast to arc uint16" );
    for ( std::size_t i = 0; i < sizeof( values ) / sizeof( long long ); ++i )
    {
        arc::int16 v = static_cast< arc::int16 >( values[ i ] );
        signed short c = static_cast< signed short >( values[ i ] );

        ARC_CHECK_EQUAL(
                static_cast< arc::uint16 >( v ),
                static_cast< arc::uint16 >( c )
        );
    }

    ARC_TEST_MESSAGE( "Checking cast to arc int32" );
    for ( std::size_t i = 0; i < sizeof( values ) / sizeof( long long ); ++i )
    {
        arc::int16 v = static_cast< arc::int16 >( values[ i ] );
        signed short c = static_cast< signed short >( values[ i ] );

        ARC_CHECK_EQUAL(
                static_cast< arc::int32 >( v ),
                static_cast< arc::int32 >( c )
        );
    }

    ARC_TEST_MESSAGE( "Checking cast to arc uint32" );
    for ( std::size_t i = 0; i < sizeof( values ) / sizeof( long long ); ++i )
    {
        arc::int16 v = static_cast< arc::int16 >( values[ i ] );
        signed short c = static_cast< signed short >( values[ i ] );

        ARC_CHECK_EQUAL(
                static_cast< arc::uint32 >( v ),
                static_cast< arc::uint32 >( c )
        );
    }

    ARC_TEST_MESSAGE( "Checking cast to arc int64" );
    for ( std::size_t i = 0; i < sizeof( values ) / sizeof( long long ); ++i )
    {
        arc::int16 v = static_cast< arc::int16 >( values[ i ] );
        signed short c = static_cast< signed short >( values[ i ] );

        ARC_CHECK_EQUAL(
                static_cast< arc::int64 >( v ),
                static_cast< arc::int64 >( c )
        );
    }

    ARC_TEST_MESSAGE( "Checking cast to arc uint64" );
    for ( std::size_t i = 0; i < sizeof( values ) / sizeof( long long ); ++i )
    {
        arc::int16 v = static_cast< arc::int16 >( values[ i ] );
        signed short c = static_cast< signed short >( values[ i ] );

        ARC_CHECK_EQUAL(
                static_cast< arc::uint64 >( v ),
                static_cast< arc::uint64 >( c )
        );
    }
}

//------------------------------------------------------------------------------
//                                 ARC::UINT16
//------------------------------------------------------------------------------

ARC_TEST_UNIT( uint16 )
{
    long long values[] = { 1200000, 60000, 3, -0, -20000 };

    ARC_TEST_MESSAGE( "Checking byte size" );
    for ( std::size_t i = 0; i < sizeof( values ) / sizeof( long long ); ++i )
    {
        arc::uint16 v = static_cast< arc::uint16 >( values[ i ] );

        ARC_CHECK_EQUAL( sizeof( v ), static_cast< std::size_t >( 2 ) );
    }

    ARC_TEST_MESSAGE( "Checking cast to char" );
    for ( std::size_t i = 0; i < sizeof( values ) / sizeof( long long ); ++i )
    {
        arc::uint16 v = static_cast< arc::uint16 >( values[ i ] );
        unsigned short c = static_cast< unsigned short >( values[ i ] );

        ARC_CHECK_EQUAL(
                static_cast< char >( v ),
                static_cast< char >( c )
        );
    }

    ARC_TEST_MESSAGE( "Checking cast to signed char" );
    for ( std::size_t i = 0; i < sizeof( values ) / sizeof( long long ); ++i )
    {
        arc::uint16 v = static_cast< arc::uint16 >( values[ i ] );
        unsigned short c = static_cast< unsigned short >( values[ i ] );

        ARC_CHECK_EQUAL(
                static_cast< signed char >( v ),
                static_cast< signed char >( c )
        );
    }

    ARC_TEST_MESSAGE( "Checking cast to unsigned char" );
    for ( std::size_t i = 0; i < sizeof( values ) / sizeof( long long ); ++i )
    {
        arc::uint16 v = static_cast< arc::uint16 >( values[ i ] );
        unsigned short c = static_cast< unsigned short >( values[ i ] );

        ARC_CHECK_EQUAL(
                static_cast< unsigned char >( v ),
                static_cast< unsigned char >( c )
        );
    }

    ARC_TEST_MESSAGE( "Checking cast to signed short" );
    for ( std::size_t i = 0; i < sizeof( values ) / sizeof( long long ); ++i )
    {
        arc::uint16 v = static_cast< arc::uint16 >( values[ i ] );
        unsigned short c = static_cast< unsigned short >( values[ i ] );

        ARC_CHECK_EQUAL(
                static_cast< signed short >( v ),
                static_cast< signed short >( c )
        );
    }

    ARC_TEST_MESSAGE( "Checking cast to unsigned short" );
    for ( std::size_t i = 0; i < sizeof( values ) / sizeof( long long ); ++i )
    {
        arc::uint16 v = static_cast< arc::uint16 >( values[ i ] );
        unsigned short c = static_cast< unsigned short >( values[ i ] );

        ARC_CHECK_EQUAL(
                static_cast< unsigned short >( v ),
                static_cast< unsigned short >( c )
        );
    }

    ARC_TEST_MESSAGE( "Checking cast to signed int" );
    for ( std::size_t i = 0; i < sizeof( values ) / sizeof( long long ); ++i )
    {
        arc::uint16 v = static_cast< arc::uint16 >( values[ i ] );
        unsigned short c = static_cast< unsigned short >( values[ i ] );

        ARC_CHECK_EQUAL(
                static_cast< signed int >( v ),
                static_cast< signed int >( c )
        );
    }

    ARC_TEST_MESSAGE( "Checking cast to unsigned int" );
    for ( std::size_t i = 0; i < sizeof( values ) / sizeof( long long ); ++i )
    {
        arc::uint16 v = static_cast< arc::uint16 >( values[ i ] );
        unsigned short c = static_cast< unsigned short >( values[ i ] );

        ARC_CHECK_EQUAL(
                static_cast< unsigned int >( v ),
                static_cast< unsigned int >( c )
        );
    }

    ARC_TEST_MESSAGE( "Checking cast to signed long" );
    for ( std::size_t i = 0; i < sizeof( values ) / sizeof( long long ); ++i )
    {
        arc::uint16 v = static_cast< arc::uint16 >( values[ i ] );
        unsigned short c = static_cast< unsigned short >( values[ i ] );

        ARC_CHECK_EQUAL(
                static_cast< signed long >( v ),
                static_cast< signed long >( c )
        );
    }

    ARC_TEST_MESSAGE( "Checking cast to unsigned long" );
    for ( std::size_t i = 0; i < sizeof( values ) / sizeof( long long ); ++i )
    {
        arc::uint16 v = static_cast< arc::uint16 >( values[ i ] );
        unsigned short c = static_cast< unsigned short >( values[ i ] );

        ARC_CHECK_EQUAL(
                static_cast< unsigned long >( v ),
                static_cast< unsigned long >( c )
        );
    }

    ARC_TEST_MESSAGE( "Checking cast to arc int8" );
    for ( std::size_t i = 0; i < sizeof( values ) / sizeof( long long ); ++i )
    {
        arc::uint16 v = static_cast< arc::uint16 >( values[ i ] );
        unsigned short c = static_cast< unsigned short >( values[ i ] );

        ARC_CHECK_EQUAL(
                static_cast< arc::int8 >( v ),
                static_cast< arc::int8 >( c )
        );
    }

    ARC_TEST_MESSAGE( "Checking cast to arc uint8" );
    for ( std::size_t i = 0; i < sizeof( values ) / sizeof( long long ); ++i )
    {
        arc::uint16 v = static_cast< arc::uint16 >( values[ i ] );
        unsigned short c = static_cast< unsigned short >( values[ i ] );

        ARC_CHECK_EQUAL(
                static_cast< arc::uint8 >( v ),
                static_cast< arc::uint8 >( c )
        );
    }

    ARC_TEST_MESSAGE( "Checking cast to arc int16" );
    for ( std::size_t i = 0; i < sizeof( values ) / sizeof( long long ); ++i )
    {
        arc::uint16 v = static_cast< arc::uint16 >( values[ i ] );
        unsigned short c = static_cast< unsigned short >( values[ i ] );

        ARC_CHECK_EQUAL(
                static_cast< arc::int16 >( v ),
                static_cast< arc::int16 >( c )
        );
    }

    ARC_TEST_MESSAGE( "Checking cast to arc uint16" );
    for ( std::size_t i = 0; i < sizeof( values ) / sizeof( long long ); ++i )
    {
        arc::uint16 v = static_cast< arc::uint16 >( values[ i ] );
        unsigned short c = static_cast< unsigned short >( values[ i ] );

        ARC_CHECK_EQUAL(
                static_cast< arc::uint16 >( v ),
                static_cast< arc::uint16 >( c )
        );
    }

    ARC_TEST_MESSAGE( "Checking cast to arc int32" );
    for ( std::size_t i = 0; i < sizeof( values ) / sizeof( long long ); ++i )
    {
        arc::uint16 v = static_cast< arc::uint16 >( values[ i ] );
        unsigned short c = static_cast< unsigned short >( values[ i ] );

        ARC_CHECK_EQUAL(
                static_cast< arc::int32 >( v ),
                static_cast< arc::int32 >( c )
        );
    }

    ARC_TEST_MESSAGE( "Checking cast to arc uint32" );
    for ( std::size_t i = 0; i < sizeof( values ) / sizeof( long long ); ++i )
    {
        arc::uint16 v = static_cast< arc::uint16 >( values[ i ] );
        unsigned short c = static_cast< unsigned short >( values[ i ] );

        ARC_CHECK_EQUAL(
                static_cast< arc::uint32 >( v ),
                static_cast< arc::uint32 >( c )
        );
    }

    ARC_TEST_MESSAGE( "Checking cast to arc int64" );
    for ( std::size_t i = 0; i < sizeof( values ) / sizeof( long long ); ++i )
    {
        arc::uint16 v = static_cast< arc::uint16 >( values[ i ] );
        unsigned short c = static_cast< unsigned short >( values[ i ] );

        ARC_CHECK_EQUAL(
                static_cast< arc::int64 >( v ),
                static_cast< arc::int64 >( c )
        );
    }

    ARC_TEST_MESSAGE( "Checking cast to arc uint64" );
    for ( std::size_t i = 0; i < sizeof( values ) / sizeof( long long ); ++i )
    {
        arc::uint16 v = static_cast< arc::uint16 >( values[ i ] );
        unsigned short c = static_cast< unsigned short >( values[ i ] );

        ARC_CHECK_EQUAL(
                static_cast< arc::uint64 >( v ),
                static_cast< arc::uint64 >( c )
        );
    }
}

//------------------------------------------------------------------------------
//                                  ARC::INT32
//------------------------------------------------------------------------------

ARC_TEST_UNIT( int32 )
{
    long long values[] = { 3242349234, 23, 0, -23495858, -42949672968 };

    ARC_TEST_MESSAGE( "Checking byte size" );
    for ( std::size_t i = 0; i < sizeof( values ) / sizeof( long long ); ++i )
    {
        arc::int32 v = static_cast< arc::int32 >( values[ i ] );

        ARC_CHECK_EQUAL( sizeof( v ), static_cast< std::size_t >( 4 ) );
    }

    ARC_TEST_MESSAGE( "Checking cast to char" );
    for ( std::size_t i = 0; i < sizeof( values ) / sizeof( long long ); ++i )
    {
        arc::int32 v = static_cast< arc::int32 >( values[ i ] );
        signed int c = static_cast< signed int >( values[ i ] );

        ARC_CHECK_EQUAL(
                static_cast< char >( v ),
                static_cast< char >( c )
        );
    }

    ARC_TEST_MESSAGE( "Checking cast to signed char" );
    for ( std::size_t i = 0; i < sizeof( values ) / sizeof( long long ); ++i )
    {
        arc::int32 v = static_cast< arc::int32 >( values[ i ] );
        signed int c = static_cast< signed int >( values[ i ] );

        ARC_CHECK_EQUAL(
                static_cast< signed char >( v ),
                static_cast< signed char >( c )
        );
    }

    ARC_TEST_MESSAGE( "Checking cast to unsigned char" );
    for ( std::size_t i = 0; i < sizeof( values ) / sizeof( long long ); ++i )
    {
        arc::int32 v = static_cast< arc::int32 >( values[ i ] );
        signed int c = static_cast< signed int >( values[ i ] );

        ARC_CHECK_EQUAL(
                static_cast< unsigned char >( v ),
                static_cast< unsigned char >( c )
        );
    }

    ARC_TEST_MESSAGE( "Checking cast to signed short" );
    for ( std::size_t i = 0; i < sizeof( values ) / sizeof( long long ); ++i )
    {
        arc::int32 v = static_cast< arc::int32 >( values[ i ] );
        signed int c = static_cast< signed int >( values[ i ] );

        ARC_CHECK_EQUAL(
                static_cast< signed short >( v ),
                static_cast< signed short >( c )
        );
    }

    ARC_TEST_MESSAGE( "Checking cast to unsigned short" );
    for ( std::size_t i = 0; i < sizeof( values ) / sizeof( long long ); ++i )
    {
        arc::int32 v = static_cast< arc::int32 >( values[ i ] );
        signed int c = static_cast< signed int >( values[ i ] );

        ARC_CHECK_EQUAL(
                static_cast< unsigned short >( v ),
                static_cast< unsigned short >( c )
        );
    }

    ARC_TEST_MESSAGE( "Checking cast to signed int" );
    for ( std::size_t i = 0; i < sizeof( values ) / sizeof( long long ); ++i )
    {
        arc::int32 v = static_cast< arc::int32 >( values[ i ] );
        signed int c = static_cast< signed int >( values[ i ] );

        ARC_CHECK_EQUAL(
                static_cast< signed int >( v ),
                static_cast< signed int >( c )
        );
    }

    ARC_TEST_MESSAGE( "Checking cast to unsigned int" );
    for ( std::size_t i = 0; i < sizeof( values ) / sizeof( long long ); ++i )
    {
        arc::int32 v = static_cast< arc::int32 >( values[ i ] );
        signed int c = static_cast< signed int >( values[ i ] );

        ARC_CHECK_EQUAL(
                static_cast< unsigned int >( v ),
                static_cast< unsigned int >( c )
        );
    }

    ARC_TEST_MESSAGE( "Checking cast to signed long" );
    for ( std::size_t i = 0; i < sizeof( values ) / sizeof( long long ); ++i )
    {
        arc::int32 v = static_cast< arc::int32 >( values[ i ] );
        signed int c = static_cast< signed int >( values[ i ] );

        ARC_CHECK_EQUAL(
                static_cast< signed long >( v ),
                static_cast< signed long >( c )
        );
    }

    ARC_TEST_MESSAGE( "Checking cast to unsigned long" );
    for ( std::size_t i = 0; i < sizeof( values ) / sizeof( long long ); ++i )
    {
        arc::int32 v = static_cast< arc::int32 >( values[ i ] );
        signed int c = static_cast< signed int >( values[ i ] );

        ARC_CHECK_EQUAL(
                static_cast< unsigned long >( v ),
                static_cast< unsigned long >( c )
        );
    }

    ARC_TEST_MESSAGE( "Checking cast to arc int8" );
    for ( std::size_t i = 0; i < sizeof( values ) / sizeof( long long ); ++i )
    {
        arc::int32 v = static_cast< arc::int32 >( values[ i ] );
        signed int c = static_cast< signed int >( values[ i ] );

        ARC_CHECK_EQUAL(
                static_cast< arc::int8 >( v ),
                static_cast< arc::int8 >( c )
        );
    }

    ARC_TEST_MESSAGE( "Checking cast to arc uint8" );
    for ( std::size_t i = 0; i < sizeof( values ) / sizeof( long long ); ++i )
    {
        arc::int32 v = static_cast< arc::int32 >( values[ i ] );
        signed int c = static_cast< signed int >( values[ i ] );

        ARC_CHECK_EQUAL(
                static_cast< arc::uint8 >( v ),
                static_cast< arc::uint8 >( c )
        );
    }

    ARC_TEST_MESSAGE( "Checking cast to arc int16" );
    for ( std::size_t i = 0; i < sizeof( values ) / sizeof( long long ); ++i )
    {
        arc::int32 v = static_cast< arc::int32 >( values[ i ] );
        signed int c = static_cast< signed int >( values[ i ] );

        ARC_CHECK_EQUAL(
                static_cast< arc::int16 >( v ),
                static_cast< arc::int16 >( c )
        );
    }

    ARC_TEST_MESSAGE( "Checking cast to arc uint16" );
    for ( std::size_t i = 0; i < sizeof( values ) / sizeof( long long ); ++i )
    {
        arc::int32 v = static_cast< arc::int32 >( values[ i ] );
        signed int c = static_cast< signed int >( values[ i ] );

        ARC_CHECK_EQUAL(
                static_cast< arc::uint16 >( v ),
                static_cast< arc::uint16 >( c )
        );
    }

    ARC_TEST_MESSAGE( "Checking cast to arc int32" );
    for ( std::size_t i = 0; i < sizeof( values ) / sizeof( long long ); ++i )
    {
        arc::int32 v = static_cast< arc::int32 >( values[ i ] );
        signed int c = static_cast< signed int >( values[ i ] );

        ARC_CHECK_EQUAL(
                static_cast< arc::int32 >( v ),
                static_cast< arc::int32 >( c )
        );
    }

    ARC_TEST_MESSAGE( "Checking cast to arc uint32" );
    for ( std::size_t i = 0; i < sizeof( values ) / sizeof( long long ); ++i )
    {
        arc::int32 v = static_cast< arc::int32 >( values[ i ] );
        signed int c = static_cast< signed int >( values[ i ] );

        ARC_CHECK_EQUAL(
                static_cast< arc::uint32 >( v ),
                static_cast< arc::uint32 >( c )
        );
    }

    ARC_TEST_MESSAGE( "Checking cast to arc int64" );
    for ( std::size_t i = 0; i < sizeof( values ) / sizeof( long long ); ++i )
    {
        arc::int32 v = static_cast< arc::int32 >( values[ i ] );
        signed int c = static_cast< signed int >( values[ i ] );

        ARC_CHECK_EQUAL(
                static_cast< arc::int64 >( v ),
                static_cast< arc::int64 >( c )
        );
    }

    ARC_TEST_MESSAGE( "Checking cast to arc uint64" );
    for ( std::size_t i = 0; i < sizeof( values ) / sizeof( long long ); ++i )
    {
        arc::int32 v = static_cast< arc::int32 >( values[ i ] );
        signed int c = static_cast< signed int >( values[ i ] );

        ARC_CHECK_EQUAL(
                static_cast< arc::uint64 >( v ),
                static_cast< arc::uint64 >( c )
        );
    }
}

//------------------------------------------------------------------------------
//                                 ARC::UINT32
//------------------------------------------------------------------------------

ARC_TEST_UNIT( uint32 )
{
    long long values[] = { 3242349234, 23, 0, -23495858, -42949672968 };

    ARC_TEST_MESSAGE( "Checking byte size" );
    for ( std::size_t i = 0; i < sizeof( values ) / sizeof( long long ); ++i )
    {
        arc::uint32 v = static_cast< arc::uint32 >( values[ i ] );

        ARC_CHECK_EQUAL( sizeof( v ), static_cast< std::size_t >( 4 ) );
    }

    ARC_TEST_MESSAGE( "Checking cast to char" );
    for ( std::size_t i = 0; i < sizeof( values ) / sizeof( long long ); ++i )
    {
        arc::uint32 v = static_cast< arc::uint32 >( values[ i ] );
        unsigned int c = static_cast< unsigned int >( values[ i ] );

        ARC_CHECK_EQUAL(
                static_cast< char >( v ),
                static_cast< char >( c )
        );
    }

    ARC_TEST_MESSAGE( "Checking cast to signed char" );
    for ( std::size_t i = 0; i < sizeof( values ) / sizeof( long long ); ++i )
    {
        arc::uint32 v = static_cast< arc::uint32 >( values[ i ] );
        unsigned int c = static_cast< unsigned int >( values[ i ] );

        ARC_CHECK_EQUAL(
                static_cast< signed char >( v ),
                static_cast< signed char >( c )
        );
    }

    ARC_TEST_MESSAGE( "Checking cast to unsigned char" );
    for ( std::size_t i = 0; i < sizeof( values ) / sizeof( long long ); ++i )
    {
        arc::uint32 v = static_cast< arc::uint32 >( values[ i ] );
        unsigned int c = static_cast< unsigned int >( values[ i ] );

        ARC_CHECK_EQUAL(
                static_cast< unsigned char >( v ),
                static_cast< unsigned char >( c )
        );
    }

    ARC_TEST_MESSAGE( "Checking cast to signed short" );
    for ( std::size_t i = 0; i < sizeof( values ) / sizeof( long long ); ++i )
    {
        arc::uint32 v = static_cast< arc::uint32 >( values[ i ] );
        unsigned int c = static_cast< unsigned int >( values[ i ] );

        ARC_CHECK_EQUAL(
                static_cast< signed short >( v ),
                static_cast< signed short >( c )
        );
    }

    ARC_TEST_MESSAGE( "Checking cast to unsigned short" );
    for ( std::size_t i = 0; i < sizeof( values ) / sizeof( long long ); ++i )
    {
        arc::uint32 v = static_cast< arc::uint32 >( values[ i ] );
        unsigned int c = static_cast< unsigned int >( values[ i ] );

        ARC_CHECK_EQUAL(
                static_cast< unsigned short >( v ),
                static_cast< unsigned short >( c )
        );
    }

    ARC_TEST_MESSAGE( "Checking cast to signed int" );
    for ( std::size_t i = 0; i < sizeof( values ) / sizeof( long long ); ++i )
    {
        arc::uint32 v = static_cast< arc::uint32 >( values[ i ] );
        unsigned int c = static_cast< unsigned int >( values[ i ] );

        ARC_CHECK_EQUAL(
                static_cast< signed int >( v ),
                static_cast< signed int >( c )
        );
    }

    ARC_TEST_MESSAGE( "Checking cast to unsigned int" );
    for ( std::size_t i = 0; i < sizeof( values ) / sizeof( long long ); ++i )
    {
        arc::uint32 v = static_cast< arc::uint32 >( values[ i ] );
        unsigned int c = static_cast< unsigned int >( values[ i ] );

        ARC_CHECK_EQUAL(
                static_cast< unsigned int >( v ),
                static_cast< unsigned int >( c )
        );
    }

    ARC_TEST_MESSAGE( "Checking cast to signed long" );
    for ( std::size_t i = 0; i < sizeof( values ) / sizeof( long long ); ++i )
    {
        arc::uint32 v = static_cast< arc::uint32 >( values[ i ] );
        unsigned int c = static_cast< unsigned int >( values[ i ] );

        ARC_CHECK_EQUAL(
                static_cast< signed long >( v ),
                static_cast< signed long >( c )
        );
    }

    ARC_TEST_MESSAGE( "Checking cast to unsigned long" );
    for ( std::size_t i = 0; i < sizeof( values ) / sizeof( long long ); ++i )
    {
        arc::uint32 v = static_cast< arc::uint32 >( values[ i ] );
        unsigned int c = static_cast< unsigned int >( values[ i ] );

        ARC_CHECK_EQUAL(
                static_cast< unsigned long >( v ),
                static_cast< unsigned long >( c )
        );
    }

    ARC_TEST_MESSAGE( "Checking cast to arc int8" );
    for ( std::size_t i = 0; i < sizeof( values ) / sizeof( long long ); ++i )
    {
        arc::uint32 v = static_cast< arc::uint32 >( values[ i ] );
        unsigned int c = static_cast< unsigned int >( values[ i ] );

        ARC_CHECK_EQUAL(
                static_cast< arc::int8 >( v ),
                static_cast< arc::int8 >( c )
        );
    }

    ARC_TEST_MESSAGE( "Checking cast to arc uint8" );
    for ( std::size_t i = 0; i < sizeof( values ) / sizeof( long long ); ++i )
    {
        arc::uint32 v = static_cast< arc::uint32 >( values[ i ] );
        unsigned int c = static_cast< unsigned int >( values[ i ] );

        ARC_CHECK_EQUAL(
                static_cast< arc::uint8 >( v ),
                static_cast< arc::uint8 >( c )
        );
    }

    ARC_TEST_MESSAGE( "Checking cast to arc int16" );
    for ( std::size_t i = 0; i < sizeof( values ) / sizeof( long long ); ++i )
    {
        arc::uint32 v = static_cast< arc::uint32 >( values[ i ] );
        unsigned int c = static_cast< unsigned int >( values[ i ] );

        ARC_CHECK_EQUAL(
                static_cast< arc::int16 >( v ),
                static_cast< arc::int16 >( c )
        );
    }

    ARC_TEST_MESSAGE( "Checking cast to arc uint16" );
    for ( std::size_t i = 0; i < sizeof( values ) / sizeof( long long ); ++i )
    {
        arc::uint32 v = static_cast< arc::uint32 >( values[ i ] );
        unsigned int c = static_cast< unsigned int >( values[ i ] );

        ARC_CHECK_EQUAL(
                static_cast< arc::uint16 >( v ),
                static_cast< arc::uint16 >( c )
        );
    }

    ARC_TEST_MESSAGE( "Checking cast to arc int32" );
    for ( std::size_t i = 0; i < sizeof( values ) / sizeof( long long ); ++i )
    {
        arc::uint32 v = static_cast< arc::uint32 >( values[ i ] );
        unsigned int c = static_cast< unsigned int >( values[ i ] );

        ARC_CHECK_EQUAL(
                static_cast< arc::int32 >( v ),
                static_cast< arc::int32 >( c )
        );
    }

    ARC_TEST_MESSAGE( "Checking cast to arc uint32" );
    for ( std::size_t i = 0; i < sizeof( values ) / sizeof( long long ); ++i )
    {
        arc::uint32 v = static_cast< arc::uint32 >( values[ i ] );
        unsigned int c = static_cast< unsigned int >( values[ i ] );

        ARC_CHECK_EQUAL(
                static_cast< arc::uint32 >( v ),
                static_cast< arc::uint32 >( c )
        );
    }

    ARC_TEST_MESSAGE( "Checking cast to arc int64" );
    for ( std::size_t i = 0; i < sizeof( values ) / sizeof( long long ); ++i )
    {
        arc::uint32 v = static_cast< arc::uint32 >( values[ i ] );
        unsigned int c = static_cast< unsigned int >( values[ i ] );

        ARC_CHECK_EQUAL(
                static_cast< arc::int64 >( v ),
                static_cast< arc::int64 >( c )
        );
    }

    ARC_TEST_MESSAGE( "Checking cast to arc uint64" );
    for ( std::size_t i = 0; i < sizeof( values ) / sizeof( long long ); ++i )
    {
        arc::uint32 v = static_cast< arc::uint32 >( values[ i ] );
        unsigned int c = static_cast< unsigned int >( values[ i ] );

        ARC_CHECK_EQUAL(
                static_cast< arc::uint64 >( v ),
                static_cast< arc::uint64 >( c )
        );
    }
}

//------------------------------------------------------------------------------
//                                  ARC::INT64
//------------------------------------------------------------------------------

ARC_TEST_UNIT( int64 )
{
    // TODO: hard to test negative values here due to Windows having 4 a byte
    // wide long
    long long values[] = { 3554534, 2353, 232, 23, 0 };

    ARC_TEST_MESSAGE( "Checking byte size" );
    for ( std::size_t i = 0; i < sizeof( values ) / sizeof( long long ); ++i )
    {
        arc::int64 v = static_cast< arc::int64 >( values[ i ] );

        ARC_CHECK_EQUAL( sizeof( v ), static_cast< std::size_t >( 8 ) );
    }

    ARC_TEST_MESSAGE( "Checking cast to char" );
    for ( std::size_t i = 0; i < sizeof( values ) / sizeof( long long ); ++i )
    {
        arc::int64 v = static_cast< arc::int64 >( values[ i ] );
        signed long c = static_cast< signed long >( values[ i ] );

        ARC_CHECK_EQUAL(
                static_cast< char >( v ),
                static_cast< char >( c )
        );
    }

    ARC_TEST_MESSAGE( "Checking cast to signed char" );
    for ( std::size_t i = 0; i < sizeof( values ) / sizeof( long long ); ++i )
    {
        arc::int64 v = static_cast< arc::int64 >( values[ i ] );
        signed long c = static_cast< signed long >( values[ i ] );

        ARC_CHECK_EQUAL(
                static_cast< signed char >( v ),
                static_cast< signed char >( c )
        );
    }

    ARC_TEST_MESSAGE( "Checking cast to unsigned char" );
    for ( std::size_t i = 0; i < sizeof( values ) / sizeof( long long ); ++i )
    {
        arc::int64 v = static_cast< arc::int64 >( values[ i ] );
        signed long c = static_cast< signed long >( values[ i ] );

        ARC_CHECK_EQUAL(
                static_cast< unsigned char >( v ),
                static_cast< unsigned char >( c )
        );
    }

    ARC_TEST_MESSAGE( "Checking cast to signed short" );
    for ( std::size_t i = 0; i < sizeof( values ) / sizeof( long long ); ++i )
    {
        arc::int64 v = static_cast< arc::int64 >( values[ i ] );
        signed long c = static_cast< signed long >( values[ i ] );

        ARC_CHECK_EQUAL(
                static_cast< signed short >( v ),
                static_cast< signed short >( c )
        );
    }

    ARC_TEST_MESSAGE( "Checking cast to unsigned short" );
    for ( std::size_t i = 0; i < sizeof( values ) / sizeof( long long ); ++i )
    {
        arc::int64 v = static_cast< arc::int64 >( values[ i ] );
        signed long c = static_cast< signed long >( values[ i ] );

        ARC_CHECK_EQUAL(
                static_cast< unsigned short >( v ),
                static_cast< unsigned short >( c )
        );
    }

    ARC_TEST_MESSAGE( "Checking cast to signed int" );
    for ( std::size_t i = 0; i < sizeof( values ) / sizeof( long long ); ++i )
    {
        arc::int64 v = static_cast< arc::int64 >( values[ i ] );
        signed long c = static_cast< signed long >( values[ i ] );

        ARC_CHECK_EQUAL(
                static_cast< signed int >( v ),
                static_cast< signed int >( c )
        );
    }

    ARC_TEST_MESSAGE( "Checking cast to unsigned int" );
    for ( std::size_t i = 0; i < sizeof( values ) / sizeof( long long ); ++i )
    {
        arc::int64 v = static_cast< arc::int64 >( values[ i ] );
        signed long c = static_cast< signed long >( values[ i ] );

        ARC_CHECK_EQUAL(
                static_cast< unsigned int >( v ),
                static_cast< unsigned int >( c )
        );
    }

    ARC_TEST_MESSAGE( "Checking cast to signed long" );
    for ( std::size_t i = 0; i < sizeof( values ) / sizeof( long long ); ++i )
    {
        arc::int64 v = static_cast< arc::int64 >( values[ i ] );
        signed long c = static_cast< signed long >( values[ i ] );

        ARC_CHECK_EQUAL(
                static_cast< signed long >( v ),
                static_cast< signed long >( c )
        );
    }

    ARC_TEST_MESSAGE( "Checking cast to unsigned long" );
    for ( std::size_t i = 0; i < sizeof( values ) / sizeof( long long ); ++i )
    {
        arc::int64 v = static_cast< arc::int64 >( values[ i ] );
        signed long c = static_cast< signed long >( values[ i ] );

        ARC_CHECK_EQUAL(
                static_cast< unsigned long >( v ),
                static_cast< unsigned long >( c )
        );
    }

    ARC_TEST_MESSAGE( "Checking cast to arc int8" );
    for ( std::size_t i = 0; i < sizeof( values ) / sizeof( long long ); ++i )
    {
        arc::int64 v = static_cast< arc::int64 >( values[ i ] );
        signed long c = static_cast< signed long >( values[ i ] );

        ARC_CHECK_EQUAL(
                static_cast< arc::int8 >( v ),
                static_cast< arc::int8 >( c )
        );
    }

    ARC_TEST_MESSAGE( "Checking cast to arc uint8" );
    for ( std::size_t i = 0; i < sizeof( values ) / sizeof( long long ); ++i )
    {
        arc::int64 v = static_cast< arc::int64 >( values[ i ] );
        signed long c = static_cast< signed long >( values[ i ] );

        ARC_CHECK_EQUAL(
                static_cast< arc::uint8 >( v ),
                static_cast< arc::uint8 >( c )
        );
    }

    ARC_TEST_MESSAGE( "Checking cast to arc int16" );
    for ( std::size_t i = 0; i < sizeof( values ) / sizeof( long long ); ++i )
    {
        arc::int64 v = static_cast< arc::int64 >( values[ i ] );
        signed long c = static_cast< signed long >( values[ i ] );

        ARC_CHECK_EQUAL(
                static_cast< arc::int16 >( v ),
                static_cast< arc::int16 >( c )
        );
    }

    ARC_TEST_MESSAGE( "Checking cast to arc uint16" );
    for ( std::size_t i = 0; i < sizeof( values ) / sizeof( long long ); ++i )
    {
        arc::int64 v = static_cast< arc::int64 >( values[ i ] );
        signed long c = static_cast< signed long >( values[ i ] );

        ARC_CHECK_EQUAL(
                static_cast< arc::uint16 >( v ),
                static_cast< arc::uint16 >( c )
        );
    }

    ARC_TEST_MESSAGE( "Checking cast to arc int32" );
    for ( std::size_t i = 0; i < sizeof( values ) / sizeof( long long ); ++i )
    {
        arc::int64 v = static_cast< arc::int64 >( values[ i ] );
        signed long c = static_cast< signed long >( values[ i ] );

        ARC_CHECK_EQUAL(
                static_cast< arc::int32 >( v ),
                static_cast< arc::int32 >( c )
        );
    }

    ARC_TEST_MESSAGE( "Checking cast to arc uint32" );
    for ( std::size_t i = 0; i < sizeof( values ) / sizeof( long long ); ++i )
    {
        arc::int64 v = static_cast< arc::int64 >( values[ i ] );
        signed long c = static_cast< signed long >( values[ i ] );

        ARC_CHECK_EQUAL(
                static_cast< arc::uint32 >( v ),
                static_cast< arc::uint32 >( c )
        );
    }

    ARC_TEST_MESSAGE( "Checking cast to arc int64" );
    for ( std::size_t i = 0; i < sizeof( values ) / sizeof( long long ); ++i )
    {
        arc::int64 v = static_cast< arc::int64 >( values[ i ] );
        signed long c = static_cast< signed long >( values[ i ] );

        ARC_CHECK_EQUAL(
                static_cast< arc::int64 >( v ),
                static_cast< arc::int64 >( c )
        );
    }

    ARC_TEST_MESSAGE( "Checking cast to arc uint64" );
    for ( std::size_t i = 0; i < sizeof( values ) / sizeof( long long ); ++i )
    {
        arc::int64 v = static_cast< arc::int64 >( values[ i ] );
        signed long c = static_cast< signed long >( values[ i ] );

        ARC_CHECK_EQUAL(
                static_cast< arc::uint64 >( v ),
                static_cast< arc::uint64 >( c )
        );
    }
}

//------------------------------------------------------------------------------
//                                 ARC::UINT64
//------------------------------------------------------------------------------


ARC_TEST_UNIT( uint64 )
{
    // TODO: hard to test negative values here due to Windows having 4 a byte
    // wide long
    long long values[] = { 3554534, 2353, 232, 23, 0 };

    ARC_TEST_MESSAGE( "Checking byte size" );
    for ( std::size_t i = 0; i < sizeof( values ) / sizeof( long long ); ++i )
    {
        arc::uint64 v = static_cast< arc::uint64 >( values[ i ] );

        ARC_CHECK_EQUAL( sizeof( v ), static_cast< std::size_t >( 8 ) );
    }

    ARC_TEST_MESSAGE( "Checking cast to char" );
    for ( std::size_t i = 0; i < sizeof( values ) / sizeof( long long ); ++i )
    {
        arc::uint64 v = static_cast< arc::uint64 >( values[ i ] );
        unsigned long c = static_cast< unsigned long >( values[ i ] );

        ARC_CHECK_EQUAL(
                static_cast< char >( v ),
                static_cast< char >( c )
        );
    }

    ARC_TEST_MESSAGE( "Checking cast to signed char" );
    for ( std::size_t i = 0; i < sizeof( values ) / sizeof( long long ); ++i )
    {
        arc::uint64 v = static_cast< arc::uint64 >( values[ i ] );
        unsigned long c = static_cast< unsigned long >( values[ i ] );

        ARC_CHECK_EQUAL(
                static_cast< signed char >( v ),
                static_cast< signed char >( c )
        );
    }

    ARC_TEST_MESSAGE( "Checking cast to unsigned char" );
    for ( std::size_t i = 0; i < sizeof( values ) / sizeof( long long ); ++i )
    {
        arc::uint64 v = static_cast< arc::uint64 >( values[ i ] );
        unsigned long c = static_cast< unsigned long >( values[ i ] );

        ARC_CHECK_EQUAL(
                static_cast< unsigned char >( v ),
                static_cast< unsigned char >( c )
        );
    }

    ARC_TEST_MESSAGE( "Checking cast to signed short" );
    for ( std::size_t i = 0; i < sizeof( values ) / sizeof( long long ); ++i )
    {
        arc::uint64 v = static_cast< arc::uint64 >( values[ i ] );
        unsigned long c = static_cast< unsigned long >( values[ i ] );

        ARC_CHECK_EQUAL(
                static_cast< signed short >( v ),
                static_cast< signed short >( c )
        );
    }

    ARC_TEST_MESSAGE( "Checking cast to unsigned short" );
    for ( std::size_t i = 0; i < sizeof( values ) / sizeof( long long ); ++i )
    {
        arc::uint64 v = static_cast< arc::uint64 >( values[ i ] );
        unsigned long c = static_cast< unsigned long >( values[ i ] );

        ARC_CHECK_EQUAL(
                static_cast< unsigned short >( v ),
                static_cast< unsigned short >( c )
        );
    }

    ARC_TEST_MESSAGE( "Checking cast to signed int" );
    for ( std::size_t i = 0; i < sizeof( values ) / sizeof( long long ); ++i )
    {
        arc::uint64 v = static_cast< arc::uint64 >( values[ i ] );
        unsigned long c = static_cast< unsigned long >( values[ i ] );

        ARC_CHECK_EQUAL(
                static_cast< signed int >( v ),
                static_cast< signed int >( c )
        );
    }

    ARC_TEST_MESSAGE( "Checking cast to unsigned int" );
    for ( std::size_t i = 0; i < sizeof( values ) / sizeof( long long ); ++i )
    {
        arc::uint64 v = static_cast< arc::uint64 >( values[ i ] );
        unsigned long c = static_cast< unsigned long >( values[ i ] );

        ARC_CHECK_EQUAL(
                static_cast< unsigned int >( v ),
                static_cast< unsigned int >( c )
        );
    }

    ARC_TEST_MESSAGE( "Checking cast to signed long" );
    for ( std::size_t i = 0; i < sizeof( values ) / sizeof( long long ); ++i )
    {
        arc::uint64 v = static_cast< arc::uint64 >( values[ i ] );
        unsigned long c = static_cast< unsigned long >( values[ i ] );

        ARC_CHECK_EQUAL(
                static_cast< signed long >( v ),
                static_cast< signed long >( c )
        );
    }

    ARC_TEST_MESSAGE( "Checking cast to unsigned long" );
    for ( std::size_t i = 0; i < sizeof( values ) / sizeof( long long ); ++i )
    {
        arc::uint64 v = static_cast< arc::uint64 >( values[ i ] );
        unsigned long c = static_cast< unsigned long >( values[ i ] );

        ARC_CHECK_EQUAL(
                static_cast< unsigned long >( v ),
                static_cast< unsigned long >( c )
        );
    }

    ARC_TEST_MESSAGE( "Checking cast to arc int8" );
    for ( std::size_t i = 0; i < sizeof( values ) / sizeof( long long ); ++i )
    {
        arc::uint64 v = static_cast< arc::uint64 >( values[ i ] );
        unsigned long c = static_cast< unsigned long >( values[ i ] );

        ARC_CHECK_EQUAL(
                static_cast< arc::int8 >( v ),
                static_cast< arc::int8 >( c )
        );
    }

    ARC_TEST_MESSAGE( "Checking cast to arc uint8" );
    for ( std::size_t i = 0; i < sizeof( values ) / sizeof( long long ); ++i )
    {
        arc::uint64 v = static_cast< arc::uint64 >( values[ i ] );
        unsigned long c = static_cast< unsigned long >( values[ i ] );

        ARC_CHECK_EQUAL(
                static_cast< arc::uint8 >( v ),
                static_cast< arc::uint8 >( c )
        );
    }

    ARC_TEST_MESSAGE( "Checking cast to arc int16" );
    for ( std::size_t i = 0; i < sizeof( values ) / sizeof( long long ); ++i )
    {
        arc::uint64 v = static_cast< arc::uint64 >( values[ i ] );
        unsigned long c = static_cast< unsigned long >( values[ i ] );

        ARC_CHECK_EQUAL(
                static_cast< arc::int16 >( v ),
                static_cast< arc::int16 >( c )
        );
    }

    ARC_TEST_MESSAGE( "Checking cast to arc uint16" );
    for ( std::size_t i = 0; i < sizeof( values ) / sizeof( long long ); ++i )
    {
        arc::uint64 v = static_cast< arc::uint64 >( values[ i ] );
        unsigned long c = static_cast< unsigned long >( values[ i ] );

        ARC_CHECK_EQUAL(
                static_cast< arc::uint16 >( v ),
                static_cast< arc::uint16 >( c )
        );
    }

    ARC_TEST_MESSAGE( "Checking cast to arc int32" );
    for ( std::size_t i = 0; i < sizeof( values ) / sizeof( long long ); ++i )
    {
        arc::uint64 v = static_cast< arc::uint64 >( values[ i ] );
        unsigned long c = static_cast< unsigned long >( values[ i ] );

        ARC_CHECK_EQUAL(
                static_cast< arc::int32 >( v ),
                static_cast< arc::int32 >( c )
        );
    }

    ARC_TEST_MESSAGE( "Checking cast to arc uint32" );
    for ( std::size_t i = 0; i < sizeof( values ) / sizeof( long long ); ++i )
    {
        arc::uint64 v = static_cast< arc::uint64 >( values[ i ] );
        unsigned long c = static_cast< unsigned long >( values[ i ] );

        ARC_CHECK_EQUAL(
                static_cast< arc::uint32 >( v ),
                static_cast< arc::uint32 >( c )
        );
    }

    ARC_TEST_MESSAGE( "Checking cast to arc int64" );
    for ( std::size_t i = 0; i < sizeof( values ) / sizeof( long long ); ++i )
    {
        arc::uint64 v = static_cast< arc::uint64 >( values[ i ] );
        unsigned long c = static_cast< unsigned long >( values[ i ] );

        ARC_CHECK_EQUAL(
                static_cast< arc::int64 >( v ),
                static_cast< arc::int64 >( c )
        );
    }

    ARC_TEST_MESSAGE( "Checking cast to arc uint64" );
    for ( std::size_t i = 0; i < sizeof( values ) / sizeof( long long ); ++i )
    {
        arc::uint64 v = static_cast< arc::uint64 >( values[ i ] );
        unsigned long c = static_cast< unsigned long >( values[ i ] );

        ARC_CHECK_EQUAL(
                static_cast< arc::uint64 >( v ),
                static_cast< arc::uint64 >( c )
        );
    }
}

} // namespace types_tests
