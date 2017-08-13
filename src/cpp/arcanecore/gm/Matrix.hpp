/*!
 * \file
 * \author David Saxon
 */
#ifndef ARCANECORE_GM_MATRIX_HPP_
#define ARCANECORE_GM_MATRIX_HPP_

#include <algorithm>

#include <arcanecore/base/Types.hpp>
#include <arcanecore/base/math/MathConstants.hpp>
#include <arcanecore/base/memory/Alignment.hpp>
#include <arcanecore/base/str/UTF8String.hpp>

#include "arcanecore/gm/QuaternionMath.hpp"
#include "arcanecore/gm/Vector.hpp"


namespace arc
{
namespace gm
{

/*!
 * \brief A generic linear algebra matrix object with simd support.
 *
 * Arcanecore Matrix types consist of vectors in column major order. All the
 * data components of matrices are guaranteed to contiguous in memory.
 *
 * \tparam T_scalar The scalar type of this matrix (e.g. float).
 * \tparam T_cols The number of columns in the matrix, this should be greater
 *                than 0.
 * \tparam T_rows The number of rows in the matrix, this should be greater than
 *                0.
 * \tparam T_use_simd Whether this matrix should be formatted in memory for simd
 *                    use.
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
    //                                 ENUMERATOR
    //--------------------------------------------------------------------------

    /*!
     * \brief The possible orders in which 3-dimensional rotation components can
     *        be applied to matrices.
     */
    enum RotationOrder
    {
        kOrderXYZ,
        kOrderXZY,
        kOrderYXZ,
        kOrderYZX,
        kOrderZXY,
        kOrderZYX
    };

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
     * \brief Creates a new matrix using a copy of the 2 given vectors as the
     *        the first 2 columns of the matrix.
     *
     * \note The matrix type must have 2 or more columns.
     */
    Matrix(const VectorType& v1, const VectorType& v2)
    {
        static_assert(
            T_cols >= 2,
            "Constructor only valid for matrices with a dimensionality of 2 or "
            "more columns"
        );

        m_storage[0] = v1;
        m_storage[1] = v2;
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
    //                          PUBLIC STATIC FUNCTIONS
    //--------------------------------------------------------------------------

    /*!
     * \brief Returns a matrix that represents a translation by the given
     *        vector.
     */
    template<std::size_t T_trans_dimensions, bool T_other_use_simd>
    static Matrix<T_scalar, T_cols, T_rows, T_use_simd> translate(
            const Vector<T_scalar, T_trans_dimensions, T_other_use_simd>& t);

    /*!
     * \brief Returns a matrix that represents a 2D rotation by the given angle.
     */
    static Matrix<T_scalar, T_cols, T_rows, T_use_simd> rotate_2d(
            T_scalar angle);

    /*!
     * \brief Returns a matrix that represents a rotation by the given 3
     *        dimensional Euler angle.
     *
     * \param order The order in which the Euler angles will be applied to the
     *              matrix.
     */
    template<bool T_other_use_simd>
    static Matrix<T_scalar, T_cols, T_rows, T_use_simd> euler_rotate(
            const Vector<T_scalar, 3, T_other_use_simd>& euler,
            RotationOrder order = kOrderZYX)
    {
        // TODO: this can probably be optimised in a single matrix build

        static_assert(
            T_cols >= 3,
            "Euler rotate is only valid for matrices with 3 or more columns"
        );
        static_assert(
            T_rows >= 3,
            "Euler rotate is only valid for matrices with 3 or more rows"
        );

        // build rotation matrices
        Matrix<T_scalar, T_cols, T_rows, T_use_simd> x(1);
        x[1][1] =  std::cos(euler[0]);
        x[1][2] =  std::sin(euler[0]);
        x[2][1] = -std::sin(euler[0]);
        x[2][2] =  std::cos(euler[0]);

        Matrix<T_scalar, T_cols, T_rows, T_use_simd> y(1);
        y[0][0] =  std::cos(euler[1]);
        y[0][2] = -std::sin(euler[1]);
        y[2][0] =  std::sin(euler[1]);
        y[2][2] =  std::cos(euler[1]);

        Matrix<T_scalar, T_cols, T_rows, T_use_simd> z(1);
        z[0][0] =  std::cos(euler[2]);
        z[0][1] =  std::sin(euler[2]);
        z[1][0] = -std::sin(euler[2]);
        z[1][1] =  std::cos(euler[2]);

        // multiply based on the rotation order
        Matrix<T_scalar, T_cols, T_rows, T_use_simd> identity(1);
        // TODO: is this round the right way? check with work code
        switch(order)
        {
            case kOrderXYZ:
            {
                x *= y;
                x *= z;
                return x;
            }
            case kOrderXZY:
            {
                x *= z;
                x *= y;
                return x;
            }
            case kOrderYXZ:
            {
                y *= x;
                y *= z;
                return y;
            }
            case kOrderYZX:
            {
                y *= z;
                y *= x;
                return y;
            }
            case kOrderZXY:
            {
                z *= x;
                z *= y;
                return z;
            }
            default:
            {
                z *= y;
                z *= x;
                return z;
            }
        }
    }

    /*!
     * \brief Returns a matrix that represents a rotation by the given angle
     *        rotated around the given 3 dimensional axis values.
     *
     * \param angle The angle (in radians) to rotate by.
     * \param axis The axis quantities to rotate by (where 1.0 means rotate
     *             around the angle by the full angle, and 0.0 means no
     *             rotation around the respective axis),
     * \param order The order in which the axis rotations will be applied to the
     *              matrix.
     */
    template<bool T_other_use_simd>
    static Matrix<T_scalar, T_cols, T_rows, T_use_simd> axis_rotate(
            T_scalar angle,
            const Vector<T_scalar, 3, T_other_use_simd>& axis,
            RotationOrder order = kOrderZYX)
    {
        // TODO: this can probably be optimised in a single matrix build

        static_assert(
            T_cols >= 3,
            "Axis rotate is only valid for matrices with 3 or more columns"
        );
        static_assert(
            T_rows >= 3,
            "Axis rotate is only valid for matrices with 3 or more rows"
        );

        // build rotation matrices
        Matrix<T_scalar, T_cols, T_rows, T_use_simd> x(1);
        // TODO: change epsilon to float epsilon
        if(axis[0] >= std::numeric_limits<float>::epsilon())
        {
            x[1][1] =  std::cos(angle * axis[0]);
            x[1][2] =  std::sin(angle * axis[0]);
            x[2][1] = -std::sin(angle * axis[0]);
            x[2][2] =  std::cos(angle * axis[0]);
        }

        Matrix<T_scalar, T_cols, T_rows, T_use_simd> y(1);
        if(axis[1] >= std::numeric_limits<float>::epsilon())
        {
            y[0][0] =  std::cos(axis[1]);
            y[0][2] = -std::sin(axis[1]);
            y[2][0] =  std::sin(axis[1]);
            y[2][2] =  std::cos(axis[1]);
        }

        Matrix<T_scalar, T_cols, T_rows, T_use_simd> z(1);
        if(axis[2] >= std::numeric_limits<float>::epsilon())
        {
            z[0][0] =  std::cos(axis[2]);
            z[0][1] =  std::sin(axis[2]);
            z[1][0] = -std::sin(axis[2]);
            z[1][1] =  std::cos(axis[2]);
        }

        // multiply based on the rotation order
        Matrix<T_scalar, T_cols, T_rows, T_use_simd> identity(1);
        // TODO: is this round the right way? check with work code
        switch(order)
        {
            case kOrderXYZ:
            {
                x *= y;
                x *= z;
                return x;
            }
            case kOrderXZY:
            {
                x *= z;
                x *= y;
                return x;
            }
            case kOrderYXZ:
            {
                y *= x;
                y *= z;
                return y;
            }
            case kOrderYZX:
            {
                y *= z;
                y *= x;
                return y;
            }
            case kOrderZXY:
            {
                z *= x;
                z *= y;
                return z;
            }
            default:
            {
                z *= y;
                z *= x;
                return z;
            }
        }
    }

    /*!
     * \brief Returns a matrix that represents the rotation defined by the given
     *        quaternion.
     */
    template<bool T_other_use_simd>
    static Matrix<T_scalar, T_cols, T_rows, T_use_simd> quaternion_rotate(
            const Quaternion<T_scalar, T_other_use_simd>& q,
            RotationOrder order = kOrderZYX)
    {
        // TODO: this can probably be optimised in a single matrix build

        // get the axis angle rotation
        T_scalar angle = static_cast<T_scalar>(0);
        Vector<T_scalar, 3> axis;
        to_axis_angle(q, angle, axis);
        return axis_rotate(angle, axis, order);
    }

    /*!
     * \brief Returns a matrix that represents a scaling by the given vector.
     */
    template<std::size_t T_scale_dimensions, bool T_other_use_simd>
    static Matrix<T_scalar, T_cols, T_rows, T_use_simd> scale(
            const Vector<T_scalar, T_scale_dimensions, T_other_use_simd>& s);

    // TODO: maybe should just remove this function
    // TODO: consolidate left/right handed co-ordinate system
    /*!
     * \brief Returns a matrix that represents a perspective projection based on
     *        the given frustum parameters.
     */
    static Matrix<T_scalar, T_cols, T_rows, T_use_simd> perspective(
            T_scalar left,
            T_scalar right,
            T_scalar top,
            T_scalar bottom,
            T_scalar near_clip,
            T_scalar far_clip)
    {
        static_assert(
            T_cols == 4 && T_rows == 4,
            "Perspective is only valid for 4x4 matrices"
        );

        T_scalar width = right - left;
        T_scalar height = top - bottom;
        T_scalar distance = near_clip - far_clip;
        T_scalar near2 = near_clip * static_cast<T_scalar>(2);

        return Matrix<T_scalar, T_cols, T_rows, T_use_simd>(
            Vector<T_scalar, 4, T_use_simd>(
                near2 / width,
                static_cast<T_scalar>(0),
                static_cast<T_scalar>(0),
                static_cast<T_scalar>(0)
            ),
            Vector<T_scalar, 4, T_use_simd>(
                static_cast<T_scalar>(0),
                near2 / height,
                static_cast<T_scalar>(0),
                static_cast<T_scalar>(0)
            ),
            Vector<T_scalar, 4, T_use_simd>(
                (right + left) / width,
                (top + bottom) / height,
                near_clip / distance,
                static_cast<T_scalar>(-1)
            ),
            Vector<T_scalar, 4, T_use_simd>(
                static_cast<T_scalar>(0),
                static_cast<T_scalar>(0),
                (near_clip * far_clip) / distance,
                static_cast<T_scalar>(0)
            )
        );
    }

    // TODO: consolidate left/right handed co-ordinate system
    /*!
     * \brief Returns a matrix that represents a perspective projection based on
     *        the given parameters.
     *
     * \param fov The horizontal field of view the camera.
     * \param aspect_ratio The aspect ration of the camera.
     * \param near_clip The distance of the near clipping plane from the camera.
     * \param far_clip The distance of the far clipping plane from the camera.
     */
    static Matrix<T_scalar, T_cols, T_rows, T_use_simd> perspective(
            T_scalar fov,
            T_scalar aspect_ratio,
            T_scalar near_clip,
            T_scalar far_clip)
    {
        static_assert(
            T_cols == 4 && T_rows == 4,
            "Perspective is only valid for 4x4 matrices"
        );

        T_scalar right = near_clip * std::tan(fov / static_cast<T_scalar>(2));
        T_scalar recip = static_cast<T_scalar>(1) / (near_clip - far_clip);

        return Matrix<T_scalar, T_cols, T_rows, T_use_simd>(
            Vector<T_scalar, 4, T_use_simd>(
                near_clip * (static_cast<T_scalar>(1) / right),
                static_cast<T_scalar>(0),
                static_cast<T_scalar>(0),
                static_cast<T_scalar>(0)
            ),
            Vector<T_scalar, 4, T_use_simd>(
                static_cast<T_scalar>(0),
                near_clip * (static_cast<T_scalar>(1) / (aspect_ratio / right)),
                static_cast<T_scalar>(0),
                static_cast<T_scalar>(0)
            ),
            Vector<T_scalar, 4, T_use_simd>(
                static_cast<T_scalar>(0),
                static_cast<T_scalar>(0),
                (far_clip + near_clip) * recip,
                static_cast<T_scalar>(-1)
            ),
            Vector<T_scalar, 4, T_use_simd>(
                static_cast<T_scalar>(0),
                static_cast<T_scalar>(0),
                static_cast<T_scalar>(2) * far_clip * near_clip * recip,
                static_cast<T_scalar>(0)
            )
        );
    }

    /*!
     * \brief Returns a matrix that represents a orthographic projection based
     *        on the given frustum parameters.
     */
    static Matrix<T_scalar, T_cols, T_rows, T_use_simd> orthographic(
            T_scalar left,
            T_scalar right,
            T_scalar top,
            T_scalar bottom,
            T_scalar near_clip,
            T_scalar far_clip)
    {
        static_assert(
            T_cols == 4 && T_rows == 4,
            "Orthographic is only valid for 4x4 matrices"
        );

        T_scalar width = right - left;
        T_scalar height = top - bottom;
        T_scalar distance = far_clip - near_clip;

        return Matrix<T_scalar, T_cols, T_rows, T_use_simd>(
            Vector<T_scalar, 4, T_use_simd>(
                static_cast<T_scalar>(2) / width,
                static_cast<T_scalar>(0),
                static_cast<T_scalar>(0),
                static_cast<T_scalar>(0)
            ),
            Vector<T_scalar, 4, T_use_simd>(
                static_cast<T_scalar>(0),
                static_cast<T_scalar>(2) / height,
                static_cast<T_scalar>(0),
                static_cast<T_scalar>(0)
            ),
            Vector<T_scalar, 4, T_use_simd>(
                static_cast<T_scalar>(0),
                static_cast<T_scalar>(0),
                static_cast<T_scalar>(-2) / distance,
                static_cast<T_scalar>(0)
            ),
            Vector<T_scalar, 4, T_use_simd>(
                (-(right + left)) / width,
                (-(top + bottom)) / height,
                (-(far_clip + near_clip)) / distance,
                static_cast<T_scalar>(1)
            )
        );
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
     * \brief Scalar addition operator.
     *
     * Adds the scalar to each component of this matrix and returns the result
     * as a new matrix.
     */
     Matrix<T_scalar, T_cols, T_rows, T_use_simd> operator+(T_scalar v)
    {
        Matrix<T_scalar, T_cols, T_rows, T_use_simd> r(*this);
        return r += v;
    }

    /*!
     * \brief Scalar compound assignment addition operator.
     *
     * Adds the scalar to each component of this matrix.
     */
    Matrix<T_scalar, T_cols, T_rows, T_use_simd>& operator+=(T_scalar v)
    {
        for(std::size_t i = 0; i < T_cols; ++i)
        {
            (*this)[i] += v;
        }
        return *this;
    }

    /*!
     * \brief Vector addition operator.
     *
     * Adds the vector to each column of this matrix and returns the result
     * as a new matrix.
     */
    template<bool T_other_use_simd>
    Matrix<T_scalar, T_cols, T_rows, T_use_simd> operator+(
        const Vector<T_scalar, T_rows, T_other_use_simd>& v)
    {
        Matrix<T_scalar, T_cols, T_rows, T_use_simd> r(*this);
        return r += v;
    }

    /*!
     * \brief Vector compound assignment addition operator.
     *
     * Adds the vector to each column of this matrix.
     */
    template<bool T_other_use_simd>
    Matrix<T_scalar, T_cols, T_rows, T_use_simd>& operator+=(
        const Vector<T_scalar, T_rows, T_other_use_simd>& v)
    {
        for(std::size_t i = 0; i < T_cols; ++i)
        {
            (*this)[i] += v;
        }
        return *this;
    }

    /*!
     * \brief Matrix addition operator.
     *
     * Adds each component of the given matrix to each component of this matrix
     * and returns the result as a new matrix.
     */
    template<bool T_other_use_simd>
    Matrix<T_scalar, T_cols, T_rows, T_use_simd> operator+(
        const Matrix<T_scalar, T_cols, T_rows, T_other_use_simd>& m)
    {
        Matrix<T_scalar, T_cols, T_rows, T_use_simd> r(*this);
        return r += m;
    }

    /*!
     * \brief Matrix compound assignment addition operator.
     *
     * Adds each component of the given matrix to each component of this matrix.
     */
    template<bool T_other_use_simd>
    Matrix<T_scalar, T_cols, T_rows, T_use_simd>& operator+=(
        const Matrix<T_scalar, T_cols, T_rows, T_other_use_simd>& m)
    {
        for(std::size_t i = 0; i < T_cols; ++i)
        {
            (*this)[i] += m[i];
        }
        return *this;
    }

    /*!
     * \brief Scalar subtraction operator.
     *
     * Subtracts the scalar from each component of this matrix and returns the
     * result as a new matrix.
     */
     Matrix<T_scalar, T_cols, T_rows, T_use_simd> operator-(T_scalar v)
    {
        Matrix<T_scalar, T_cols, T_rows, T_use_simd> r(*this);
        return r -= v;
    }

    /*!
     * \brief Scalar compound assignment subtraction operator.
     *
     * Subtracts the scalar from each component of this matrix.
     */
    Matrix<T_scalar, T_cols, T_rows, T_use_simd>& operator-=(T_scalar v)
    {
        for(std::size_t i = 0; i < T_cols; ++i)
        {
            (*this)[i] -= v;
        }
        return *this;
    }

    /*!
     * \brief Vector subtraction operator.
     *
     * Subtracts the vector from each column of this matrix and returns the
     * result as a new matrix.
     */
    template<bool T_other_use_simd>
    Matrix<T_scalar, T_cols, T_rows, T_use_simd> operator-(
        const Vector<T_scalar, T_rows, T_other_use_simd>& v)
    {
        Matrix<T_scalar, T_cols, T_rows, T_use_simd> r(*this);
        return r -= v;
    }

    /*!
     * \brief Vector compound assignment subtraction operator.
     *
     * Subtracts the vector from each column of this matrix.
     */
    template<bool T_other_use_simd>
    Matrix<T_scalar, T_cols, T_rows, T_use_simd>& operator-=(
        const Vector<T_scalar, T_rows, T_other_use_simd>& v)
    {
        for(std::size_t i = 0; i < T_cols; ++i)
        {
            (*this)[i] -= v;
        }
        return *this;
    }

    /*!
     * \brief Matrix subtraction operator.
     *
     * Subtracts each component of the given matrix from each component of this
     * matrix and returns the result as a new matrix.
     */
    template<bool T_other_use_simd>
    Matrix<T_scalar, T_cols, T_rows, T_use_simd> operator-(
        const Matrix<T_scalar, T_cols, T_rows, T_other_use_simd>& m)
    {
        Matrix<T_scalar, T_cols, T_rows, T_use_simd> r(*this);
        return r -= m;
    }

    /*!
     * \brief Matrix compound assignment subtraction operator.
     *
     * Subtracts each component of the given matrix from each component of this
     * matrix.
     */
    template<bool T_other_use_simd>
    Matrix<T_scalar, T_cols, T_rows, T_use_simd>& operator-=(
        const Matrix<T_scalar, T_cols, T_rows, T_other_use_simd>& m)
    {
        for(std::size_t i = 0; i < T_cols; ++i)
        {
            (*this)[i] -= m[i];
        }
        return *this;
    }

    /*!
     * \brief Scalar multiplication operator.
     *
     * Multiplies each component of this matrix by the given scalar and returns
     * the result as a new matrix.
     */
    Matrix<T_scalar, T_cols, T_rows, T_use_simd> operator*(T_scalar v)
    {
        Matrix<T_scalar, T_cols, T_rows, T_use_simd> r(*this);
        return r *= v;
    }

    /*!
     * \brief Scalar compound assignment multiplication operator.
     *
     * Multiplies each component of this matrix by the given scalar.
     */
    Matrix<T_scalar, T_cols, T_rows, T_use_simd>& operator*=(T_scalar v)
    {
        for(std::size_t i = 0; i < T_cols; ++i)
        {
            (*this)[i] *= v;
        }
        return *this;
    }

    /*!
     * \brief Vector multiplication operator.
     *
     * Multiplies this matrix by the given vector and returns the result as a
     * new vector.
     */
    template<bool T_other_use_simd>
    VectorType operator*(const Vector<T_scalar, T_rows, T_other_use_simd>& v)
    {
        VectorType result;
        for(std::size_t i = 0; i < T_cols; ++i)
        {
            result += (*this)[i] * VectorType(v[i]);
        }
        return result;
    }

    /*!
     * \brief Matrix multiplication operator.
     *
     * Multiplies each component of this matrix by the each component in the
     * given matrix and returns the result as a new matrix.
     */
    template<bool T_other_use_simd>
    Matrix<T_scalar, T_cols, T_rows, T_use_simd> operator*(
            const Matrix<T_scalar, T_cols, T_rows, T_other_use_simd>& m)
    {
        Matrix<T_scalar, T_cols, T_rows, T_use_simd> r(*this);
        for(std::size_t i = 0; i < T_cols; ++i)
        {
            r[i] = (*this) * m[i];
        }
        return r;
    }

    /*!
     * \brief Matrix compound assignment multiplication operator.
     *
     * Multiplies each component of this matrix by the each component in the
     * given matrix.
     */
    template<bool T_other_use_simd>
    Matrix<T_scalar, T_cols, T_rows, T_use_simd>& operator*=(
            const Matrix<T_scalar, T_cols, T_rows, T_other_use_simd>& m)
    {
        static_assert(
            T_cols == T_rows,
            "Only matrices with the number of columns equal to the number of "
            "rows may be multiplied"
        );

        *this = (*this) * m;
        return *this;
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
//                               EXTERNAL OPERATORS
//------------------------------------------------------------------------------

template<
    typename T_scalar,
    std::size_t T_cols,
    std::size_t T_rows,
    bool T_use_simd = false
>
inline arc::str::UTF8String& operator<<(
        arc::str::UTF8String& s,
        const Matrix<T_scalar, T_cols, T_rows, T_use_simd>& m)
{
    s << "[";
    for(std::size_t i = 0; i < T_cols; ++i)
    {
        s << m[i];
        if(i < (T_cols - 1))
        {
            s << ", ";
        }
    }
    s << "]";
    return s;
}

template<
    typename T_scalar,
    std::size_t T_cols,
    std::size_t T_rows,
    bool T_use_simd = false
>
inline std::ostream& operator<<(
        std::ostream& s,
        const Matrix<T_scalar, T_cols, T_rows, T_use_simd>& m)
{
    s << "[";
    for(std::size_t i = 0; i < T_cols; ++i)
    {
        s << m[i];
        if(i < (T_cols - 1))
        {
            s << ", ";
        }
    }
    s << "]";
    return s;
}

//------------------------------------------------------------------------------
//                                TYPE DEFINITIONS
//------------------------------------------------------------------------------

typedef Matrix<float, 2, 2> Matrix22f;
typedef Matrix<float, 3, 3> Matrix33f;
typedef Matrix<float, 3, 4> Matrix34f;
typedef Matrix<float, 4, 4> Matrix44f;

typedef Matrix<double, 2, 2> Matrix22d;
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

//----------------------I N L I N E -- E X T E N S I O N S----------------------
#include "arcanecore/gm/MatrixTransformations.inl"


#endif
