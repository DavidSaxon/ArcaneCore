#include "arcanecore/test/ArcTest.hpp"

ARC_TEST_MODULE( base.data.byte_operations )

#include "arcanecore/base/data/ByteOperations.hpp"

namespace byte_operations_tests
{

//------------------------------------------------------------------------------
//                                BYTES TO UINT32
//------------------------------------------------------------------------------

class BytesToUint32Fixture : public arc::test::Fixture
{
public:

    //----------------------------PUBLIC ATTRIBUTES-----------------------------

    std::vector< unsigned char* >  big_endian_bytes;
    std::vector< unsigned char* >  little_endian_bytes;
    std::vector< std::size_t > lengths;
    std::vector< arc::uint32 > results;

    std::vector< unsigned char* > bad_bytes;
    std::vector< std::size_t > bad_lengths;

    //-------------------------PUBLIC MEMBER FUNCTIONS--------------------------

    virtual void setup()
    {
        {
            unsigned char* b = new unsigned char[ 1 ];
            b[ 0 ] = 1;
            big_endian_bytes.push_back( b );
            lengths.push_back( 1 );
            results.push_back( 1 );
        }

        {
            unsigned char* b = new unsigned char[ 4 ];
            b[ 0 ] = 0;
            b[ 1 ] = 0;
            b[ 2 ] = 0;
            b[ 3 ] = 0;
            big_endian_bytes.push_back( b );
            lengths.push_back( 4 );
            results.push_back( 0 );
        }

        {
            unsigned char* b = new unsigned char[ 4 ];
            b[ 0 ] = 0;
            b[ 1 ] = 0;
            b[ 2 ] = 0;
            b[ 3 ] = 1;
            big_endian_bytes.push_back( b );
            lengths.push_back( 4 );
            results.push_back( 1 );
        }

        {
            unsigned char* b = new unsigned char[ 3 ];
            b[ 0 ] = 0;
            b[ 1 ] = 0;
            b[ 2 ] = 1;
            big_endian_bytes.push_back( b );
            lengths.push_back( 3 );
            results.push_back( 1 );
        }

        {
            unsigned char* b = new unsigned char[ 3 ];
            b[ 0 ] = 1;
            b[ 1 ] = 0;
            b[ 2 ] = 0;
            big_endian_bytes.push_back( b );
            lengths.push_back( 3 );
            results.push_back( 65536 );
        }

        {
            unsigned char* b = new unsigned char[ 4 ];
            b[ 0 ] = 1;
            b[ 1 ] = 0;
            b[ 2 ] = 0;
            b[ 3 ] = 0;
            big_endian_bytes.push_back( b );
            lengths.push_back( 4 );
            results.push_back( 16777216 );
        }

        {
            unsigned char* b = new unsigned char[ 4 ];
            b[ 0 ] = 0xFF;
            b[ 1 ] = 0;
            b[ 2 ] = 0;
            b[ 3 ] = 0;
            big_endian_bytes.push_back( b );
            lengths.push_back( 4 );
            results.push_back( 4278190080 );
        }

        {
            unsigned char* b = new unsigned char[ 1 ];
            b[ 0 ] = 203;
            big_endian_bytes.push_back( b );
            lengths.push_back( 1 );
            results.push_back( 203 );
        }

        {
            unsigned char* b = new unsigned char[ 2 ];
            b[ 0 ] = 0x7E;
            b[ 1 ] = 0xB0;
            big_endian_bytes.push_back( b );
            lengths.push_back( 2 );
            results.push_back( 32432 );
        }

        {
            unsigned char* b = new unsigned char[ 3 ];
            b[ 0 ] = 0x1;
            b[ 1 ] = 0xE3;
            b[ 2 ] = 0xF6;
            big_endian_bytes.push_back( b );
            lengths.push_back( 3 );
            results.push_back( 123894 );
        }

        {
            unsigned char* b = new unsigned char[ 4 ];
            b[ 0 ] = 0x8B;
            b[ 1 ] = 0xF0;
            b[ 2 ] = 0xF1;
            b[ 3 ] = 0x86;
            big_endian_bytes.push_back( b );
            lengths.push_back( 4 );
            results.push_back( 2347823494 );
        }

        // reverse data for little endian check
        for( std::size_t i = 0; i < big_endian_bytes.size(); ++i )
        {
            unsigned char* b = new unsigned char[ lengths[ i ] ];
            for ( std::size_t j = 0; j < lengths[ i ]; ++j )
            {
                b[ j ] = big_endian_bytes[ i ][ lengths[ i ] - j - 1 ];
            }
            little_endian_bytes.push_back( b );
        }

        {
            unsigned char* b = new unsigned char[ 5 ];
            bad_bytes.push_back( b );
            bad_lengths.push_back( 5 );
        }

        {
            unsigned char* b = new unsigned char[ 3 ];
            bad_bytes.push_back( b );
            bad_lengths.push_back( 5 );
        }

        {
            unsigned char* b = new unsigned char[ 10 ];
            bad_bytes.push_back( b );
            bad_lengths.push_back( 7 );
        }

        {
            unsigned char* b = new unsigned char[ 340511 ];
            bad_bytes.push_back( b );
            bad_lengths.push_back( 340511 );
        }
    }

    virtual void teardown()
    {
        for( std::size_t i = 0; i < big_endian_bytes.size(); ++i )
        {
            delete[] big_endian_bytes[ i ];
            delete[] little_endian_bytes[ i ];
        }
        for ( std::size_t i = 0; i < bad_bytes.size(); ++i )
        {
            delete[] bad_bytes[ i ];
        }
    }
};

ARC_TEST_UNIT_FIXTURE( bytes_to_uint32, BytesToUint32Fixture )
{
    ARC_TEST_MESSAGE( "Checking big endian bytes" );
    for ( std::size_t i = 0; i < fixture->big_endian_bytes.size(); ++i )
    {
        ARC_CHECK_EQUAL(
                arc::data::bytes_to_uint32(
                        fixture->big_endian_bytes[ i ],
                        fixture->lengths[ i ],
                        arc::data::ENDIAN_BIG
                ),
                fixture->results[ i ]
        );
    }

    ARC_TEST_MESSAGE( "Checking little endian bytes" );
    for ( std::size_t i = 0; i < fixture->little_endian_bytes.size(); ++i )
    {
        ARC_CHECK_EQUAL(
                arc::data::bytes_to_uint32(
                        fixture->little_endian_bytes[ i ],
                        fixture->lengths[ i ],
                        arc::data::ENDIAN_LITTLE
                ),
                fixture->results[ i ]
        );
    }

    ARC_TEST_MESSAGE( "Checking conversion errors" );
    for ( std::size_t i = 0; i < fixture->bad_bytes.size(); ++i )
    {
        ARC_CHECK_THROW(
                arc::data::bytes_to_uint32(
                        fixture->bad_bytes[ i ],
                        fixture->bad_lengths[ i ]
                ),
                arc::ex::ConversionDataError
        )
    }
}

} // namespace byte_operations_tests
