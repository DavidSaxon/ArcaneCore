#ifndef ARCANECORE_GM_VEC_INL_
#define ARCANECORE_GM_VEC_INL_

#ifndef ARC_GM_DISABLE_SSE
    #include <arcanecore/base/simd/Include.hpp>
#endif

namespace arc
{
namespace gm
{

//------------------------------------------------------------------------------
//                         VECTOR STORAGE SPECIALISATIONS
//------------------------------------------------------------------------------

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
struct VectorStorage<arc::uint32, 4, true>
{
    typedef __m128i SimdData;
    ARC_MEMORY_ALIGN(16) arc::uint32 data[4];
};

template<>
struct VectorStorage<arc::int32, 4, true>
{
    typedef __m128i SimdData;
    ARC_MEMORY_ALIGN(16) arc::int32 data[4];
};

//-----------------------------DEFAULT STORAGE TYPE-----------------------------


template<typename T_scalar, arc::uint32 T_dimensions>
struct VectorStorage<T_scalar, T_dimensions, false>
{
    typedef char SimdData;
    T_scalar data[T_dimensions];
};

//------------------------------------------------------------------------------
//                                     VECTOR
//------------------------------------------------------------------------------

//---------------------------------CONSTRUCTORS---------------------------------

template<typename T_scalar, arc::uint32 T_dimensions, bool T_use_simd>
Vector<T_scalar, T_dimensions, T_use_simd>::Vector()
{
    // initialise to zero
    for(std::size_t i = 0; i < T_dimensions; ++i)
    {
        (*this)[i] = 0;
    }
}

template<typename T_scalar, arc::uint32 T_dimensions, bool T_use_simd>
Vector<T_scalar, T_dimensions, T_use_simd>::Vector(
        T_scalar x,
        T_scalar y,
        T_scalar z)
{
    // TODO: check dimensions

    (*this)[0] = x;
    (*this)[1] = y;
    (*this)[2] = z;
}

//----------------------------------OPERATORS-----------------------------------

template<typename T_scalar, arc::uint32 T_dimensions, bool T_use_simd>
T_scalar& Vector<T_scalar, T_dimensions, T_use_simd>::operator[](
    std::size_t index)
{
    // TODO: check dimensions
    return m_storage.data[index];
}

template<typename T_scalar, arc::uint32 T_dimensions, bool T_use_simd>
const T_scalar& Vector<T_scalar, T_dimensions, T_use_simd>::operator[](
    std::size_t index) const
{
    // TODO: check dimensions
    return m_storage.data[index];
}

} // namespace gm
} // namespace arc

#endif
