add_executable(calculator
  src/main.cpp
)

target_link_libraries(calculator PRIVATE mathlib)

target_include_directories(mathlib
  PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_compile_options(calculator PRIVATE ${PROJ_WARNINGS} ${PROJ_SANITIZERS})
target_link_options(calculator PRIVATE ${PROJ_SANITIZERS})

include(GNUInstallDirs)
install(TARGETS calculator
  RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
