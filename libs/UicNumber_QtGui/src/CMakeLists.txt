##############################################################
#  Copyright Philippe Steinmann 2020 - 2025.
#  Distributed under the Boost Software License, Version 1.0.
#  (See accompanying file LICENSE.txt or copy at
#  https://www.boost.org/LICENSE_1_0.txt)
##############################################################
include(GenerateExportHeader)
include(MdtInstallLibrary)

add_library(Mdt_UicNumber_QtGui
  Mdt/UicNumber/UicNumberValidator.cpp
)

add_library(Mdt::UicNumber_QtGui ALIAS Mdt_UicNumber_QtGui)


# if(BUILD_USE_IPO_LTO)
#   set_target_properties(Mdt_UicNumber_QtGui
#     PROPERTIES INTERPROCEDURAL_OPTIMIZATION TRUE
#   )
# endif()

target_include_directories(Mdt_UicNumber_QtGui
  PUBLIC
   $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
   $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}>
)

target_link_libraries(Mdt_UicNumber_QtGui
  PUBLIC
    Mdt::UicNumber_Qt Qt6::Gui
)

generate_export_header(Mdt_UicNumber_QtGui)

mdt_install_library(
  TARGET Mdt_UicNumber_QtGui
  RUNTIME_DESTINATION ${CMAKE_INSTALL_BINDIR}
  LIBRARY_DESTINATION ${CMAKE_INSTALL_LIBDIR}
  ARCHIVE_DESTINATION ${CMAKE_INSTALL_LIBDIR}
  INCLUDES_DIRECTORY .
  INCLUDES_FILE_WITHOUT_EXTENSION
  ADDITIONAL_INCLUDES_FILES "${CMAKE_CURRENT_BINARY_DIR}/mdt_uicnumber_qtgui_export.h"
  INCLUDES_DESTINATION ${MDT_INSTALL_INCLUDEDIR}
  EXPORT_NAME UicNumber_QtGui
  EXPORT_NAMESPACE ${MDT_INSTALL_PACKAGE_NAME}::
  INSTALL_NAMESPACE ${MDT_INSTALL_PACKAGE_NAME}
  FIND_PACKAGE_PATHS ..
  INSTALL_IS_UNIX_SYSTEM_WIDE ${MDT_INSTALL_IS_UNIX_SYSTEM_WIDE}
  VERSION ${PROJECT_VERSION}
  SOVERSION ${PROJECT_VERSION_MAJOR}
  VERSION_COMPATIBILITY ExactVersion
  RUNTIME_COMPONENT Mdt_UicNumber_Runtime
  DEVELOPMENT_COMPONENT Mdt_UicNumber_Dev
)
