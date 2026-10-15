// Copyright (c) 2026 silver984 (https://github.com/silver984)
// SPDX-License-Identifier: MIT

#ifndef AXIOM_TRAITS_H_
#define AXIOM_TRAITS_H_

#include <concepts>
#include <type_traits>

namespace axiom::traits {

template <typename T>
concept scalar = std::is_scalar_v<T>;

template <typename T>
concept operable_array = requires(T a, T const b, std::uint8_t i) {
  typename T::axiom_operable_array;
  requires scalar<typename T::value_type>;
  { a[i] } -> std::same_as<typename T::value_type&>;
  { b[i] } -> std::same_as<typename T::value_type const&>;
};

template <typename T>
concept scalar_or_operable_array = scalar<T> || operable_array<T>;

// TODO(silver984): implement for other operations
template <typename T>
concept no_addition_operable_array = operable_array<T> && requires { typename T::no_addition; };

} // namespace axiom::traits

#endif // AXIOM_TRAITS_H_