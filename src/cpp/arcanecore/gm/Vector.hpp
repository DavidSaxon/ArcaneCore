/*!
 * \file
 * \author David Saxon
 */
#ifndef ARCANECORE_GM_VECTOR_HPP_
#define ARCANECORE_GM_VECTOR_HPP_

#include <arcanecore/base/Types.hpp>
#include <arcanecore/base/memory/Alignment.hpp>
#include <arcanecore/base/str/UTF8String.hpp>

#ifndef ARC_GM_DISABLE_SSE
    #include <arcanecore/base/simd/Include.hpp>
#endif

namespace arc
{
namespace gm
{

//------------------------------------------------------------------------------
//                                 SWIZZLING TAGS
//------------------------------------------------------------------------------

/*!
 * \brief Is used to signify at compile time which vector components should be
 *        used in 2-dimensional swizzling constructor.
 */
template <std::size_t T_x_component, std::size_t T_y_component>
struct Swizzle2 {};

/*!
 * \brief Is used to signify at compile time which vector components should be
 *        used in 3-dimensional swizzling constructor.
 */
template <
    std::size_t T_x_component,
    std::size_t T_y_component,
    std::size_t T_z_component
>
struct Swizzle3 {};

/*!
 * \brief Is used to signify at compile time which vector components should be
 *        used in 4-dimensional swizzling constructor.
 */
template <
    std::size_t T_x_component,
    std::size_t T_y_component,
    std::size_t T_z_component,
    std::size_t T_w_component
>
struct Swizzle4 {};

//------------------------------------------------------------------------------
//                                 VECTOR STORAGE
//------------------------------------------------------------------------------

/*!
 * \brief The internal storage of vectors.
 *
 * \tparam T_scalar The scalar type that this is storing vector information for.
 * \tparam T_dimensions The number of dimensions of the vector that is using
 *                      this storage.
 * \tparam T_use_simd Whether this storage should be formatted in memory for
 *                    simd use.
 */
template<typename T_scalar, std::size_t T_dimensions, bool T_use_simd>
struct VectorStorage;

//-------------------------SUPPORTED SIMD STORAGE TYPES-------------------------

template<>
struct VectorStorage<float, 3, true>
{
    typedef __m128 SimdData;
    ARC_MEMORY_ALIGN(16) float data[3];
};

template<>
struct VectorStorage<float, 4, true>
{
    typedef __m128 SimdData;
    ARC_MEMORY_ALIGN(16) float data[4];
};

template<>
struct VectorStorage<double, 2, true>
{
    typedef __m128d SimdData;
    ARC_MEMORY_ALIGN(16) double data[2];
};

template<>
struct VectorStorage<arc::uint32, 3, true>
{
    typedef __m128i SimdData;
    ARC_MEMORY_ALIGN(16) arc::uint32 data[3];
};

template<>
struct VectorStorage<arc::uint32, 4, true>
{
    typedef __m128i SimdData;
    ARC_MEMORY_ALIGN(16) arc::uint32 data[4];
};

template<>
struct VectorStorage<arc::int32, 3, true>
{
    typedef __m128i SimdData;
    ARC_MEMORY_ALIGN(16) arc::int32 data[3];
};

template<>
struct VectorStorage<arc::int32, 4, true>
{
    typedef __m128i SimdData;
    ARC_MEMORY_ALIGN(16) arc::int32 data[4];
};

//-----------------------------DEFAULT STORAGE TYPE-----------------------------

template<typename T_scalar, std::size_t T_dimensions>
struct VectorStorage<T_scalar, T_dimensions, false>
{
    typedef char SimdData;
    T_scalar data[T_dimensions];
};

//------------------------------------------------------------------------------
//                                     VECTOR
//------------------------------------------------------------------------------

/*!
 * \brief A generic linear algebra vector object with simd support.
 *
 * \tparam T_scalar The scalar type of this vector (e.g. float).
 * \tparam T_dimensions The number of dimensions in this vector, this should be
 *                      greater than 0.
 * \tparam T_use_simd Whether this vector should be formatted in memory for simd
 *                    use.
 */
template<typename T_scalar, std::size_t T_dimensions, bool T_use_simd = false>
class Vector
    : public arc::memory::AlignedBase<Vector<
        T_scalar,
        T_dimensions,
        T_use_simd
      >>
{
public:

    //--------------------------------------------------------------------------
    //                            TYPEDEF DEFINITIONS
    //--------------------------------------------------------------------------

    /*!
     * \brief The storage object this vector is using.
     */
    typedef VectorStorage<T_scalar, T_dimensions, T_use_simd> Storage;
    /*!
     * \brief The simd data of this object (if valid).
     */
    typedef typename VectorStorage<T_scalar, T_dimensions, T_use_simd>::SimdData
        SimdType;

    //--------------------------------------------------------------------------
    //                                CONSTRUCTORS
    //--------------------------------------------------------------------------

    /*!
     * \brief Creates a new vector with all components initialised to 0.
     */
    Vector()
    {
        // initialise to zero
        for(std::size_t i = 0; i < T_dimensions; ++i)
        {
            (*this)[i] = 0;
        }
    }

    /*!
     * \brief Creates a new vector with all components initialised to the given
     *        scalar
     */
    Vector(T_scalar scalar)
    {
        // initialise to scalar
        for(std::size_t i = 0; i < T_dimensions; ++i)
        {
            (*this)[i] = scalar;
        }
    }

    /*!
     * \brief Creates a new vector with the x and y components initialised to
     *        the given values, and any further components initialised to 0.
     *
     * \note The vector must have 2 or more dimensions.
     */
    Vector(T_scalar x, T_scalar y)
    {
        static_assert(
            T_dimensions >= 2,
            "Constructor only valid for vectors with a dimensionality of 2 or "
            "more"
        );

        (*this)[0] = x;
        (*this)[1] = y;

        // initialise to zero
        for(std::size_t i = 2; i < T_dimensions; ++i)
        {
            (*this)[i] = 0;
        }
    }

    /*!
     * \brief Creates a new vector with the x, y, and z components initialised
     *        to the given values, and any further components initialised to 0.
     *
     * \note The vector must have 3 or more dimensions.
     */
    Vector(T_scalar x, T_scalar y, T_scalar z)
    {
        static_assert(
            T_dimensions >= 3,
            "Constructor only valid for vectors with a dimensionality of 3 or "
            "more"
        );

        (*this)[0] = x;
        (*this)[1] = y;
        (*this)[2] = z;

        // initialise to zero
        for(std::size_t i = 3; i < T_dimensions; ++i)
        {
            (*this)[i] = 0;
        }
    }

    /*!
     * \brief Creates a new vector with the x, y, z, and w components
     *        initialised to the given values, and any further components
     *        initialised to 0.
     *
     * \note The vector must have 4 or more dimensions.
     */
    Vector(T_scalar x, T_scalar y, T_scalar z, T_scalar w)
    {
        static_assert(
            T_dimensions >= 4,
            "Constructor only valid for vectors with a dimensionality of 4 or "
            "more"
        );

        (*this)[0] = x;
        (*this)[1] = y;
        (*this)[2] = z;
        (*this)[3] = w;

        // initialise to zero
        for(std::size_t i = 4; i < T_dimensions; ++i)
        {
            (*this)[i] = 0;
        }
    }

    /*!
     * \brief Creates a new vector using the x and y components from the xy
     *        2-dimensional vector and the z value as the z component.
     *
     * \note The vector must have 3 or more dimensions.
     */
    template<bool T_other_use_simd>
    Vector(
            const Vector<T_scalar, 2, T_other_use_simd>& xy,
            T_scalar z)
    {
        static_assert(
            T_dimensions >= 3,
            "Constructor only valid for vectors with a dimensionality of 3 or "
            "more"
        );

        (*this)[0] = xy[0];
        (*this)[1] = xy[1];
        (*this)[2] = z;

        // initialise to zero
        for(std::size_t i = 3; i < T_dimensions; ++i)
        {
            (*this)[i] = 0;
        }
    }

    /*!
     * \brief Creates a new vector using the x and y components from the xy
     *        2-dimensional vector and the z and w components from zw
     *        2-dimensional vector. Any further component are initialised to 0.
     *
     * \note The vector must have 4 or more dimensions.
     */
    template<bool T_other_use_simd>
    Vector(
            const Vector<T_scalar, 2, T_other_use_simd>& xy,
            const Vector<T_scalar, 2, T_other_use_simd>& zw)
    {
        static_assert(
            T_dimensions >= 4,
            "Constructor only valid for vectors with a dimensionality of 4 or "
            "more"
        );

        (*this)[0] = xy[0];
        (*this)[1] = xy[1];
        (*this)[2] = zw[0];
        (*this)[3] = zw[1];

        // initialise to zero
        for(std::size_t i = 4; i < T_dimensions; ++i)
        {
            (*this)[i] = 0;
        }
    }

    /*!
     * \brief Creates a new vector using the x, y, and z components from the xyz
     *        3-dimensional vector and the w value as the w component.
     *
     * \note The vector must have 3 or more dimensions.
     */
    template<bool T_other_use_simd>
    Vector(
            const Vector<T_scalar, 3, T_other_use_simd>& xyz,
            T_scalar w)
    {
        static_assert(
            T_dimensions >= 4,
            "Constructor only valid for vectors with a dimensionality of 4 or "
            "more"
        );

        (*this)[0] = xyz[0];
        (*this)[1] = xyz[1];
        (*this)[2] = xyz[2];
        (*this)[3] = w;

        // initialise to zero
        for(std::size_t i = 4; i < T_dimensions; ++i)
        {
            (*this)[i] = 0;
        }
    }

    /*!
     * \brief Copies the values from the other given vector of the same scalar
     *        type and dimensions to this vector.
     */
    template<bool T_other_use_simd>
    Vector(const Vector<T_scalar, T_dimensions, T_other_use_simd>& v)
    {
        for(std::size_t i = 0; i < T_dimensions; ++i)
        {
            (*this)[i] = v[i];
        }
    }

    /*!
     * \brief Copies the values from the other given vector of the same scalar
     *        type to this vector.
     *
     * If the other vector has less dimensions than this vector, this vector's
     * extra components will be initialized to zero. Likewise if the other
     * vector has more dimensions than this vector the extra components will be
     * truncated.
     */
    template<std::size_t T_other_dimensions, bool T_other_use_simd>
    Vector(const Vector<T_scalar, T_other_dimensions, T_other_use_simd>& v)
    {
        if(T_dimensions < T_other_dimensions)
        {
            for(std::size_t i = 0; i < T_dimensions; ++i)
            {
                (*this)[i] = v[i];
            }
        }
        else
        {
            for(std::size_t i = 0; i < T_other_dimensions; ++i)
            {
                (*this)[i] = v[i];
            }
            for(std::size_t i = T_other_dimensions; i < T_dimensions; ++i)
            {
                (*this)[i] = 0;
            }
        }
    }

    /*!
     * \brief Creates a new vector with the x and y components sourced from
     *        the given vector using the indices defines via the template type
     *        of the swizzle parameter, while other components are initialised
     *        to zero.
     *
     * \tparam T_x_component The index of the component to use from the given
     *                       vector for this vector's x component.
     * \tparam T_y_component The index of the component to use from the given
     *                       vector for this vector's y component.
     *
     * \note The vector must have 2 or more dimensions.
     */
    template<
        std::size_t T_other_dimensions,
        bool T_other_use_simd,
        std::size_t T_x_component,
        std::size_t T_y_component
    >
    Vector(
            const Vector<T_scalar, T_other_dimensions, T_other_use_simd>& v,
            const Swizzle2<T_x_component, T_y_component>& swizzle)
    {
        // check dimensionality
        static_assert(
            T_dimensions >= 2,
            "Constructor only valid for vectors with a dimensionality of 2 or "
            "more"
        );

        // check swizzle indices
        static_assert(
            T_x_component < T_other_dimensions,
            "Swizzle x component index out of the given vector's bounds"
        );
        static_assert(
            T_y_component < T_other_dimensions,
            "Swizzle y component index out of the given vector's bounds"
        );

        // initialise to component or zero
        (*this)[0] = v[T_x_component];
        (*this)[1] = v[T_y_component];
        for(std::size_t i = 2; i < T_dimensions; ++i)
        {
            (*this)[i] = 0;
        }
    }

    /*!
     * \brief Creates a new vector with the x, y, and z components sourced from
     *        the given vector using the indices defines via the template type
     *        of the swizzle parameter, while other components are initialised
     *        to zero.
     *
     * \tparam T_x_component The index of the component to use from the given
     *                       vector for this vector's x component.
     * \tparam T_y_component The index of the component to use from the given
     *                       vector for this vector's y component.
     * \tparam T_z_component The index of the component to use from the given
     *                       vector for this vector's z component.
     *
     * \note The vector must have 3 or more dimensions.
     */
    template<
        std::size_t T_other_dimensions,
        bool T_other_use_simd,
        std::size_t T_x_component,
        std::size_t T_y_component,
        std::size_t T_z_component
    >
    Vector(
            const Vector<T_scalar, T_other_dimensions, T_other_use_simd>& v,
            const Swizzle3<
                T_x_component,
                T_y_component,
                T_z_component
            >& swizzle)
    {
        // check dimensionality
        static_assert(
            T_dimensions >= 3,
            "Constructor only valid for vectors with a dimensionality of 3 or "
            "more"
        );

        // check swizzle indices
        static_assert(
            T_x_component < T_other_dimensions,
            "Swizzle x component index out of the given vector's bounds"
        );
        static_assert(
            T_y_component < T_other_dimensions,
            "Swizzle y component index out of the given vector's bounds"
        );
        static_assert(
            T_z_component < T_other_dimensions,
            "Swizzle z component index out of the given vector's bounds"
        );

        // initialise to component or zero
        (*this)[0] = v[T_x_component];
        (*this)[1] = v[T_y_component];
        (*this)[2] = v[T_z_component];
        for(std::size_t i = 3; i < T_dimensions; ++i)
        {
            (*this)[i] = 0;
        }
    }

    /*!
     * \brief Creates a new vector with the x, y, z, and w components sourced
     *        from the given vector using the indices defines via the template
     *        type of the swizzle parameter, while other components are
     *        initialised to zero.
     *
     * \tparam T_x_component The index of the component to use from the given
     *                       vector for this vector's x component.
     * \tparam T_y_component The index of the component to use from the given
     *                       vector for this vector's y component.
     * \tparam T_z_component The index of the component to use from the given
     *                       vector for this vector's z component.
     * \tparam T_w_component The index of the component to use from the given
     *                       vector for this vector's w component.
     *
     * \note The vector must have 3 or more dimensions.
     */
    template<
        std::size_t T_other_dimensions,
        bool T_other_use_simd,
        std::size_t T_x_component,
        std::size_t T_y_component,
        std::size_t T_z_component,
        std::size_t T_w_component
    >
    Vector(
            const Vector<T_scalar, T_other_dimensions, T_other_use_simd>& v,
            const Swizzle4<
                T_x_component,
                T_y_component,
                T_z_component,
                T_w_component
            >& swizzle)
    {
        // check dimensionality
        static_assert(
            T_dimensions >= 4,
            "Constructor only valid for vectors with a dimensionality of 4 or "
            "more"
        );

        // check swizzle indices
        static_assert(
            T_x_component < T_other_dimensions,
            "Swizzle x component index out of the given vector's bounds"
        );
        static_assert(
            T_y_component < T_other_dimensions,
            "Swizzle y component index out of the given vector's bounds"
        );
        static_assert(
            T_z_component < T_other_dimensions,
            "Swizzle z component index out of the given vector's bounds"
        );
        static_assert(
            T_w_component < T_other_dimensions,
            "Swizzle w component index out of the given vector's bounds"
        );

        // initialise to component or zero
        (*this)[0] = v[T_x_component];
        (*this)[1] = v[T_y_component];
        (*this)[2] = v[T_z_component];
        (*this)[3] = v[T_w_component];
        for(std::size_t i = 4; i < T_dimensions; ++i)
        {
            (*this)[i] = 0;
        }
    }

    /*!
     * \brief Tag that is used to provided a unique typed argument to the Simd
     *        direct assignment constructor.
     */
    enum SimdAssign
    {
        kSimdAssignTag
    };

    /*!
     * \brief Optimisation constructor which directly assigns the internal SIMD
     *        data of the vector to the given data.
     *
     * \param data The SIMD data the will be assigned to the internal data of
     *             this vector.
     * \param dummy A dummy parameter which differentiates this constructor from
     *              the scalar constructor.
     */
    Vector(SimdType data, SimdAssign tag)
        : m_simd_data(data)
    {
    }

    //--------------------------------------------------------------------------
    //                                 OPERATORS
    //--------------------------------------------------------------------------

    /*!
     * \brief Assigns the components of this vector to be the given scalar
     *        value.
     */
    Vector<T_scalar, T_dimensions, T_use_simd>& operator=(T_scalar scalar)
    {
        for(std::size_t i = 0; i < T_dimensions; ++i)
        {
            (*this)[i] = scalar;
        }
        return *this;
    }

    /*!
     * \brief Assigns the components of this vector to be a copy of the other
     *        vectors components.
     */
    template<bool T_other_use_simd>
    Vector<T_scalar, T_dimensions, T_use_simd>& operator=(
            const Vector<T_scalar, T_dimensions, T_other_use_simd>& v)
    {
        for(std::size_t i = 0; i < T_dimensions; ++i)
        {
            (*this)[i] = v[i];
        }
        return *this;
    }

    /*!
     * \brief Assigns the components of this vector to be a copy of the other
     *        vectors components.
     *
     * If the other vector has less dimensions than this vector, this vector's
     * extra components will be initialized to zero. Likewise if the other
     * vector has more dimensions than this vector the extra components will be
     * truncated.
     */
    template<std::size_t T_other_dimensions, bool T_other_use_simd>
    Vector<T_scalar, T_dimensions, T_use_simd>& operator=(
            const Vector<T_scalar, T_other_dimensions, T_other_use_simd>& v)
    {
        if(T_dimensions < T_other_dimensions)
        {
            for(std::size_t i = 0; i < T_dimensions; ++i)
            {
                (*this)[i] = v[i];
            }
        }
        else
        {
            for(std::size_t i = 0; i < T_other_dimensions; ++i)
            {
                (*this)[i] = v[i];
            }
            for(std::size_t i = T_other_dimensions; i < T_dimensions; ++i)
            {
                (*this)[i] = 0;
            }
        }
        return *this;
    }

    /*!
     * \brief Compares whether the given vectors are considered equal.
     *
     * \note If the dimensions differ the vectors will never be considered
     *       equal. However whether the the vector is formated in memory for
     *       simd or not will not affect this equality check.
     *
     * \warning This performs a standard equality check of the individual
     *          components of the vectors, so beware of comparing floating point
     *          vector types.
     */
    template<std::size_t T_other_dimensions, bool T_other_use_simd>
    bool operator==(
            const Vector<
                T_scalar,
                T_other_dimensions,
                T_other_use_simd
            >& v) const
    {
        if(T_other_dimensions != T_dimensions)
        {
            return false;
        }

        for(std::size_t i = 0; i < T_dimensions; ++i)
        {
            if((*this)[i] != v[i])
            {
                return false;
            }
        }
        return true;
    }

    /*!
     * \brief Compares whether the given vectors are considered not equal.
     *
     * \note If the dimensions differ the vectors will never be considered
     *       equal. However whether the the vector is formated in memory for
     *       simd or not will not affect this equality check.
     *
     * \warning This performs a standard equality check of the individual
     *          components of the vectors, so beware of comparing floating point
     *          vector types.
     */
    template<std::size_t T_other_dimensions, bool T_other_use_simd>
    bool operator!=(
            const Vector<
                T_scalar,
                T_other_dimensions,
                T_other_use_simd
            >& v) const
    {
        return !((*this) == v);
    }

    /*!
     * \brief Returns the scalar component for the given index.
     *
     * \note This does not check whether the index is within range of the
     *       vector's dimensionality.
     */
    T_scalar& operator[](std::size_t index)
    {
        return m_storage.data[index];
    }

    /*!
     * \brief Returns the const scalar component for the given index.
     *
     * \note This does not check whether the index is within range of the
     *       vector's dimensionality.
     */
    const T_scalar& operator[](std::size_t index) const
    {
        return m_storage.data[index];
    }

    /*!
     * \brief Negation operator.
     *
     * Returns a copy of this vector with its components negated.
     */
    Vector<T_scalar, T_dimensions, T_use_simd> operator-() const
    {
        Vector<T_scalar, T_dimensions, T_use_simd> r;
        for(std::size_t i = 0; i < T_dimensions; ++i)
        {
            r[i] = -(*this)[i];
        }
        return r;
    }

    /*!
     * \brief Scalar addition operator.
     *
     * Adds the given scalar to each component of this vector and returns the
     * result as a new vector.
     */
    Vector<T_scalar, T_dimensions, T_use_simd> operator+(T_scalar scalar) const
    {
        Vector<T_scalar, T_dimensions, T_use_simd> r;
        for(std::size_t i = 0; i < T_dimensions; ++i)
        {
            r[i] = (*this)[i] + scalar;
        }
        return r;
    }

    /*!
     * \brief Scalar compound assignment addition operator.
     *
     * Adds the given scalar to each component of this vector.
     */
    Vector<T_scalar, T_dimensions, T_use_simd>& operator+=(T_scalar scalar)
    {
        for(std::size_t i = 0; i < T_dimensions; ++i)
        {
            (*this)[i] += scalar;
        }
        return *this;
    }

    /*!
     * \brief Addition operator.
     *
     * Adds each component of the given vector to each component of this vector
     * and returns the result as a new vector.
     */
    template<bool T_other_use_simd>
    Vector<T_scalar, T_dimensions, T_use_simd> operator+(
        const Vector<T_scalar, T_dimensions, T_other_use_simd>& v) const
    {
        Vector<T_scalar, T_dimensions, T_use_simd> r;
        for(std::size_t i = 0; i < T_dimensions; ++i)
        {
            r[i] = (*this)[i] + v[i];
        }
        return r;
    }

    /*!
     * \brief Compound assignment addition operator.
     *
     * Adds each component of the given vector to each component of this vector.
     */
    template<bool T_other_use_simd>
    Vector<T_scalar, T_dimensions, T_use_simd>& operator+=(
        const Vector<T_scalar, T_dimensions, T_other_use_simd>& v)
    {
        for(std::size_t i = 0; i < T_dimensions; ++i)
        {
            (*this)[i] += v[i];
        }
        return *this;
    }

    /*!
     * \brief Scalar subtraction operator.
     *
     * Subtracts the given scalar from each component of this vector and returns
     * the result as a new vector.
     */
    Vector<T_scalar, T_dimensions, T_use_simd> operator-(T_scalar scalar) const
    {
        Vector<T_scalar, T_dimensions, T_use_simd> r;
        for(std::size_t i = 0; i < T_dimensions; ++i)
        {
            r[i] = (*this)[i] - scalar;
        }
        return r;
    }

    /*!
     * \brief Scalar compound assignment subtraction operator.
     *
     * Subtracts the given scalar from each component of this vector.
     */
    Vector<T_scalar, T_dimensions, T_use_simd>& operator-=(T_scalar scalar)
    {
        for(std::size_t i = 0; i < T_dimensions; ++i)
        {
            (*this)[i] -= scalar;
        }
        return *this;
    }

    /*!
     * \brief Subtraction operator.
     *
     * Subtracts each component of the given vector from each component of this
     * vector and returns the result as a new vector.
     */
    template<bool T_other_use_simd>
    Vector<T_scalar, T_dimensions, T_use_simd> operator-(
        const Vector<T_scalar, T_dimensions, T_other_use_simd>& v) const
    {
        Vector<T_scalar, T_dimensions, T_use_simd> r;
        for(std::size_t i = 0; i < T_dimensions; ++i)
        {
            r[i] = (*this)[i] - v[i];
        }
        return r;
    }

    /*!
     * \brief Compound assignment subtraction operator.
     *
     * Subtracts each component of the given vector from each component of this
     * vector.
     */
    template<bool T_other_use_simd>
    Vector<T_scalar, T_dimensions, T_use_simd>& operator-=(
        const Vector<T_scalar, T_dimensions, T_other_use_simd>& v)
    {
        for(std::size_t i = 0; i < T_dimensions; ++i)
        {
            (*this)[i] -= v[i];
        }
        return *this;
    }

    /*!
     * \brief Scalar multiplication operator.
     *
     * Multiplies each component of this vector by the given scalar and returns
     * the result as a new vector.
     */
    Vector<T_scalar, T_dimensions, T_use_simd> operator*(T_scalar scalar) const
    {
        Vector<T_scalar, T_dimensions, T_use_simd> r;
        for(std::size_t i = 0; i < T_dimensions; ++i)
        {
            r[i] = (*this)[i] * scalar;
        }
        return r;
    }

    /*!
     * \brief Scalar compound assignment multiplication operator.
     *
     * Multiplies each component of this vector by the given scalar.
     */
    Vector<T_scalar, T_dimensions, T_use_simd>& operator*=(T_scalar scalar)
    {
        for(std::size_t i = 0; i < T_dimensions; ++i)
        {
            (*this)[i] *= scalar;
        }
        return *this;
    }

    /*!
     * \brief Multiplication operator.
     *
     * Multiplies each component of this given vector by each component of the
     * given vector and returns the result as a new vector.
     */
    template<bool T_other_use_simd>
    Vector<T_scalar, T_dimensions, T_use_simd> operator*(
        const Vector<T_scalar, T_dimensions, T_other_use_simd>& v) const
    {
        Vector<T_scalar, T_dimensions, T_use_simd> r;
        for(std::size_t i = 0; i < T_dimensions; ++i)
        {
            r[i] = (*this)[i] * v[i];
        }
        return r;
    }

    /*!
     * \brief Compound assignment multiplication operator.
     *
     * Multiplies each component of this vector by each component of the given
     * vector.
     */
    template<bool T_other_use_simd>
    Vector<T_scalar, T_dimensions, T_use_simd>& operator*=(
        const Vector<T_scalar, T_dimensions, T_other_use_simd>& v)
    {
        for(std::size_t i = 0; i < T_dimensions; ++i)
        {
            (*this)[i] *= v[i];
        }
        return *this;
    }

    /*!
     * \brief Scalar division operator.
     *
     * Divides each component of this vector by the given scalar and returns
     * the result as a new vector.
     */
    Vector<T_scalar, T_dimensions, T_use_simd> operator/(T_scalar scalar) const
    {
        Vector<T_scalar, T_dimensions, T_use_simd> r;
        for(std::size_t i = 0; i < T_dimensions; ++i)
        {
            r[i] = (*this)[i] / scalar;
        }
        return r;
    }

    /*!
     * \brief Scalar compound assignment division operator.
     *
     * Divides each component of this vector by the given scalar.
     */
    Vector<T_scalar, T_dimensions, T_use_simd>& operator/=(T_scalar scalar)
    {
        for(std::size_t i = 0; i < T_dimensions; ++i)
        {
            (*this)[i] /= scalar;
        }
        return *this;
    }

    /*!
     * \brief Division operator.
     *
     * Divides each component of this given vector by each component of the
     * given vector and returns the result as a new vector.
     */
    template<bool T_other_use_simd>
    Vector<T_scalar, T_dimensions, T_use_simd> operator/(
        const Vector<T_scalar, T_dimensions, T_other_use_simd>& v) const
    {
        Vector<T_scalar, T_dimensions, T_use_simd> r;
        for(std::size_t i = 0; i < T_dimensions; ++i)
        {
            r[i] = (*this)[i] / v[i];
        }
        return r;
    }

    /*!
     * \brief Compound assignment division operator.
     *
     * Multiplies each component of this vector by each component of the given
     * vector.
     */
    template<bool T_other_use_simd>
    Vector<T_scalar, T_dimensions, T_use_simd>& operator/=(
        const Vector<T_scalar, T_dimensions, T_other_use_simd>& v)
    {
        for(std::size_t i = 0; i < T_dimensions; ++i)
        {
            (*this)[i] /= v[i];
        }
        return *this;
    }

    //--------------------------------------------------------------------------
    //                          PUBLIC MEMBER FUNCTIONS
    //--------------------------------------------------------------------------

    /*!
     * \brief Provides access the first component of this vector.
     */
    T_scalar& x()
    {
        return (*this)[0];
    }

    /*!
     * \brief Provides const access the first component of this vector.
     */
    const T_scalar& x() const
    {
        return (*this)[0];
    }

    /*!
     * \brief Provides access the second component of this vector.
     *
     * \note This vector must have 2 or more dimensions.
     */
    T_scalar& y()
    {
        static_assert(
            T_dimensions >= 2,
            "y() function only valid for vectors with a dimensionality of 2 or "
            "more"
        );

        return (*this)[1];
    }

    /*!
     * \brief Provides const access the second component of this vector.
     *
     * \note This vector must have 2 or more dimensions.
     */
    const T_scalar& y() const
    {
        static_assert(
            T_dimensions >= 2,
            "y() function only valid for vectors with a dimensionality of 2 or "
            "more"
        );

        return (*this)[1];
    }

    /*!
     * \brief Provides access the third component of this vector.
     *
     * \note This vector must have 3 or more dimensions.
     */
    T_scalar& z()
    {
        static_assert(
            T_dimensions >= 3,
            "z() function only valid for vectors with a dimensionality of 3 or "
            "more"
        );

        return (*this)[2];
    }

    /*!
     * \brief Provides const access the third component of this vector.
     *
     * \note This vector must have 3 or more dimensions.
     */
    const T_scalar& z() const
    {
        static_assert(
            T_dimensions >= 3,
            "z() function only valid for vectors with a dimensionality of 3 or "
            "more"
        );

        return (*this)[2];
    }

    /*!
     * \brief Provides access the fourth component of this vector.
     *
     * \note This vector must have 4 or more dimensions.
     */
    T_scalar& w()
    {
        static_assert(
            T_dimensions >= 4,
            "w() function only valid for vectors with a dimensionality of 4 or "
            "more"
        );

        return (*this)[3];
    }

    /*!
     * \brief Provides const access the fourth component of this vector.
     *
     * \note This vector must have 4 or more dimensions.
     */
    const T_scalar& w() const
    {
        static_assert(
            T_dimensions >= 4,
            "w() function only valid for vectors with a dimensionality of 4 or "
            "more"
        );

        return (*this)[3];
    }

    /*!
     * \brief Returns the number of dimensions this vector has.
     */
    std::size_t get_dimensions() const
    {
        return T_dimensions;
    }

    /*!
     * \brief Returns whether this vector has a valid simd data representation.
     */
    bool has_simd() const
    {
        return T_use_simd;
    }


    /*!
     * \brief Returns the simd representation of this Vector's data.
     *
     * \note This should only be used on vectors that are using simd.
     */
    SimdType& get_simd()
    {
        static_assert(
            T_use_simd == true,
            "Vector does not have simd data"
        );

        return m_simd_data;
    }

    /*!
     * \brief Returns the const simd representation of this Vector's data.
     *
     * \note This should only be used on vectors that are using simd.
     */
    const SimdType& get_simd() const
    {
        static_assert(
            T_use_simd == true,
            "Vector does not have simd data"
        );

        return m_simd_data;
    }

private:

    //--------------------------------------------------------------------------
    //                             PRIVATE ATTRIBUTES
    //--------------------------------------------------------------------------

    /*!
     * \brief The storage of this vector, union-ed with the simd type so it can
     *        be used interchangeably.
     */
    union
    {
        Storage m_storage;
        typename Storage::SimdData m_simd_data;
    };
};

//------------------------------------------------------------------------------
//                               EXTERNAL OPERATORS
//------------------------------------------------------------------------------

template<typename T_scalar, std::size_t T_dimensions, bool T_use_simd>
inline arc::str::UTF8String& operator<<(
        arc::str::UTF8String& s,
        const Vector<T_scalar, T_dimensions, T_use_simd>& v)
{
    s << "(";
    for(std::size_t i = 0; i < T_dimensions; ++i)
    {
        s << v[i];
        if(i < (T_dimensions - 1))
        {
            s << ", ";
        }
    }
    s << ")";
    return s;
}

template<typename T_scalar, std::size_t T_dimensions, bool T_use_simd>
inline std::ostream& operator<<(
        std::ostream& s,
        const Vector<T_scalar, T_dimensions, T_use_simd>& v)
{
    s << "(";
    for(std::size_t i = 0; i < T_dimensions; ++i)
    {
        s << v[i];
        if(i < (T_dimensions - 1))
        {
            s << ", ";
        }
    }
    s << ")";
    return s;
}

//------------------------------------------------------------------------------
//                                TYPE DEFINITIONS
//------------------------------------------------------------------------------

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

// TODO 2u?
typedef Vector<arc::uint32, 3, ARC_GM_USE_SIMD> SimdVector3u;
typedef Vector<arc::uint32, 4, ARC_GM_USE_SIMD> SimdVector4u;

// TODO: 2i?
typedef Vector<arc::int32, 3, ARC_GM_USE_SIMD>  SimdVector3i;
typedef Vector<arc::int32, 4, ARC_GM_USE_SIMD>  SimdVector4i;

} // namespace gm
} // namespace arc

//----------------------I N L I N E -- E X T E N S I O N S----------------------
#ifndef ARC_GM_DISABLE_SSE
    #include "arcanecore/gm/VectorSimd3f.inl"
    #include "arcanecore/gm/VectorSimd4f.inl"
#endif

#endif
