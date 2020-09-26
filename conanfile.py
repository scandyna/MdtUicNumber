from conans import ConanFile, CMake, tools
import os


class MdtUicNumberConan(ConanFile):
  name = "MdtUicNumber"
  #version = "0.1"
  license = "BSD 3-Clause"
  url = "https://gitlab.com/scandyna/mdtuicnumber"
  description = "C++ library to work with UIC numbers"
  settings = "os", "compiler", "build_type", "arch"
  options = {"build_tests": [True, False]}
  default_options = {"build_tests": False}
  requires = "MdtCMakeModules/[>=0.14.3]@scandyna/testing"
  generators = "cmake_paths", "virtualenv"
  exports_sources = "libs/*", "CMakeLists.txt", "conanfile.py", "LICENSE.txt"
  # If no_copy_source is False, conan copies sources to build directory and does in-source build,
  # resulting having build files installed in the package
  # See also: https://github.com/conan-io/conan/issues/350
  no_copy_source = True

  def set_version(self):
    if os.path.exists(".git"):
      git = tools.Git()
      self.version = "%s" % (git.get_tag())

  def requirements(self):

    if self.options.build_tests:
      self.requires("Catch2/[>=2.11.1]@catchorg/stable")


  def package_id(self):
    del self.info.options.build_tests


  def configure_cmake(self):
    cmake = CMake(self)
    cmake.definitions["FROM_CONAN_PROJECT_VERSION"] = self.version
    cmake.definitions["CMAKE_TOOLCHAIN_FILE"] = "%s/conan_paths.cmake" % (self.build_folder)
    cmake.definitions["ENABLE_QT_SUPPORT"] = "ON"
    cmake.definitions["WARNING_AS_ERROR"] = "ON"
    return cmake


  def build(self):
    cmake = self.configure_cmake()
    cmake.configure()
    cmake.build()


  def package(self):
    cmake = self.configure_cmake()
    cmake.install()
