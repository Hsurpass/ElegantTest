from conans import ConanFile, CMake

class MyProjectConan(ConanFile):
    name = "my_project"
    version = "1.0"
    settings = "os", "compiler", "build_type", "arch"
    generators = "cmake"
    requires = (
        "fmt/8.1.1",
        "spdlog/1.10.0"
    )

    def build(self):
        cmake = CMake(self)
        cmake.configure()
        cmake.build()
