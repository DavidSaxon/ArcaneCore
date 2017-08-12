/*!
 * \file
 * \author David Saxon
 * \brief Template specialistations for SIMD 4D float vector math.
 */
#ifndef ARCANECORE_GM_VECTORMATHSIMD4F_INL_
#define ARCANECORE_GM_VECTORMATHSIMD4F_INL_

#include <arcanecore/base/math/MathConstants.hpp>
#include <arcanecore/base/simd/Include.hpp>
#include <arcanecore/base/data/BinaryOperations.hpp>

namespace arc
{
namespace gm
{

//------------------------------------------------------------------------------
//                                   CONSTANTS
//------------------------------------------------------------------------------

/*!
 * \brief The constant value of 0.0F.
 */
static const SimdVector4f ZERO_4f(0.0F);
/*!
 * \brief The constant value of 1.
 */
static const SimdVector4f ONE_4f(1.0F);
/*!
 * \brief The constant value of 0.5.
 */
static const SimdVector4f HALF_4f(0.5F);
/*!
 * \brief The constant value of the smallest float.
 */
static const SimdVector4f EPSILON_4f(std::numeric_limits<float>::epsilon());
/*!
 * \brief The smallest non-denormalised float number.
 */
static const SimdVector4f MIN_DENORM_4f(
    arc::data::bit_cast<float>(0x00800000U));
/*!
 * \brief Bit mask the covers the sign-bit of a 32-bit floating point number.
 */
static const SimdVector4f FLOAT_SIGN_MASK_4f(
    arc::data::bit_cast<float>(0x80000000));
/*!
 * \brief Bit mask the covers everything but the sign-bit of a 32-bit floating
 *        point number.
 */
static const SimdVector4f FLOAT_INVERT_SIGN_MASK_4f(
    arc::data::bit_cast<float>(~0x80000000));
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
 * \brief The value of PI.
 */
static const SimdVector4f PI_4f(arc::math::PI_F);
/*!
 * \brief The value of 2.0 / PI.
 */
static const SimdVector4f TWO_OVER_PI_4f(2.0F / arc::math::PI_F);
/*!
 * \brief The value of 4.0 / PI.
 */
static const SimdVector4f FOUR_OVER_PI_4f(4.0F / arc::math::PI_F);

//------------------------------------------------------------------------------
//                                HIDDEN CONSTANTS
//------------------------------------------------------------------------------

namespace
{

/*!
 * \brief The value 1 stored as a simd integer.
 */
static const SimdVector4i I_ONE_4f(1);
/*!
 * \brief The value ~1 stored as a simd integer.
 */
static const SimdVector4i I_INVERT_ONE_4f(~1);
/*!
 * \brief The value 2 stored as a simd integer.
 */
static const SimdVector4i I_TWO_4f(2);
/*!
 * \brief The value 4 stored as a simd integer.
 */
static const SimdVector4i I_FOUR_4f(4);
/*!
 * \brief The value 0x7F stored as a simd integer.
 */
static const SimdVector4i I_Ox7F_4f(0x7F);

} // namespace anonymous

//------------------------------------------------------------------------------
//                                   FUNCTIONS
//------------------------------------------------------------------------------

//-------------------------------------ABS--------------------------------------

template<>
inline SimdVector4f abs(const SimdVector4f& v)
{
    return SimdVector4f(
        _mm_and_ps(v.get_simd(), FLOAT_INVERT_SIGN_MASK_4f.get_simd()),
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

//------------------------------------FLOOR-------------------------------------

template<>
inline SimdVector4f floor(const SimdVector4f& v)
{
    __m128i v0 = _mm_setzero_si128();
    __m128i v1 = _mm_cmpeq_epi32(v0, v0);
    __m128i ji = _mm_srli_epi32(v1, 25);
    __m128i j0 = _mm_slli_epi32(ji, 23);
    __m128 j = *((__m128*) &j0);
    __m128i i = _mm_cvttps_epi32(v.get_simd());
    __m128 fi = _mm_cvtepi32_ps(i);
    __m128 igx = _mm_cmpgt_ps(fi, v.get_simd());
    j = _mm_and_ps(igx, j);
    return SimdVector4f(_mm_sub_ps(fi, j), SimdVector4f::kSimdAssignTag);
}

//-------------------------------------CEIL-------------------------------------

template<>
inline SimdVector4f ceil(const SimdVector4f& v)
{
    __m128i v0 = _mm_setzero_si128();
    __m128i v1 = _mm_cmpeq_epi32(v0, v0);
    __m128i ji = _mm_srli_epi32( v1, 25);
    __m128i j0 = _mm_slli_epi32(ji, 23);
    __m128 j = *((__m128*) &j0);
    __m128i i = _mm_cvttps_epi32(v.get_simd());
    __m128 fi = _mm_cvtepi32_ps(i);
    __m128 igx = _mm_cmplt_ps(fi, v.get_simd());
    j = _mm_and_ps(igx, j);
    return SimdVector4f(_mm_add_ps(fi, j), SimdVector4f::kSimdAssignTag);
}

//------------------------------------ROUND-------------------------------------

template<>
inline SimdVector4f round(const SimdVector4f& v)
{
    __m128 v0 = _mm_setzero_ps();
    __m128 v1 = _mm_cmpeq_ps(v0, v0);
    __m128i v2 = _mm_srli_epi32(*((__m128i*) &v1), 2);
    __m128 vNearest2 = *((__m128*) &v2);
    __m128i i = _mm_cvttps_epi32(v.get_simd());
    __m128 vTrunc = _mm_cvtepi32_ps(i);
    __m128 rmd = _mm_sub_ps(v.get_simd(), vTrunc);
    // This feels like a bit of a hack... but it ensures that 0.5 rounds up
    // rather than down
    rmd = _mm_add_ps(rmd, EPSILON_4f.get_simd());
    __m128 rmd2 = _mm_mul_ps(rmd, vNearest2);
    __m128i rmd2i = _mm_cvttps_epi32(rmd2);
    __m128 rmd2Trunc = _mm_cvtepi32_ps(rmd2i);
    return SimdVector4f(
        _mm_add_ps(vTrunc, rmd2Trunc),
        SimdVector4f::kSimdAssignTag
    );
}

//-------------------------------------DOT--------------------------------------

template<>
inline float dot(const SimdVector4f& a, const SimdVector4f& b)
{
    __m128 r1 = _mm_mul_ps(a.get_simd(), b.get_simd());
    __m128 r2 = _mm_hadd_ps(r1, r1);
    __m128 r3 = _mm_hadd_ps(r2, r2);

    SimdVector4f r(r3, SimdVector4f::kSimdAssignTag);
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
inline SimdVector4f log(const SimdVector4f& v)
{
     // mask for any component that are invalid (less than or equal to 0)
     __m128 invalid_mask = _mm_cmple_ps(v.get_simd(), _mm_setzero_ps());
     // setup the return value and cut off any denormalised stuff
    __m128 x = _mm_max_ps(v.get_simd(), MIN_DENORM_4f.get_simd());

     __m128i emm0 = _mm_srli_epi32(_mm_castps_si128(x), 23);

     // keep only the fractional part of the value
     x = _mm_and_ps(
         x,
         FLOAT_INVERT_EXPONENT_MASK_4f.get_simd()
     );
     x = _mm_or_ps(x, HALF_4f.get_simd());

     emm0 = _mm_sub_epi32(emm0, I_Ox7F_4f.get_simd());
     __m128 e =  _mm_cvtepi32_ps(emm0);
     e =  _mm_add_ps(e, ONE_4f.get_simd());

     __m128 mask =_mm_cmplt_ps(x, LOG_SQRTHF_4f.get_simd());
     __m128 temp = _mm_and_ps(x, mask);

     x = _mm_sub_ps(x, ONE_4f.get_simd());
     e = _mm_sub_ps(e, _mm_and_ps(ONE_4f.get_simd(), mask));
     x = _mm_add_ps(x, temp);


     __m128 z = _mm_mul_ps(x, x);

     __m128 y = LOG_P0_4f.get_simd();
     y = _mm_mul_ps(y, x);
     y = _mm_add_ps(y, LOG_P1_4f.get_simd());
     y = _mm_mul_ps(y, x);
     y = _mm_add_ps(y, LOG_P2_4f.get_simd());
     y = _mm_mul_ps(y, x);
     y = _mm_add_ps(y, LOG_P3_4f.get_simd());
     y = _mm_mul_ps(y, x);
     y = _mm_add_ps(y, LOG_P4_4f.get_simd());
     y = _mm_mul_ps(y, x);
     y = _mm_add_ps(y, LOG_P5_4f.get_simd());
     y = _mm_mul_ps(y, x);
     y = _mm_add_ps(y, LOG_P6_4f.get_simd());
     y = _mm_mul_ps(y, x);
     y = _mm_add_ps(y, LOG_P7_4f.get_simd());
     y = _mm_mul_ps(y, x);
     y = _mm_add_ps(y, LOG_P8_4f.get_simd());
     y = _mm_mul_ps(y, x);

     y = _mm_mul_ps(y, z);

     temp = _mm_mul_ps(e, LOG_Q1_4f.get_simd());
     y = _mm_add_ps(y, temp);

     temp = _mm_mul_ps(z, HALF_4f.get_simd());
     y = _mm_sub_ps(y, temp);

     temp = _mm_mul_ps(e, LOG_Q2_4f.get_simd());
     x = _mm_add_ps(x, y);
     x = _mm_add_ps(x, temp);
     x = _mm_or_ps(x, invalid_mask);

     return SimdVector4f(x, SimdVector4f::kSimdAssignTag);
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
inline SimdVector4f log2(const SimdVector4f& v)
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
inline SimdVector4f exp(const SimdVector4f& v)
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
    emm0 = _mm_add_epi32(emm0, I_Ox7F_4f.get_simd());
    emm0 = _mm_slli_epi32(emm0, 23);
    __m128 pow2n = _mm_castsi128_ps(emm0);

    return SimdVector4f(
        _mm_mul_ps(y, pow2n),
        SimdVector4f::kSimdAssignTag
    );
}

//-------------------------------------SQRT-------------------------------------

template<>
inline SimdVector4f sqrt(const SimdVector4f& v)
{
    return SimdVector4f(
        _mm_sqrt_ps(v.get_simd()),
        SimdVector4f::kSimdAssignTag
    );
}

//------------------------------------RSQRT-------------------------------------

template<>
inline SimdVector4f rsqrt(const SimdVector4f& v)
{
    return SimdVector4f(
        _mm_rsqrt_ps(v.get_simd()),
        SimdVector4f::kSimdAssignTag
    );
}

//-------------------------------------SIN--------------------------------------

// trig specific constants
namespace
{

static const SimdVector4f TRIG_DP1_4f(-0.78515625F);
static const SimdVector4f TRIG_DP2_4f(-2.4187564849853515625e-4F);
static const SimdVector4f TRIG_DP3_4f(-3.77489497744594108e-8F);
static const SimdVector4f TRIG_SIN_COF_P0_4f(-1.9515295891e-4F);
static const SimdVector4f TRIG_SIN_COF_P1_4f(8.3321608736e-3F);
static const SimdVector4f TRIG_SIN_COF_P2_4f(-1.6666654611e-1F);
static const SimdVector4f TRIG_COS_COF_P0_4f(2.443315711809948e-5F);
static const SimdVector4f TRIG_COS_COF_P1_4f(-1.388731625493765e-3F);
static const SimdVector4f TRIG_COS_COF_P2_4f(4.166664568298827e-2F);

} // namespace anonymous

template<>
inline SimdVector4f sin(const SimdVector4f& v)
{
    __m128 x = v.get_simd();
    __m128 sign_bit = x;
    // take the absolute value
    x = _mm_and_ps(v.get_simd(), FLOAT_INVERT_SIGN_MASK_4f.get_simd());
    // extract the sign bit
    sign_bit = _mm_and_ps(sign_bit, FLOAT_SIGN_MASK_4f.get_simd());

    // scale by 4/PI
    __m128 y = _mm_mul_ps(x, FOUR_OVER_PI_4f.get_simd());

    // store the integer part of y in mm0
    __m128i emm2 = _mm_cvttps_epi32(y);
    // j = (j + 1) & (~1)
    emm2 = _mm_add_epi32(emm2, I_ONE_4f.get_simd());
    emm2 = _mm_and_si128(emm2, I_INVERT_ONE_4f.get_simd());
    y = _mm_cvtepi32_ps(emm2);

    // get the swap sign flag
    __m128i emm0 = _mm_and_si128(emm2, I_FOUR_4f.get_simd());
    emm0 = _mm_slli_epi32(emm0, 29);

    // get the polynom selection mask, there is one polynom for 0 < x <= PI / 4
    // and another for PI / 4 < x <= PI / 2
    // both branches will be computed
    emm2 = _mm_and_si128(emm2, I_TWO_4f.get_simd());
    emm2 = _mm_cmpeq_epi32(emm2, _mm_setzero_si128());

    __m128 swap_sign_bit = _mm_castsi128_ps(emm0);
    __m128 poly_mask = _mm_castsi128_ps(emm2);
    sign_bit = _mm_xor_ps(sign_bit, swap_sign_bit);

    // the magic pass: "Extended precision modular arithmetic"
    // x = ((x - y * DP1) - y * DP2) - y * DP3)
    __m128 xmm1 = TRIG_DP1_4f.get_simd();
    __m128 xmm2 = TRIG_DP2_4f.get_simd();
    __m128 xmm3 = TRIG_DP3_4f.get_simd();
    xmm1 = _mm_mul_ps(y, xmm1);
    xmm2 = _mm_mul_ps(y, xmm2);
    xmm3 = _mm_mul_ps(y, xmm3);
    x = _mm_add_ps(x, xmm1);
    x = _mm_add_ps(x, xmm2);
    x = _mm_add_ps(x, xmm3);

    // evaluate the first polynom: 0 <= x <= PI / 4
    y = TRIG_COS_COF_P0_4f.get_simd();
    __m128 z = _mm_mul_ps(x, x);

    y = _mm_mul_ps(y, z);
    y = _mm_add_ps(y, TRIG_COS_COF_P1_4f.get_simd());
    y = _mm_mul_ps(y, z);
    y = _mm_add_ps(y, TRIG_COS_COF_P2_4f.get_simd());
    y = _mm_mul_ps(y, z);
    y = _mm_mul_ps(y, z);
    __m128 tmp = _mm_mul_ps(z, HALF_4f.get_simd());
    y = _mm_sub_ps(y, tmp);
    y = _mm_add_ps(y, ONE_4f.get_simd());

    // evaluate the second polynom PI / 4 <= x <= 0
    __m128 y2 = TRIG_SIN_COF_P0_4f.get_simd();
    y2 = _mm_mul_ps(y2, z);
    y2 = _mm_add_ps(y2, TRIG_SIN_COF_P1_4f.get_simd());
    y2 = _mm_mul_ps(y2, z);
    y2 = _mm_add_ps(y2, TRIG_SIN_COF_P2_4f.get_simd());
    y2 = _mm_mul_ps(y2, z);
    y2 = _mm_mul_ps(y2, x);
    y2 = _mm_add_ps(y2, x);

    // select the correct result from the two polynoms
    xmm3 = poly_mask;
    y2 = _mm_and_ps(xmm3, y2);
    y = _mm_andnot_ps(xmm3, y);
    y = _mm_add_ps(y, y2);
    // update the sign
    y = _mm_xor_ps(y, sign_bit);

    return SimdVector4f(y, SimdVector4f::kSimdAssignTag);
}

//-------------------------------------COS--------------------------------------

template<>
inline SimdVector4f cos(const SimdVector4f& v)
{
    __m128 x = v.get_simd();
    // take the absolute value
    x = _mm_and_ps(v.get_simd(), FLOAT_INVERT_SIGN_MASK_4f.get_simd());

    // scale by 4/PI
    __m128 y = _mm_mul_ps(x, FOUR_OVER_PI_4f.get_simd());

    // store the integer part of y in mm0
    __m128i emm2 = _mm_cvttps_epi32(y);
    // j = (j + 1) & (~1)
    emm2 = _mm_add_epi32(emm2, I_ONE_4f.get_simd());
    emm2 = _mm_and_si128(emm2, I_INVERT_ONE_4f.get_simd());
    y = _mm_cvtepi32_ps(emm2);

    emm2 = _mm_sub_epi32(emm2, I_TWO_4f.get_simd());

    // get the swap sign flag
    __m128i emm0 = _mm_andnot_si128(emm2, I_FOUR_4f.get_simd());
    emm0 = _mm_slli_epi32(emm0, 29);

    // get the polynom selection mask, there is one polynom for 0 < x <= PI / 4
    // and another for PI / 4 < x <= PI / 2
    // both branches will be computed
    emm2 = _mm_and_si128(emm2, I_TWO_4f.get_simd());
    emm2 = _mm_cmpeq_epi32(emm2, _mm_setzero_si128());

    __m128 sign_bit = _mm_castsi128_ps(emm0);
    __m128 poly_mask = _mm_castsi128_ps(emm2);

    // the magic pass: "Extended precision modular arithmetic"
    // x = ((x - y * DP1) - y * DP2) - y * DP3)
    __m128 xmm1 = TRIG_DP1_4f.get_simd();
    __m128 xmm2 = TRIG_DP2_4f.get_simd();
    __m128 xmm3 = TRIG_DP3_4f.get_simd();
    xmm1 = _mm_mul_ps(y, xmm1);
    xmm2 = _mm_mul_ps(y, xmm2);
    xmm3 = _mm_mul_ps(y, xmm3);
    x = _mm_add_ps(x, xmm1);
    x = _mm_add_ps(x, xmm2);
    x = _mm_add_ps(x, xmm3);

    // evaluate the first polynom: 0 <= x <= PI / 4
    y = TRIG_COS_COF_P0_4f.get_simd();
    __m128 z = _mm_mul_ps(x, x);

    y = _mm_mul_ps(y, z);
    y = _mm_add_ps(y, TRIG_COS_COF_P1_4f.get_simd());
    y = _mm_mul_ps(y, z);
    y = _mm_add_ps(y, TRIG_COS_COF_P2_4f.get_simd());
    y = _mm_mul_ps(y, z);
    y = _mm_mul_ps(y, z);
    __m128 tmp = _mm_mul_ps(z, HALF_4f.get_simd());
    y = _mm_sub_ps(y, tmp);
    y = _mm_add_ps(y, ONE_4f.get_simd());

    // evaluate the second polynom PI / 4 <= x <= 0
    __m128 y2 = TRIG_SIN_COF_P0_4f.get_simd();
    y2 = _mm_mul_ps(y2, z);
    y2 = _mm_add_ps(y2, TRIG_SIN_COF_P1_4f.get_simd());
    y2 = _mm_mul_ps(y2, z);
    y2 = _mm_add_ps(y2, TRIG_SIN_COF_P2_4f.get_simd());
    y2 = _mm_mul_ps(y2, z);
    y2 = _mm_mul_ps(y2, x);
    y2 = _mm_add_ps(y2, x);

    // select the correct result from the two polynoms
    xmm3 = poly_mask;
    y2 = _mm_and_ps(xmm3, y2);
    y = _mm_andnot_ps(xmm3, y);
    y = _mm_add_ps(y, y2);
    // update the sign
    y = _mm_xor_ps(y, sign_bit);

    return SimdVector4f(y, SimdVector4f::kSimdAssignTag);
}

//------------------------------------SINCOS------------------------------------

template<>
inline void sincos(
        const SimdVector4f& v,
        SimdVector4f& r_sin,
        SimdVector4f& r_cos)
{
    __m128 x = v.get_simd();
    __m128 sign_bit_sin = x;
    // take the absolute value
    x = _mm_and_ps(v.get_simd(), FLOAT_INVERT_SIGN_MASK_4f.get_simd());
    // extract the sign bit
    sign_bit_sin = _mm_and_ps(sign_bit_sin, FLOAT_SIGN_MASK_4f.get_simd());

    // scale by 4/PI
    __m128 y = _mm_mul_ps(x, FOUR_OVER_PI_4f.get_simd());

    // store the integer part of y in emm2
    __m128i emm2 = _mm_cvttps_epi32(y);
    // j = (j + 1) & (~1)
    emm2 = _mm_add_epi32(emm2, I_ONE_4f.get_simd());
    emm2 = _mm_and_si128(emm2, I_INVERT_ONE_4f.get_simd());
    y = _mm_cvtepi32_ps(emm2);

    __m128i emm4 = emm2;

    // get the swap sign flag for sin
    __m128i emm0 = _mm_and_si128(emm2, I_FOUR_4f.get_simd());
    emm0 = _mm_slli_epi32(emm0, 29);
    __m128 swap_sign_bit_sin = _mm_castsi128_ps(emm0);

    // get the polynom selection mask for sin
    emm2 = _mm_and_si128(emm2, I_TWO_4f.get_simd());
    emm2 = _mm_cmpeq_epi32(emm2, _mm_setzero_si128());

    __m128 poly_mask = _mm_castsi128_ps(emm2);

    // the magic pass: "Extended precision modular arithmetic"
    // x = ((x - y * DP1) - y * DP2) - y * DP3)
    __m128 xmm1 = TRIG_DP1_4f.get_simd();
    __m128 xmm2 = TRIG_DP2_4f.get_simd();
    __m128 xmm3 = TRIG_DP3_4f.get_simd();
    xmm1 = _mm_mul_ps(y, xmm1);
    xmm2 = _mm_mul_ps(y, xmm2);
    xmm3 = _mm_mul_ps(y, xmm3);
    x = _mm_add_ps(x, xmm1);
    x = _mm_add_ps(x, xmm2);
    x = _mm_add_ps(x, xmm3);

    emm4 = _mm_sub_epi32(emm4, I_TWO_4f.get_simd());
    emm4 = _mm_andnot_si128(emm4, I_FOUR_4f.get_simd());
    emm4 = _mm_slli_epi32(emm4, 29);
    __m128 sign_bit_cos = _mm_castsi128_ps(emm4);
    sign_bit_sin = _mm_xor_ps(sign_bit_sin, swap_sign_bit_sin);

    // evaluate the first polynom: 0 <= x <= PI / 4
    y = TRIG_COS_COF_P0_4f.get_simd();
    __m128 z = _mm_mul_ps(x, x);

    y = _mm_mul_ps(y, z);
    y = _mm_add_ps(y, TRIG_COS_COF_P1_4f.get_simd());
    y = _mm_mul_ps(y, z);
    y = _mm_add_ps(y, TRIG_COS_COF_P2_4f.get_simd());
    y = _mm_mul_ps(y, z);
    y = _mm_mul_ps(y, z);
    __m128 tmp = _mm_mul_ps(z, HALF_4f.get_simd());
    y = _mm_sub_ps(y, tmp);
    y = _mm_add_ps(y, ONE_4f.get_simd());

    // evaluate the second polynom PI / 4 <= x <= 0
    __m128 y2 = TRIG_SIN_COF_P0_4f.get_simd();
    y2 = _mm_mul_ps(y2, z);
    y2 = _mm_add_ps(y2, TRIG_SIN_COF_P1_4f.get_simd());
    y2 = _mm_mul_ps(y2, z);
    y2 = _mm_add_ps(y2, TRIG_SIN_COF_P2_4f.get_simd());
    y2 = _mm_mul_ps(y2, z);
    y2 = _mm_mul_ps(y2, x);
    y2 = _mm_add_ps(y2, x);

    // select the correct result from the two polynoms
    xmm3 = poly_mask;
    __m128 ysin2 = _mm_and_ps(xmm3, y2);
    __m128 ysin1 = _mm_andnot_ps(xmm3, y);
    y2 = _mm_sub_ps(y2, ysin2);
    y = _mm_sub_ps(y, ysin1);

    xmm1 = _mm_add_ps(ysin1, ysin2);
    xmm2 = _mm_add_ps(y, y2);

    // update the sign and return
    r_sin.get_simd() = _mm_xor_ps(xmm1, sign_bit_sin);
    r_cos.get_simd() = _mm_xor_ps(xmm2, sign_bit_cos);
}

} // namespace gm
} // namespace arc

#endif
