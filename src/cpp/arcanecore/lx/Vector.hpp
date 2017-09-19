/*!
 * \file
 * \author David Saxon
 * \brief Supplies vector types.
 */
#ifndef ARCANECORE_LX_VECTOR_HPP_
#define ARCANECORE_LX_VECTOR_HPP_

#include "arcanecore/lx/__eigen/Dense"

namespace arc
{
namespace lx
{

/*!
 * \brief A 2-dimensional floating point vector type.
 */
typedef Eigen::Matrix<float, 2, 1> Vector2f;

/*!
 * \brief A 3-dimensional floating point vector type.
 */
typedef Eigen::Matrix<float, 3, 1> Vector3f;

/*!
 * \brief A 4-dimensional floating point vector type.
 */
typedef Eigen::Matrix<float, 4, 1> Vector4f;

} // namespace lx
} // namespace arc

#endif
