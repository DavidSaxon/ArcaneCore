/*!
 * \file
 * \author David Saxon
 * \brief Math operations for matrices.
 */
#ifndef ARCANECORE_GM_MATRIXMATH_HPP_
#define ARCANECORE_GM_MATRIXMATH_HPP_

#include "arcanecore/gm/Matrix.hpp"


namespace arc
{
namespace gm
{

/*!
 * \brief Matrix by scalar component assignment multiplication operator.
 *
 *  Multiplies the components of the matrix by the scalar.
 */
template<
    typename T_scalar,
    std::size_t T_cols,
    std::size_t T_rows,
    bool T_use_simd
>
Matrix<T_scalar, T_rows, T_cols, T_use_simd>& operator*=(
        Matrix<T_scalar, T_rows, T_cols, T_use_simd>& m,
        T_scalar v)
{
    for(std::size_t i = 0; i < T_cols; ++i)
    {
        m[i] *= v;
    }
    return m;
}

/*!
 * \brief Matrix by scalar multiplication operator.
 *
 * Multiplies the components of the matrix by the scalar and returns the result
 * as a new matrix.
 */
template<
    typename T_scalar,
    std::size_t T_cols,
    std::size_t T_rows,
    bool T_use_simd
>
Matrix<T_scalar, T_rows, T_cols, T_use_simd> operator*(
        const Matrix<T_scalar, T_rows, T_cols, T_use_simd>& m,
        T_scalar v)
{
    Matrix<T_scalar, T_cols, T_rows, T_use_simd> r(m);
    return r *= v;
}

/*!
 * \brief Vector by matrix multiplication operator.
 *
 * Multiplies the vector by the matrix and returns the result as a new vector.
 */
template<
    typename T_scalar,
    std::size_t T_cols,
    std::size_t T_rows,
    bool T_use_simd_1,
    bool T_use_simd_2
>
Vector<T_scalar, T_cols, T_use_simd_1> operator*(
        const Vector<T_scalar, T_cols, T_use_simd_1>& v,
        const Matrix<T_scalar, T_rows, T_cols, T_use_simd_2>& m)
{
    Vector<T_scalar, T_cols, T_use_simd_1> result;
    for(std::size_t i = 0; i < T_cols; ++i)
    {
        result += m[i] * v[i];
    }
    return result;
}

/*!
 * \brief Vector by Matrix component assignment multiplication operator.
 *
 *  Multiplies the vector by the matrix.
 */
template<
    typename T_scalar,
    std::size_t T_cols,
    std::size_t T_rows,
    bool T_use_simd_1,
    bool T_use_simd_2
>
Vector<T_scalar, T_cols, T_use_simd_1>& operator*=(
        Vector<T_scalar, T_cols, T_use_simd_1>& v,
        const Matrix<T_scalar, T_rows, T_cols, T_use_simd_2>& m)
{
    v = v * m;
}



} // namespace gm
} // namespace arc

#endif
