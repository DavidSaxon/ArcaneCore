#include "chaoscore/test/ChaosTest.hpp"

CHAOS_TEST_MODULE( base.data.bitwise_float )

#include "chaoscore/base/data/BitwiseFloat.hpp"

namespace bitwise_float_tests
{

//------------------------------------------------------------------------------
//                                 TODO REMOVE ME
//------------------------------------------------------------------------------

CHAOS_TEST_UNIT( dev )
{
    chaos::data::BitwiseFloat f( 0.2F );

    std::cout << "raw     : " << f.int_rep << std::endl;
    std::cout << "sign    : " << f.get_sign_bit() << std::endl;
    std::cout << "exponent: " << f.get_exponent() << std::endl;
    std::cout << "mantissa: " << f.get_mantissa() << std::endl;

    std::cout << ":: " << ( ( 1 << 23 ) - 1 ) << std::endl;
}

} // namespace bitwise_float_tests
