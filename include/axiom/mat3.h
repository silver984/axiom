// Copyright (c) 2026 silver984 (https://github.com/silver984)
// SPDX-License-Identifier: MIT

#ifndef AXIOM_MAT3_H_
#define AXIOM_MAT3_H_

#include "operable_array.h"
#include "vec2.h"

#include <cmath>

namespace axiom::internal {
// forward declared
struct mat3_multiplication;
} // namespace axiom::internal

namespace axiom {

template <traits::arithmetic T = float>
class mat3 final : public operable_array<mat3, T, 9> {
 public:
  using multiplication = internal::mat3_multiplication;

  constexpr mat3() = default;

  template <typename Self>
  constexpr decltype(auto) operator[](this Self&& self, std::size_t i) {
    return std::forward_like<Self>(self.m_[i]);
  }

  template <typename Self>
  constexpr decltype(auto) operator[](this Self&& self, std::size_t row, std::size_t col) {
    return std::forward_like<Self>(self.m_[row * 3 + col]);
  }

  [[nodiscard]] static mat3 rotation(T rad) {
    T const c = std::cos(rad);
    T const s = std::sin(rad);
    mat3 out;
    out[0, 0] = c;
    out[0, 1] = -s;
    out[1, 0] = s;
    out[1, 1] = c;
    return out;
  }

  [[nodiscard]] static mat3 skew(vec2<T> rad) {
    // vec2<T> const t = tan(rad);
    mat3 out;
    // out[0, 1] = t.x;
    // out[1, 0] = t.y;
    return out;
  }

  [[nodiscard]] constexpr static mat3 translation(vec2<T> val) {
    mat3 out;
    out[0, 2] = val.x;
    out[1, 2] = val.y;
    return out;
  }

  [[nodiscard]] constexpr static mat3 scale(vec2<T> val) {
    mat3 out;
    out[0, 0] = val.x;
    out[1, 1] = val.y;
    return out;
  }

  [[nodiscard]] constexpr vec2<T> transform_point(vec2<T> val) const {
    return vec2<T>(val.x * (*this)[0, 0] + val.y * (*this)[0, 1] + (*this)[0, 2],
                   val.x * (*this)[1, 0] + val.y * (*this)[1, 1] + (*this)[1, 2]);
  }

  [[nodiscard]] constexpr vec2<T> translation() const {
    return vec2<T>((*this)[0, 2], (*this)[1, 2]);
  }

 private:
  T m_[9] = {
    T{1}, T{0}, T{0}, //
    T{0}, T{1}, T{0}, //
    T{0}, T{0}, T{1},
  };
};

} // namespace axiom

namespace axiom::internal {

struct mat3_multiplication final {
  template <traits::arithmetic T, traits::arithmetic U>
  [[nodiscard]] constexpr decltype(auto) operator()(mat3<T> const& lhs, mat3<U> const& rhs) const {
    using common_value_type = std::common_type_t<T, U>;
    mat3<common_value_type> out;
    for (std::size_t row = 0; row < 3; ++row) {
      for (std::size_t col = 0; col < 3; ++col) {
        common_value_type sum{};
        for (std::size_t k = 0; k < 3; ++k) {
          sum += static_cast<common_value_type>(lhs[row, k]) *
                 static_cast<common_value_type>(rhs[k, col]);
        }
        out[row, col] = sum;
      }
    }
    return out;
  }
};

} // namespace axiom::internal

#endif // AXIOM_MAT3_H_