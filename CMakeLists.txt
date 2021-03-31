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

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
