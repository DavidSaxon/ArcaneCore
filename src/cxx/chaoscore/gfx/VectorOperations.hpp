/*!
 * \file
 * \brief Operations relating to vectors.
 * \author David Saxon
 */
#ifndef CHAOSCORE_GFX_VECTOROPERATIONS_HPP_
#define CHAOSCORE_GFX_VECTOROPERATIONS_HPP_

#include "chaoscore/gfx/Vector2.hpp"
#include "chaoscore/gfx/Vector3.hpp"
#include "chaoscore/gfx/Vector4.hpp"

namespace chaos
{
namespace gfx
{

/*!
 * \brief Calculates the magnitude of the given Vector2.
 */
float magnitude( const Vector2& v );

/*!
 * \brief Calculates the magnitude of the given Vector3.
 */
float magnitude( const Vector3& v );

/*!
 * \brief Calculates the magnitude of the given Vector4.
 */
float magnitude( const Vector4& v );

} // namespace gfx
} // namespace chaos

#endif
