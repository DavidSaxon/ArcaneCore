/*!
 * \file
 * \author David Saxon
 */
#ifndef ARCANECORE_GM_VECTORSMID_INL_
#define ARCANECORE_GM_VECTORSMID_INL_

#ifndef ARC_GM_DISABLE_SSE
    #include <arcanecore/base/simd/Include.hpp>
#endif

namespace arc
{
namespace gm
{

// TODO: constructors

template<> template<>
inline SimdVector3f SimdVector3f::operator+(const SimdVector3f& v) const
{
    SimdVector3f r;
    r.m_simd_data = _mm_add_ps(m_simd_data, v.m_simd_data);
    return r;
}

template<> template<>
inline SimdVector4f SimdVector4f::operator+(const SimdVector4f& v) const
{
    SimdVector4f r;
    r.m_simd_data = _mm_add_ps(m_simd_data, v.m_simd_data);
    return r;
}

template<> template<>
inline SimdVector3f& SimdVector3f::operator+=(const SimdVector3f& v)
{
    m_simd_data = _mm_add_ps(m_simd_data, v.m_simd_data);
    return *this;
}

template<> template<>
inline SimdVector4f& SimdVector4f::operator+=(const SimdVector4f& v)
{
    m_simd_data = _mm_add_ps(m_simd_data, v.m_simd_data);
    return *this;
}

} // namespace gm
} // namespace arc

#endif
