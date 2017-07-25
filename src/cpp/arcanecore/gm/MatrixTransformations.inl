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
        const Vector<T_scalar, 2, T_other_use_simd>& t,
        Matrix<T_scalar, T_cols, T_rows, T_use_simd>& identity)
{
    static_assert(
        false,
        "translate not yet implemented for the given matrix dimensions"
    );
}

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
        const Vector<T_scalar, 2, T_other_use_simd>& t)
{
    // hand of to implementation function
    Matrix<T_scalar, T_cols, T_rows, T_use_simd> identity(1);
    translate_(t, identity);
    return identity;
}

} // namespace gm
} // namespace arc

#endif
