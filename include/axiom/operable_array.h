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

#ifndef AXIOM_OPERABLE_ARRAY_H_
#define AXIOM_OPERABLE_ARRAY_H_

#include "operations.h"
#include "scalar.h"

#include <concepts>
#include <cstdint>
#include <type_traits>
#include <utility>

namespace axiom::traits {

template <typename T>
concept op_arr = requires(T a, T const b, std::uint8_t i) {
  typename T::axiom_op_arr;
  requires scalar<typename T::value_type>;
  { a[i] } -> std::same_as<typename T::value_type&>;
  { b[i] } -> std::same_as<typename T::value_type const&>;
};

template <typename T>
concept numeric_or_op_arr = scalar<T> || op_arr<T>;

// TODO(silver984): implement for other operations
template <typename T>
concept op_arr_no_addition = op_arr<T> && requires { typename T::no_addition; };

} // namespace axiom::traits

namespace axiom {

template <template <traits::scalar> typename Derived, traits::scalar ValueType,
          std::uint8_t Capacity>
class operable_array {
 public:
  using axiom_op_arr = void;
  using value_type   = ValueType;

  template <traits::op_arr Self>
  [[nodiscard]] constexpr auto operator+(this Self&& self) {
    return std::forward_like<Self>(self);
  }

  template <traits::op_arr Self>
  [[nodiscard]] constexpr auto operator-(this Self const& self) {
    Self out;
    for (std::uint8_t i = 0; i < capacity; ++i) {
      out[i] = -(self[i]);
    }
    return out;
  }

  template <traits::op_arr Self, traits::numeric_or_op_arr Rhs>
    requires(!traits::op_arr_no_addition<Self>)
  [[nodiscard]] constexpr auto operator+(this Self const& self,
                                         Rhs const& rhs) {
    return std::forward_like<Self>(self)
      .template evaluate<operations::addition>(rhs);
  }

  template <traits::op_arr Self, traits::numeric_or_op_arr Rhs>
  [[nodiscard]] constexpr auto operator-(this Self const& self,
                                         Rhs const& rhs) {
    return std::forward_like<Self>(self)
      .template evaluate<operations::subtraction>(rhs);
  }

  template <traits::op_arr Self, traits::numeric_or_op_arr Rhs>
  [[nodiscard]] constexpr auto operator*(this Self const& self,
                                         Rhs const& rhs) {
    return std::forward_like<Self>(self)
      .template evaluate<operations::multiplication>(rhs);
  }

  template <traits::op_arr Self, traits::numeric_or_op_arr Rhs>
  [[nodiscard]] constexpr auto operator/(this Self const& self,
                                         Rhs const& rhs) {
    return std::forward_like<Self>(self)
      .template evaluate<operations::division>(rhs);
  }

  // TODO(silver984): All other operators

  static constexpr std::uint8_t capacity = Capacity;

 private:
  template <typename Operation, traits::op_arr Self,
            traits::numeric_or_op_arr Rhs>
  [[nodiscard]] constexpr auto evaluate(this Self const& self, Rhs const& rhs) {
    Operation operation{};
    if constexpr (traits::scalar<Rhs>) {
      using common_value_t = std::common_type_t<ValueType, Rhs>;
      Derived<common_value_t> out{};
      for (std::uint8_t i = 0; i < capacity; ++i) {
        out[i] = operation(static_cast<common_value_t>(self[i]),
                           static_cast<common_value_t>(rhs));
      }
      return out;
    } else {
      using common_value_t =
        std::common_type_t<ValueType, typename Rhs::value_type>;
      Derived<common_value_t> out{};
      for (std::uint8_t i = 0; i < capacity; ++i) {
        out[i] = operation(static_cast<common_value_t>(self[i]),
                           static_cast<common_value_t>(rhs[i]));
      }
      return out;
    }
  }

  template <typename Operation, traits::op_arr Self,
            traits::numeric_or_op_arr Rhs>
  constexpr auto perform(this Self& self, Rhs const& rhs) {
    Operation operation{};
    for (std::uint8_t i = 0; i < capacity; ++i) {
      if constexpr (traits::scalar<Rhs>) {
        operation(self[i], static_cast<ValueType>(rhs));
      } else {
        operation(self[i], static_cast<ValueType>(rhs[i]));
      }
    }
    return std::forward_like<Self>(self);
  }
};

} // namespace axiom

#endif // AXIOM_OPERABLE_ARRAY_H_