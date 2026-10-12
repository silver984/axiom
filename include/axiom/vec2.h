/*
MIT License

Copyright (c) 2026 silver984

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

#ifndef AXIOM_VEC2_H_
#define AXIOM_VEC2_H_

#include "axiom/operable_array.h"
#include "numeric.h"
#include "operable_array.h"

namespace axiom {

template <traits::numeric T = float>
struct vec2 final : public operable_array<vec2, T, 2> {
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