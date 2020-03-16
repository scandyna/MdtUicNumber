##############################################################
#  Copyright Philippe Steinmann 2020 - 2020.
#  Distributed under the Boost Software License, Version 1.0.
#  (See accompanying file LICENSE.txt or copy at
#  https://www.boost.org/LICENSE_1_0.txt)
##############################################################
include(MdtAddTest)

mdt_add_test(
  NAME ErrorTest
  TARGET errorTest
  DEPENDENCIES Mdt::UicNumber Mdt::Catch2Main
  SOURCE_FILES
    src/ErrorTest.cpp
)

mdt_add_test(
  NAME AlgorithmTest
  TARGET algorithmTest
  DEPENDENCIES Mdt::UicNumber Mdt::Catch2Main
  SOURCE_FILES
    src/AlgorithmTest.cpp
)

mdt_add_test(
  NAME CheckDigitTest
  TARGET checkDigitTest
  DEPENDENCIES Mdt::UicNumber Mdt::Catch2Main
  SOURCE_FILES
    src/CheckDigitTest.cpp
)

mdt_add_test(
  NAME StringFormatValidationTest
  TARGET stringFormatValidationTest
  DEPENDENCIES Mdt::UicNumber Mdt::Catch2Main
  SOURCE_FILES
    src/StringFormatValidationTest.cpp
)

mdt_add_test(
  NAME UicNumberTest
  TARGET uicNumberTest
  DEPENDENCIES Mdt::UicNumber Mdt::Catch2Main
  SOURCE_FILES
    src/UicNumberTest.cpp
)
