#ifndef SQUARE_H
#define SQUARE_H

#include <glm/glm.hpp>
#include "game.h"
#include "shape.h"

class Square : public Shape
{
public:

    int side;

    Square()
        : Shape(glm::ivec2(100, 100), glm::vec3(1.0, 1.0, 1.0))
    {}

    Square(glm::ivec2 position, int side, glm::vec3 colour)
        : Shape(position, colour)
        , side(side)
    { initialize(); }

protected:

    glm::vec2 dimensionsNorm;

    void initVertices() override
    {
        printf("Creating vertices...\n");
        positionNorm = (glm::vec2)position / (glm::vec2)Game::windowDimensions - 0.5f;
        dimensionsNorm = (float)side / (glm::vec2)Game::windowDimensions;
        vertices = {
            positionNorm.x,                    positionNorm.y,                     0.0f,
            positionNorm.x + dimensionsNorm.x, positionNorm.y,                     0.0f,
            positionNorm.x + dimensionsNorm.x, positionNorm.y + dimensionsNorm.y,  0.0f,
            positionNorm.x,                   positionNorm.y + dimensionsNorm.y, 0.0f,
        };
    }

    void initIndices() override
    {
        indices = {
            0, 1, 2,  // First triangle
            2, 3, 0   // Second triangle
        };
    }

};

#endif