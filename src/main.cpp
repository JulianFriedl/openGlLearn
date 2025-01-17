#include <glad/glad.h> //include glad before glfw as glfw needs glad to access opengl
#include <GLFW/glfw3.h>
#include <iostream>

const char *vertexShaderSource = "#version 330 core\n"
    "layout (location = 0) in vec3 aPos;\n"
    "void main()\n"
    "{\n"
    "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
    "}\0";

const char *fragmentShaderSource = "#version 330 core\n"
    "out vec4 FragColor;\n"
    "void main()\n"
    "{\n"
        "FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
    "}\0";

const char *fragmentShaderSource_yellow = "#version 330 core\n"
    "out vec4 FragColor;\n"
    "void main()\n"
    "{\n"
        "FragColor = vec4(0.6f, 0.6f, 0.3f, 1.0f);\n"
    "}\0";

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

    // setup vertex shader
    // The main purpose of the vertex shader is to transform 3D coordinates into different 3D coordinates
    // (more on that later) and the vertex shader allows us to do some basic processing on the vertex attributes.
    unsigned int vertexShader;
    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    // The glShaderSource function takes the shader object to compile to as its first argument.
    // The second argument specifies how many strings we're passing as source code, which is only one.
    // The third parameter is the actual source code of the vertex shader
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);

    // check for errors on compilation
    int  success;
    char infoLog[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);

    if(!success)
    {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
    }

    // setup fragment shader
    // The main purpose of the fragment shader is to calculate the final color of a pixel and this is
    // usually the stage where all the advanced OpenGL effects occur. Usually the fragment shader contains
    // data about the 3D scene that it can use to calculate the final pixel color (like lights, shadows,
    // color of the light and so on)
    unsigned int fragmentShader;
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);

    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if(!success)
    {
        glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
    }


    unsigned int fragmentShader_yellow;
    fragmentShader_yellow = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader_yellow, 1, &fragmentShaderSource_yellow, NULL);
    glCompileShader(fragmentShader_yellow);

    glGetShaderiv(fragmentShader_yellow, GL_COMPILE_STATUS, &success);
    if(!success)
    {
        glGetShaderInfoLog(fragmentShader_yellow, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
    }

    // Shader Program
    unsigned int shaderProgram;
    shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if(!success) {
        glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::PROGRAM::COMPILATION_FAILED\n" << infoLog << std::endl;
    }


    unsigned int shaderProgram2;
    shaderProgram2 = glCreateProgram();
    glAttachShader(shaderProgram2, vertexShader);
    glAttachShader(shaderProgram2, fragmentShader_yellow);
    glLinkProgram(shaderProgram2);

    glGetProgramiv(shaderProgram2, GL_LINK_STATUS, &success);
    if(!success) {
        glGetProgramInfoLog(shaderProgram2, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::PROGRAM2::COMPILATION_FAILED\n" << infoLog << std::endl;
    }


    // After linking the shader program, the shader obj are no longer needed
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
    glDeleteShader(fragmentShader_yellow);

    // specify vertex data layout

    // The first parameter specifies which vertex attribute we want to configure.
    // Remember that we specified the location of the position vertex attribute in the vertex shader
    // with layout (location = 0). This sets the location of the vertex attribute to 0
    // and since we want to pass data to this vertex attribute, we pass in 0
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);


    float vertices[] = {
        0.5f,  0.5f, 0.0f,  // top right
        0.5f, -0.5f, 0.0f,  // bottom right
        -0.5f, -0.5f, 0.0f,  // bottom left
        -0.5f,  0.5f, 0.0f   // top left
    };

    float vertices_triangle_1[] = {
        -0.5f,  -0.5f, 0.0f,
        -0.25f,  0.5f, 0.0f,
        0.0f,  -0.5f, 0.0f,
    };

    float vertices_triangle_2[] = {
        0.0f,  0.0f, 0.0f,
        0.25f,  0.5f, 0.0f,
        0.5f,  0.0f, 0.0f,
    };


    unsigned int VBO1, VBO2; // id for opengl obj
    glGenBuffers(1, &VBO1); // gen opengl obj
    glGenBuffers(1, &VBO2);

    // Usually when you have multiple objects you want to draw, you first generate/configure
    // all the VAOs (and thus the required VBO and attribute pointers) and store those for later use.
    // The moment we want to draw one of our objects, we take the corresponding VAO, bind it,
    // then draw the object and unbind the VAO again
    unsigned int VAO1, VAO2;
    glGenVertexArrays(1, &VAO1);
    glGenVertexArrays(1, &VAO2);

    // 1. bind Vertex Array Object
    glBindVertexArray(VAO1);
    // The GL_ARRAY_BUFFER target for buffer objects represents the intent to use that buffer
    // object for vertex attribute data. However, binding to this target alone doesn't do anything;
    // it's only the call to glVertexAttribPointer (or equivalent functions) that uses whatever buffer
    // was bound to that target for the attribute data for that attribute.
    // 2. copy our vertices array in a buffer for OpenGL to use
    glBindBuffer(GL_ARRAY_BUFFER, VBO1);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices_triangle_1), vertices_triangle_1, GL_STATIC_DRAW);

    // 4. then set our vertex attributes pointers
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    // You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
    // VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
    glBindVertexArray(0);


    glBindVertexArray(VAO2);
    glBindBuffer(GL_ARRAY_BUFFER, VBO2);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices_triangle_2), vertices_triangle_2, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glBindVertexArray(0);

    // Wirefram mode
    // glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    while(!glfwWindowShouldClose(window))
    {
        processInput(window);

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT); // make the buffer set all pixel to ClearColor

        glUseProgram(shaderProgram);

        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        glBindVertexArray(VAO1);
        glDrawArrays(GL_TRIANGLES, 0, 6);

        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
        glUseProgram(shaderProgram2);
        glBindVertexArray(VAO2);
        glDrawArrays(GL_TRIANGLES, 0, 6);

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
