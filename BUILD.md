[[_TOC_]]

# Build MdtUicNumber - OLD

This chapter is like the previous (Install MdtUicNumber),
but covers some more details, like the dependencies and options to run the unit tests.

## Required tools and libraries

Some tools and libraries are required to build MdtUicNumber:
 - Git
 - CMake
 - Conan (optional)
 - A compiler (Gcc or Clang or MSVC)
 - Qt5 (optional, for Qt unit tests, can be managed by Conan)
 - Make (optional)

For a overview how to install them, see https://gitlab.com/scandyna/build-and-install-cpp

## Configure MdtUicNumber with Conan

Here is a list of available Conan options:

| Option           | Default | Possible Values  | Explanations |
| -----------------|:------- |:----------------:|--------------|
| shared           | True    |  [True, False]   | Build as shared library |


Install the dependencies:
```bash
conan install -s build_type=RelWithDebInfo --build=missing ..
```

Configure MdtUicNumber:
```bash
source activate.sh
cmake -DCMAKE_BUILD_TYPE=RelWithDebInfo -DBUILD_TESTS=ON -DCMAKE_INSTALL_PREFIX=~/opt/MdtUicNumber ..
cmake-gui .
```

It is also possible to run Qt tests.
Those tests do not need a very recent version of Qt,
so using the system wide installed one on Linux is sufficient.

To enable Qt support, add the `-DENABLE_QT_SUPPORT=ON` to the cmake configuration command line,
or enable it with cmake-gui.

## Build MdtUicNumber and run the tests

Build:
```bash
cmake --build . --config RelWithDebInfo
```

To run the tests:
```bash
ctest . --output-on-failure -C RelWithDebInfo -j4
```

Note that the `--config RelWithDebInfo` is only mandatory
for multi configuration build systems, like MSVC.

## Configure and build with ASan and UBSan

Install the dependencies:
```bash
conan install -s build_type=RelWithDebInfo --build=missing ..
```

Configure MdtUicNumber:
```bash
source activate.sh
cmake -DCMAKE_BUILD_TYPE=Instrumented -DBUILD_TESTS=ON -DCMAKE_INSTALL_PREFIX=~/opt/MdtUicNumber ..
cmake-gui .
```

Set the various options, like `BUILD_TYPE_INSTRUMENTED_OPTIMIZATION_LEVEL`,
`BUILD_TYPE_INSTRUMENTED_USE_DEBUG_SYMBOLS` and `BUILD_TYPE_INSTRUMENTED_DEFINE_NDEBUG`.

Build:
```bash
cmake --build . --config Instrumented
```
or:
```bash
make -j4
```

To run the tests:
```bash
ctest . --output-on-failure -C Instrumented -j4
```

## Configure and build with Clang

This requires modifications in the `settings_user.yml` Conan configuration,
and also some profile files.
See my [conan-config repository](https://gitlab.com/scandyna/conan-config) for more informations.

Install the dependencies:
```bash
conan install --profile linux_clang6.0_x86_64_libc++ -s build_type=RelWithDebInfo --build=missing ..
```

Configure MdtUicNumber:
```bash
source activate.sh
cmake ..
cmake-gui .
```

Build and run the tests:
```bash
make -j4
make test
```

# Build API doc

Install the dependencies:
```bash
conan install --output-folder . --profile:build $CONAN_PROFILE_BUILD --profile:host $CONAN_PROFILE_HOST --settings:build build_type=Release --settings:host build_type=Debug ..
```

Configure MdtUicNumber:
```bash
cmake -DCMAKE_TOOLCHAIN_FILE=conan_toolchain.cmake -DCMAKE_BUILD_TYPE=Debug -DBUILD_CPP_API_DOC=ON ..
```

Build the API doc:
```bash
doxygen
```
