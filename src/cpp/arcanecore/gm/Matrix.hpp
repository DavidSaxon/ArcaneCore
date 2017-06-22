/*!
 * \file
 * \author David Saxon
 */
#ifndef ARCANECORE_GM_MATRIX_HPP_
#define ARCANECORE_GM_MATRIX_HPP_

#include <algorithm>

#include <arcanecore/base/Types.hpp>
#include <arcanecore/base/memory/Alignment.hpp>
#include <arcanecore/base/str/UTF8String.hpp>

#include "arcanecore/gm/Vector.hpp"


namespace arc
{
namespace gm
{

/*!
 * \brief TODO: column major
 */
template<
    typename T_scalar,
    std::size_t T_cols,
    std::size_t T_rows,
    bool T_use_simd = false
>
class Matrix
    : public arc::memory::AlignedBase<Matrix<
        T_scalar,
        T_cols,
        T_rows,
        T_use_simd
      >>
{
public:

    //--------------------------------------------------------------------------
    //                              TYPE DEFINITIONS
    //--------------------------------------------------------------------------

    /*!
     * \brief the arc::gm::Vector type being used for the matrix columns.
     */
    typedef Vector<T_scalar, T_rows, T_use_simd> VectorType;

    //--------------------------------------------------------------------------
    //                                CONSTRUCTORS
    //--------------------------------------------------------------------------

    /*!
     * \brief Creates a new matrix initialised to zero.
     */
    Matrix()
    {
        // do nothing vector initialisation will default to zero
    }

    /*!
     * \brief Creates a new matrix with diagonal components set to the given
     *        value and all other components to 0.
     *
     * \note passing 1 to this constructor will create an identity matrix.
     */
    Matrix(T_scalar value)
    {
        for(std::size_t i = 0; i < T_cols; ++i)
        {
            m_storage[i][i] = value;
        }
    }

    /*!
     * \biref Creates a new matrix and copies the values from the given data
     *        array into the values of this matrix in column major order.
     */
    Matrix(const T_scalar* data)
    {
        for(std::size_t i = 0; i < T_cols; ++i)
        {
            for(std::size_t j = 0; j < T_rows; ++j)
            {
                m_storage[i][j] = data[(i * T_rows) + j];
            }
        }
    }

    /*!
     * \brief Creates a new matrix using a copy of the given vector as each
     *        column in the matrix.
     */
    Matrix(const VectorType& v)
    {
        for(std::size_t i = 0; i < T_cols; ++i)
        {
            m_storage[i] = v;
        }
    }

    /*!
     * \brief Creates a new matrix using a copy of the 3 given vectors as the
     *        the first 3 columns of the matrix.
     *
     * \note The matrix type must have 3 or more columns.
     */
    Matrix(const VectorType& v1, const VectorType& v2, const VectorType& v3)
    {
        static_assert(
            T_cols >= 3,
            "Constructor only valid for matrices with a dimensionality of 3 or "
            "more columns"
        );

        m_storage[0] = v1;
        m_storage[1] = v2;
        m_storage[2] = v3;
    }

    /*!
     * \brief Creates a new matrix using a copy of the 4 given vectors as the
     *        the first 4 columns of the matrix.
     *
     * \note The matrix type must have 4 or more columns.
     */
    Matrix(
            const VectorType& v1,
            const VectorType& v2,
            const VectorType& v3,
            const VectorType& v4)
    {
        static_assert(
            T_cols >= 4,
            "Constructor only valid for matrices with a dimensionality of 4 or "
            "more columns"
        );

        m_storage[0] = v1;
        m_storage[1] = v2;
        m_storage[2] = v3;
        m_storage[3] = v4;
    }

    /*!
     * \brief Copies the values of the given matrix of the same scalar type and
     *        dimensionality as this matrix.
     */
    template<bool T_other_use_simd>
    Matrix(const Matrix<T_scalar, T_cols, T_rows, T_other_use_simd>& m)
    {
        for(std::size_t i = 0; i < T_cols; ++i)
        {
            m_storage[i] = m[i];
        }
    }

    /*!
     * \brief Copies the values of the given matrix of the same scalar type as
     *        this matrix.
     *
     * If the other matrix has less columns/rows than this matrix the extra
     * columns/rows will be initialised to zero. Likewise if the other matrix
     * has more columns/rows extra values will be truncated.
     */
    template<
        std::size_t T_other_cols,
        std::size_t T_other_rows,
        bool T_other_use_simd
    >
    Matrix(
            const Matrix<
                T_scalar,
                T_other_cols,
                T_other_rows,
                T_other_use_simd
            >& m)
    {
        // vector constructors will do the rest
        for(std::size_t i = 0; i < std::min(T_cols, T_other_cols); ++i)
        {
            m_storage[i] = m[i];
        }
    }

    //--------------------------------------------------------------------------
    //                                 OPERATORS
    //--------------------------------------------------------------------------

    /*!
     * \brief Assigns the given value to the diagonal components of the matrix
     *        and sets all other values to 0.
     */
    Matrix<T_scalar, T_cols, T_rows, T_use_simd>& operator=(T_scalar value)
    {
        for(std::size_t i = 0; i < T_cols; ++i)
        {
            for(std::size_t j = 0; j < T_rows; ++j)
            {
                if(i == j)
                {
                    m_storage[i][j] = value;
                    continue;
                }
                m_storage[i][j] = 0.0F;
            }
        }

        return *this;
    }

    /*!
     * \brief Assigns each column of this matrix to be a copy of the given
     *        vector.
     */
    Matrix<T_scalar, T_cols, T_rows, T_use_simd>& operator=(const VectorType& v)
    {
        for(std::size_t i = 0; i < T_cols; ++i)
        {
            m_storage[i] = v;
        }

        return *this;
    }

    /*!
     * \brief Assigns the values of the given matrix of the same scalar type and
     *        dimensionality as this matrix.
     */
    template<bool T_other_use_simd>
    Matrix<T_scalar, T_cols, T_rows, T_use_simd>& operator=(
            const Matrix<T_scalar, T_cols, T_rows, T_other_use_simd>& m)
    {
        for(std::size_t i = 0; i < T_cols; ++i)
        {
            m_storage[i] = m[i];
        }

        return *this;
    }

    /*!
     * \brief Assigns the values of the given matrix of the same scalar type as
     *        this matrix.
     *
     * If the other matrix has less columns/rows than this matrix the extra
     * columns/rows will be set to zero. Likewise if the other matrix has more
     * columns/rows extra values will be truncated.
     */
    template<
        std::size_t T_other_cols,
        std::size_t T_other_rows,
        bool T_other_use_simd
    >
    Matrix<T_scalar, T_cols, T_rows, T_use_simd>& operator=(
            const Matrix<
                T_scalar,
                T_other_cols,
                T_other_rows,
                T_other_use_simd
            >& m)
    {
        // vector constructors will do the rest
        for(std::size_t i = 0; i < T_cols; ++i)
        {
            if(i < T_other_cols)
            {
                m_storage[i] = m[i];
            }
            else
            {
                m_storage[i] = VectorType();
            }
        }

        return *this;
    }

    /*!
     * \brief Compares whether the given matrices are considered equal.
     *
     * \note If the dimensionality of the rows or columns are not the same the
     *       matrices will never be considered equal. However whether the matrix
     *       is formatted in for simd will not affect this equality check.
     *
     * \warning This performs a standard equality check of the individual
     *          components of the matrices, so beware of comparing floating
     *          point matrix types.
     */
    template<
        std::size_t T_other_cols,
        std::size_t T_other_rows,
        bool T_other_use_simd
    >
    bool operator==(
            const Matrix<
                T_scalar,
                T_other_cols,
                T_other_rows,
                T_other_use_simd
            >& m)
    {
        for(std::size_t i = 0; i < T_cols; ++i)
        {
            if(m_storage[i] != m[i])
            {
                return false;
            }
        }
        return true;
    }

    /*!
     * \brief Compares whether the given matrices are considered not equal.
     *
     * \note If the dimensionality of the rows or columns are not the same the
     *       matrices will never be considered equal. However whether the matrix
     *       is formatted in for simd will not affect this equality check.
     *
     * \warning This performs a standard equality check of the individual
     *          components of the matrices, so beware of comparing floating
     *          point matrix types.
     */
    template<
        std::size_t T_other_cols,
        std::size_t T_other_rows,
        bool T_other_use_simd
    >
    bool operator!=(
            const Matrix<
                T_scalar,
                T_other_cols,
                T_other_rows,
                T_other_use_simd
            >& m)
    {
        return !((*this) == m);
    }

    /*!
     * \brief Returns the vector for the column at the given index.
     *
     * \note This does not check whether the index is within range of the
     *       matrix's columns.
     */
    VectorType& operator[](std::size_t index)
    {
        return m_storage[index];
    }

    /*!
     * \brief Returns the const vector for the column at the given index.
     *
     * \note This does not check whether the index is within range of the
     *       matrix's columns.
     */
    const VectorType& operator[](std::size_t index) const
    {
        return m_storage[index];
    }

    /*!
     * \brief Negation operator.
     *
     * Returns a copy of this vector with each of its components negated.
     */
    Matrix<T_scalar, T_cols, T_rows, T_use_simd> operator-() const
    {
        Matrix<T_scalar, T_cols, T_rows, T_use_simd> r;
        for(std::size_t i = 0; i < T_cols; ++i)
        {
            r[i] = -m_storage[i];
        }
        return r;
    }

private:

    //--------------------------------------------------------------------------
    //                             PRIVATE ATTRIBUTES
    //--------------------------------------------------------------------------

    /*!
     * \brief The storage of this matrix.
     */
    VectorType m_storage[T_cols];

};

//------------------------------------------------------------------------------
//                                TYPE DEFINITIONS
//------------------------------------------------------------------------------

typedef Matrix<float, 3, 3> Matrix33f;
typedef Matrix<float, 3, 4> Matrix34f;
typedef Matrix<float, 4, 4> Matrix44f;

typedef Matrix<double, 3, 3> Matrix33d;
typedef Matrix<double, 3, 4> Matrix34d;
typedef Matrix<double, 4, 4> Matrix44d;

// define the Simd types whether or not it's enabled, since we want to be able
// turn it off and on easily without having to update the matrix types
// everywhere in the code.
#undef ARC_GM_USE_SIMD
#ifndef ARC_GM_DISABLE_SSE
    #define ARC_GM_USE_SIMD true
#else
    #define ARC_GM_USE_SIMD false
#endif

typedef Matrix<float, 3, 3, ARC_GM_USE_SIMD> SimdMatrix33f;
typedef Matrix<float, 3, 4, ARC_GM_USE_SIMD> SimdMatrix34f;
typedef Matrix<float, 4, 4, ARC_GM_USE_SIMD> SimdMatrix44f;

} // namespace gm
} // namespace arc


#endif
