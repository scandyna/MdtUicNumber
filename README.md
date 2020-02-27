# MdtUicNumber

C++ library to work with UIC numbers.

This library is based on informations found on the web, starting from
Wikipedia [UIC identification marking for tractive stock](https://en.wikipedia.org/wiki/UIC_identification_marking_for_tractive_stock)

# Usage

## Required tools and libraries

Some tools and libraries are required to use MdtUicNumber:
 - Git
 - CMake
 - Conan (optional)
 - A compiler (Gcc or Clang or MSVC)
 - Make (optional)

For a overview how to install them, see https://gitlab.com/scandyna/build-and-install-cpp

## Project description

In your source directory, create a CMakeLists.txt:
```cmake
cmake_minimum_required(VERSION 3.10)
project(MyApp)

find_package(Threads REQUIRED)
find_package(Mdt0 COMPONENTS UicNumber REQUIRED)

add_executable(myApp myApp.cpp)
target_link_libraries(myApp Mdt0::UicNumber)
```

## Project configuration with Conan

In your source directory, create a `conanfile.txt`:
```conan
[requires]
MdtUicNumber/x.y.z@scandyna/testing

[generators]
cmake_paths
```

Create a build directory and cd to it:
```bash
mkdir build
cd build
```

Install the dependencies:
```bash
conan install -s build_type=Release --build=missing ..
```

Configure your project:
```bash
cmake -DCMAKE_TOOLCHAIN_FILE=conan_paths.cmake -DCMAKE_BUILD_TYPE=Release ..
cmake-gui .
```

## Project configuration without Conan

Build MdtUicNumber (see below) and install it somewhere, for example in `~/opt/MdtUicNumber`.

Create a build directory and cd to it:
```bash
mkdir build
cd build
```

Configure your project:
```bash
cmake -DCMAKE_PREFIX_PATH=~/opt/MdtUicNumber -DCMAKE_BUILD_TYPE=Release ..
cmake-gui .
```

Build your project:
```bash
cmake --build . --config Release
```

Note that the `--config Release` is only mandatory
for multi configuration build systems, like MSVC.


# Install MdtUicNumber

This chapter covers only the installation of the library.
To run the unit tests, see the next chapter.

Get MdtUicNumber:
```bash
git clone git@gitlab.com:scandyna/mdtuicnumber.git
```

Create a build directory and cd to it:
```bash
mkdir build
cd build
```

## Note about install prefix

Some note on the `CMAKE_INSTALL_PREFIX`:
 - To target a system wide installation on Linux, set it to `/usr` (`-DCMAKE_INSTALL_PREFIX=/usr`) .
 - For other locations, spcecify also the <package-name>, (for example `-DCMAKE_INSTALL_PREFIX=~/opt/MdtUicNumber`).

For details about that, see:
 - https://scandyna.gitlab.io/mdt-cmake-modules/Modules/MdtInstallDirs.html
 - https://cmake.org/cmake/help/latest/variable/CMAKE_INSTALL_PREFIX.html
 - https://scandyna.gitlab.io/mdt-cmake-modules/Modules/MdtInstallLibrary.html

## Configure MdtUicNumber with Conan

Install the dependencies:
```bash
conan install -s build_type=Release --build=missing ..
```

Configure MdtUicNumber:
```bash
cmake -DCMAKE_TOOLCHAIN_FILE=conan_paths.cmake -DCMAKE_BUILD_TYPE=Release -DCMAKE_INSTALL_PREFIX=~/opt/MdtUicNumber ..
cmake-gui .
```

## Configure MdtUicNumber without Conan

MdtUicNumber requires mdt-cmake-modules.
To install it, see https://gitlab.com/scandyna/mdt-cmake-modules .

```bash
cmake -DCMAKE_PREFIX_PATH=path/to/mdt-cmake-modules -DCMAKE_BUILD_TYPE=Release -DCMAKE_INSTALL_PREFIX=~/opt/MdtUicNumber ..
cmake-gui .
```

## Build and install MdtUicNumber

To build and install, run:
```cmd
cmake --build . --target INSTALL --config Release
```

Note that the `--config Release` is only mandatory
for multi configuration build systems, like MSVC.


# Work on MdtUicNumber

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
| build_tests      | False   |  [True, False]   | If True, will also require Catch2 |

Install the dependencies:
```bash
conan install -s build_type=RelWithDebInfo -o build_tests=True --build=missing ..
```

Configure MdtUicNumber:
```bash
cmake -DCMAKE_TOOLCHAIN_FILE=conan_paths.cmake -DCMAKE_BUILD_TYPE=RelWithDebInfo -DBUILD_TESTS=ON -DCMAKE_INSTALL_PREFIX=~/opt/MdtUicNumber ..
cmake-gui .
```

It is also possible to run Qt tests.
Those tests do not need a very recent version of Qt,
so using the system wide installed one on Linux is sufficient.

To enable Qt test, add the `-DBUILD_QT_TESTS=ON` to the cmake configuration command line,
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
conan install -s build_type=RelWithDebInfo -o build_tests=True --build=missing ..
```

Configure MdtUicNumber:
```bash
cmake -DCMAKE_TOOLCHAIN_FILE=conan_paths.cmake -DCMAKE_BUILD_TYPE=Instrumented -DBUILD_TESTS=ON -DCMAKE_INSTALL_PREFIX=~/opt/MdtUicNumber ..
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
