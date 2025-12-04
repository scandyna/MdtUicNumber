##############################################################
#  Copyright Philippe Steinmann 2020 - 2025.
#  Distributed under the Boost Software License, Version 1.0.
#  (See accompanying file LICENSE.txt or copy at
#  https://www.boost.org/LICENSE_1_0.txt)
##############################################################
cmake_minimum_required(VERSION 3.22)
project(MdtUicNumberTest)

find_package(MdtCMakeModules REQUIRED)
find_package(Mdt0 COMPONENTS UicNumber REQUIRED)

include(MdtAddTest)

enable_testing()

mdt_add_test(
  NAME RunSimpleApp
  TARGET simpleApp
  DEPENDENCIES Mdt0::UicNumber
  SOURCE_FILES
    main.cpp
)
