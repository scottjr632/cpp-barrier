cmake_minimum_required(VERSION 3.8)
project(rezsem VERSION 1.0.0 LANGUAGES CXX)
option(REZSEM_BUILD_TESTS OFF)

include(GNUInstallDirs)

add_library(rezsem INTERFACE)
add_library(rezsem::rezsem ALIAS rezsem)

target_compile_features(rezsem INTERFACE cxx_std_17)
target_include_directories(rezsem INTERFACE
  $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
  $<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}/include>)

if(ARGPARSE_BUILD_TESTS)
  add_subdirectory(test)
endif()

install(TARGETS rezsem EXPORT rezsemConfig)
install(EXPORT rezsemConfig
        NAMESPACE rezsem::
        DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/rezsem)
install(FILES ${CMAKE_CURRENT_LIST_DIR}/include/rezsem/rezsem.hpp
        DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/rezsem)

export(EXPORT rezsemConfig
       NAMESPACE rezsem::)