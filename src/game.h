#ifndef GAME_H
#define GAME_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include <stdio.h>
#include <stdlib.h>

#include "shape.h"

inline void framebuffer_size_callback(GLFWwindow* window, int width, int height);

class Game
{
public:

    Game()
        : dimensions(800, 600)
        , title("float")
    {
        if (!glfwInit())
        {
            printf("Failed to initialize GLFW\n");
            exit(1);
        }

        window = glfwCreateWindow(dimensions.x, dimensions.y, title, NULL, NULL);
        if (!(window))
        {
            glfwTerminate();
            exit(1);
        }

        glfwSetWindowUserPointer(window, this);
        glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

        glfwMakeContextCurrent(window);
        glewInit();
        glEnable(GL_VERTEX_PROGRAM_POINT_SIZE);

        initGame();
    }

    ~Game()
    {
        glfwDestroyWindow(window);
        glfwTerminate();
    }

    void loop()
    {
        while (!glfwWindowShouldClose(window))
        {
            glClear(GL_COLOR_BUFFER_BIT);

            sq.perFrame(0.1);
            sq.draw();
            
            glfwSwapBuffers(window);
            glfwPollEvents();
        }
    }

    void setDimensions(int width, int height)
    {
        dimensions.x = width;
        dimensions.y = height;
    }

private:

    // Window
    GLFWwindow *window;
    char title[32];
    glm::ivec2 dimensions;

    // Sprites
    Shape sq;

    void initGame()
    {
        sq = Shape(glm::ivec2(10, 10), glm::ivec2(50, 50), glm::vec3(255, 0, 0), dimensions);
    }

};

inline void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    Game *game = static_cast<Game*>(glfwGetWindowUserPointer(window));
    if (game) game->setDimensions(width, height);
    glViewport(0, 0, width, height);
}

#endif