//
//  main.cpp
//  Chess-Board
//
//  Created by Chas Ladhar on 19/05/2024.
//

#include <iostream>

// GLEW
#include <GL/glew.h>

// GLFW
#include <GLFW/glfw3.h>

// Window dimensions
// Use GLint over regular int as GLint is consistent length on any compiler
const GLint WIDTH = 800, HEIGHT = 600;

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

void processInput(GLFWwindow *window)
{
    // Check if the user has pressed the escape key
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

int main(int argc, const char * argv[]) {
    
    // Init GLFW
    glfwInit();
    
    // GLFW Properties
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    
    // Required for MacOS otherwise it will crash
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    
    // Set window to be resizable
    glfwWindowHint(GLFW_RESIZABLE, GL_TRUE);
    
    
    // Create a GLFWwindow object that we can use for GLFW's functions
    GLFWwindow *window = glfwCreateWindow(WIDTH, HEIGHT, "Chess-Board", nullptr, nullptr);
    
    int screenWidth, screenHeight;
    
    glfwGetFramebufferSize( window, &screenWidth, &screenHeight );
    
    
    // Check that window was created successfully
    if (nullptr == window)
    {
           std::cout << "Failed to create GLFW window" << std::endl;
           glfwTerminate();

           return -1;
    }
    
    glfwMakeContextCurrent(window);
    
    // Define the viewport dimensions
    // First two parameters set location of lower left corner of window.
    // Third and fourth parameter set the width and height of the rendering window in pixels.
    // Note that processed coordinates in OpenGL are between -1 and 1 so we effectively map from the range (-1 to 1) to (0, WIDTH) and (0, HEIGHT).
    glViewport(0, 0, screenWidth, screenHeight);
    
    // Whenever window changes in size, GLFW calls this function. We register the function here
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    
    // Game loop
    while (!glfwWindowShouldClose(window))
    {
        // Clear previous buffer ready for next buffer
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        
        // input
        processInput(window);
        
        // Rendering Commands, remember OpenGL is all about transforming 3D coordinates, to 2D pixels that fit on our screen.
        
        
        
        
        
        
        
        
        
        
        // Swaps old buffer for new buffer. (We write to the back buffer while front buffer is being shown, then when back buffer is ready, we swap the two buffers)
        glfwSwapBuffers(window);
        
        // Checks if any events are triggered (keyboard, moust input e.g.) and updates window state by calling the corresponding callback methods which we register outside the loop.
        glfwPollEvents();
        
    }
    
    // Terminate GLFW, clearing any resources allocated by GLFW.
    glfwTerminate();
     
    return 0;

}



