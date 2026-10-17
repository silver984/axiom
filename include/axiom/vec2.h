// Copyright (c) 2026 silver984 (https://github.com/silver984)
// SPDX-License-Identifier: MIT

#ifndef AXIOM_VEC2_H_
#define AXIOM_VEC2_H_

#include "operable_array.h"

namespace axiom {

template <traits::arithmetic T = float>
struct vec2 final : operable_array<vec2, T, 2> {
  constexpr vec2() = default;

  constexpr vec2(T v)
    : x(v)
    , y(v) {
  }

  constexpr vec2(T xv, T yv)
    : x(xv)
    , y(yv) {
  }

  template <typename Self>
  constexpr decltype(auto) operator[](this Self&& self, std::size_t i) {
    return i == 0 ? std::forward_like<Self>(self.x) : std::forward_like<Self>(self.y);
  }

  T x = T{0};
  T y = T{0};
};

} // namespace axiom

#endif // AXIOM_VEC2_H_