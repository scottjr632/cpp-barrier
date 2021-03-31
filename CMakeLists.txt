cmake_minimum_required(VERSION 3.0.0)
project(semaphores VERSION 0.1.0)

include(CTest)
enable_testing()

if(BUILD_TESTING)
  add_subdirectory(tests)
endif()

find_package(Threads REQUIRED)
add_library(semaphores semaphores.cpp)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
