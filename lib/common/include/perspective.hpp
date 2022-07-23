#pragma once
#include "type_aliases.hpp"
#include <cmath>

namespace gl {

// static auto perspective(float fovy, float aspect, float zNear, float zFar) {

//   // safety checks
//   assert(aspect > 0);
//   assert(zFar > zNear);

//   const float tanHalfFovy = tan(fovy / 2);

//   // gl::A4 result;
//   Eigen::Matrix<float, 4, 4> result;

//   result(0, 0) = 1.0 / (aspect * tanHalfFovy);
//   result(1, 1) = 1.0 / (tanHalfFovy);
//   result(2, 2) = -(zFar + zNear) / (zFar - zNear);
//   result(3, 2) = -1.0;
//   result(2, 3) = -(2.0 * zFar * zNear) / (zFar - zNear);

//   return result;
// }

} // namespace gl