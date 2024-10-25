#include <stdio.h>
#include <stdlib.h>
#include "game.h"
#include "shape.h"
#include "square.h"

void before()
{
    Game::add(new Square(glm::ivec2(100, 100), 50, glm::vec3(1.0, 0.0, 0.0)));
}

void perFrame()
{
    for (Shape *shape : Game::shapes)
    {
        shape->position.x += 1;
        shape->position.y += 1;
    }
}

void after()
{

}

int main(int argc, char **argv)
{
    Game::start(800, 600, "float");
    before();
    Game::loop(perFrame);
    after();
    Game::end();
    return 0;
}
