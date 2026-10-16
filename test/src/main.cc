// Copyright (c) 2026 silver984 (https://github.com/silver984)
// SPDX-License-Identifier: MIT

#include <axiom/vec2.h>

int main() {
  constexpr axiom::vec2<> a(8.f);
  constexpr auto c = a + a;
  constexpr auto b = c.x;
  return 0;
}
