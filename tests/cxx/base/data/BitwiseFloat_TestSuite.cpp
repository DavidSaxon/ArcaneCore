#include "chaoscore/test/ChaosTest.hpp"

CHAOS_TEST_MODULE( base.data.bitwise_float )

#include <cmath>
#include <limits>

#include "chaoscore/base/data/BitwiseFloat.hpp"
#include "chaoscore/io/format/FormatOperations.hpp"

namespace bitwise_float_tests
{

//------------------------------------------------------------------------------
//                                GENERIC FIXTURE
//------------------------------------------------------------------------------

class BitwiseFloatGenericFixture : public chaos::test::Fixture
{
public:

    //----------------------------PUBLIC ATTRIBUTES-----------------------------

    std::vector< chaos::data::BitwiseFloat > floats;
    std::vector< chaos::uint32 > raw;
    std::vector< bool > sign;
    std::vector< chaos::uint32 > exponent;
    std::vector< chaos::uint32 > mantissa;

    //-------------------------PUBLIC MEMBER FUNCTIONS--------------------------

    virtual void setup()
    {
        floats.push_back( chaos::data::BitwiseFloat( 0.0F ) );
        raw.push_back( 0 );
        sign.push_back( 0 );
        exponent.push_back( 0 );
        mantissa.push_back( 0 );

        floats.push_back( chaos::data::BitwiseFloat( 1.40129846e-45 ) );
        raw.push_back( 1 );
        sign.push_back( 0 );
        exponent.push_back( 0 );
        mantissa.push_back( 1 );

        floats.push_back( chaos::data::BitwiseFloat( 1.17549435e-38 ) );
        raw.push_back( 0x800000 );
        sign.push_back( 0 );
        exponent.push_back( 1 );
        mantissa.push_back( 0 );

        floats.push_back( chaos::data::BitwiseFloat( 1.0 ) );
        raw.push_back( 0x3F800000 );
        sign.push_back( 0 );
        exponent.push_back( 127 );
        mantissa.push_back( 0 );

        floats.push_back( chaos::data::BitwiseFloat( 1.99999988 ) );
        raw.push_back( 0x3FFFFFFF );
        sign.push_back( 0 );
        exponent.push_back( 127 );
        mantissa.push_back( 0x7FFFFF );

        floats.push_back( chaos::data::BitwiseFloat( 16777215 ) );
        raw.push_back( 0x4B7FFFFF );
        sign.push_back( 0 );
        exponent.push_back( 150 );
        mantissa.push_back( 0x7FFFFF );

        floats.push_back( chaos::data::BitwiseFloat( 3.40282347e+38 ) );
        raw.push_back( 0x7F7FFFFF );
        sign.push_back( 0 );
        exponent.push_back( 254 );
        mantissa.push_back( 0x7FFFFF );

        floats.push_back( chaos::data::BitwiseFloat( -1.0 ) );
        raw.push_back( 0xBF800000 );
        sign.push_back( 1 );
        exponent.push_back( 127 );
        mantissa.push_back( 0 );

        floats.push_back( chaos::data::BitwiseFloat(
                std::numeric_limits<float>::infinity() ) );
        raw.push_back( 0x7F800000 );
        sign.push_back( 0 );
        exponent.push_back( 255 );
        mantissa.push_back( 0 );

        floats.push_back( chaos::data::BitwiseFloat(
                -std::numeric_limits<float>::infinity() ) );
        raw.push_back( 0xFF800000 );
        sign.push_back( 1 );
        exponent.push_back( 255 );
        mantissa.push_back( 0 );

        floats.push_back( chaos::data::BitwiseFloat( NAN ) );
        raw.push_back( 0x7FC00000 );
        sign.push_back( 0 );
        exponent.push_back( 255 );
        mantissa.push_back( 4194304 );
    }
};

//------------------------------------------------------------------------------
//                                    INT REP
//------------------------------------------------------------------------------

CHAOS_TEST_UNIT_FIXTURE( int_rep, BitwiseFloatGenericFixture )
{
    for ( std::size_t i = 0; i < fixture->floats.size(); ++i )
    {
        CHAOS_CHECK_EQUAL( fixture->floats[ i ].int_rep, fixture->raw[ i ] );
    }
}

//------------------------------------------------------------------------------
//                                  GET SIGN BIT
//------------------------------------------------------------------------------

CHAOS_TEST_UNIT_FIXTURE( get_sign_bit, BitwiseFloatGenericFixture )
{
    for ( std::size_t i = 0; i < fixture->floats.size(); ++i )
    {
        CHAOS_CHECK_EQUAL(
                fixture->floats[ i ].get_sign_bit(),
                fixture->sign[ i ]
        );
    }
}

//------------------------------------------------------------------------------
//                                  GET EXPONENT
//------------------------------------------------------------------------------

CHAOS_TEST_UNIT_FIXTURE( get_exponent, BitwiseFloatGenericFixture )
{
    for ( std::size_t i = 0; i < fixture->floats.size(); ++i )
    {
        CHAOS_CHECK_EQUAL(
                fixture->floats[ i ].get_exponent(),
                fixture->exponent[ i ]
        );
    }
}

//------------------------------------------------------------------------------
//                                  GET MANTISSA
//------------------------------------------------------------------------------

CHAOS_TEST_UNIT_FIXTURE( get_mantissa, BitwiseFloatGenericFixture )
{
    for ( std::size_t i = 0; i < fixture->floats.size(); ++i )
    {
        CHAOS_CHECK_EQUAL(
                fixture->floats[ i ].get_mantissa(),
                fixture->mantissa[ i ]
        );
    }
}

//------------------------------------------------------------------------------
//                                   SET VALUES
//------------------------------------------------------------------------------

CHAOS_TEST_UNIT_FIXTURE( set_values, BitwiseFloatGenericFixture )
{
    for ( std::size_t i = 0; i < fixture->floats.size(); ++i )
    {
        chaos::data::BitwiseFloat f( 0.0F );
        f.int_rep = 0;
        f.set_sign_bit( fixture->sign[ i ] );
        f.set_exponent( fixture->exponent[ i ] );
        f.set_mantissa( fixture->mantissa[ i ] );

        CHAOS_CHECK_EQUAL( f.int_rep, fixture->floats[ i ].int_rep );
    }
}


} // namespace bitwise_float_tests
