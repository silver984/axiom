// Copyright (c) 2026 silver984 (https://github.com/silver984)
// SPDX-License-Identifier: MIT

#include <axiom/mat3.h>
#include <axiom/vec2.h>

int main() {
  constexpr axiom::vec2<> a(8.f);
  constexpr auto c = a + a;
  constexpr auto b = c.x;
  constexpr axiom::mat3<> d;
  constexpr axiom::mat3<> e;
  constexpr axiom::mat3<> f = d * e;
  constexpr auto g          = f[0, 0];
  return 0;
}
