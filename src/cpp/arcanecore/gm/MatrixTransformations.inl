/*!
 * \file
 * \author David Saxon
 * \brief Template specialistations for Matrix transformations.
 */
#ifndef ARCANECORE_GM_MATRIXTRANSFORMATIONS_INL_
#define ARCANECORE_GM_MATRIXTRANSFORMATIONS_INL_


namespace arc
{
namespace gm
{

//------------------------------------------------------------------------------
//                                   TRANSLATE
//------------------------------------------------------------------------------

//--------------------T E M P L A T E    D E F I N I T I O N--------------------

template<
    typename T_scalar,
    std::size_t T_cols,
    std::size_t T_rows,
    bool T_use_simd,
    bool T_other_use_simd
>
inline void translate_(
        const Vector<T_scalar, T_rows - 1, T_other_use_simd>& t,
        Matrix<T_scalar, T_cols, T_rows, T_use_simd>& identity);

//---------------T E M P L A T E    S P E C I A L I S A T I O N S---------------

template<
    typename T_scalar,
    bool T_use_simd,
    bool T_other_use_simd
>
inline void translate_(
        const Vector<T_scalar, 2, T_other_use_simd>& t,
        Matrix<T_scalar, 3, 3, T_use_simd>& identity)
{
    identity[2][0] = t[0];
    identity[2][1] = t[1];
}

template<
    typename T_scalar,
    bool T_use_simd,
    bool T_other_use_simd
>
inline void translate_(
        const Vector<T_scalar, 3, T_other_use_simd>& t,
        Matrix<T_scalar, 3, 4, T_use_simd>& identity)
{
    identity[0][3] = t[0];
    identity[1][3] = t[1];
    identity[2][3] = t[2];
}

template<
    typename T_scalar,
    bool T_use_simd,
    bool T_other_use_simd
>
inline void translate_(
        const Vector<T_scalar, 3, T_other_use_simd>& t,
        Matrix<T_scalar, 4, 4, T_use_simd>& identity)
{
    identity[3][0] = t[0];
    identity[3][1] = t[1];
    identity[3][2] = t[2];
}

//-------------------------C L A S S    F U N C T I O N-------------------------

template<
    typename T_scalar,
    std::size_t T_cols,
    std::size_t T_rows,
    bool T_use_simd
>
template<bool T_other_use_simd>
inline Matrix<T_scalar, T_cols, T_rows, T_use_simd>
    Matrix<T_scalar, T_cols, T_rows, T_use_simd>::translate(
        const Vector<T_scalar, T_rows - 1, T_other_use_simd>& t)
{
    // hand of to implementation function
    Matrix<T_scalar, T_cols, T_rows, T_use_simd> identity(1);
    translate_(t, identity);
    return identity;
}

//------------------------------------------------------------------------------
//                                   ROTATE 2D
//------------------------------------------------------------------------------

//--------------------T E M P L A T E    D E F I N I T I O N--------------------

template<
    typename T_scalar,
    std::size_t T_cols,
    std::size_t T_rows,
    bool T_use_simd
>
inline void rotate_2d_(
        T_scalar angle,
        Matrix<T_scalar, T_cols, T_rows, T_use_simd>& zero);

//---------------T E M P L A T E    S P E C I A L I S A T I O N S---------------

template<
    typename T_scalar,
    bool T_use_simd
>
inline void rotate_2d_(T_scalar angle, Matrix<T_scalar, 2, 2, T_use_simd>& zero)
{
    zero[0][0] =  std::cos(angle);
    zero[0][1] =  std::sin(angle);
    zero[1][0] = -std::sin(angle);
    zero[1][1] =  std::cos(angle);
}

//-------------------------C L A S S    F U N C T I O N-------------------------

template<
    typename T_scalar,
    std::size_t T_cols,
    std::size_t T_rows,
    bool T_use_simd
>
inline Matrix<T_scalar, T_cols, T_rows, T_use_simd>
    Matrix<T_scalar, T_cols, T_rows, T_use_simd>::rotate_2d(T_scalar angle)
{
    // hand of to implementation function
    Matrix<T_scalar, T_cols, T_rows, T_use_simd> zero;
    rotate_2d_(angle, zero);
    return zero;
}

//------------------------------------------------------------------------------
//                                  EULER ROTATE
//------------------------------------------------------------------------------

//--------------------T E M P L A T E    D E F I N I T I O N--------------------

// template<
//     typename T_scalar,
//     std::size_t T_cols,
//     std::size_t T_rows,
//     bool T_use_simd,
//     bool T_other_use_simd
// >
// inline void euler_rotate_(
//         const Vector<T_scalar, 3, T_other_use_simd>& euler,
//         RotationOrder order,
//         Matrix<T_scalar, T_cols, T_rows, T_use_simd>& identity);

//---------------T E M P L A T E    S P E C I A L I S A T I O N S---------------

// template<
//     typename T_scalar,
//     bool T_use_simd,
//     bool T_other_use_simd
// >
// inline void euler_rotate_(
//         const Vector<T_scalar, 3, T_other_use_simd>& euler,
//         RotationOrder order,
//         Matrix<T_scalar, 3, 3, T_use_simd>& identity)
// {


// }

// TODO: 3x4

// TODO: 4x4

//-------------------------C L A S S    F U N C T I O N-------------------------

// template<
//     typename T_scalar,
//     std::size_t T_cols,
//     std::size_t T_rows,
//     bool T_use_simd
// >
// template<bool T_other_use_simd>
// inline Matrix<T_scalar, T_cols, T_rows, T_use_simd> euler_rotate(
//         const Vector<T_scalar, 3, T_other_use_simd>& euler,
//         RotationOrder order)
// {
//     // hand of to implementation function
//     Matrix<T_scalar, T_cols, T_rows, T_use_simd> identity(1);
//     euler_rotate_(euler, identity);
//     return identity;
// }

} // namespace gm
} // namespace arc

#endif
