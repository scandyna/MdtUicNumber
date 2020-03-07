##############################################################
#  Copyright Philippe Steinmann 2020 - 2020.
#  Distributed under the Boost Software License, Version 1.0.
#  (See accompanying file LICENSE.txt or copy at
#  https://www.boost.org/LICENSE_1_0.txt)
##############################################################
include(MdtAddTest)

mdt_add_test(
  NAME ErrorQtTest
  TARGET errorQtTest
  DEPENDENCIES Mdt::UicNumber_Qt Mdt::Catch2Main
  SOURCE_FILES
    src/ErrorQtTest.cpp
)

mdt_add_test(
  NAME AlgorithmQStringTest
  TARGET algorithmQStringTest
  DEPENDENCIES Mdt::UicNumber_Qt Mdt::Catch2Main
  SOURCE_FILES
    src/AlgorithmQStringTest.cpp
)

mdt_add_test(
  NAME UicNumberQStringTest
  TARGET uicNumberQStringTest
  DEPENDENCIES Mdt::UicNumber_Qt Mdt::Catch2Main
  SOURCE_FILES
    src/UicNumberQStringTest.cpp
)
