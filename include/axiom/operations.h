// Copyright (c) 2026 silver984 (https://github.com/silver984)
// SPDX-License-Identifier: MIT

#ifndef AXIOM_OPERATIONS_H_
#define AXIOM_OPERATIONS_H_

namespace axiom::operations {

struct addition final {
  template <typename Lhs, typename Rhs>
    requires requires(Lhs lhs, Rhs rhs) { lhs + rhs; }
  [[nodiscard]] constexpr auto operator()(Lhs lhs, Rhs rhs) const {
    return lhs + rhs;
  }
};

struct addition_assign final {
  template <typename Lhs, typename Rhs>
    requires requires(Lhs lhs, Rhs rhs) { lhs += rhs; }
  constexpr Lhs& operator()(Lhs& lhs, Rhs rhs) const {
    return lhs += rhs;
  }
};

struct subtraction final {
  template <typename Lhs, typename Rhs>
    requires requires(Lhs lhs, Rhs rhs) { lhs - rhs; }
  [[nodiscard]] constexpr auto operator()(Lhs lhs, Rhs rhs) const {
    return lhs - rhs;
  }
};

struct subtraction_assign final {
  template <typename Lhs, typename Rhs>
    requires requires(Lhs lhs, Rhs rhs) { lhs -= rhs; }
  constexpr Lhs& operator()(Lhs& lhs, Rhs rhs) const {
    return lhs -= rhs;
  }
};

struct multiplication final {
  template <typename Lhs, typename Rhs>
    requires requires(Lhs lhs, Rhs rhs) { lhs * rhs; }
  [[nodiscard]] constexpr auto operator()(Lhs lhs, Rhs rhs) const {
    return lhs * rhs;
  }
};

struct multiplication_assign final {
  template <typename Lhs, typename Rhs>
    requires requires(Lhs lhs, Rhs rhs) { lhs *= rhs; }
  constexpr Lhs& operator()(Lhs& lhs, Rhs rhs) const {
    return lhs *= rhs;
  }
};

struct division final {
  template <typename Lhs, typename Rhs>
    requires requires(Lhs lhs, Rhs rhs) { lhs / rhs; }
  [[nodiscard]] constexpr auto operator()(Lhs lhs, Rhs rhs) const {
    return lhs / rhs;
  }
};

struct division_assign final {
  template <typename Lhs, typename Rhs>
    requires requires(Lhs lhs, Rhs rhs) { lhs /= rhs; }
  constexpr Lhs& operator()(Lhs& lhs, Rhs rhs) const {
    return lhs /= rhs;
  }
};

constexpr addition sum;
constexpr subtraction difference;
constexpr multiplication product;
constexpr division quotient;

constexpr addition_assign assign_sum;
constexpr subtraction_assign assign_difference;
constexpr multiplication_assign assign_product;
constexpr division_assign assign_quotient;

} // namespace axiom::operations

#endif // AXIOM_OPERATIONS_H_