add_library(mathlib SHARED
  src/mathlib.cpp
)

target_include_directories(mathlib
  PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_compile_options(mathlib PRIVATE ${PROJ_WARNINGS} ${PROJ_SANITIZERS})
target_link_options(mathlib PRIVATE ${PROJ_SANITIZERS})

include(GNUInstallDirs)
install(TARGETS mathlib
  LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
)
install(FILES include/mathlib.hpp
  DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)
