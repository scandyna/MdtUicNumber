##############################################################
#  Copyright Philippe Steinmann 2020 - 2025.
#  Distributed under the Boost Software License, Version 1.0.
#  (See accompanying file LICENSE.txt or copy at
#  https://www.boost.org/LICENSE_1_0.txt)
##############################################################
include(GenerateExportHeader)
include(MdtInstallLibrary)

add_library(Mdt_UicNumber_Qt INTERFACE)
add_library(Mdt::UicNumber_Qt ALIAS Mdt_UicNumber_Qt)

# target_compile_features(Mdt_UicNumber_Qt PUBLIC cxx_std_17)

# if(BUILD_USE_IPO_LTO)
#   set_target_properties(Mdt_UicNumber_Qt
#     PROPERTIES INTERPROCEDURAL_OPTIMIZATION TRUE
#   )
# endif()

target_include_directories(Mdt_UicNumber_Qt
  INTERFACE
   $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
   $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}>
)

target_link_libraries(Mdt_UicNumber_Qt
  INTERFACE
    Mdt::UicNumber Qt6::Core
)

# generate_export_header(Mdt_UicNumber_Qt)

mdt_install_interface_library(
  TARGET Mdt_UicNumber_Qt
  LIBRARY_DESTINATION ${CMAKE_INSTALL_LIBDIR}
  INCLUDES_DIRECTORY .
  INCLUDES_FILE_WITHOUT_EXTENSION
#   ADDITIONAL_INCLUDES_FILES "${CMAKE_CURRENT_BINARY_DIR}/mdt_uicnumber_export.h"
  INCLUDES_DESTINATION ${MDT_INSTALL_INCLUDEDIR}
  EXPORT_NAME UicNumber_Qt
  EXPORT_NAMESPACE ${MDT_INSTALL_PACKAGE_NAME}::
  INSTALL_NAMESPACE ${MDT_INSTALL_PACKAGE_NAME}
  FIND_PACKAGE_PATHS ..
  VERSION ${PROJECT_VERSION}
  VERSION_COMPATIBILITY ExactVersion
  DEVELOPMENT_COMPONENT Mdt_UicNumber_Dev
)
