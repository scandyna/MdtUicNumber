[[_TOC_]]

# MdtUicNumber

C++ library to work with UIC numbers.

This library is based on informations found on the web, starting from
Wikipedia [UIC identification marking for tractive stock](https://en.wikipedia.org/wiki/UIC_identification_marking_for_tractive_stock)

This project is composed in some libraries:

| Package           | CMake target         | Description               | Main dependency |
|:------------------|:---------------------|:--------------------------|:----------------|
|mdtuicnumber       |Mdt0::UicNumber       |Core lib                   |None             |
|mdtuicnumber_qtcore|Mdt0::UicNumber_Qt    |Mainly adds unicode support|QtCore           |
|mdtuicnumber_qtgui |Mdt0::UicNumber_QtGui |Mainly offers QValidators  |QtGui            |

Note: the `Mdt0::UicNumber_Qt` target is wrongly named, and could change in the future.
See: https://gitlab.com/scandyna/mdtuicnumber/-/issues/3

# Usage

For the available classes, functions, and their usage,
see [the API documentation](https://scandyna.gitlab.io/mdtuicnumber)

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
cmake_minimum_required(VERSION 3.22)
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
mdtuicnumber/x.y.z@scandyna/testing

[generators]
CMakeDeps
CMakeToolchain
VirtualBuildEnv
```

Create a build directory and cd to it:
```bash
mkdir build
cd build
```

Install the dependencies:
```bash
conan install --output-folder . --profile:build $CONAN_PROFILE_BUILD --profile:host $CONAN_PROFILE_HOST --settings:build build_type=Release --settings:host build_type=$BUILD_TYPE --options:host "&:shared=$BUILD_SHARED_LIBS"  ..
```

Activate the build environment:
```bash
source conanbuild.sh
```

Configure your project:
```bash
cmake -DCMAKE_TOOLCHAIN_FILE=conan_toolchain.cmake -DCMAKE_BUILD_TYPE=Release ..
cmake-gui .
```

To restore the standard environment:
```bash
source deactivate_conanbuild.sh
```

# Work on MdtUicNumber

## Build

See [BUILD](BUILD.md).

## Create Conan package

See [README](packaging/conan/README.md) in the conan packaging folder.


# OLD stuff

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
source activate.sh
cmake -DCMAKE_BUILD_TYPE=Release -DCMAKE_INSTALL_PREFIX=~/opt/MdtUicNumber ..
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
