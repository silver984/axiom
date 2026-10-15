// Copyright (c) 2026 silver984 (https://github.com/silver984)
// SPDX-License-Identifier: MIT

#ifndef AXIOM_OPERABLE_ARRAY_H_
#define AXIOM_OPERABLE_ARRAY_H_

#include "operations.h"
#include "traits.h"

#include <cstdint>
#include <utility>

namespace axiom {

template <template <traits::scalar> typename Derived, traits::scalar ValueType,
          std::uint8_t Capacity>
class operable_array {
 public:
  using axiom_operable_array = void;
  using value_type           = ValueType;

  template <traits::operable_array Self>
  [[nodiscard]] constexpr auto operator+(this Self&& self) {
    return std::forward_like<Self>(self);
  }

  template <traits::operable_array Self>
  [[nodiscard]] constexpr auto operator-(this Self const& self) {
    Self out;
    for (std::uint8_t i = 0; i < capacity; ++i) {
      out[i] = -(self[i]);
    }
    return out;
  }

  template <traits::operable_array Self, traits::scalar_or_operable_array Rhs>
    requires(!traits::no_addition_operable_array<Self>)
  [[nodiscard]] constexpr auto operator+(this Self const& self, Rhs const& rhs) {
    if constexpr (requires {
                    typename Self::addition;
                    requires std::is_default_constructible_v<typename Self::addition>;
                  }) {
      using custom_addition = typename Self::addition;
      custom_addition operation{};
      return operation(self, rhs);
    } else {
      return std::forward_like<Self>(self).template evaluate<operations::addition>(rhs);
    }
  }

  template <traits::operable_array Self, traits::scalar_or_operable_array Rhs>
  [[nodiscard]] constexpr auto operator-(this Self const& self, Rhs const& rhs) {
    return std::forward_like<Self>(self).template evaluate<operations::subtraction>(rhs);
  }

  template <traits::operable_array Self, traits::scalar_or_operable_array Rhs>
  [[nodiscard]] constexpr auto operator*(this Self const& self, Rhs const& rhs) {
    return std::forward_like<Self>(self).template evaluate<operations::multiplication>(rhs);
  }

  template <traits::operable_array Self, traits::scalar_or_operable_array Rhs>
  [[nodiscard]] constexpr auto operator/(this Self const& self, Rhs const& rhs) {
    return std::forward_like<Self>(self).template evaluate<operations::division>(rhs);
  }

  // TODO(silver984): All other operators

  static constexpr std::uint8_t capacity = Capacity;

 private:
  template <typename Operation, traits::operable_array Self, traits::scalar_or_operable_array Rhs>
  [[nodiscard]] constexpr auto evaluate(this Self const& self, Rhs const& rhs) {
    Operation operation{};
    if constexpr (traits::scalar<Rhs>) {
      using common_value_t = std::common_type_t<ValueType, Rhs>;
      Derived<common_value_t> out{};
      for (std::uint8_t i = 0; i < capacity; ++i) {
        out[i] = operation(static_cast<common_value_t>(self[i]), static_cast<common_value_t>(rhs));
      }
      return out;
    } else {
      using common_value_t = std::common_type_t<ValueType, typename Rhs::value_type>;
      Derived<common_value_t> out{};
      for (std::uint8_t i = 0; i < capacity; ++i) {
        out[i] =
          operation(static_cast<common_value_t>(self[i]), static_cast<common_value_t>(rhs[i]));
      }
      return out;
    }
  }

  template <typename Operation, traits::operable_array Self, traits::scalar_or_operable_array Rhs>
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