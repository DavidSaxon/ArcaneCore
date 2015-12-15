#include "chaoscore/base/data/BitwiseFloat.hpp"

namespace chaos
{
namespace data
{

//------------------------------------------------------------------------------
//                                  CONSTRUCTOR
//------------------------------------------------------------------------------

BitwiseFloat::BitwiseFloat( float value )
    :
    float_rep( value )
{
}

//------------------------------------------------------------------------------
//                            PUBLIC MEMBER FUNCTIONS
//------------------------------------------------------------------------------

bool BitwiseFloat::get_sign_bit() const
{
    return ( int_rep >> 31 ) == 1;
}

void BitwiseFloat::set_sign_bit( bool sign )
{
    int_rep =
            ( static_cast< chaos::uint32 >( sign ) << 31 ) |
            ( int_rep & 0x7FFFFFFF );
}

chaos::uint32 BitwiseFloat::get_exponent() const
{
    return ( int_rep >> 23 ) & 0xFF;
}

void BitwiseFloat::set_exponent( chaos::uint8 exponent )
{
    int_rep = ( static_cast< chaos::uint32 >( exponent )  << 23 ) |
              ( int_rep & 0x807FFFFF );
}

chaos::uint32 BitwiseFloat::get_mantissa() const
{
    return int_rep & 0x7FFFFF;
}

void BitwiseFloat::set_mantissa( chaos::uint32 mantissa )
{
    int_rep = ( mantissa & 0x7FFFFF ) | ( int_rep & 0xFF800000 );
}

} // namespace data
} // namespace chaos
