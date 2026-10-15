// Copyright (c) 2026 silver984 (https://github.com/silver984)
// SPDX-License-Identifier: MIT

#ifndef AXIOM_VEC2_H_
#define AXIOM_VEC2_H_

#include "operable_array.h"

namespace axiom::internal {

struct vec2_addition final {
  template <traits::operable_array Vec2, traits::scalar_or_operable_array Rhs>
  [[nodiscard]] constexpr auto operator()(Vec2 const& v, Rhs const& rhs) const {
    return 0;
  }
};

} // namespace axiom::internal

namespace axiom {

template <traits::arithmetic T = float>
struct vec2 final : public operable_array<vec2, T, 2> {
  using addition = internal::vec2_addition;

  constexpr vec2() = default;

  constexpr vec2(T v)
    : x(v)
    , y(v) {
  }

  constexpr vec2(T xv, T yv)
    : x(xv)
    , y(yv) {
  }

  constexpr T& operator[](uint8_t i) {
    return i == 0 ? x : y;
  }

  [[nodiscard]] constexpr T const& operator[](uint8_t i) const {
    return i == 0 ? x : y;
  }

  T x = T{0};
  T y = T{0};
};

} // namespace axiom

#endif // AXIOM_VEC2_H_