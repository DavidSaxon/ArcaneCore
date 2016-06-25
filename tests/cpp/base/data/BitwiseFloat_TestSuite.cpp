#include "arcanecore/test/ArcTest.hpp"

ARC_TEST_MODULE( base.data.bitwise_float )

#include <limits>

#include "arcanecore/base/data/BitwiseFloat.hpp"
#include "arcanecore/io/format/FormatOperations.hpp"

namespace bitwise_float_tests
{

//------------------------------------------------------------------------------
//                                GENERIC FIXTURE
//------------------------------------------------------------------------------

class BitwiseFloatGenericFixture : public arc::test::Fixture
{
public:

    //----------------------------PUBLIC ATTRIBUTES-----------------------------

    std::vector< arc::data::BitwiseFloat > floats;
    std::vector< arc::uint32 > raw;
    std::vector< bool > sign;
    std::vector< arc::uint32 > exponent;
    std::vector< arc::uint32 > mantissa;

    //-------------------------PUBLIC MEMBER FUNCTIONS--------------------------

    virtual void setup()
    {
        floats.push_back( arc::data::BitwiseFloat( 0.0F ) );
        raw.push_back( 0 );
        sign.push_back( 0 );
        exponent.push_back( 0 );
        mantissa.push_back( 0 );

        floats.push_back( arc::data::BitwiseFloat( 1.40129846e-45F ) );
        raw.push_back( 1 );
        sign.push_back( 0 );
        exponent.push_back( 0 );
        mantissa.push_back( 1 );

        floats.push_back( arc::data::BitwiseFloat( 1.17549435e-38F ) );
        raw.push_back( 0x800000 );
        sign.push_back( 0 );
        exponent.push_back( 1 );
        mantissa.push_back( 0 );

        floats.push_back( arc::data::BitwiseFloat( 1.0 ) );
        raw.push_back( 0x3F800000 );
        sign.push_back( 0 );
        exponent.push_back( 127 );
        mantissa.push_back( 0 );

        floats.push_back( arc::data::BitwiseFloat( 1.99999988F ) );
        raw.push_back( 0x3FFFFFFF );
        sign.push_back( 0 );
        exponent.push_back( 127 );
        mantissa.push_back( 0x7FFFFF );

        floats.push_back( arc::data::BitwiseFloat( 16777215 ) );
        raw.push_back( 0x4B7FFFFF );
        sign.push_back( 0 );
        exponent.push_back( 150 );
        mantissa.push_back( 0x7FFFFF );

        floats.push_back( arc::data::BitwiseFloat( -1.0 ) );
        raw.push_back( 0xBF800000 );
        sign.push_back( 1 );
        exponent.push_back( 127 );
        mantissa.push_back( 0 );

        floats.push_back( arc::data::BitwiseFloat(
                std::numeric_limits<float>::infinity() ) );
        raw.push_back( 0x7F800000 );
        sign.push_back( 0 );
        exponent.push_back( 255 );
        mantissa.push_back( 0 );

        floats.push_back( arc::data::BitwiseFloat(
                -std::numeric_limits<float>::infinity() ) );
        raw.push_back( 0xFF800000 );
        sign.push_back( 1 );
        exponent.push_back( 255 );
        mantissa.push_back( 0 );
    }
};

//------------------------------------------------------------------------------
//                               FLOAT CONSTRUCTOR
//------------------------------------------------------------------------------

ARC_TEST_UNIT_FIXTURE( float_constructor, BitwiseFloatGenericFixture )
{
    ARC_FOR_EACH( it, fixture->floats )
    {
        arc::data::BitwiseFloat f( it->float_rep );
        ARC_CHECK_EQUAL( f.int_rep, it->int_rep );
    }
}

//------------------------------------------------------------------------------
//                                COPY CONSTRUCTOR
//------------------------------------------------------------------------------

ARC_TEST_UNIT_FIXTURE( copy_constructor, BitwiseFloatGenericFixture )
{
    ARC_FOR_EACH( it, fixture->floats )
    {
        arc::data::BitwiseFloat f( *it );
        ARC_CHECK_EQUAL( f.int_rep, it->int_rep );
    }
}

//------------------------------------------------------------------------------
//                              ASSIGNMENT OPERATOR
//------------------------------------------------------------------------------

ARC_TEST_UNIT_FIXTURE( assignment_operator, BitwiseFloatGenericFixture )
{
    ARC_FOR_EACH( it, fixture->floats )
    {
        arc::data::BitwiseFloat f( 0 );
        f = *it;

        ARC_CHECK_EQUAL( f.int_rep, it->int_rep );
    }
}

//------------------------------------------------------------------------------
//                                    INT REP
//------------------------------------------------------------------------------

ARC_TEST_UNIT_FIXTURE( int_rep, BitwiseFloatGenericFixture )
{
    for ( std::size_t i = 0; i < fixture->floats.size(); ++i )
    {
        ARC_CHECK_EQUAL( fixture->floats[ i ].int_rep, fixture->raw[ i ] );
    }
}

//------------------------------------------------------------------------------
//                                  GET SIGN BIT
//------------------------------------------------------------------------------

ARC_TEST_UNIT_FIXTURE( get_sign_bit, BitwiseFloatGenericFixture )
{
    for ( std::size_t i = 0; i < fixture->floats.size(); ++i )
    {
        ARC_CHECK_EQUAL(
                fixture->floats[ i ].get_sign_bit(),
                fixture->sign[ i ]
        );
    }
}

//------------------------------------------------------------------------------
//                                  GET EXPONENT
//------------------------------------------------------------------------------

ARC_TEST_UNIT_FIXTURE( get_exponent, BitwiseFloatGenericFixture )
{
    for ( std::size_t i = 0; i < fixture->floats.size(); ++i )
    {
        ARC_CHECK_EQUAL(
                fixture->floats[ i ].get_exponent(),
                fixture->exponent[ i ]
        );
    }
}

//------------------------------------------------------------------------------
//                                  GET MANTISSA
//------------------------------------------------------------------------------

ARC_TEST_UNIT_FIXTURE( get_mantissa, BitwiseFloatGenericFixture )
{
    for ( std::size_t i = 0; i < fixture->floats.size(); ++i )
    {
        ARC_CHECK_EQUAL(
                fixture->floats[ i ].get_mantissa(),
                fixture->mantissa[ i ]
        );
    }
}

//------------------------------------------------------------------------------
//                                   SET VALUES
//------------------------------------------------------------------------------

ARC_TEST_UNIT_FIXTURE( set_values, BitwiseFloatGenericFixture )
{
    for ( std::size_t i = 0; i < fixture->floats.size(); ++i )
    {
        arc::data::BitwiseFloat f( 0.0F );
        f.int_rep = 0;
        f.set_sign_bit( fixture->sign[ i ] );
        f.set_exponent( fixture->exponent[ i ] );
        f.set_mantissa( fixture->mantissa[ i ] );

        ARC_CHECK_EQUAL( f.int_rep, fixture->floats[ i ].int_rep );
    }
}

//------------------------------------------------------------------------------
//                            PRECISION AWAY FROM ZERO
//------------------------------------------------------------------------------

ARC_TEST_UNIT( precision_away_from_zero )
{
    arc::data::BitwiseFloat f( std::numeric_limits<float>::infinity() );
    ARC_CHECK_THROW(
            f.precision_away_from_zero(),
            arc::ex::ArithmeticError
    );
}

} // namespace bitwise_float_tests
