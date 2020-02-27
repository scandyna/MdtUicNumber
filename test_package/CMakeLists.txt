##############################################################
#  Copyright Philippe Steinmann 2020 - 2020.
#  Distributed under the Boost Software License, Version 1.0.
#  (See accompanying file LICENSE.txt or copy at
#  https://www.boost.org/LICENSE_1_0.txt)
##############################################################

find_package(MdtCMakeModules REQUIRED)
find_package(Mdt0 COMPONENTS UicNumber REQUIRED)

add_executable(simpleApp test_package.cpp)
target_link_libraries(simpleApp Mdt0::UicNumber)

enable_testing()

include(MdtRuntimeEnvironment)

add_test(NAME RunSimpleApp COMMAND simpleApp)
mdt_set_test_library_env_path(NAME RunSimpleApp TARGET simpleApp)
