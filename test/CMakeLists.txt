# Copyright (c) 2026 silver984 (https://github.com/silver984)
# SPDX-License-Identifier: MIT

add_executable(test_app)

set_target_properties(
  test_app PROPERTIES
  OUTPUT_NAME "Test"
)

file(GLOB TEST_APPLICATION_SOURCE src/*.c*)
target_sources(test_app PRIVATE ${TEST_APPLICATION_SOURCE})
target_link_libraries(test_app PRIVATE axiom::axiom)