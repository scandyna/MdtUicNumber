##############################################################
#  Copyright Philippe Steinmann 2020 - 2025.
#  Distributed under the Boost Software License, Version 1.0.
#  (See accompanying file LICENSE.txt or copy at
#  https://www.boost.org/LICENSE_1_0.txt)
##############################################################
include(MdtAddTest)

mdt_add_test(
  NAME UicNumberValidatorTest
  TARGET uicNumberValidatorTest
  DEPENDENCIES Mdt::UicNumber_QtGui Qt6::Test Qt6::Widgets
  SOURCE_FILES
    src/UicNumberValidatorTest.cpp
)
# mdt_set_test_asan_options(
#   NAME UicNumberValidatorTest
#   OPTIONS
# )

# GL-4 (https://gitlab.com/scandyna/mdtuicnumber/-/issues/4)
if(SANITIZER_ENABLE_ADDRESS)
  set_tests_properties(UicNumberValidatorTest PROPERTIES DISABLED YES)
endif()
