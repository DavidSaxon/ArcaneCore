/*!
 * \file
 * \author David Saxon
 */
#ifndef ARCANECORE_GM_VEC_HPP_
#define ARCANECORE_GM_VEC_HPP_

#include <arcanecore/base/Types.hpp>
#include <arcanecore/base/memory/Alignment.hpp>

namespace arc
{
namespace gm
{

//------------------------------------------------------------------------------
//                                 VECTOR STORAGE
//------------------------------------------------------------------------------

// TODO: can this be internal to the driver
/*!
 * \brief The internal storage of vectors.
 *
 * TODO: finish docs.
 */
template<typename T_scalar, arc::uint32 T_dimensions, bool T_use_simd>
struct VectorStorage;

//------------------------------------------------------------------------------
//                                     VECTOR
//------------------------------------------------------------------------------

// TODO: should we always force inline for vector operations?
/*!
 * \brief TODO
 */
template<typename T_scalar, arc::uint32 T_dimensions, bool T_use_simd = false>
class Vector
    : public arc::memory::AlignedBase<Vector<
        T_scalar,
        T_dimensions,
        T_use_simd
      >>
{
public:

    //--------------------------------------------------------------------------
    //                                CONSTRUCTORS
    //--------------------------------------------------------------------------

    /*!
     * \brief TODO:
     */
    inline Vector();

    /*!
     * \brief TODO:
     */
    inline Vector(T_scalar x, T_scalar y, T_scalar z);

    //--------------------------------------------------------------------------
    //                                 OPERATORS
    //--------------------------------------------------------------------------

    /*!
     * \brief TODO:
     */
    inline T_scalar& operator[](std::size_t index);

    /*!
     * \brief TODO:
     */
    inline const T_scalar& operator[](std::size_t index) const;

private:

    //--------------------------------------------------------------------------
    //                            TYPEDEF DEFINITIONS
    //--------------------------------------------------------------------------

    typedef VectorStorage<T_scalar, T_dimensions, T_use_simd> Storage;

    //--------------------------------------------------------------------------
    //                             PRIVATE ATTRIBUTES
    //--------------------------------------------------------------------------

    union
    {
        Storage m_storage;
        typename Storage::SimdData m_simd_data;
    };
};

} // namespace gm
} // namespace arc

#include "arcanecore/gm/Vector.inl"

//------------------------------------------------------------------------------
//                                TYPE DEFINITIONS
//------------------------------------------------------------------------------

namespace arc
{
namespace gm
{

typedef Vector<float, 2> Vector2f;
typedef Vector<float, 3> Vector3f;
typedef Vector<float, 4> Vector4f;

typedef Vector<double, 2> Vector2d;
typedef Vector<double, 3> Vector3d;
typedef Vector<double, 4> Vector4d;

typedef Vector<arc::uint32, 2> Vector2u;
typedef Vector<arc::uint32, 3> Vector3u;
typedef Vector<arc::uint32, 4> Vector4u;

typedef Vector<arc::int32, 2> Vector2i;
typedef Vector<arc::int32, 3> Vector3i;
typedef Vector<arc::int32, 4> Vector4i;

// define the Simd types whether or not it's enabled, since we want to be able
// turn it off and on easily without having to update the vector types
// everywhere in the code.
#ifndef ARC_GM_DISABLE_SSE
    #define ARC_GM_USE_SIMD true
#else
    #define ARC_GM_USE_SIMD false
#endif

// TODO: 2f?
typedef Vector<float, 3, ARC_GM_USE_SIMD>       SimdVector3f;
typedef Vector<float, 4, ARC_GM_USE_SIMD>       SimdVector4f;

typedef Vector<double, 2, ARC_GM_USE_SIMD>      SimdVector2d;

// TODO 2u and 3u?
typedef Vector<arc::uint32, 4, ARC_GM_USE_SIMD> SimdVector4u;

// TODO: 2i and 3i?
typedef Vector<arc::int32, 4, ARC_GM_USE_SIMD>  SimdVector4i;

} // namespace gm
} // namespace arc

#endif
