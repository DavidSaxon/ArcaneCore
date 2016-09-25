/*!
 * \file
 * \author David Saxon
 */
#ifndef ARCANECORE_GM_VEC4_HPP_
#define ARCANECORE_GM_VEC4_HPP_

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
class Vec4;

#endif
// IN_DOXYGEN

//------------------------------------------------------------------------------
//                                TYPE DEFINITIONS
//------------------------------------------------------------------------------

typedef Vec4<arc::int32>  Vec4i;
typedef Vec4<arc::uint32> Vec4ui;
typedef Vec4<arc::int64>  Vec4l;
typedef Vec4<arc::uint64> Vec4ul;
typedef Vec4<float>       Vec4f;
typedef Vec4<double>      Vec4d;

/*!
 * \brief Represents a 4 dimensional vector.
 *
 * For more explicit Vec4 operations and functions see Vec4Operations.hpp
 *
 * \tparam DataType The data type of the vector's components. This should be a
 *                  numerical type.
 */
template <typename DataType>
class Vec4
{
public:

    //--------------------------------------------------------------------------
    //                             PUBLIC ATTRIBUTES
    //--------------------------------------------------------------------------

    DataType x;
    DataType y;
    DataType z;
    DataType w;

    //--------------------------------------------------------------------------
    //                                CONSTRUCTORS
    //--------------------------------------------------------------------------

    /*!
     * \brief Default constructor.
     *
     * Creates a new Vec4 with the x, y, z, and w components initialised to 0.
     */
    Vec4()
        :
        x(0),
        y(0),
        z(0),
        w(0)
    {
    }

    /*!
     * \brief Component constructor.
     *
     * Creates a new Vec4 with the given x, y, z, and w component values.
     */
    Vec4(
            const DataType& _x,
            const DataType& _y,
            const DataType& _z,
            const DataType& _w)
        :
        x(_x),
        y(_y),
        z(_z),
        w(_w)
    {
    }

    /*!
     * \brief Scalar constructor.
     *
     * Creates a new Vec4 with the x, y, z, and w components initialised to be
     * the given scalar.
     */
    Vec4(const DataType& scalar)
        :
        x(scalar),
        y(scalar),
        z(scalar),
        w(scalar)
    {
    }

    /*!
     * \brief Copy constructor.
     *
     * Creates a new copy of the given Vec4.
     */
    Vec4(const Vec4& other)
        :
        x(other.x),
        y(other.y),
        z(other.z),
        w(other.w)
    {
    }

    /*!
     * \brief Move constructor.
     *
     * Moves resources from the given Vec4 to this Vec4.
     */
    Vec4(Vec4&& other)
        :
        x(other.x),
        y(other.y),
        z(other.z),
        w(other.w)
    {
        other.x = 0;
        other.y = 0;
        other.z = 0;
        other.w = 0;
    }

    //--------------------------------------------------------------------------
    //                                 OPERATORS
    //--------------------------------------------------------------------------

    /*!
     * \brief Assignment operator.
     *
     * Sets this Vec4 to be a copy of the given Vec4.
     */
    Vec4& operator=(const Vec4& other)
    {
        x = other.x;
        y = other.y;
        z = other.z;
        w = other.w;

        return *this;
    }

    /*!
     * \brief Scalar assignment operator.
     *
     * Sets the components of this Vec4 to be the given scalar value.
     */
    Vec4& operator=(const DataType& scalar)
    {
        x = scalar;
        y = scalar;
        z = scalar;
        w = scalar;

        return *this;
    }

    /*!
     * \brief Move operator.
     *
     * Moves resources from the given Vec4 to this Vec4.
     */
    Vec4& operator=(Vec4&& other)
    {
        x = other.x;
        y = other.y;
        z = other.z;
        w = other.w;
        other.x = 0;
        other.y = 0;
        other.z = 0;
        other.w = 0;

        return *this;
    }
};

// undo forced packing
#pragma pack()

} // namespace gm
} // namespace arc

#endif
