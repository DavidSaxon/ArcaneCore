/*!
 * \file
 * \author David Saxon
 * \brief This file should be included to include relevant SMID headers
 *        dependent on which instruction set is enabled.
 */
#ifndef ARCANECORE_BASE_SIMD_INCLUDE_HPP_
#define ARCANECORE_BASE_SIMD_INCLUDE_HPP_

#if defined(__SSE__)
    #include <xmmintrin.h>
#elif defined(__SSE2__)
    #include <emmintrin.h>
    #include <xmmintrin.h>
#elif defined(__SSE3__)
    #include <pmmintrin.h>
    #include <xmmintrin.h>
#elif defined(__SSE4_1__)
    #include <smmintrin.h>
    #include <xmmintrin.h>
#elif defined(__SSE4_2__ )
    #include <nmmintrin.h>
    #include <xmmintrin.h>
#elif defined(__AVX__)
    #include <immintrin.h>
    #include <xmmintrin.h>
#elif defined(__AVX2__)
    #include <emmintrin.h>
    #include <xmmintrin.h>
#else
    #error No SMID instruction set found
#endif

#endif
