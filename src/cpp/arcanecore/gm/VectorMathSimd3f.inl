/*!
 * \file
 * \author David Saxon
 * \brief Template specialistations for SIMD 3D float vector math.
 */
#ifndef ARCANECORE_GM_VECTORMATHSIMD3F_INL_
#define ARCANECORE_GM_VECTORMATHSIMD3F_INL_

#include <arcanecore/base/simd/Include.hpp>

namespace arc
{
namespace gm
{

//-------------------------------------DOT--------------------------------------

template<>
float dot(const SimdVector3f& a, const SimdVector3f& b)
{
    SimdVector3f r(_mm_dp_ps(a.get_simd(), b.get_simd(), 0x71), true);
    return r[0];
}

template<>
SimdVector3f cross(const SimdVector3f& a, const SimdVector3f& b)
{
    // align the vectors for the cross product
    const __m128 align_a1 = _mm_shuffle_ps(
        a.get_simd(),
        a.get_simd(),
        _MM_SHUFFLE(3, 0, 2, 1)
    );
    const __m128 align_a2 = _mm_shuffle_ps(
        a.get_simd(),
        a.get_simd(),
        _MM_SHUFFLE(3, 1, 0, 2)
    );
    const __m128 align_b1 = _mm_shuffle_ps(
        b.get_simd(),
        b.get_simd(),
        _MM_SHUFFLE(3, 1, 0, 2)
    );
    const __m128 align_b2 = _mm_shuffle_ps(
        b.get_simd(),
        b.get_simd(),
        _MM_SHUFFLE(3, 0, 2, 1)
    );

    return SimdVector3f(
        _mm_sub_ps(
            _mm_mul_ps(align_a1, align_b1),
            _mm_mul_ps(align_b2, align_a2)
        ),
        true
    );
}

} // namespace gm
} // namespace arc

#endif
