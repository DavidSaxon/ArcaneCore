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

    // TODO: getters and setters


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
     * \brief Retrieves the sign bit of the floating point number.
     */
    bool get_sign_bit() const;

    // TODO: DOC
    void set_sign_bit( bool sign );

    /*!
     * \brief Retrieves the exponent section of the floating point number.
     */
    chaos::uint32 get_exponent() const;

    // TODO: DOC
    void set_exponent( chaos::uint32 exponent );

    /*!
     * \brief Retrieves the mantissa section of the floating point number.
     */
    chaos::uint32 get_mantissa() const;

    // TODO: DOC
    void set_mantissa( chaos::uint32 mantissa );
};

} // namespace data
} // namespace chaos

#endif
