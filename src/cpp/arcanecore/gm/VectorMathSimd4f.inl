/*!
 * \file
 * \author David Saxon
 * \brief Template specialistations for SIMD 4D float vector math.
 */
#ifndef ARCANECORE_GM_VECTORMATHSIMD4F_INL_
#define ARCANECORE_GM_VECTORMATHSIMD4F_INL_

#include <arcanecore/base/simd/Include.hpp>

namespace arc
{
namespace gm
{

//-------------------------------------DOT--------------------------------------

template<>
float dot(const SimdVector4f& a, const SimdVector4f& b)
{
    SimdVector4f r(_mm_dp_ps(a.get_simd(), b.get_simd(), 0xF1), true);
    return r[0];
}

} // namespace gm
} // namespace arc

#endif
