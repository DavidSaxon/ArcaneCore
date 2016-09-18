/*!
 * \file
 * \author David Saxon
 */
#ifndef ARCANECORE_GM_VEC3_HPP_
#define ARCANECORE_GM_VEC3_HPP_

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
class Vec3;

#endif
// IN_DOXYGEN

//------------------------------------------------------------------------------
//                                TYPE DEFINITIONS
//------------------------------------------------------------------------------

typedef Vec3<arc::int32>  Vec3i;
typedef Vec3<arc::uint32> Vec3ui;
typedef Vec3<arc::int64>  Vec3l;
typedef Vec3<arc::uint64> Vec3ul;
typedef Vec3<float>       Vec3f;
typedef Vec3<double>      Vec3d;

/*!
 * \brief Represents a 3 dimensional vector.
 *
 * For more explicit Vec3 operations and functions see Vec3Operations.hpp
 *
 * \tparam DataType The data type of the vector's components. This should be a
 *                  numerical type.
 */
template <typename DataType>
class Vec3
{
public:

    //--------------------------------------------------------------------------
    //                             PUBLIC ATTRIBUTES
    //--------------------------------------------------------------------------

    DataType x;
    DataType y;
    DataType z;

    //--------------------------------------------------------------------------
    //                                CONSTRUCTORS
    //--------------------------------------------------------------------------

    /*!
     * \brief Default constructor.
     *
     * Creates a new Vec3 with the x, y, and z components initialised to 0.
     */
    Vec3()
        :
        x(0),
        y(0),
        z(0)
    {
    }

    /*!
     * \brief Component constructor.
     *
     * Creates a new Vec3 with the given x, y, and z component values.
     */
    Vec3(const DataType& _x, const DataType& _y, const DataType& _z)
        :
        x(_x),
        y(_y),
        z(_z)
    {
    }

    /*!
     * \brief Scalar constructor.
     *
     * Creates a new Vec3 with the x, y, and z components initialised to be the
     * given scalar.
     */
    Vec3(const DataType& scalar)
        :
        x(scalar),
        y(scalar),
        z(scalar)
    {
    }

    /*!
     * \brief Copy constructor.
     *
     * Creates a new copy of the given Vec3.
     */
    Vec3(const Vec3& other)
        :
        x(other.x),
        y(other.y),
        z(other.z)
    {
    }

    /*!
     * \brief Move constructor.
     *
     * Moves resources from the given Vec3 to this Vec3.
     */
    Vec3(Vec3&& other)
        :
        x(other.x),
        y(other.y),
        z(other.z)
    {
        other.x = 0;
        other.y = 0;
        other.z = 0;
    }

    //--------------------------------------------------------------------------
    //                                 OPERATORS
    //--------------------------------------------------------------------------

    /*!
     * \brief Assignment operator.
     *
     * Sets this Vec3 to be a copy of the given Vec3.
     */
    Vec3& operator=(const Vec3& other)
    {
        x = other.x;
        y = other.y;
        z = other.z;

        return *this;
    }

    /*!
     * \brief Scalar assignment operator.
     *
     * Sets the components of this Vec3 to be the given scalar value.
     */
    Vec3& operator=(const DataType& scalar)
    {
        x = scalar;
        y = scalar;
        z = scalar;

        return *this;
    }

    /*!
     * \brief Move operator.
     *
     * Moves resources from the given Vec3 to this Vec3.
     */
    Vec3& operator=(Vec3&& other)
    {
        x = other.x;
        y = other.y;
        z = other.z;
        other.x = 0;
        other.y = 0;
        other.z = 0;

        return *this;
    }
};

// undo forced packing
#pragma pack()

} // namespace gm
} // namespace arc

#endif
