#ifndef SHAPE_H
#define SHAPE_H

#include <glm/glm.hpp>
#include <vector>
#include "shader.h"

class Shape
{
public:

    glm::ivec2 position;
    glm::vec3 colour;

    Shape(glm::ivec2 position, glm::vec3 colour)
        : position(position)
        , colour(colour)
        , shader(vertexShaderSource, fragmentShaderSource)
    {}

    void draw()
    {
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices.data()), vertices.data()); // Update VBO with new positions
        glUseProgram(shader.ID);
        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
    }

    virtual void perFrame(float dt)
    {

    }

private:

    // Shaders
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
    Shader shader;

    void createBuffers()
    {
        // Create VAO, VBO, EBO
        glGenVertexArrays(1, &VAO);
        glGenBuffers(1, &VBO);
        glGenBuffers(1, &EBO);

        // Bind the Vertex Array Object first, then bind and set vertex buffer(s) and attribute pointer(s).
        glBindVertexArray(VAO);

        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), vertices.data(), GL_STATIC_DRAW);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size()*sizeof(int), indices.data(), GL_STATIC_DRAW);

        // Position attribute
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);
    }

protected:

    // Vertices
    GLuint VBO, VAO, EBO;
    std::vector<int> indices;
    std::vector<float> vertices;

    glm::vec2 positionNorm;

    void initialize()
    {
        initVertices();
        initIndices();
        createBuffers();
    }

    virtual void initVertices() = 0;
    virtual void initIndices() = 0;

};

#endif