from conan import ConanFile
from conan.tools.cmake import CMakeToolchain, CMakeDeps, CMake, cmake_layout
from conan.tools.files import copy
import os


class MdtUicNumberQtCoreConan(ConanFile):
  name = "mdtuicnumber_qtgui"
  license = "BSD 3-Clause"
  url = "https://gitlab.com/scandyna/mdtuicnumber"
  description = "C++ library to work with UIC numbers"
  settings = "os", "compiler", "build_type", "arch"
  options = {"shared": [True, False]}
  default_options = {"shared": True}
  package_type = "library"
  generators = "CMakeDeps", "VirtualBuildEnv"

  def set_version(self):
    if not self.version:
      self.version = "0.0.0"

  def layout(self):
    cmake_layout(self)

  def requirements(self):
    self.requires("mdtcmakeconfig/0.2.3@scandyna/testing")
    self.requires(f"mdtuicnumber_qtcore/{self.version}@scandyna/testing", transitive_headers=True)
    self.requires("qt/5.15.16", transitive_headers=True, transitive_libs=True)

  def build_requirements(self):
    self.test_requires("mdtcmakemodules/0.21.0@scandyna/testing")

  def export_sources(self):
    source_root = os.path.join(self.recipe_folder, "../../../")
    copy(self, "LICENSE.txt", source_root, self.export_sources_folder)
    copy(self, "CMakeLists.txt", source_root, self.export_sources_folder)
    copy(self, "libs/UicNumber_QtGui/*", source_root, self.export_sources_folder)

  def generate(self):
    tc = CMakeToolchain(self)
    tc.variables["FROM_CONAN_PROJECT_VERSION"] = self.version
    tc.variables["BUILD_UIC_NUMBER"] = "OFF"
    tc.variables["BUILD_UIC_NUMBER_QT_CORE"] = "OFF"
    tc.variables["BUILD_UIC_NUMBER_QT_GUI"] = "ON"
    tc.variables["USE_UIC_NUMBER_IMPORT_TARGET"] = "ON"
    tc.variables["USE_UIC_NUMBER_QT_CORE_IMPORT_TARGET"] = "ON"
    tc.generate()

  def build(self):
    cmake = CMake(self)
    cmake.configure()
    cmake.build()

  def package(self):
    cmake = CMake(self)
    cmake.install()

  def package_id(self):
    self.info.clear()

  def package_info(self):
    # self.cpp_info.bindirs = []
    # self.cpp_info.libdirs = []
    # self.cpp_info.includedirs = ['include']
    self.cpp_info.libs = ["Mdt0UicNumber_QtGui"]
    self.cpp_info.set_property("cmake_file_name", "Mdt0UicNumber_QtGui")
    self.cpp_info.set_property("cmake_target_name", "Mdt0::UicNumber_QtGui")
