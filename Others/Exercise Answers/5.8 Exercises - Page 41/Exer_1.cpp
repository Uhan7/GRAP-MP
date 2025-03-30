/*
1. Try to draw 2 triangles next to each other
using glDrawArrays
by adding more vertices to your data.

Solution: /src/1.getting_started/2.3.hello_triangle_ exercise1/.
*/

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>

// Resizing Window
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

// Receiving Inputs
void processInput(GLFWwindow *window)
{
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

// Vertex Shader (for now)
const char *vertexShaderSource =
    "#version 330 core\n"
    "layout (location = 0) in vec3 aPos;\n"
    "void main()\n"
    "{\n"
    " gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
    "}\0";

// Fragment Shader (for now)
const char *fragmentShaderSource =
    "#version 330 core\n"
    "out vec4 FragColor;\n"
    "void main() {\n"
    "FragColor = vec4(0.8f, 0.9f, 0.5f, 1.0f);\n"
    "}\0";

int main()
{
    // Setting Up
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    // Window Stuff
    GLFWwindow* window = glfwCreateWindow(800, 600, "Epik Kart Deluxe HD", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);

    // Resize Viewport when Scaling Window
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    // Load GLAD
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    // Shaders
    unsigned int vertexShader;
    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);

    unsigned int fragmentShader;
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);

    // Shader Program for Linking
    unsigned int shaderProgram;
    shaderProgram = glCreateProgram();

    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    // Use Program, so every shader and rendering call will use our shaderProgram
    // glUseProgram(shaderProgram);
    // commented it out for now so I can change shaders while it runs

    // Delete unused shaders (since we already have shaderProgram)
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    // Define Vertices
    float vertices[] = {
        -1.0f, -0.5f, 0.0f,
        -0.5f,  0.5f, 0.0f,
         0.0f, -0.5f, 0.0f,

         0.0f,  0.5f, 0.0f,
         0.5f, -0.5f, 0.0f,
         1.0f,  0.5f, 0.0f
    };

    // unsigned int indices[] = {
    //     0, 1, 2, // First Triangle
    //     3, 4, 5  // Second Triangle
    // };


    // Let's store a VBO in our GPU
    unsigned int VBO;
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // Also create a VAO
    unsigned int VAO;
    glGenVertexArrays(1, &VAO);

    glBindVertexArray(VAO);

    // Tell OpenGL How to Interpret Vertex Data
    glVertexAttribPointer(
        0,                  // location = 0
        3,                  // 3 values in vec3
        GL_FLOAT,           // data type, we used float
        GL_FALSE,           // normalize?
        3 * sizeof(float),  // the "stride" between consecutive vertex attributes
        (void*)0            // offset where it begins, just keep it at the start
    );
    glEnableVertexAttribArray(0);   // again, location = 0

    // Then an EBO because we're cool like that
    // unsigned int EBO;
    // glGenBuffers(1, &EBO);

    // glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    // glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    // Render Loop every FRAME
    while(!glfwWindowShouldClose(window))
    {
        // Input
        processInput(window);

        // Rendering
        glClearColor(0.2f, 0.1f, 0.5f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        // glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        glUseProgram(shaderProgram);
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 6);

        //Check Events and Swap Buffers
        glfwPollEvents();
        glfwSwapBuffers(window);
    }

    glfwTerminate();

    return 0;
}