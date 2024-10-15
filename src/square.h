#ifndef SQUARE_H
#define SQUARE_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include <stdio.h>

#include <vector>

#include "shader.h"

class Square
{
public:

    // Initializers
    Square();
    Square(glm::ivec2 position, glm::ivec2 dimensions, glm::vec3 colour, glm::ivec2 windowDimensions);
    
    // State handling
    void perFrame(float dt);
    void draw();
    void onUpdate(glm::ivec2 windowDimensions);

    // Update
    void applyGravity();
    void detectCollision();

    // Callback
    
private:

    // Primary attributes
    glm::ivec2 position;
    glm::ivec2 dimensions;
    glm::vec2 positionNorm;
    glm::vec2 dimensionsNorm;
    glm::vec3 colour;

    // OpenGL objects
    GLuint VBO, VAO, EBO;
    std::vector<float> vertices;

    // Shader attributes
    Shader shader;
    const char *vertexShaderSource = R"(
        #version 330 core
        layout(location = 0) in vec3 aPos;
        void main()
        {
            gl_Position = vec4(aPos, 1.0);
        }
    )";
    const char *fragmentShaderSource = R"(
        #version 330 core
        out vec4 FragColor;
        void main()
        {
            FragColor = vec4(0.0, 1.0, 0.0, 1.0);
        }
    )";

};

#endif
