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
    return int_rep >> 31;
}

chaos::int32 BitwiseFloat::get_exponent() const
{
    return ( int_rep >> 23 ) & 0xFF;
}

chaos::int32 BitwiseFloat::get_mantissa() const
{
    return int_rep & 0x7FFFFF;
}

} // namespace data
} // namespace chaos
