cmake_minimum_required(VERSION 3.15)

project(
  database
  LANGUAGES CXX
  VERSION 1.0
  DESCRIPTION "Database")

# UNIX, WIN32, WINRT, CYGWIN, APPLE are environment variables as flags set by
# default system
if(UNIX)
  message("This is a ${CMAKE_SYSTEM_NAME} system")
elseif(APPLE)
  message("This is a Mac System")
elseif(WIN32)
  message("This is a Windows System")
endif()

option(FORCE_COLORED_OUTPUT
       "Always produce ANSI-colored output (GNU/Clang only)." ON)
if(${FORCE_COLORED_OUTPUT})
  message("Enable ANSI-colored output (GNU/Clang only)")
  if("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
    add_compile_options(-fdiagnostics-color=always)
  elseif("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
    add_compile_options(-fcolor-diagnostics)
  endif()
endif()

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_CXX_EXTENSIONS On)

# print function
function(print)
  foreach(var ${ARGN})
    message("${var} = ${${var}}")
  endforeach()
endfunction(print)

print(CMAKE_CXX_STANDARD CMAKE_CXX_STANDARD_REQUIRED)
print(CMAKE_CXX_COMPILER_ID)

# comiple option -g -O1 -fno-omit-frame-pointer -fno-optimize-sibling-calls

# file(GLOB_RECURSE SOURCES "src/*.cpp")
file(GLOB SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/*.hpp"
     "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp")

set(TARGET_PA final)
add_executable(${TARGET_PA})

# target_include_directories(pa8 PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}) Use
# target_sources to add header-files too to help IDE show all sources
target_sources(${TARGET_PA} PUBLIC ${SOURCES})
# target_compile_options(${TARGET_PA} PUBLIC ${CXXFLAG})
print(CMAKE_CURRENT_SOURCE_DIR)

# options
option(ENABLE_CCACHE "Enable ccache" ON)
option(ENABLE_CPPCHECK "Enable static analysis with cppcheck" OFF)
option(ENABLE_CLANG_TIDY "Enable static analysis with clang-tidy" OFF)

# # gTest message("Building GoogleTest.") include(FetchContent)
# FetchContent_Declare( googletest URL
# https://github.com/google/googletest/archive/609281088cfefc76f9d0ce82e1ff6c30cc3591e5.zip
# )

# # For Windows: Prevent overriding the parent project's compiler/linker
# settings set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
# FetchContent_MakeAvailable(googletest) add_executable( test test/test.cc )
# target_link_libraries( test gtest_main ) include(GoogleTest)
# gtest_discover_tests(test)

# ccache
if(ENABLE_CCACHE)
  find_program(CCACHE_FOUND ccache)

  if(CCACHE_FOUND)
    message("Using Fast Compiler Cache(ccache).")
    set_property(GLOBAL PROPERTY RULE_LAUNCH_COMPILE ccache)
  else()
    message("ccache not found cannot use")
  endif()
endif()

if(ENABLE_CPPCHECK)
  find_program(CPPCHECK cppcheck)

  if(CPPCHECK)
    set(CMAKE_CXX_CPPCHECK ${CPPCHECK} --supress=missingInclude --enable=all)
  else()
    message(SEND_ERROR "cppcheck requested but executalbe not found")
  endif()
endif()

if(ENABLE_CLANG_TIDY)
  find_program(CLANGTIDY clang-tidy)

  if(CLANGTIDY)
    set(CMAKE_CXX_CLANG_TIDY ${CLANGTIDY})
  else()
    message(SEND_ERROR "clang-tidy requested but executalbe not found")
  endif()
endif()

# Very basic PCH EXAMPLE
option(ENABLE_PCH "Enable Precompile Headers" ON)

if(ENABLE_PCH)
  message("Enable Precompile Headers")
  target_precompile_headers(
    ${TARGET_PA}
    INTERFACE
    <algorithm>
    <array>
    <vector>
    <string>
    <optional>
    <variant>
    <map>
    <utility>
    <memory>
    <iostream>
    <fstream>
    <sstream>
    "Faked.hpp"
    "TestAutomatic.hpp"
    "TestManually.hpp"
    "Timer.hpp"
    "Scanner.hpp"
    "TokenSequencer.hpp"
    "TestSequencer.hpp"
    "View.hpp"
    "TabularView.hpp"
    "TableFormatter.hpp"
    "BasicTypes.hpp"
    "Errors.hpp"
    "keywords.hpp"
    "Helpers.hpp"
    "AboutUs.hpp")
endif()


