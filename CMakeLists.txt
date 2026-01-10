cmake_minimum_required(VERSION 3.20)
project(calculator LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# ---------------- Options ----------------
option(ENABLE_STRICT_WARNINGS "Enable extra strict warnings" OFF)
option(ENABLE_SANITIZERS "Enable ASan/UBSan in Debug" ON)

# ---------------- Warnings ----------------
set(PROJ_WARNINGS
  -Wall -Wextra -Wpedantic
)

if(ENABLE_STRICT_WARNINGS)
  list(APPEND PROJ_WARNINGS -Wconversion -Wsign-conversion)
endif()

# Werror policy: Debug OR CI env var
set(PROJ_WERROR OFF)
if(CMAKE_BUILD_TYPE STREQUAL "Debug")
  set(PROJ_WERROR ON)
endif()
if(DEFINED ENV{CI})
  set(PROJ_WERROR ON)
endif()

if(PROJ_WERROR)
  list(APPEND PROJ_WARNINGS -Werror)
endif()

# ---------------- Sanitizers (Debug only) ----------------
set(PROJ_SANITIZERS "")
if(ENABLE_SANITIZERS AND (CMAKE_BUILD_TYPE STREQUAL "Debug"))
  if(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
    set(PROJ_SANITIZERS -fsanitize=address,undefined -fno-omit-frame-pointer)
  endif()
endif()

add_subdirectory(lib)
add_subdirectory(app)

# ---------------- clang-tidy: run during compilation ----------------
find_program(CLANG_TIDY_EXE NAMES clang-tidy)
if(CLANG_TIDY_EXE)
  set(CMAKE_CXX_CLANG_TIDY "${CLANG_TIDY_EXE}")
else()
  message(WARNING "clang-tidy not found -> static analysis disabled")
endif()

# ---------------- clang-format: run before build ----------------
find_program(CLANG_FORMAT_EXE NAMES clang-format)
if(CLANG_FORMAT_EXE)
  file(GLOB_RECURSE ALL_FORMAT_SOURCES
    "${CMAKE_SOURCE_DIR}/app/*.cpp"
    "${CMAKE_SOURCE_DIR}/lib/math/src/*.cpp"
    "${CMAKE_SOURCE_DIR}/lib/math/include/*.h"
  )

  add_custom_target(format
    COMMAND ${CLANG_FORMAT_EXE} -i ${ALL_FORMAT_SOURCES}
    COMMENT "Running clang-format (Google style)..."
  )

  # Make sure format runs on normal build
  add_dependencies(mathlib format)
  add_dependencies(calculator format)
else()
  message(WARNING "clang-format not found -> formatting disabled")
endif()
