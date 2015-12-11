#ifndef CHAOSCORE_GFX_VECTOR2_HPP_
#define CHAOSCORE_GFX_VECTOR2_HPP_

#include "chaoscore/base/uni/UTF8String.hpp"

namespace chaos
{
namespace gfx
{

/*!
 * \brief Represents a 2 dimensional vector.
 */
class Vector2
{
public:

    //--------------------------------------------------------------------------
    //                             PUBLIC ATTRIBUTES
    //--------------------------------------------------------------------------

    /*!
     * \brief X access component of this vector.
     */
    float x;
    /*!
     * \brief Y access component of this vector.
     */
    float y;

    //--------------------------------------------------------------------------
    //                                CONSTRUCTORS
    //--------------------------------------------------------------------------

    /*!
     * \brief Default constructor.
     *
     * Creates a new Vector2 with the x and y components initialised as 0.
     */
    Vector2();

    /*!
     * \brief Component constructor.
     *
     * Creates a new Vector2 with the given x any y component values.
     */
    Vector2( float x, float y );

    /*!
     * \brief Scalar constructor.
     *
     * Creates a new Vector2 with both the x and y components set to the given
     * value.
     */
    Vector2( float scalar );

    /*!
     * \brief Copy constructor.
     *
     * Creates a copy of the other given Vector2.
     */
    Vector2( const Vector2& other );

    //--------------------------------------------------------------------------
    //                                 OPERATORS
    //--------------------------------------------------------------------------

    /*!
     * \brief Assignment operator.
     *
     * Assigns the values of this Vector2 to be a copy of the values of the
     * other given Vector2.
     *
     * \param other Vector2 to copy data from.
     * \return A reference to this Vector2 once the assignment has taken place.
     */
    Vector2& operator=( const Vector2& other );

    /*!
     * \brief Equality operator.
     *
     * Compares whether this Vector2 and the other given Vector2 are considered
     * equal.
     *
     * \param other Vector2 to compare this vector against.
     * \return Whether the vectors are considered equal.
     */
    bool operator==( const Vector2& other ) const;

    /*!
     * \brief Inequality operator.
     *
     * Compares whether this Vector2 and the other given Vector2 are not
     * considered equal.
     *
     * \param other Vector2 to compare this vector against.
     * \return Whether the vectors are not considered equal.
     */
    bool operator!=( const Vector2& other ) const;

    /*!
     * \brief Scalar addition operator.
     *
     * Computes the result of this Vector2 being added with the given scalar and
     * returns the result a a new Vector2.
     */
    Vector2 operator+( float scalar ) const;

    /*!
     * \brief Scalar compound addition operator.
     *
     * Adds the given scalar to this Vector2.
     *
     * \param scalar The scalar to add to this Vector2.
     * \return A reference to this vector once the addition has taken place.
     */
    const Vector2& operator+=( float scalar );

    /*!
     * \brief Vector addition operator.
     *
     * Computes the result of this Vector2 being added with the other given
     * Vector2. The result is returned as a new Vector2.
     */
    Vector2 operator+( const Vector2& other ) const;

    /*!
     * \brief Compound vector addition operator.
     *
     * Adds the given Vector2 to this Vector2.
     *
     * \param other The Vector2 to add to this Vector2.
     * \return A reference to this vector after the addition has taken place.
     */
    const Vector2& operator+=( const Vector2& other );
};

//------------------------------------------------------------------------------
//                               EXTERNAL OPERATORS
//------------------------------------------------------------------------------

chaos::uni::UTF8String& operator<<(
        chaos::uni::UTF8String& s,
        const Vector2& v );

std::ostream& operator<<( std::ostream& stream, const Vector2& v );

} // namespace gfx
} // namespace chaos

#endif
