﻿# CMakeList.txt : CMake project for Vmc, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

project(Vmc)

include_directories("private")

# Add source to this project's executable.
add_executable (${PROJECT_NAME} "Vmc.cpp" "Vmc.h" "demoApp.cpp" "private/FlagRegister.h")
set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 20)

target_link_libraries(${PROJECT_NAME}
	vmc::identifiers
)

# TODO: Add tests and install targets if needed.
