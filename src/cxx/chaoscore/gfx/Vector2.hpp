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
