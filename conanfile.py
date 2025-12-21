from conan import ConanFile
from conan.tools.env import VirtualBuildEnv
from conan.tools.cmake import CMakeToolchain, CMakeDeps, CMake

# This recipe is only to install dependencies to build MdtUicNumber
# The recipes to create packages are in packaging/conan/ subfolder
class MdtUicNumberConan(ConanFile):
  name = "mdtuicnumber"
  license = "BSD 3-Clause"
  url = "https://gitlab.com/scandyna/mdtuicnumber"
  description = "C++ library to work with UIC numbers"
  settings = "os", "compiler", "build_type", "arch"
  options = {"shared": [True, False]}
  default_options = {"shared": True}
  generators = "CMakeDeps", "VirtualBuildEnv"

  def requirements(self):
    self.requires("qt/6.8.3")

  def build_requirements(self):
    self.test_requires("catch2/2.13.10")
    self.test_requires("mdtcmakemodules/0.22.0@scandyna/testing")

  def generate(self):
    tc = CMakeToolchain(self)
    # tc.variables["FROM_CONAN_PROJECT_VERSION"] = self.version
    # tc.variables["ENABLE_QT_SUPPORT"] = "ON"
    tc.generate()
