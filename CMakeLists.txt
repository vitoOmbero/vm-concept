# CMakeList.txt : Top-level CMake project file, do global configuration
# and include sub-projects here.
#
cmake_minimum_required (VERSION 3.8)

project ("Virtual Machine Concept")

# Include sub-projects.
add_subdirectory ("Identifiers")
add_subdirectory ("Vmc")
add_subdirectory ("Asmc")