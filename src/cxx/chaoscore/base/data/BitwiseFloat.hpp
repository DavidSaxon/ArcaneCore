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
 * Floating point numbers are composed of three sections: sign, exponent, and
 * mantissa. These sections are laid out like so:
 *
 * \code
 * 0 00000000 00000000000000000000000
 * ^ \------/ \---------------------/
 * |     |                |
 * \ 8-bit exponent       |
 *  \                23-bit mantissa
 * sign bit
 * \endcode
 *
 * This object provides functions for reading and writing these sections of a
 * floating point number.
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
    chaos::uint32 int_rep;

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
     * \brief Retrieves the sign bit of this floating point number.
     */
    bool get_sign_bit() const;

    /*!
     * \brief Sets the sign bit (most significant bit) of this float.
     */
    void set_sign_bit( bool sign );

    /*!
     * \brief Retrieves the 8-bit exponent section of this floating point
     *        number.
     */
    chaos::uint32 get_exponent() const;

    /*!
     * \brief Sets the 8-bit exponent section of this floating point number.
     */
    void set_exponent( chaos::uint8 exponent );

    /*!
     * \brief Retrieves the 23-bit mantissa section of this floating point
     *        number.
     */
    chaos::uint32 get_mantissa() const;

    /*!
     * \brief Sets the 23-bit mantissa section of this floating point number.
     *
     * \note While a 32-bit input value is accepted only the least significant
     *       23-bits of this value will be used.
     */
    void set_mantissa( chaos::uint32 mantissa );
};

} // namespace data
} // namespace chaos

#endif
