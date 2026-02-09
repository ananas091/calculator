cmake_minimum_required(VERSION 3.20)
project(calculator)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_compile_options(
    -Wall
    -Wextra
    -Wpedantic
    -Wshadow
    -Wconversion
)

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    add_compile_options(-fsanitize=address,undefined -fno-omit-frame-pointer)
    add_link_options(-fsanitize=address,undefined)
endif()

include(FetchContent)

FetchContent_Declare(
    mathlib
    GIT_REPOSITORY https://github.com/ananas091/mathlib.git
    GIT_TAG main
)

FetchContent_Declare(
    json
    GIT_REPOSITORY https://github.com/nlohmann/json.git
    GIT_TAG v3.12.0
)

FetchContent_Declare(
    googletest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG v1.17.0
)

FetchContent_Declare(
    spdlog
    GIT_REPOSITORY https://github.com/gabime/spdlog.git
    GIT_TAG v1.17.0
)

FetchContent_MakeAvailable(mathlib json googletest spdlog)

add_library(calculator_lib
    src/parser.cpp
    src/runner.cpp
    src/checker.cpp
    src/calculator.cpp
    src/printer.cpp
    src/logger.cpp
)
target_include_directories(calculator_lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_link_libraries(calculator_lib PUBLIC mathlib nlohmann_json::nlohmann_json spdlog::spdlog)

add_executable(calculator src/main.cpp)
target_link_libraries(calculator PRIVATE calculator_lib)

enable_testing()

add_executable(calculator_tests
    tests/test_calculator.cpp
)
target_link_libraries(calculator_tests PRIVATE calculator_lib GTest::gtest_main)

include(GoogleTest)
gtest_discover_tests(calculator_tests)

include(GNUInstallDirs)

set_target_properties(calculator PROPERTIES
    INSTALL_RPATH "$ORIGIN/../${CMAKE_INSTALL_LIBDIR}"
)

install(TARGETS mathlib
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
)

install(TARGETS calculator RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR})

find_program(CLANG_TIDY_EXE NAMES clang-tidy)
if(CLANG_TIDY_EXE)
    set(CMAKE_CXX_CLANG_TIDY "${CLANG_TIDY_EXE}")
endif()

find_program(CLANG_FORMAT_EXE NAMES clang-format)
if(CLANG_FORMAT_EXE)
    file(GLOB_RECURSE ALL_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")
    
    add_custom_target(format
        COMMAND ${CLANG_FORMAT_EXE} -i ${ALL_SOURCES}
        COMMENT "Running clang-format..."
    )
    
    add_dependencies(calculator format)
endif()