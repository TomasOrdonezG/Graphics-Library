#include "shape.h"

Shape::Shape() {}

Shape::Shape(glm::ivec2 position, glm::ivec2 dimensions, glm::vec3 colour, glm::ivec2 windowDimensions)
    : position(position)
    , dimensions(dimensions)
    , colour(colour)
{
    shader = Shader(vertexShaderSource, fragmentShaderSource);

    onUpdate(windowDimensions);
    unsigned int indices[] = {
        0, 1, 2,  // First triangle
        2, 3, 0   // Second triangle
    };

    // Buffer: Array stored in the GPU
    // Vertex: A point in 3D space, stores more attributes like color, texture coordinates, normal vector, etc
    // Vertex Buffer Object (VBO): Buffer of vertices
    // Vertex Array Object (VAO): Buffer of references to VBOs
    // Element Buffer Object (EBO): Stores indices that reference vertices stored in a VBO (helps saving memory by reusing vertices)
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    // Bind the Vertex Array Object first, then bind and set vertex buffer(s) and attribute pointer(s).
    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), vertices.data(), GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    // Position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
}
    
void Shape::perFrame(float dt)
{
    applyGravity();
    detectCollision();
}

void Shape::draw()
{
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices.data()), vertices.data()); // Update VBO with new positions

    glUseProgram(shader.ID);
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}

void Shape::onUpdate(glm::ivec2 windowDimensions)
{
    // Recalculate vertices
    positionNorm = (glm::vec2)position / (glm::vec2)windowDimensions - 0.5f;
    dimensionsNorm = (glm::vec2)dimensions / (glm::vec2)windowDimensions;
    vertices = {
        positionNorm.x,                    positionNorm.y,                     0.0f,
        positionNorm.x + dimensionsNorm.x, positionNorm.y,                     0.0f,
        positionNorm.x + dimensionsNorm.x, positionNorm.y + dimensionsNorm.y,  0.0f,
        positionNorm.x,                   positionNorm.y + dimensionsNorm.y, 0.0f,
    };
}

void Shape::applyGravity()
{

}

void Shape::detectCollision()
{

}
