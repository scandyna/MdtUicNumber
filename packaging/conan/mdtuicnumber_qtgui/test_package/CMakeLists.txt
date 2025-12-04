##############################################################
#  Copyright Philippe Steinmann 2020 - 2025.
#  Distributed under the Boost Software License, Version 1.0.
#  (See accompanying file LICENSE.txt or copy at
#  https://www.boost.org/LICENSE_1_0.txt)
##############################################################
cmake_minimum_required(VERSION 3.22)
project(MdtUicNumberQuiTest)

find_package(MdtCMakeModules REQUIRED)
find_package(Mdt0 COMPONENTS UicNumber_QtGui REQUIRED)

include(MdtAddTest)

enable_testing()

mdt_add_test(
  NAME UicNumberQtGuiTest
  TARGET uicNumberQtGuiTest
  DEPENDENCIES Mdt0::UicNumber_QtGui Qt5::Widgets
  SOURCE_FILES
    main.cpp
)
