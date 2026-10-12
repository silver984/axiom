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