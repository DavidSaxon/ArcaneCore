/*!
 * \file
 * \author David Saxon
 * \brief Template specialistations for SIMD 4D float vector math.
 */
#ifndef ARCANECORE_GM_VECTORMATHSIMD4F_INL_
#define ARCANECORE_GM_VECTORMATHSIMD4F_INL_

#include <arcanecore/base/simd/Include.hpp>

#include <arcanecore/base/data/BinaryOperations.hpp>

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
static const SimdVector4f ONE_4f(1.0F);
/*!
 * \brief The constant value of 0.5.
 */
static const SimdVector4f HALF_4f(0.5F);
/*!
 * \brief The smallest non-denormalised float number.
 */
static const SimdVector4f MIN_DENORM_4f(
    arc::data::bit_cast<float>(0x00800000U));
// TODO: REMOVE ME?
/*!
 * \brief Bit mask the covers the exponent of a 32-bit floating point number
 */
static const SimdVector4f FLOAT_EXPONENT_MASK_4f(
    arc::data::bit_cast<float>(0x7F800000U));
/*!
 * \brief Bit mask the covers the everything but the exponent of a 32-bit
 *        floating point number.
 */
static const SimdVector4f FLOAT_INVERT_EXPONENT_MASK_4f(
    arc::data::bit_cast<float>(~0x7F800000U));
/*!
 * \brief The value 0x7F stored as a simd integer.
 */
static const SimdVector4i I_Ox7F_4F(0x7F);

} // namespace anonymous

//------------------------------------------------------------------------------
//                                   FUNCTIONS
//------------------------------------------------------------------------------

//-------------------------------------ABS--------------------------------------

template<>
inline SimdVector4f abs(const SimdVector4f& v)
{
    return SimdVector4f(
        _mm_and_ps(
            v.get_simd(),
            _mm_set_ps1(arc::data::bit_cast<float>(0x7FFFFFFF))
        ),
        SimdVector4f::kSimdAssignTag
    );
}

//-------------------------------------MIN--------------------------------------

template<>
inline SimdVector4f min(const SimdVector4f& a, const SimdVector4f& b)
{
    return SimdVector4f(
        _mm_min_ps(
            a.get_simd(),
            b.get_simd()
        ),
        SimdVector4f::kSimdAssignTag
    );
}

//-------------------------------------MAX--------------------------------------

template<>
inline SimdVector4f max(const SimdVector4f& a, const SimdVector4f& b)
{
    return SimdVector4f(
        _mm_max_ps(
            a.get_simd(),
            b.get_simd()
        ),
        SimdVector4f::kSimdAssignTag
    );
}

//------------------------------------CLAMP-------------------------------------

template<>
inline SimdVector4f clamp(
        const SimdVector4f& v,
        const SimdVector4f& lower_threshold,
        const SimdVector4f& upper_threshold)
{
    return SimdVector4f(
        _mm_max_ps(
            lower_threshold.get_simd(),
            _mm_min_ps(upper_threshold.get_simd(), v.get_simd())

        ),
        SimdVector4f::kSimdAssignTag
    );
}

//-------------------------------------DOT--------------------------------------

template<>
float dot(const SimdVector4f& a, const SimdVector4f& b)
{
    SimdVector4f r(
        _mm_dp_ps(a.get_simd(), b.get_simd(), 0xF1),
        SimdVector4f::kSimdAssignTag
    );
    return r[0];
}

//-------------------------------------LOG--------------------------------------

// log specific constants
namespace
{

static const SimdVector4f LOG_SQRTHF_4f(0.707106781186547524F);
static const SimdVector4f LOG_P0_4f( 7.0376836292e-2F);
static const SimdVector4f LOG_P1_4f(-1.1514610310e-1F);
static const SimdVector4f LOG_P2_4f(1.1676998740e-1F);
static const SimdVector4f LOG_P3_4f(-1.2420140846e-1F);
static const SimdVector4f LOG_P4_4f( 1.4249322787e-1F);
static const SimdVector4f LOG_P5_4f(-1.6668057665e-1F);
static const SimdVector4f LOG_P6_4f( 2.0000714765e-1F);
static const SimdVector4f LOG_P7_4f(-2.4999993993e-1F);
static const SimdVector4f LOG_P8_4f( 3.3333331174e-1F);
static const SimdVector4f LOG_Q1_4f(-2.12194440e-4F);
static const SimdVector4f LOG_Q2_4f( 0.693359375F);

} // namespace anonymous

template<>
SimdVector4f log(const SimdVector4f& v)
{
    // mask for any component that are invalid (less than or equal to 0)
    __m128 invalid_mask = _mm_cmple_ps(v.get_simd(), _mm_setzero_ps());
    // setup the return value and cut off any denormalised stuff
    SimdVector4f x(
        _mm_max_ps(v.get_simd(), MIN_DENORM_4f.get_simd()),
        SimdVector4f::kSimdAssignTag
    );

    __m128i emm0 = _mm_srli_epi32(_mm_castps_si128(x.get_simd()), 23);

    // keep only the fractional part of the value
    x.get_simd() = _mm_and_ps(
        x.get_simd(),
        FLOAT_INVERT_EXPONENT_MASK_4f.get_simd()
    );
    x.get_simd() = _mm_or_ps(x.get_simd(), HALF_4f.get_simd());

    emm0 = _mm_sub_epi32(emm0, I_Ox7F_4F.get_simd());
    __m128 e =  _mm_cvtepi32_ps(emm0);
    e =  _mm_add_ps(e, ONE_4f.get_simd());

    __m128 mask =_mm_cmplt_ps(x.get_simd(), LOG_SQRTHF_4f.get_simd());
    __m128 temp = _mm_and_ps(x.get_simd(), mask);

    x.get_simd() = _mm_sub_ps(x.get_simd(), ONE_4f.get_simd());
    e = _mm_sub_ps(e, _mm_and_ps(ONE_4f.get_simd(), mask));
    x.get_simd() = _mm_add_ps(x.get_simd(), temp);


    __m128 z = _mm_mul_ps(x.get_simd(), x.get_simd());

    __m128 y = LOG_P0_4f.get_simd();
    y = _mm_mul_ps(y, x.get_simd());
    y = _mm_add_ps(y, LOG_P1_4f.get_simd());
    y = _mm_mul_ps(y, x.get_simd());
    y = _mm_add_ps(y, LOG_P2_4f.get_simd());
    y = _mm_mul_ps(y, x.get_simd());
    y = _mm_add_ps(y, LOG_P3_4f.get_simd());
    y = _mm_mul_ps(y, x.get_simd());
    y = _mm_add_ps(y, LOG_P4_4f.get_simd());
    y = _mm_mul_ps(y, x.get_simd());
    y = _mm_add_ps(y, LOG_P5_4f.get_simd());
    y = _mm_mul_ps(y, x.get_simd());
    y = _mm_add_ps(y, LOG_P6_4f.get_simd());
    y = _mm_mul_ps(y, x.get_simd());
    y = _mm_add_ps(y, LOG_P7_4f.get_simd());
    y = _mm_mul_ps(y, x.get_simd());
    y = _mm_add_ps(y, LOG_P8_4f.get_simd());
    y = _mm_mul_ps(y, x.get_simd());

    y = _mm_mul_ps(y, z);

    temp = _mm_mul_ps(e, LOG_Q1_4f.get_simd());
    y = _mm_add_ps(y, temp);

    temp = _mm_mul_ps(z, HALF_4f.get_simd());
    y = _mm_sub_ps(y, temp);

    temp = _mm_mul_ps(e, LOG_Q2_4f.get_simd());
    x.get_simd() = _mm_add_ps(x.get_simd(), y);
    x.get_simd() = _mm_add_ps(x.get_simd(), temp);
    x.get_simd() = _mm_or_ps(x.get_simd(), invalid_mask);

    return x;
}

//-------------------------------------LOG2-------------------------------------

// lookup table
namespace
{

static const std::size_t LOG2_TABLE_SIZE_LOG2_4f = 8;
static const std::size_t LOG2_TABLE_SIZE_4f = 1 << LOG2_TABLE_SIZE_LOG2_4f;

static float LOG2_LOOK_UP_TABLE_4f[2 * LOG2_TABLE_SIZE_4f];

// use the constructor to globally initialise the log2 lookup table
struct Log2LookupTableInit4f
{
    Log2LookupTableInit4f()
    {
        for (std::size_t i = 0; i < LOG2_TABLE_SIZE_4f; ++i)
        {
            LOG2_LOOK_UP_TABLE_4f[i] =
                std::log2(1.0F + i * (1.0F / (LOG2_TABLE_SIZE_4f - 1)));
        }
    }
};
static const Log2LookupTableInit4f Log2LookupTableInit4fInstance;

} // namespace anonymous

template<>
SimdVector4f log2(const SimdVector4f& v)
{
    __m128i exponent_mask = _mm_set1_epi32(0x7F800000);
    __m128i mantissa_mask = _mm_set1_epi32(0x007FFFFF);

    __m128i i = _mm_castps_si128(v.get_simd());

    __m128 e = _mm_cvtepi32_ps(_mm_sub_epi32(
        _mm_srli_epi32(_mm_and_si128(i, exponent_mask), 23),
        _mm_set1_epi32(127)
    ));

    SimdVector4i index(
        _mm_srli_epi32(
            _mm_and_si128(i, mantissa_mask), 23 - LOG2_TABLE_SIZE_LOG2_4f
        ),
        SimdVector4i::kSimdAssignTag
    );

    SimdVector4f expfpart;
    expfpart[0] = LOG2_LOOK_UP_TABLE_4f[index[0]];
    expfpart[1] = LOG2_LOOK_UP_TABLE_4f[index[1]];
    expfpart[2] = LOG2_LOOK_UP_TABLE_4f[index[2]];
    expfpart[3] = LOG2_LOOK_UP_TABLE_4f[index[3]];

    return SimdVector4f(
        _mm_add_ps(expfpart.get_simd(), e),
        SimdVector4f::kSimdAssignTag
    );
}

//-------------------------------------EXP--------------------------------------

// exp specific constants
namespace
{

static const SimdVector4f EXP_HIGH_4f(88.3762626647949F);
static const SimdVector4f EXP_LOW_4f (-88.3762626647949F);

static const SimdVector4f EXP_LOG2EF_4f(1.44269504088896341F);
static const SimdVector4f EXP_C1_4f(0.693359375F);
static const SimdVector4f EXP_C2_4f(-2.12194440e-4F);
static const SimdVector4f EXP_P0_4f(1.9875691500E-4F);
static const SimdVector4f EXP_P1_4f(1.3981999507E-3F);
static const SimdVector4f EXP_P2_4f(8.3334519073E-3F);
static const SimdVector4f EXP_P3_4f(4.1665795894E-2F);
static const SimdVector4f EXP_P4_4f(1.6666665459E-1F);
static const SimdVector4f EXP_P5_4f(5.0000001201E-1F);

} // namespace anonymous

template<>
SimdVector4f exp(const SimdVector4f& v)
{
    // setup the result and clamp between EXP_LOW and EXP_HIGH
    __m128 x = _mm_max_ps(v.get_simd(), EXP_LOW_4f.get_simd());
    x = _mm_min_ps(x, EXP_HIGH_4f.get_simd());

    // express exp(x) as exp(g + n * log(2))
    __m128 fx = _mm_mul_ps(x, EXP_LOG2EF_4f.get_simd());
    fx = _mm_add_ps(fx, HALF_4f.get_simd());

    // floor the floats (by truncating)
    __m128i emm0 = _mm_cvttps_epi32(fx);
    __m128 temp  = _mm_cvtepi32_ps(emm0);

    // if greater, subtract 1
    __m128 mask = _mm_cmpgt_ps(temp, fx);
    mask = _mm_and_ps(mask, ONE_4f.get_simd());
    fx = _mm_sub_ps(temp, mask);

    temp = _mm_mul_ps(fx, EXP_C1_4f.get_simd());
    __m128 z = _mm_mul_ps(fx, EXP_C2_4f.get_simd());

    x = _mm_sub_ps(x, temp);
    x = _mm_sub_ps(x, z);

    z = _mm_mul_ps(x, x);

    __m128 y = EXP_P0_4f.get_simd();
    y = _mm_mul_ps(y, x);
    y = _mm_add_ps(y, EXP_P1_4f.get_simd());
    y = _mm_mul_ps(y, x);
    y = _mm_add_ps(y, EXP_P2_4f.get_simd());
    y = _mm_mul_ps(y, x);
    y = _mm_add_ps(y, EXP_P3_4f.get_simd());
    y = _mm_mul_ps(y, x);
    y = _mm_add_ps(y, EXP_P4_4f.get_simd());
    y = _mm_mul_ps(y, x);
    y = _mm_add_ps(y, EXP_P5_4f.get_simd());
    y = _mm_mul_ps(y, z);
    y = _mm_add_ps(y, x);
    y = _mm_add_ps(y, ONE_4f.get_simd());

    // build 2^n
    emm0 = _mm_cvttps_epi32(fx);
    emm0 = _mm_add_epi32(emm0, I_Ox7F_4F.get_simd());
    emm0 = _mm_slli_epi32(emm0, 23);
    __m128 pow2n = _mm_castsi128_ps(emm0);

    return SimdVector4f(
        _mm_mul_ps(y, pow2n),
        SimdVector4f::kSimdAssignTag
    );
}

} // namespace gm
} // namespace arc

#endif
