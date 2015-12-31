#ifndef CHAOSCORE_GFX_VECTOR4_HPP_
#define CHAOSCORE_GFX_VECTOR4_HPP_

#include "chaoscore/base/uni/UTF8String.hpp"

namespace chaos
{
namespace gfx
{

class Vector4
{
public:

    //--------------------------------------------------------------------------
    //                             PUBLIC ATTRIBUTES
    //--------------------------------------------------------------------------

    /*!
     * \brief X component of this Vector4.
     */
    float x;
    /*!
     * \brief Y component of this Vector4.
     */
    float y;
    /*!
     * \brief Z component of this Vector4.
     */
    float z;
    /*!
     * \brief W component of this Vector4.
     */
    float w;

    //--------------------------------------------------------------------------
    //                                CONSTRUCTORS
    //--------------------------------------------------------------------------

    /*!
     * \brief Default constructor.
     *
     * Creates a new Vector4 with the x, y, z, and w components initialised as
     * 0.
     */
    Vector4();

    /*!
     * \brief Component constructor.
     *
     * Creates a new Vector4 with the given x, y, z, and w component values.
     */
    Vector4( float x, float y, float z, float w );

    /*!
     * \brief Scalar constructor.
     *
     * Creates a new Vector4 with the x, y, z, and w components to the given
     * scalar.
     */
    Vector4( float scalar );


    //--------------------------------------------------------------------------
    //                                 OPERATORS
    //--------------------------------------------------------------------------

    /*!
     * \brief Equality operator.
     *
     * Compares whether this Vector4 and the other given Vector4 are considered
     * "equal". A comparison of the component of the vector is performed using
     * chaos::math::float_equals using the default values for
     * ```delta_threshold``` and ```ulps_threshold```.
     *
     * \param other Vector4 to compare this vector against.
     * \return Whether the vectors are considered equal.
     */
    bool operator==( const Vector4& other ) const;

    /*!
     * \brief Inequality operator.
     *
     * Compares this Vector4 and the other given Vector4 are not considered
     * "equal". See Vector4::operator== for further information.
     *
     * \param other Vector4 to compare this vector against.
     * \return Whether the vectors are not considered equal.
     */
    bool operator!=( const Vector4& other ) const;

};

//------------------------------------------------------------------------------
//                               EXTERNAL OPERATORS
//------------------------------------------------------------------------------

chaos::uni::UTF8String& operator<<(
        chaos::uni::UTF8String& s,
        const Vector4& v );

std::ostream& operator<<( std::ostream& stream, const Vector4& v );

} // namespace gfx
} // namespace chaos

#endif
