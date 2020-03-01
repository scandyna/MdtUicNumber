##############################################################
#  Copyright Philippe Steinmann 2020 - 2020.
#  Distributed under the Boost Software License, Version 1.0.
#  (See accompanying file LICENSE.txt or copy at
#  https://www.boost.org/LICENSE_1_0.txt)
##############################################################
include(GenerateExportHeader)
include(MdtInstallLibrary)

# TODO: if it stays a header only library,
#       it should be a INTERFACE library
#       For this case, mdt_install_library() will not work
#       (See CMake generates errors, that make sense)
add_library(Mdt_UicNumber INTERFACE)
add_library(Mdt::UicNumber ALIAS Mdt_UicNumber)

# target_compile_features(Mdt_UicNumber PUBLIC cxx_std_17)

# if(BUILD_USE_IPO_LTO)
#   set_target_properties(QCoreApplicationForNonQtUsage
#     PROPERTIES INTERPROCEDURAL_OPTIMIZATION TRUE
#   )
# endif()

target_include_directories(Mdt_UicNumber
  INTERFACE
   $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
   $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}>
)

# generate_export_header(Mdt_UicNumber)

mdt_install_interface_library(
  TARGET Mdt_UicNumber
  LIBRARY_DESTINATION ${CMAKE_INSTALL_LIBDIR}
  INCLUDES_DIRECTORY .
  INCLUDES_FILE_WITHOUT_EXTENSION
#   ADDITIONAL_INCLUDES_FILES "${CMAKE_CURRENT_BINARY_DIR}/mdt_uicnumber_export.h"
  INCLUDES_DESTINATION ${MDT_INSTALL_INCLUDEDIR}
  EXPORT_NAME UicNumber
  EXPORT_NAMESPACE ${MDT_INSTALL_PACKAGE_NAME}::
  INSTALL_NAMESPACE ${MDT_INSTALL_PACKAGE_NAME}
  FIND_PACKAGE_PATHS ..
  VERSION ${PROJECT_VERSION}
  VERSION_COMPATIBILITY ExactVersion
  DEVELOPMENT_COMPONENT Mdt_UicNumber_Dev
)
