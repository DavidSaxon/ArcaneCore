/*!
 * \file
 * \author David Saxon
 * \brief Template specialistations for SIMD 3D float vector math.
 */
#ifndef ARCANECORE_GM_VECTORMATHSIMD3F_INL_
#define ARCANECORE_GM_VECTORMATHSIMD3F_INL_

#include <arcanecore/base/simd/Include.hpp>

namespace arc
{
namespace gm
{

// template<
//     std::size_t T_x_component,
//     std::size_t T_y_component,
//     std::size_t T_z_component,
//     bool T_use_simd,
//     bool T_other_simd
// >
// inline SimdVector3f swizzle3(const Vector<float, 2, true>& v)
// {
//     static_assert(
//         T_x_component < 2,
//         "Template x component index out of the given vector's bounds"
//     );
//     static_assert(
//         T_y_component < 2,
//         "Template y component index out of the given vector's bounds"
//     );
//     static_assert(
//         T_z_component < 2,
//         "Template z component index out of the given vector's bounds"
//     );

//     // TODO: REMOVE ME
//     std::cout << "USING SIMD SWIZZLE3" << std::endl;

//     return SimdVector3f(
//         v[T_x_component],
//         v[T_y_component],
//         v[T_z_component]
//     );
// }

// template<
//     std::size_t T_x_component,
//     std::size_t T_y_component,
//     std::size_t T_z_component
// >
// inline SimdVector3f swizzle3(const Vector<float, 4, true>& v)
// {
//     static_assert(
//         T_x_component < 4,
//         "Template x component index out of the given vector's bounds"
//     );
//     static_assert(
//         T_y_component < 4,
//         "Template y component index out of the given vector's bounds"
//     );
//     static_assert(
//         T_z_component < 4,
//         "Template z component index out of the given vector's bounds"
//     );

//     // TODO: REMOVE ME
//     std::cout << "USING SIMD SWIZZLE3" << std::endl;

//     return SimdVector3f(
//         v[T_x_component],
//         v[T_y_component],
//         v[T_z_component]
//     );
// }

} // namespace gm
} // namespace arc

#endif
