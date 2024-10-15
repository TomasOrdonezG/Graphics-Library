#include "game.h"

namespace Game
{

    glm::ivec2 windowDimensions;
    GLFWwindow *window = NULL;
    bool isInitialized = false;
    std::vector<Shape*> shapes;

    void framebuffer_size_callback(GLFWwindow* window, int width, int height)
    {
        windowDimensions = glm::ivec2(width, height);
        glViewport(0, 0, width, height);
    }

    void loop()
    {
        while (!glfwWindowShouldClose(window))
        {
            glClear(GL_COLOR_BUFFER_BIT);

            for (Shape *shape : shapes)
            {
                shape->perFrame(0.1);
                shape->draw();
            }

            // * Game logic goes here
            
            glfwSwapBuffers(window);
            glfwPollEvents();
        }
    }

    void add(Shape *shape)
    {
        shapes.push_back(shape);
    }

    void start(int w, int h, const char *title)
    {
        // Check if game is initialized, it should not be
        if (isInitialized)
        {
            fprintf(stderr, "Error: `start` called with already initialized window\n");
            exit(1);
        }
        
        if (!glfwInit())
        {
            fprintf(stderr, "Error: Failed to initialize GLFW\n");
            exit(1);
        }

        // Set dimensions and create window
        windowDimensions = glm::ivec2(w, h);
        window = glfwCreateWindow(windowDimensions.x, windowDimensions.y, title, NULL, NULL);

        if (window == NULL)
        {
            fprintf(stderr, "Error: Failed to create GLFW window\n");
            exit(1);
        }

        glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
        glfwMakeContextCurrent(window);

        glewInit();
        glEnable(GL_VERTEX_PROGRAM_POINT_SIZE);

        isInitialized = true;
    }

    void end()
    {
        if (!isInitialized)
        {
            fprintf(stderr, "Error: `end` called with uninitialized window\n");
            exit(1);
        }

        glfwTerminate();
        glfwDestroyWindow(window);
        isInitialized = false;
    }

}
