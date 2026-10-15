# Copyright (c) 2026 silver984 (https://github.com/silver984)
# SPDX-License-Identifier: MIT

cmake_minimum_required(VERSION 3.31.6)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_SCAN_FOR_MODULES OFF)

project(axiom LANGUAGES CXX)

add_library(axiom INTERFACE)
add_library(axiom::axiom ALIAS axiom)

target_include_directories(axiom INTERFACE include)

option(AXIOM_BUILD_TEST "Build test application" OFF)
if (AXIOM_BUILD_TEST)
  add_subdirectory(test)
endif()