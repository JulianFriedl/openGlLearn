cmake_minimum_required(VERSION 3.10)

# Enable export of compile_commands.json
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Project name
project(openGlLearn)

# C++ standard
set(CMAKE_CXX_STANDARD 17)

set(OpenGL_GL_PREFERENCE GLVND)

# Add source files
add_executable(openGlLearn src/main.cpp src/glad.c)

# Include directories
target_include_directories(openGlLearn PRIVATE include)

# Link libraries
find_package(OpenGL REQUIRED)
find_package(glfw3 REQUIRED)
target_link_libraries(openGlLearn OpenGL::GL glfw)
