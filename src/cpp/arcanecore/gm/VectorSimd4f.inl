/*!
 * \file
 * \author David Saxon
 * \brief Template specialistations for SIMD 4D float vectors.
 */
#ifndef ARCANECORE_GM_VECTORSMID4F_INL_
#define ARCANECORE_GM_VECTORSMID4F_INL_

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
inline SimdVector4f::Vector()
{
    m_simd_data = _mm_setzero_ps();
}

//------------------------------SCALAR CONSTRUCTOR------------------------------

template<>
inline SimdVector4f::Vector(float scalar)
{
    m_simd_data = _mm_set_ps1(scalar);
}

//-------------------------------COPY CONSTRUCTOR-------------------------------

template<>
template<>
inline SimdVector4f::Vector(const SimdVector4f& v)
{
    m_simd_data = v.m_simd_data;
}

//------------------------------------------------------------------------------
//                                   OPERATORS
//------------------------------------------------------------------------------

//------------------------------SCALAR ASSIGNMENT-------------------------------

template<>
inline SimdVector4f& SimdVector4f::operator=(float scalar)
{
    m_simd_data = _mm_set_ps1(scalar);
    return *this;
}

//------------------------------VECTOR ASSIGNMENT-------------------------------

template<>
template<>
inline SimdVector4f& SimdVector4f::operator=(const SimdVector4f& v)
{
    m_simd_data = v.m_simd_data;
    return *this;
}

//-----------------------------------NEGATION-----------------------------------

template<>
inline SimdVector4f SimdVector4f::operator-() const
{
    return SimdVector4f(_mm_xor_ps(m_simd_data, _mm_set1_ps(-0.f)), true);
}

//-------------------------------SCALAR ADDITION--------------------------------

template<>
inline SimdVector4f SimdVector4f::operator+(float scalar) const
{
    return SimdVector4f(_mm_add_ps(m_simd_data, _mm_set_ps1(scalar)), true);
}

template<>
inline SimdVector4f& SimdVector4f::operator+=(float scalar)
{
    m_simd_data = _mm_add_ps(m_simd_data, _mm_set_ps1(scalar));
    return *this;
}

//-------------------------------VECTOR ADDITION--------------------------------

template<>
template<>
inline SimdVector4f SimdVector4f::operator+(const SimdVector4f& v) const
{
    return SimdVector4f(_mm_add_ps(m_simd_data, v.m_simd_data), true);
}

template<>
template<>
inline SimdVector4f& SimdVector4f::operator+=(const SimdVector4f& v)
{
    m_simd_data = _mm_add_ps(m_simd_data, v.m_simd_data);
    return *this;
}

//------------------------------SCALAR SUBTRACTION------------------------------

template<>
inline SimdVector4f SimdVector4f::operator-(float scalar) const
{
    return SimdVector4f(_mm_sub_ps(m_simd_data, _mm_set_ps1(scalar)), true);
}

template<>
inline SimdVector4f& SimdVector4f::operator-=(float scalar)
{
    m_simd_data = _mm_sub_ps(m_simd_data, _mm_set_ps1(scalar));
    return *this;
}

//------------------------------VECTOR SUBTRACTION------------------------------

template<>
template<>
inline SimdVector4f SimdVector4f::operator-(const SimdVector4f& v) const
{
    return SimdVector4f(_mm_add_ps(m_simd_data, v.m_simd_data), true);
}

template<>
template<>
inline SimdVector4f& SimdVector4f::operator-=(const SimdVector4f& v)
{
    m_simd_data = _mm_add_ps(m_simd_data, v.m_simd_data);
    return *this;
}

//----------------------------SCALAR MULTIPLICATION-----------------------------

template<>
inline SimdVector4f SimdVector4f::operator*(float scalar) const
{
    return SimdVector4f(_mm_mul_ps(m_simd_data, _mm_set_ps1(scalar)), true);
}

template<>
inline SimdVector4f& SimdVector4f::operator*=(float scalar)
{
    m_simd_data = _mm_mul_ps(m_simd_data, _mm_set_ps1(scalar));
    return *this;
}

//----------------------------VECTOR MULTIPLICATION-----------------------------

template<>
template<>
inline SimdVector4f SimdVector4f::operator*(const SimdVector4f& v) const
{
    return SimdVector4f(_mm_mul_ps(m_simd_data, v.m_simd_data), true);
}

template<>
template<>
inline SimdVector4f& SimdVector4f::operator*=(const SimdVector4f& v)
{
    m_simd_data = _mm_mul_ps(m_simd_data, v.m_simd_data);
    return *this;
}

//-------------------------------SCALAR DIVISION--------------------------------

template<>
inline SimdVector4f SimdVector4f::operator/(float scalar) const
{
    return SimdVector4f(_mm_div_ps(m_simd_data, _mm_set_ps1(scalar)), true);
}

template<>
inline SimdVector4f& SimdVector4f::operator/=(float scalar)
{
    m_simd_data = _mm_div_ps(m_simd_data, _mm_set_ps1(scalar));
    return *this;
}

//-------------------------------VECTOR DIVISION--------------------------------

template<>
template<>
inline SimdVector4f SimdVector4f::operator/(const SimdVector4f& v) const
{
    return SimdVector4f(_mm_div_ps(m_simd_data, v.m_simd_data), true);
}

template<>
template<>
inline SimdVector4f& SimdVector4f::operator/=(const SimdVector4f& v)
{
    m_simd_data = _mm_div_ps(m_simd_data, v.m_simd_data);
    return *this;
}

} // namespace gm
} // namespace arc

#endif
