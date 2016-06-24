#include "arcanecore/base/data/BitwiseFloat.hpp"

#include "arcanecore/base/Exceptions.hpp"

namespace arc
{
namespace data
{

//------------------------------------------------------------------------------
//                                  CONSTRUCTORS
//------------------------------------------------------------------------------

BitwiseFloat::BitwiseFloat(float value)
    :
    float_rep(value)
{
}

BitwiseFloat::BitwiseFloat(const BitwiseFloat& other)
    :
    float_rep(other.float_rep)
{
}

//------------------------------------------------------------------------------
//                                   OPERATORS
//------------------------------------------------------------------------------

BitwiseFloat& BitwiseFloat::operator=(const BitwiseFloat& other)
{
    float_rep = other.float_rep;

    return *this;
}

bool BitwiseFloat::operator==(const BitwiseFloat& other) const
{
    return int_rep == other.int_rep;
}

bool BitwiseFloat::operator!=(const BitwiseFloat& other) const
{
    return !((*this) == other);
}

//------------------------------------------------------------------------------
//                            PUBLIC MEMBER FUNCTIONS
//------------------------------------------------------------------------------

bool BitwiseFloat::get_sign_bit() const
{
    return (int_rep >> 31) == 1;
}

void BitwiseFloat::set_sign_bit(bool sign)
{
    int_rep =
            (static_cast<arc::uint32>(sign) << 31) | (int_rep & 0x7FFFFFFF);
}

arc::uint32 BitwiseFloat::get_exponent() const
{
    return (int_rep >> 23) & 0xFF;
}

void BitwiseFloat::set_exponent(arc::uint8 exponent)
{
    int_rep = (static_cast<arc::uint32>(exponent)  << 23) |
              (int_rep & 0x807FFFFF);
}

arc::uint32 BitwiseFloat::get_mantissa() const
{
    return int_rep & 0x7FFFFF;
}

void BitwiseFloat::set_mantissa(arc::uint32 mantissa)
{
    int_rep = (mantissa & 0x7FFFFF) | (int_rep & 0xFF800000);
}

float BitwiseFloat::precision_away_from_zero() const
{
    // can't check precision for infinity or NaN
    if (get_exponent() == 255)
    {
        throw arc::ex::ArithmeticError(
                "Cannot resolve precision away from zero of infinity or NaN");
    }

    // create a copy and increment
    BitwiseFloat c(float_rep);
    ++c.int_rep;
    // return delta
    return c.float_rep - float_rep;
}

float BitwiseFloat::precision_towards_zero() const
{
    // can't check precision for zero
    if (get_exponent() == 0 && get_mantissa() == 0)
    {
        throw arc::ex::ArithmeticError(
                "Cannot resolve precision towards zero for value 0");
    }
    if (get_exponent() == 255 && get_mantissa() != 0)
    {
        throw arc::ex::ArithmeticError(
                "Cannot resolve precision towards zero for NaN");
    }

    // create a copy and decrement
    BitwiseFloat c(float_rep);
    --c.int_rep;
    // return delta
    float delta = c.float_rep - float_rep;
    return -delta;
}

} // namespace data
} // namespace arc
