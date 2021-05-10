project(rezsem)
cmake_minimum_required(VERSION 3.6)

if(MSVC)
  # Force to always compile with W4
  if(CMAKE_CXX_FLAGS MATCHES "/W[0-4]")
    string(REGEX REPLACE "/W[0-4]" "/W4" CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
  else()
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W4")
  endif()
elseif(CMAKE_COMPILER_IS_GNUCC OR CMAKE_COMPILER_IS_GNUCXX)
  # Update if necessary
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wno-long-long -pedantic")
endif()

if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Release)
endif()

# Disable deprecation for windows
if (WIN32)
	add_compile_definitions(_CRT_SECURE_NO_WARNINGS)
endif()

find_package(Threads REQUIRED)
file( GLOB files "bench_*.cpp" )

ADD_LIBRARY(nanobench nanobench.cpp)

foreach(file ${files})
    string(REGEX REPLACE "(^.*/|\\.[^.]*$)" "" file_without_ext ${file})
    add_executable(${file_without_ext} ${file})
    include_directories("../include" ".")
    target_link_libraries(${file_without_ext} nanobench)
    target_link_libraries(${file_without_ext} ${CMAKE_THREAD_LIBS_INIT})

    set_target_properties(${file_without_ext} PROPERTIES OUTPUT_NAME bench)

    set_property(TARGET ${file_without_ext} PROPERTY CXX_STANDARD 17)
    set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT ${file_without_ext})

endforeach()


# ADD_EXECUTABLE(REZSEMBENCH ${TEST_SOURCES})
# INCLUDE_DIRECTORIES("../include" ".")
# target_link_libraries(REZSEMBENCH nanobench)
# target_link_libraries(REZSEMBENCH ${CMAKE_THREAD_LIBS_INIT})
# set_target_properties(REZSEMBENCH PROPERTIES OUTPUT_NAME bench)

# set_property(TARGET REZSEMBENCH PROPERTY CXX_STANDARD 17)
# set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT REZSEMBENCH)
