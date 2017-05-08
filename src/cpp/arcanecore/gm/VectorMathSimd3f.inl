/*!
 * \file
 * \author David Saxon
 * \brief Template specialistations for SIMD 3D float vector math.
 */
#ifndef ARCANECORE_GM_VECTORMATHSIMD3F_INL_
#define ARCANECORE_GM_VECTORMATHSIMD3F_INL_

#include <arcanecore/base/simd/Include.hpp>

#include <arcanecore/base/data/BinaryOperations.hpp>


// TODO: REMOVE ME
#include <xmmintrin.h>

namespace arc
{
namespace gm
{

//------------------------------------------------------------------------------
//                                   CONSTANTS
//------------------------------------------------------------------------------

namespace
{

/*!
 * \brief The constant value of 1.
 */
static const SimdVector3f ONE_3f(1.0F);
/*!
 * \brief The constant value of 0.5.
 */
static const SimdVector3f HALF_3f(0.5F);
/*!
 * \brief The smallest non-denormalised float number.
 */
static const SimdVector3f MIN_DENORM_3f(
    arc::data::bit_cast<float>(0x00800000U));
/*!
 * \brief Bit mask the covers the exponent of a 32-bit floating point number
 */
static const SimdVector3f FLOAT_EXPONENT_MASK_3f(
    arc::data::bit_cast<float>(0x7F800000U));
/*!
 * \brief Bit mask the covers the everything but the exponent of a 32-bit
 *        floating point number.
 */
static const SimdVector3f FLOAT_INVERT_EXPONENT_MASK_3f(
    arc::data::bit_cast<float>(~0x7F800000U));
/*!
 * \brief The value 0x7F stored as a simd integer.
 */
static const SimdVector3i I_Ox7F_3F(0x7F);

} // namespace anonymous

//------------------------------------------------------------------------------
//                                   FUNCTIONS
//------------------------------------------------------------------------------

//-------------------------------------ABS--------------------------------------

template<>
inline SimdVector3f abs(const SimdVector3f& v)
{
    return SimdVector3f(
        _mm_and_ps(
            v.get_simd(),
            _mm_set_ps1(arc::data::bit_cast<float>(0x7FFFFFFFU))
        ),
        SimdVector3f::kSimdAssignTag
    );
}

//-------------------------------------MIN--------------------------------------

template<>
inline SimdVector3f min(const SimdVector3f& a, const SimdVector3f& b)
{
    return SimdVector3f(
        _mm_min_ps(
            a.get_simd(),
            b.get_simd()
        ),
        SimdVector3f::kSimdAssignTag
    );
}

//-------------------------------------MAX--------------------------------------

template<>
inline SimdVector3f max(const SimdVector3f& a, const SimdVector3f& b)
{
    return SimdVector3f(
        _mm_max_ps(
            a.get_simd(),
            b.get_simd()
        ),
        SimdVector3f::kSimdAssignTag
    );
}

//------------------------------------CLAMP-------------------------------------

template<>
inline SimdVector3f clamp(
        const SimdVector3f& v,
        const SimdVector3f& lower_threshold,
        const SimdVector3f& upper_threshold)
{
    return SimdVector3f(
        _mm_max_ps(
            lower_threshold.get_simd(),
            _mm_min_ps(upper_threshold.get_simd(), v.get_simd())

        ),
        SimdVector3f::kSimdAssignTag
    );
}

//-------------------------------------DOT--------------------------------------

template<>
float dot(const SimdVector3f& a, const SimdVector3f& b)
{
    SimdVector3f r(
        _mm_dp_ps(a.get_simd(), b.get_simd(), 0x71),
        SimdVector3f::kSimdAssignTag
    );
    return r[0];
}

//------------------------------------CROSS-------------------------------------

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
        SimdVector3f::kSimdAssignTag
    );
}

//-------------------------------------LOG--------------------------------------

// log specific constants
namespace
{

// for calculating log
static const SimdVector3f LOG_SQRTHF_3f(0.707106781186547524F);
static const SimdVector3f LOG_P0_3f( 7.0376836292e-2F);
static const SimdVector3f LOG_P1_3f(-1.1514610310e-1F);
static const SimdVector3f LOG_P2_3f(1.1676998740e-1F);
static const SimdVector3f LOG_P3_3f(-1.2420140846e-1F);
static const SimdVector3f LOG_P4_3f( 1.4249322787e-1F);
static const SimdVector3f LOG_P5_3f(-1.6668057665e-1F);
static const SimdVector3f LOG_P6_3f( 2.0000714765e-1F);
static const SimdVector3f LOG_P7_3f(-2.4999993993e-1F);
static const SimdVector3f LOG_P8_3f( 3.3333331174e-1F);
static const SimdVector3f LOG_Q1_3f(-2.12194440e-4F);
static const SimdVector3f LOG_Q2_3f( 0.693359375F);

} // namespace anonymous

template<>
SimdVector3f log(const SimdVector3f& v)
{
    // mask for any component that are invalid (less than or equal to 0)
    __m128 invalid_mask = _mm_cmple_ps(v.get_simd(), _mm_setzero_ps());
    // setup the return value and cut off any denormalised stuff
    SimdVector3f x(
        _mm_max_ps(v.get_simd(), MIN_DENORM_3f.get_simd()),
        SimdVector3f::kSimdAssignTag
    );

    __m128i emm0 = _mm_srli_epi32(_mm_castps_si128(x.get_simd()), 23);

    // keep only the fractional part of the value
    x.get_simd() = _mm_and_ps(
        x.get_simd(),
        FLOAT_INVERT_EXPONENT_MASK_3f.get_simd()
    );
    x.get_simd() = _mm_or_ps(x.get_simd(), HALF_3f.get_simd());

    emm0 = _mm_sub_epi32(emm0, I_Ox7F_3F.get_simd());
    __m128 e =  _mm_cvtepi32_ps(emm0);
    e =  _mm_add_ps(e, ONE_3f.get_simd());

    __m128 mask =_mm_cmplt_ps(x.get_simd(), LOG_SQRTHF_3f.get_simd());
    __m128 temp = _mm_and_ps(x.get_simd(), mask);

    x.get_simd() = _mm_sub_ps(x.get_simd(), ONE_3f.get_simd());
    e = _mm_sub_ps(e, _mm_and_ps(ONE_3f.get_simd(), mask));
    x.get_simd() = _mm_add_ps(x.get_simd(), temp);


    __m128 z = _mm_mul_ps(x.get_simd(), x.get_simd());

    __m128 y = LOG_P0_3f.get_simd();
    y = _mm_mul_ps(y, x.get_simd());
    y = _mm_add_ps(y, LOG_P1_3f.get_simd());
    y = _mm_mul_ps(y, x.get_simd());
    y = _mm_add_ps(y, LOG_P2_3f.get_simd());
    y = _mm_mul_ps(y, x.get_simd());
    y = _mm_add_ps(y, LOG_P3_3f.get_simd());
    y = _mm_mul_ps(y, x.get_simd());
    y = _mm_add_ps(y, LOG_P4_3f.get_simd());
    y = _mm_mul_ps(y, x.get_simd());
    y = _mm_add_ps(y, LOG_P5_3f.get_simd());
    y = _mm_mul_ps(y, x.get_simd());
    y = _mm_add_ps(y, LOG_P6_3f.get_simd());
    y = _mm_mul_ps(y, x.get_simd());
    y = _mm_add_ps(y, LOG_P7_3f.get_simd());
    y = _mm_mul_ps(y, x.get_simd());
    y = _mm_add_ps(y, LOG_P8_3f.get_simd());
    y = _mm_mul_ps(y, x.get_simd());

    y = _mm_mul_ps(y, z);

    temp = _mm_mul_ps(e, LOG_Q1_3f.get_simd());
    y = _mm_add_ps(y, temp);

    temp = _mm_mul_ps(z, HALF_3f.get_simd());
    y = _mm_sub_ps(y, temp);

    temp = _mm_mul_ps(e, LOG_Q2_3f.get_simd());
    x.get_simd() = _mm_add_ps(x.get_simd(), y);
    x.get_simd() = _mm_add_ps(x.get_simd(), temp);
    x.get_simd() = _mm_or_ps(x.get_simd(), invalid_mask);

    return x;
}

//-------------------------------------LOG2-------------------------------------

// lookup table
namespace
{

static const std::size_t LOG2_TABLE_SIZE_LOG2_3f = 8;
static const std::size_t LOG2_TABLE_SIZE_3f = 1 << LOG2_TABLE_SIZE_LOG2_3f;

static float LOG2_LOOK_UP_TABLE_3f[2 * LOG2_TABLE_SIZE_3f];

// use the constructor to globally initialise the log2 lookup table
struct Log2LookupTableInit3f
{
    Log2LookupTableInit3f()
    {
        for (std::size_t i = 0; i < LOG2_TABLE_SIZE_3f; ++i)
        {
            LOG2_LOOK_UP_TABLE_3f[i] =
                std::log2(1.0F + i * (1.0F / (LOG2_TABLE_SIZE_3f - 1)));
        }
    }
};
static const Log2LookupTableInit3f Log2LookupTableInit3fInstance;

} // namespace anonymous

template<>
SimdVector3f log2(const SimdVector3f& v)
{
    __m128i exponent_mask = _mm_set1_epi32(0x7F800000);
    __m128i mantissa_mask = _mm_set1_epi32(0x007FFFFF);

    __m128i i = _mm_castps_si128(v.get_simd());

    __m128 e = _mm_cvtepi32_ps(_mm_sub_epi32(
        _mm_srli_epi32(_mm_and_si128(i, exponent_mask), 23),
        _mm_set1_epi32(127)
    ));

    SimdVector3i index(
        _mm_srli_epi32(
            _mm_and_si128(i, mantissa_mask), 23 - LOG2_TABLE_SIZE_LOG2_3f
        ),
        SimdVector3i::kSimdAssignTag
    );

    SimdVector3f expfpart;
    expfpart[0] = LOG2_LOOK_UP_TABLE_3f[index[0]];
    expfpart[1] = LOG2_LOOK_UP_TABLE_3f[index[1]];
    expfpart[2] = LOG2_LOOK_UP_TABLE_3f[index[2]];

    return SimdVector3f(
        _mm_add_ps(expfpart.get_simd(), e),
        SimdVector3f::kSimdAssignTag
    );
}

//-------------------------------------EXP--------------------------------------

// exp specific constants
namespace
{

static const SimdVector3f EXP_HIGH_3f(88.3762626647949F);
static const SimdVector3f EXP_LOW_3f (-88.3762626647949F);

static const SimdVector3f EXP_LOG2EF_3f(1.44269504088896341F);
static const SimdVector3f EXP_C1_3f(0.693359375F);
static const SimdVector3f EXP_C2_3f(-2.12194440e-4F);
static const SimdVector3f EXP_P0_3f(1.9875691500E-4F);
static const SimdVector3f EXP_P1_3f(1.3981999507E-3F);
static const SimdVector3f EXP_P2_3f(8.3334519073E-3F);
static const SimdVector3f EXP_P3_3f(4.1665795894E-2F);
static const SimdVector3f EXP_P4_3f(1.6666665459E-1F);
static const SimdVector3f EXP_P5_3f(5.0000001201E-1F);

} // namespace anonymous

template<>
SimdVector3f exp(const SimdVector3f& v)
{
    // setup the result and clamp between EXP_LOW and EXP_HIGH
    __m128 x = _mm_max_ps(v.get_simd(), EXP_LOW_3f.get_simd());
    x = _mm_min_ps(x, EXP_HIGH_3f.get_simd());

    // express exp(x) as exp(g + n * log(2))
    __m128 fx = _mm_mul_ps(x, EXP_LOG2EF_3f.get_simd());
    fx = _mm_add_ps(fx, HALF_3f.get_simd());

    // floor the floats (by truncating)
    __m128i emm0 = _mm_cvttps_epi32(fx);
    __m128 temp  = _mm_cvtepi32_ps(emm0);

    // if greater, subtract 1
    __m128 mask = _mm_cmpgt_ps(temp, fx);
    mask = _mm_and_ps(mask, ONE_3f.get_simd());
    fx = _mm_sub_ps(temp, mask);

    temp = _mm_mul_ps(fx, EXP_C1_3f.get_simd());
    __m128 z = _mm_mul_ps(fx, EXP_C2_3f.get_simd());

    x = _mm_sub_ps(x, temp);
    x = _mm_sub_ps(x, z);

    z = _mm_mul_ps(x, x);

    __m128 y = EXP_P0_3f.get_simd();
    y = _mm_mul_ps(y, x);
    y = _mm_add_ps(y, EXP_P1_3f.get_simd());
    y = _mm_mul_ps(y, x);
    y = _mm_add_ps(y, EXP_P2_3f.get_simd());
    y = _mm_mul_ps(y, x);
    y = _mm_add_ps(y, EXP_P3_3f.get_simd());
    y = _mm_mul_ps(y, x);
    y = _mm_add_ps(y, EXP_P4_3f.get_simd());
    y = _mm_mul_ps(y, x);
    y = _mm_add_ps(y, EXP_P5_3f.get_simd());
    y = _mm_mul_ps(y, z);
    y = _mm_add_ps(y, x);
    y = _mm_add_ps(y, ONE_3f.get_simd());

    // build 2^n
    emm0 = _mm_cvttps_epi32(fx);
    emm0 = _mm_add_epi32(emm0, I_Ox7F_3F.get_simd());
    emm0 = _mm_slli_epi32(emm0, 23);
    __m128 pow2n = _mm_castsi128_ps(emm0);

    return SimdVector3f(
        _mm_mul_ps(y, pow2n),
        SimdVector3f::kSimdAssignTag
    );
}

} // namespace gm
} // namespace arc

#endif
