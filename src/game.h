#ifndef WINDOW_H
#define WINDOW_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include <stdio.h>

#include <vector>

#include "shape.h"

namespace Game
{

    extern glm::ivec2 windowDimensions;
    extern GLFWwindow *window;
    extern bool isInitialized;
    extern std::vector<Shape*> shapes;

    void framebuffer_size_callback(GLFWwindow* window, int width, int height);

    void loop();
    void add(Shape *shape);
    void start(int w, int h, const char *title);
    void end();

}

#endif