// Copyright (c) 2026 silver984 (https://github.com/silver984)
// SPDX-License-Identifier: MIT

#ifndef AXIOM_TRAITS_H_
#define AXIOM_TRAITS_H_

#include <concepts>
#include <type_traits>

namespace axiom::traits {

template <typename T>
concept arithmetic = std::is_arithmetic_v<T>;

template <typename T>
concept operable_array = requires(T a, T const b, std::size_t i) {
  typename T::axiom_operable_array;
  requires arithmetic<typename T::value_type>;
  { T::capacity } -> std::same_as<std::size_t>;
  { a[i] } -> std::same_as<typename T::value_type&>;
  { b[i] } -> std::same_as<typename T::value_type const&>;
};

template <typename Left, typename Right>
concept same_capacity_operable_arrays =
  operable_array<Left> && operable_array<Right> && Left::capacity == Right::capacity;
template <typename T>
concept no_addition_operable_array = requires {
  requires operable_array<T>;
  typename T::no_addition;
};

template <typename T>
concept no_subtraction_operable_array = requires {
  requires operable_array<T>;
  typename T::no_subtraction;
};

template <typename T>
concept no_multiplication_operable_array = requires {
  requires operable_array<T>;
  typename T::no_multiplication;
};

template <typename T>
concept no_division_operable_array = requires {
  requires operable_array<T>;
  typename T::no_division;
};

} // namespace axiom::traits

#endif // AXIOM_TRAITS_H_