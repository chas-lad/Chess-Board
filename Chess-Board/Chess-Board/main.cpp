#include <iostream>
#include <vector>
#include "shader.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "board.h"

// Window dimensions
const GLint WIDTH = 800, HEIGHT = 600;

void framebuffer_size_callback(GLFWwindow* window, int width, int height);


int main(int argc, const char * argv[]) {
    // Initialize GLFW
    if (!glfwInit()) {
        std::cout << "Failed to initialize GLFW" << std::endl;
        return -1;
    }

    // GLFW Properties
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // Required for MacOS

    // Set window to be resizable
    glfwWindowHint(GLFW_RESIZABLE, GL_TRUE);

    // Create a GLFW window
    GLFWwindow *window = glfwCreateWindow(WIDTH, HEIGHT, "Chess-Board", nullptr, nullptr);
    if (!window) {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);

    // Initialize GLEW
    GLenum err = glewInit();
    if (GLEW_OK != err) {
        std::cout << "Error: " << glewGetErrorString(err) << std::endl;
        return -1;
    }

    // Set viewport dimensions
    int screenWidth, screenHeight;
    glfwGetFramebufferSize(window, &screenWidth, &screenHeight);
    glViewport(0, 0, screenWidth, screenHeight);

    // Register framebuffer size callback
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    // Build and compile shader program
    Shader ourShader("vertex.vs", "fragment.fs");

    // Set up vertex data (and buffer(s)) and configure vertex attributes
    std::vector<float> vertices;
    createChessboard(vertices);

    unsigned int VBO, VAO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), vertices.data(), GL_STATIC_DRAW);

    // Position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // Color attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    
    // Inside your main function
    // Define orthographic projection matrix
    float left = -4.0f;
    float right = 4.0f;
    float bottom = -4.0f;
    float top = 4.0f;
    float near_plane = -1.0f;
    float far_plane = 1.0f;

    float projectionMatrix[4][4] = {
        {2.0f / (right - left), 0.0f, 0.0f, -(right + left) / (right - left)},
        {0.0f, 2.0f / (top - bottom), 0.0f, -(top + bottom) / (top - bottom)},
        {0.0f, 0.0f, -2.0f / (far_plane - near_plane), -(far_plane + near_plane) / (far_plane - near_plane)},
        {0.0f, 0.0f, 0.0f, 1.0f}
    };

    // Set projection matrix in shader
    ourShader.use();
    glUniformMatrix4fv(glGetUniformLocation(ourShader.ID, "projection"), 1, GL_FALSE, &projectionMatrix[0][0]);


    while (!glfwWindowShouldClose(window)) {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // Render the chessboard
        ourShader.use();
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, vertices.size() / 6);

        // Swap buffers and poll IO events
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // Clean up
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);

    // Terminate GLFW
    glfwTerminate();

    return 0;
}

// Framebuffer size callback function
void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}
