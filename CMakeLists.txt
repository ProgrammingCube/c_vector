cmake_minimum_required( VERSION 3.15 )
project(CVector VERSION 1.0.0 LANGUAGES C)

add_library(vector SHARED src/vector_core.c)

target_include_directories(vector PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
)

set_target_properties(vector PROPERTIES C_VISIBILITY_PRESET hidden)

set_target_properties(vector PROPERTIES 
    PUBLIC_HEADER "include/vector.h" 
)

include(GNUInstallDirs)
install(TARGETS vector
    EXPORT CVectorTargets
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)

install(EXPORT CVectorTargets
    FILE CVectorConfig.cmake
    NAMESPACE CVector::
    DESTINATION lib/cmake/CVector
)

enable_testing()
add_subdirectory(tests)
