/**
 * @file Core.h
 * @author Enzo Gaban
 * @brief Some common definitions
 *
 */

#pragma once

#include <assert.h>

namespace scip {

constexpr double epsilon = 1e-5;

/**
 * @brief Checks if a is less than or equal to b, considering an error.
 *
 * @tparam T real number type
 * @param a smaller number
 * @param b larger number
 * @return true if a <= b
 */
template <typename T>
constexpr bool is_leq(T a, T b) {
  return b - a >= -epsilon;
}

}  // namespace scip