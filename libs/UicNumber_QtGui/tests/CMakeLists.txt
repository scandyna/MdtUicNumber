##############################################################
#  Copyright Philippe Steinmann 2020 - 2020.
#  Distributed under the Boost Software License, Version 1.0.
#  (See accompanying file LICENSE.txt or copy at
#  https://www.boost.org/LICENSE_1_0.txt)
##############################################################
include(MdtAddTest)

# mdt_add_test(
#   NAME UicNumberValidatorTest
#   TARGET uicNumberValidatorTest
#   DEPENDENCIES Mdt::UicNumber_QtGui Qt5::Test Qt5::Widgets
#   SOURCE_FILES
#     src/UicNumberValidatorTest.cpp
# )
# mdt_set_test_asan_options(
#   NAME UicNumberValidatorTest
#   OPTIONS
# )

add_executable(uicNumberValidatorTest src/UicNumberValidatorTest.cpp)
target_link_libraries(uicNumberValidatorTest PRIVATE Mdt::UicNumber_QtGui Qt5::Test Qt5::Widgets)
add_test(NAME UicNumberValidatorTest COMMAND uicNumberValidatorTest)
