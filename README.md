A basic OpenGL project using GLFW and GLAD.

## Dependencies
Run the following commands to install the required dependencies:
```bash
sudo apt update
sudo apt install -y cmake build-essential libglfw3-dev libgl-dev
```

## Building the Project

   ```bash
   mkdir build
   cd build
   cmake ..
   make
   ./openGlLearn
   ```

## Dependencies Overview
- **CMake**: Build system generator.
- **GLFW**: Window and input handling library.
- **GLAD**: OpenGL loader (included in the `include` and `src` directories).
- **OpenGL**: Graphics library for rendering.

