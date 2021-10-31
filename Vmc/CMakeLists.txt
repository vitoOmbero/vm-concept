# CMakeList.txt : CMake project for Vmc, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

include_directories("private")

# Add source to this project's executable.
add_executable (Vmc "Vmc.cpp" "Vmc.h" "demoApp.cpp" "private/FlagRegister.h")
set_property(TARGET Vmc PROPERTY CXX_STANDARD 20)

# TODO: Add tests and install targets if needed.
