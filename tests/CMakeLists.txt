project(barrier)
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
file(GLOB TEST_SOURCES
	main.cpp
	"test_*.cpp"
)

set_source_files_properties(main.cpp
    PROPERTIES
    COMPILE_DEFINITIONS DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN)
	
ADD_EXECUTABLE(BARRIER ${TEST_SOURCES})
INCLUDE_DIRECTORIES("../include" ".")
target_link_libraries(BARRIER ${CMAKE_THREAD_LIBS_INIT})
set_target_properties(BARRIER PROPERTIES OUTPUT_NAME tests)

set_property(TARGET BARRIER PROPERTY CXX_STANDARD 17)
set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT BARRIER)
