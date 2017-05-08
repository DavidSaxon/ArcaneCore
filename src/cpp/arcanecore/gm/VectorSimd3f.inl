/*!
 * \file
 * \author David Saxon
 * \brief Template specialistations for SIMD 3D float vectors.
 */
#ifndef ARCANECORE_GM_VECTORSMID3F_INL_
#define ARCANECORE_GM_VECTORSMID3F_INL_

#include <arcanecore/base/simd/Include.hpp>

namespace arc
{
namespace gm
{

//------------------------------------------------------------------------------
//                                  CONSTRUCTORS
//------------------------------------------------------------------------------

//-------------------------------ZERO CONSTRUCTOR-------------------------------

template<>
inline SimdVector3f::Vector()
{
    m_simd_data = _mm_setzero_ps();
}

//------------------------------SCALAR CONSTRUCTOR------------------------------

template<>
inline SimdVector3f::Vector(float scalar)
{
    m_simd_data = _mm_set_ps1(scalar);
}

//-------------------------------COPY CONSTRUCTOR-------------------------------

template<>
template<>
inline SimdVector3f::Vector(const SimdVector3f& v)
{
    m_simd_data = v.m_simd_data;
}

//----------------------------SWIZZLE 3 CONSTRUCTOR-----------------------------

template<
    std::size_t T_x_component,
    std::size_t T_y_component,
    std::size_t T_z_component,
    std::size_t T_dimensions,
    bool T_use_simd>
inline void swizzle3_3f(
        const Vector<float, T_dimensions, T_use_simd>& a,
        SimdVector3f& b)
{
    // default behavior
    b[0] = a[T_x_component];
    b[1] = a[T_y_component];
    b[2] = a[T_z_component];
    for(std::size_t i = 3; i < 3; ++i)
    {
        b[i] = 0;
    }
}

template<
    std::size_t T_x_component,
    std::size_t T_y_component,
    std::size_t T_z_component,
    std::size_t T_dimensions>
inline void swizzle3_3f(
        const Vector<float, T_dimensions, true>& a,
        SimdVector3f& b)
{
    b.get_simd() = _mm_shuffle_ps(
        a.get_simd(),
        a.get_simd(),
        _MM_SHUFFLE(3, T_z_component, T_y_component, T_x_component)
    );
}

template<>
template<
    std::size_t T_other_dimensions,
    bool T_other_use_simd,
    std::size_t T_x_component,
    std::size_t T_y_component,
    std::size_t T_z_component
>
inline SimdVector3f::Vector(
        const Vector<float, T_other_dimensions, T_other_use_simd>& v,
        const Swizzle3<
            T_x_component,
            T_y_component,
            T_z_component
        >& swizzle)
{
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

    swizzle3_3f<T_x_component, T_y_component, T_z_component>(v, *this);
}

//------------------------------------------------------------------------------
//                                   OPERATORS
//------------------------------------------------------------------------------

//------------------------------SCALAR ASSIGNMENT-------------------------------

template<>
inline SimdVector3f& SimdVector3f::operator=(float scalar)
{
    m_simd_data = _mm_set_ps1(scalar);
    return *this;
}

//------------------------------VECTOR ASSIGNMENT-------------------------------

template<>
template<>
inline SimdVector3f& SimdVector3f::operator=(const SimdVector3f& v)
{
    m_simd_data = v.m_simd_data;
    return *this;
}

//-----------------------------------NEGATION-----------------------------------

template<>
inline SimdVector3f SimdVector3f::operator-() const
{
    return SimdVector3f(
        _mm_xor_ps(m_simd_data, _mm_set1_ps(-0.f)),
        SimdVector3f::kSimdAssignTag
    );
}

//-------------------------------SCALAR ADDITION--------------------------------

template<>
inline SimdVector3f SimdVector3f::operator+(float scalar) const
{
    return SimdVector3f(
        _mm_add_ps(m_simd_data, _mm_set_ps1(scalar)),
        SimdVector3f::kSimdAssignTag
    );
}

template<>
inline SimdVector3f& SimdVector3f::operator+=(float scalar)
{
    m_simd_data = _mm_add_ps(m_simd_data, _mm_set_ps1(scalar));
    return *this;
}

//-------------------------------VECTOR ADDITION--------------------------------

template<>
template<>
inline SimdVector3f SimdVector3f::operator+(const SimdVector3f& v) const
{
    return SimdVector3f(
        _mm_add_ps(m_simd_data, v.m_simd_data),
        SimdVector3f::kSimdAssignTag
    );
}

template<>
template<>
inline SimdVector3f& SimdVector3f::operator+=(const SimdVector3f& v)
{
    m_simd_data = _mm_add_ps(m_simd_data, v.m_simd_data);
    return *this;
}

//------------------------------SCALAR SUBTRACTION------------------------------

template<>
inline SimdVector3f SimdVector3f::operator-(float scalar) const
{
    return SimdVector3f(
        _mm_sub_ps(m_simd_data, _mm_set_ps1(scalar)),
        SimdVector3f::kSimdAssignTag
    );
}

template<>
inline SimdVector3f& SimdVector3f::operator-=(float scalar)
{
    m_simd_data = _mm_sub_ps(m_simd_data, _mm_set_ps1(scalar));
    return *this;
}

//------------------------------VECTOR SUBTRACTION------------------------------

template<>
template<>
inline SimdVector3f SimdVector3f::operator-(const SimdVector3f& v) const
{
    return SimdVector3f(
        _mm_sub_ps(m_simd_data, v.m_simd_data),
        SimdVector3f::kSimdAssignTag
    );
}

template<>
template<>
inline SimdVector3f& SimdVector3f::operator-=(const SimdVector3f& v)
{
    m_simd_data = _mm_sub_ps(m_simd_data, v.m_simd_data);
    return *this;
}

//----------------------------SCALAR MULTIPLICATION-----------------------------

template<>
inline SimdVector3f SimdVector3f::operator*(float scalar) const
{
    return SimdVector3f(
        _mm_mul_ps(m_simd_data, _mm_set_ps1(scalar)),
        SimdVector3f::kSimdAssignTag
    );
}

template<>
inline SimdVector3f& SimdVector3f::operator*=(float scalar)
{
    m_simd_data = _mm_mul_ps(m_simd_data, _mm_set_ps1(scalar));
    return *this;
}

//----------------------------VECTOR MULTIPLICATION-----------------------------

template<>
template<>
inline SimdVector3f SimdVector3f::operator*(const SimdVector3f& v) const
{
    return SimdVector3f(
        _mm_mul_ps(m_simd_data, v.m_simd_data),
        SimdVector3f::kSimdAssignTag
    );
}

template<>
template<>
inline SimdVector3f& SimdVector3f::operator*=(const SimdVector3f& v)
{
    m_simd_data = _mm_mul_ps(m_simd_data, v.m_simd_data);
    return *this;
}

//-------------------------------SCALAR DIVISION--------------------------------

template<>
inline SimdVector3f SimdVector3f::operator/(float scalar) const
{
    return SimdVector3f(
        _mm_div_ps(m_simd_data, _mm_set_ps1(scalar)),
        SimdVector3f::kSimdAssignTag
    );
}

template<>
inline SimdVector3f& SimdVector3f::operator/=(float scalar)
{
    m_simd_data = _mm_div_ps(m_simd_data, _mm_set_ps1(scalar));
    return *this;
}

//-------------------------------VECTOR DIVISION--------------------------------

template<>
template<>
inline SimdVector3f SimdVector3f::operator/(const SimdVector3f& v) const
{
    return SimdVector3f(
        _mm_div_ps(m_simd_data, v.m_simd_data),
        SimdVector3f::kSimdAssignTag
    );
}

template<>
template<>
inline SimdVector3f& SimdVector3f::operator/=(const SimdVector3f& v)
{
    m_simd_data = _mm_div_ps(m_simd_data, v.m_simd_data);
    return *this;
}

} // namespace gm
} // namespace arc

#endif
