cmake_minimum_required(VERSION 3.10)

# Enable export of compile_commands.json
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Project name
project(openGlLearn)

# C++ standard
set(CMAKE_CXX_STANDARD 17)

set(OpenGL_GL_PREFERENCE GLVND)

# Add source files and create executables
add_executable(triangles src/triangles.cpp src/glad.c)
add_executable(shaders src/shaders.cpp src/glad.c)

# Include directories
target_include_directories(triangles PRIVATE include)
target_include_directories(shaders PRIVATE include)

# Link libraries
find_package(OpenGL REQUIRED)
find_package(glfw3 REQUIRED)
target_link_libraries(triangles OpenGL::GL glfw)
target_link_libraries(shaders OpenGL::GL glfw)
