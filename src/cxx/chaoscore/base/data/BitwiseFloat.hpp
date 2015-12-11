#ifndef CHAOSCORE_BASE_DATA_BITWISEFLOAT_HPP_
#define CHAOSCORE_BASE_DATA_BITWISEFLOAT_HPP_

#include "chaoscore/base/Types.hpp"

namespace chaos
{
namespace data
{

/*!
 * \brief Object that can be used to read and write the bits of a floating point
 *        number.
 *
 * TODO: DOC
 */
union BitwiseFloat
{
public:

    //--------------------------------------------------------------------------
    //                             PUBLIC ATTRIBUTES
    //--------------------------------------------------------------------------

    /*!
     * \brief Access to the float representation.
     */
    float float_rep;
    /*!
     * \brief Access to the int representation.
     */
    chaos::int32 int_rep;

    //--------------------------------------------------------------------------
    //                                CONSTRUCTOR
    //--------------------------------------------------------------------------

    /*!
     * \brief Creates a new BitewiseFloat initialised with the given value.
     */
    BitwiseFloat( float value );

    //--------------------------------------------------------------------------
    //                          PUBLIC MEMBER FUNCTIONS
    //--------------------------------------------------------------------------

    /*!
     * \brief Retrieves the sign bit of the floating point number.
     */
    bool get_sign_bit() const;

    /*!
     * \brief Retrieves the exponent section of the floating point number.
     */
    chaos::int32 get_exponent() const;

    /*!
     * \brief Retrieves the mantissa section of the floating point number.
     */
    chaos::int32 get_mantissa() const;
};

} // namespace data
} // namespace chaos

#endif
