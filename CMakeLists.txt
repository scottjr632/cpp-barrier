cmake_minimum_required(VERSION 3.0.0)
project(rezsemaphores VERSION 0.1.0)

include(CTest)

option(BUILD_TESTING "Build unit tests" OFF)

if (BUILD_TESTING)
  enable_testing()
  add_subdirectory(tests)
endif()

find_package(Threads REQUIRED)
add_library(rezsemaphores semaphores.cpp)
set_target_properties(rezsemaphores PROPERTIES PUBLIC_HEADER rezsemaphores.hpp)

add_library(Rezsemaphores::rezsemaphores ALIAS rezsemaphores)
set(INSTALL_CONFIGDIR ${CMAKE_INSTALL_LIBDIR}/cmake/RezSem)
install(TARGETS rezsemaphores
        PUBLIC_HEADER
        DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})


set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)

#####################
# ConfigVersion file
##
include(CMakePackageConfigHelpers)
write_basic_package_version_file(
    ${CMAKE_CURRENT_BINARY_DIR}/RezSemConfigVersion.cmake
    VERSION ${PROJECT_VERSION}
    COMPATIBILITY AnyNewerVersion
)

configure_package_config_file(
    ${CMAKE_CURRENT_LIST_DIR}/CMake/RezSemConfig.cmake.in
    ${CMAKE_CURRENT_BINARY_DIR}/RezSemConfig.cmake
    INSTALL_DESTINATION ${INSTALL_CONFIGDIR}
)

## Install all the helper files
install(
    FILES
      ${CMAKE_CURRENT_BINARY_DIR}/RezSemConfig.cmake
      ${CMAKE_CURRENT_BINARY_DIR}/RezSemConfigVersion.cmake
    DESTINATION ${INSTALL_CONFIGDIR}
)