/*!
 * \file
 * \author David Saxon
 */
#ifndef ARCANECORE_GM_VEC2_HPP_
#define ARCANECORE_GM_VEC2_HPP_

#include <arcanecore/base/Types.hpp>

namespace arc
{
namespace gm
{

// we want to ensure there is no padding between the vector components
#pragma pack(1)

//------------------------------------------------------------------------------
//                              FORWARD DECLARATIONS
//------------------------------------------------------------------------------

// hide from doxygen
#ifndef IN_DOXYGEN

template <typename DataType>
class Vec2;

#endif
// IN_DOXYGEN

//------------------------------------------------------------------------------
//                                TYPE DEFINITIONS
//------------------------------------------------------------------------------

typedef Vec2<arc::int32>  Vec2i;
typedef Vec2<arc::uint32> Vec2ui;
typedef Vec2<arc::int64>  Vec2l;
typedef Vec2<arc::uint64> Vec2ul;
typedef Vec2<float>       Vec2f;
typedef Vec2<double>      Vec2d;

/*!
 * \brief Represents a 2 dimensional vector.
 *
 * For more explicit Vec2 operations and functions see Vec2Operations.hpp
 *
 * \tparam DataType The data type of the vector's components. This should be a
 *                  numerical type.
 */
template <typename DataType>
class Vec2
{
public:

    //--------------------------------------------------------------------------
    //                             PUBLIC ATTRIBUTES
    //--------------------------------------------------------------------------

    DataType x;
    DataType y;

    //--------------------------------------------------------------------------
    //                                CONSTRUCTORS
    //--------------------------------------------------------------------------

    /*!
     * \brief Default constructor.
     *
     * Creates a new Vec2 with the x and y components initialised to 0.
     */
    Vec2()
        :
        x(0),
        y(0)
    {
    }

    /*!
     * \brief Component constructor.
     *
     * Creates a new Vec2 with the given x and y component values.
     */
    Vec2(const DataType& _x, const DataType& _y)
        :
        x(_x),
        y(_y)
    {
    }

    /*!
     * \brief Scalar constructor.
     *
     * Creates a new Vec2 with the x and y components initialised to be the
     * given scalar.
     */
    Vec2(const DataType& scalar)
        :
        x(scalar),
        y(scalar)
    {
    }

    /*!
     * \brief Copy constructor.
     *
     * Creates a new copy of the given Vec2.
     */
    Vec2(const Vec2& other)
        :
        x(other.x),
        y(other.y)
    {
    }

    /*!
     * \brief Move constructor.
     *
     * Moves resources from the given Vec2 to this Vec2.
     */
    Vec2(Vec2&& other)
        :
        x(other.x),
        y(other.y)
    {
        other.x = 0;
        other.y = 0;
    }

    //--------------------------------------------------------------------------
    //                                 OPERATORS
    //--------------------------------------------------------------------------

    /*!
     * \brief Assignment operator.
     *
     * Sets this Vec2 to be a copy of the given Vec2.
     */
    Vec2& operator=(const Vec2& other)
    {
        x = other.x;
        y = other.y;

        return *this;
    }

    /*!
     * \brief Scalar assignment operator.
     *
     * Sets the components of this Vec2 to be the given scalar value.
     */
    Vec2& operator=(const DataType& scalar)
    {
        x = scalar;
        y = scalar;

        return *this;
    }

    /*!
     * \brief Move operator.
     *
     * Moves resources from the given Vec2 to this Vec2.
     */
    Vec2& operator=(Vec2&& other)
    {
        x = other.x;
        y = other.y;
        other.x = 0;
        other.y = 0;

        return *this;
    }
};

// undo forced packing
#pragma pack()

} // namespace gm
} // namespace arc

#endif
