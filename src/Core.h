#pragma once

#include <assert.h>

namespace scip {

constexpr double epsilon = 1e-5;

template <typename T>
constexpr bool are_real_equals(T a, T b) {
  return b - a >= -epsilon;
}

}  // namespace scip
