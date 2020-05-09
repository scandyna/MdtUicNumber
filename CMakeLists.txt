##############################################################
#  Copyright Philippe Steinmann 2020 - 2020.
#  Distributed under the Boost Software License, Version 1.0.
#  (See accompanying file LICENSE.txt or copy at
#  https://www.boost.org/LICENSE_1_0.txt)
##############################################################
cmake_minimum_required(VERSION 3.10)

#######################################################
# Project definition with versionning got from git tag
#######################################################

# CMAKE_PREFIX_PATH is empty before any call to project()
# Because set_project_version() does not exist,
# we call the project command twice (is there a cleaner solution?)
project(MdtUicNumber)

find_package(Git REQUIRED)
find_package(MdtCMakeModules REQUIRED)

include(MdtVersionUtils)

set(INITIAL_PROJECT_VERSION)
if(FROM_CONAN_PROJECT_VERSION)
  set(INITIAL_PROJECT_VERSION ${FROM_CONAN_PROJECT_VERSION})
else()
  mdt_cmake_project_version_from_git_tag(INITIAL_PROJECT_VERSION DEFAULT_VERSION 0.1.0)
endif()

project(MdtUicNumber VERSION ${INITIAL_PROJECT_VERSION})

unset(INITIAL_PROJECT_VERSION)

#######################
# Options
#######################

include(MdtBuildOptionsUtils)
include(MdtSanitizers)

set(CMAKE_CXX_VISIBILITY_PRESET hidden)
set(CMAKE_VISIBILITY_INLINES_HIDDEN YES)

option(ENABLE_QT_SUPPORT "Enable Qt support" OFF)
option(BUILD_TESTS "Build the tests" OFF)
option(BUILD_BENCHMARKS "Build the benchmarks" OFF)
option(BUILD_CPP_API_DOC "Generate Doxyfile for C++ API documentation" OFF)
mdt_set_available_build_types(Release Debug RelWithDebInfo MinSizeRel Instrumented)
option(WARNING_AS_ERROR "Threat warnings as errors" OFF)

mdt_get_available_optimization_levels(AVAILABLE_OPTIMIZATION_LEVELS)
set(BUILD_TYPE_INSTRUMENTED_OPTIMIZATION_LEVEL "" CACHE STRING "Set optimization level for Instrumented build")
set_property(CACHE BUILD_TYPE_INSTRUMENTED_OPTIMIZATION_LEVEL PROPERTY STRINGS ${AVAILABLE_OPTIMIZATION_LEVELS})
option(BUILD_TYPE_INSTRUMENTED_USE_DEBUG_SYMBOLS "Add debug symbols (-g on Gcc/Clang, /DEBUG on MSVC)" ON)
option(BUILD_TYPE_INSTRUMENTED_DEFINE_NDEBUG "Set NDEBUG definition for Instrumented build (will disable assert)" OFF)

if(ENABLE_QT_SUPPORT)
  option(BUILD_SHARED_LIBS "Build shared libraries (has sense for some Qt support libraries)" ON)
endif()

mdt_add_address_sanitizer_option_if_available(SANITIZER_ENABLE_ADDRESS
  HELP_STRING "Enable address sanitizer for Instrumented build"
  INITIAL_VALUE OFF
)
mdt_add_memory_sanitizer_option_if_available(SANITIZER_ENABLE_MEMORY
  HELP_STRING "Enable memory sanitizer for Instrumented build"
  INITIAL_VALUE OFF
)
mdt_add_undefined_sanitizer_option_if_available(SANITIZER_ENABLE_UNDEFINED
  HELP_STRING "Enable undefined behaviour sanitizer for Instrumented build"
  INITIAL_VALUE OFF
)
mdt_add_thread_sanitizer_option_if_available(SANITIZER_ENABLE_THREAD
  HELP_STRING "Enable thread sanitizer for Instrumented build (can be incompatible with other sanitizers)"
  INITIAL_VALUE OFF
)

#######################
# Warnings
#######################

if(MSVC)
  add_compile_options(/W3)
  if(WARNING_AS_ERROR)
    add_compile_options(/WX)
  endif()
else()
  add_compile_options(-Wall -Wextra -pedantic)
  if(WARNING_AS_ERROR)
    add_compile_options(-Werror)
  endif()
endif()


# See https://stackoverflow.com/questions/46798456/handling-gccs-noexcept-type-warning
if( (${CMAKE_CXX_COMPILER_ID} MATCHES "GNU") AND (${CMAKE_CXX_COMPILER_VERSION} VERSION_GREATER_EQUAL 7.2) )
  add_compile_options(-Wno-noexcept-type)
endif()

#######################
# Paths to dependencies
#######################

include(AddQt5ToCMakePrefixPath)

set(QT_PREFIX_PATH CACHE PATH "Path to the root of Qt distribution. (For example: /opt/qt/Qt5/5.13.0/gcc_64). If empty, system distribution is considered.")
add_qt5_to_cmake_prefix_path("${QT_PREFIX_PATH}")

#######################
# Dependencies
#######################

if(BUILD_TESTS)
  find_package(Catch2 REQUIRED)
endif()

if(ENABLE_QT_SUPPORT)
  find_package(Threads REQUIRED)
  find_package(Qt5 COMPONENTS Core Gui REQUIRED)
  if(BUILD_TESTS)
    find_package(Qt5 COMPONENTS Test Widgets REQUIRED)
  endif()
endif()

#######################
# Windows specific
#######################

# On Windows, RPATH do not exist
# To be able to run tests, we have to put all binaries in the same directory
if(WIN32)
  set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")
endif()

#######################
# Sanitizers
#######################

if(SANITIZER_ENABLE_ADDRESS)
  mdt_build_with_address_sanitizer(BUILD_TYPES Instrumented)
endif()
if(SANITIZER_ENABLE_MEMORY)
  mdt_build_with_memory_sanitizer(BUILD_TYPES Instrumented)
endif()
if(SANITIZER_ENABLE_UNDEFINED)
  mdt_build_with_undefined_sanitizer(BUILD_TYPES Instrumented)
endif()
if(SANITIZER_ENABLE_THREAD)
  mdt_build_with_thread_sanitizer(BUILD_TYPES Instrumented)
endif()

#######################
# Instrumented build
#######################

if(BUILD_TYPE_INSTRUMENTED_OPTIMIZATION_LEVEL)
  add_compile_options($<$<CONFIG:Instrumented>:${BUILD_TYPE_INSTRUMENTED_OPTIMIZATION_LEVEL}>)
endif()

if(BUILD_TYPE_INSTRUMENTED_USE_DEBUG_SYMBOLS)
  mdt_add_debug_symbols_compile_option(BUILD_TYPES Instrumented)
endif()

if(BUILD_TYPE_INSTRUMENTED_DEFINE_NDEBUG)
  add_definitions($<$<CONFIG:Instrumented>:NDEBUG>)
endif()

#######################
# Documentation
#######################

if(BUILD_CPP_API_DOC)
  configure_file(
    "${PROJECT_SOURCE_DIR}/Doxyfile.in"
    "${PROJECT_BINARY_DIR}/Doxyfile"
  )
endif()

#######################
# Install
#######################

set(MDT_INSTALL_PACKAGE_NAME Mdt${PROJECT_VERSION_MAJOR})
include(GNUInstallDirs)
include(MdtInstallDirs)
include(MdtPackageConfigHelpers)

mdt_install_namespace_package_config_file(
  INSTALL_NAMESPACE ${MDT_INSTALL_PACKAGE_NAME}
  DESTINATION "${CMAKE_INSTALL_LIBDIR}/cmake/${MDT_INSTALL_PACKAGE_NAME}"
  COMPONENT Mdt_Dev
)

#######################
# Qt
#######################

# TODO: should be imposed on tests only ? NOTE: not a target property, will it be propagated ??
if(ENABLE_QT_SUPPORT)
  add_definitions(-DQT_NO_CAST_DEFINITIONS -DQT_NO_CAST_FROM_ASCII -DQT_NO_CAST_TO_ASCII -DQT_NO_CAST_FROM_BYTEARRAY)
  set(CMAKE_AUTOMOC ON)
  set(CMAKE_AUTOUIC ON)
endif()

#######################
# Sources and tests
#######################

if(BUILD_TESTS)
  add_library(Mdt_Catch2Main STATIC Catch2Main.cpp)
  target_link_libraries(Mdt_Catch2Main PUBLIC Catch2::Catch2)
  add_library(Mdt::Catch2Main ALIAS Mdt_Catch2Main)

  enable_testing()
endif()


add_subdirectory(libs/UicNumber)

if(ENABLE_QT_SUPPORT)
  add_subdirectory(libs/UicNumber_Qt)
  add_subdirectory(libs/UicNumber_QtGui)
endif()
