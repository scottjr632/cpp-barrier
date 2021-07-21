cmake_minimum_required(VERSION 3.8)
project(barrier VERSION 1.0.0 LANGUAGES CXX)
option(BARRIER_BUILD_TESTS OFF)

include(GNUInstallDirs)

add_library(barrier INTERFACE)
add_library(barrier::barrier ALIAS barrier)

target_compile_features(barrier INTERFACE cxx_std_17)
target_include_directories(barrier INTERFACE
  $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
  $<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}/include>)

if(BARRIER_BUILD_TESTS)
  add_subdirectory(tests)
endif()

install(TARGETS barrier EXPORT barrierConfig)
install(EXPORT barrierConfig
        NAMESPACE barrier::
        DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/barrier)
install(FILES ${CMAKE_CURRENT_LIST_DIR}/include/barrier/barrier.hpp
        DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/barrier)

export(EXPORT barrierConfig
       NAMESPACE barrier::)
