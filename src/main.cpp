#include <glad/glad.h> //include glad before glfw as glfw needs glad to access opengl
#include <GLFW/glfw3.h>
#include <iostream>

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *window);

int main(){
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); // can't user lower version number then 3
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); // core profile limits opengl functions to modern ones

    GLFWwindow* window = glfwCreateWindow(800, 600, "dask", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }
    // Behind the scenes OpenGL uses the data specified via glViewport to transform the 2D coordinates
    // it processed to coordinates on your screen. For example, a processed point of location (-0.5,0.5)
    // would (as its final transformation) be mapped to (200,450) in screen coordinates. Note that processed
    // coordinates in OpenGL are between -1 and 1 so we effectively map from the range (-1 to 1) to (0, 800) and (0, 600).
    glViewport(0, 0, 800, 600); //tell opengl the window size


    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    while(!glfwWindowShouldClose(window))
    {
        processInput(window);

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT); // make the buffer set all pixel to ClearColor

        glfwSwapBuffers(window); //swaps the color buffer, a large 2D buffer of color values for each pixel
        glfwPollEvents(); //checks keyboard/mouse events
    }

    glfwTerminate();
    return 0;
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    // Adjust the viewport to the new window size
    glViewport(0, 0, width, height);
}
void processInput(GLFWwindow *window)
{
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}
