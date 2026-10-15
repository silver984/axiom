// Copyright (c) 2026 silver984 (https://github.com/silver984)
// SPDX-License-Identifier: MIT

#ifndef AXIOM_NUMERIC_H_
#define AXIOM_NUMERIC_H_

#include <type_traits>

namespace axiom::traits {
template <typename T>
concept scalar = std::is_scalar_v<T>;
} // namespace axiom::traits

#endif // AXIOM_NUMERIC_H_